#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <logging.h>

#include <handlefile.h>
#include <rslib.h>

static FILE* open_file(const char* filename)
{
    if(filename == NULL) {
        Log(LOG_ERROR,"Null Filename passed to open_file");
        return NULL;
    }
    
    FILE *file = fopen(filename, "r");
    
    if(!file)
        Log(LOG_ERROR,"Unable to open file: %s",filename);

    return file;
}

static size_t get_file_size(FILE *file)
{
    if(!file) {
        Log(LOG_ERROR,"Invalid(NULL) File pointer passed");
        return 0;
    }

    long initial_pos = ftell(file);
    size_t filesize = -1;
    
    fseek(file,0,2);
    filesize = ftell(file);

    // Restoring file cursor to wherever it was
    fseek(file,initial_pos, SEEK_SET);

    if(!filesize)
        Log(LOG_WARNING,"Filesize is 0");

    return filesize;
}

static unsigned long long get_nr_blocks(size_t filesize)
{
    if(!filesize)
        Log(LOG_WARNING,"Zero Filesize passed");
    
    unsigned long long nr_blocks;

    nr_blocks = (filesize/DEFAULT_BLK_SIZE)+1;
    if(filesize % DEFAULT_BLK_SIZE == 0)
        nr_blocks--;

    return nr_blocks;    
}

struct file_t* get_file_blocks(char *filename)
{
    if(!filename) {
        Log(LOG_ERROR,"Invalid Filename passed");
        return NULL;
    }

    FILE *file_handle;
    file_handle = open_file(filename);

    if(!file_handle) {
        Log(LOG_ERROR,"Unable to open the file(%s)",filename);
        return NULL;
    }
    
    size_t          count = 0;
    char*           buffer;
    struct file_t*  file_info;

    buffer = (char*)malloc(DEFAULT_BLK_SIZE);

    if(!buffer) {
        Log(LOG_ERROR,"Unable to allocate buffer memory for reading the file");
        fclose(file_handle);
        return NULL;
    }
    
    size_t filesize = get_file_size(file_handle);
    
    if(!filesize) {
        Log(LOG_WARNING,"Filesize of %s is zero");
    }
    
    file_info = (struct file_t*)malloc(sizeof(struct file_t));

    if(!file_info) {
        Log(LOG_ERROR,"Unable to allocate memory for file_t");
        free(buffer);
        fclose(file_handle);
        return NULL;
    }

    file_info->nr_blocks = get_nr_blocks(filesize);
    if(!(file_info->nr_blocks)) {
        Log(LOG_WARNING,"Number of blocks are zero");
    }

    file_info->pieces = (struct file_piece_t*)
        malloc(sizeof(struct file_piece_t)*
                (file_info->nr_blocks));
    
    if(!(file_info->pieces)) {
        Log(LOG_ERROR,"Unable to allocate memory for file_piece_t");
        free(buffer);
        free(file_info);
        fclose(file_handle);
        return NULL;
    }
    
    file_info->nr_blocks = 0;

    while((count = fread(buffer, 1, DEFAULT_BLK_SIZE, file_handle)) != 0) {
        char *temp_data;
        temp_data = (char*)malloc(DEFAULT_BLK_SIZE);

        if(!temp_data) {
            Log(LOG_ERROR,"Unable to allocate memory for block buffer");
            free(buffer);
            for(int i=0;i<file_info->nr_blocks;i++)
                free(file_info->pieces+i);
            free(file_info);
            fclose(file_handle);
            return NULL;
        }

        memcpy(temp_data,buffer,count);
        struct file_piece_t *fpiece = file_info->pieces + 
                                        file_info->nr_blocks;
        fpiece->data = (void*)temp_data;
        fpiece->blk_size = count;
        file_info->nr_blocks++;
    }
    
    // Handle out of memory in the middle

    free(buffer);
    return file_info;
}

void write_file(struct file_t* file, const char* filename)
{
    if(!file || !filename) {
        Log(LOG_ERROR,"Invalid Null parameters passed to write_file");
        return;
    }

    FILE* file_handle = fopen(filename, "wb");

    if(!file_handle) {
        Log(LOG_ERROR,"Unable to open the file(%s) for writing",filename);
        return;
    }

    size_t count = 0;

    for(int i=0;i<file->nr_blocks;i++) {
        struct file_piece_t *fpiece;
        fpiece = file->pieces+i;
        count = fwrite((char*)fpiece->data,1,fpiece->blk_size,file_handle );
        
        if(count != fpiece->blk_size)
            Log(LOG_WARNING,"Unable to fully write to file[Data]");
        
        count = fwrite(fpiece->parity,2,6,file_handle);
        
        if(count != 6)
            Log(LOG_WARNING,"Unable to fully write to file[Parity]");
    }

    fflush(file_handle);
    fclose(file_handle);
}

void generate_parity(struct file_t* f)
{
    if(!f || !(f->pieces)) {
        Log(LOG_ERROR,"Invalid(Null) parameter(s) passed to generate parity");
        return;
    }

    struct rs_control *rs_decoder = NULL;
    rs_decoder = init_rs (10, 0x409, 0, 1, 6);

    if(!rs_decoder) {
        Log(LOG_ERROR,"Unable to initialize the Reed Solomon Engine");
        return;
    }

    for(int i=0;i<f->nr_blocks;i++) {
        struct file_piece_t *fp = f->pieces+i;
        
        if(!(fp->data)) {
            Log(LOG_ERROR,"fpiece(%d)-data is null",i+1);
            for(int j=0;j<i;j++) {
                struct file_piece_t *piece = f->pieces+j;
                free(piece->parity);
            }
            return;
        }

        char*       parity_data;
        uint16_t*   par;

        par         = malloc(sizeof(uint16_t)*6);

        if(!par) {
            Log(LOG_ERROR,"Unable to allocate memory to parity buffers");
            for(int j=0;j<i;j++) {
                struct file_piece_t *piece = f->pieces+j;
                free(piece->parity);
            }
            return;
        }

        parity_data = (char*)par;

        memset(par, 0, sizeof(par));
        encode_rs8(rs_decoder, (unsigned char*)fp->data, fp->blk_size, par, 0);

        fp->parity = par;
    }
}

struct file_t* recover_file(const char* filename)
{
    if(!filename) {
        Log(LOG_ERROR,"Invalid(Null) filename passed to recover file");
        return NULL;
    }

    FILE* file_handle = open_file(filename);

    if(!file_handle) {
        Log(LOG_ERROR,"Unable to open the file(%s)",filename);
        return NULL;
    }

    size_t count            = 0;
    size_t file_size        = get_file_size(file_handle);
    
    if(file_size == 0)
        Log(LOG_WARNING,"Filesize of (%s) is zero",filename);
    
    unsigned long nr_blocks = (int)file_size/(DEFAULT_BLK_SIZE+12);

    if(file_size % (DEFAULT_BLK_SIZE+12) != 0) {
        nr_blocks++;
    }

    struct file_t *file = (struct file_t*)malloc(sizeof(struct file_t));

    if(!file) {
        Log(LOG_WARNING,"Unable to allocate memory to file_t");
        return NULL;
    }

    file->nr_blocks = nr_blocks;
    file->pieces    = (struct file_piece_t*)
                        malloc(nr_blocks * sizeof(struct file_piece_t));

    if(!(file->pieces)) {
        Log(LOG_WARNING,"Unable to allocate memory to file_piece_t");
        free(file);
        return NULL;
    }

    for(int i=0;i<nr_blocks; i++) {
        
        struct file_piece_t* fpiece = &(file->pieces[i]);
        uint16_t*            parity;
        parity = (uint16_t*)malloc(sizeof(uint16_t)*6);

        if(!parity) {
            Log(LOG_ERROR,"Unable to allocate memory to parity buffers");
            for(int j=0;j<i;j++) {
                struct file_piece_t* piece = &(file->pieces[i]);
                free(piece->parity);
                free(piece->data);
            }
            free(file->pieces);
            free(file);
            return NULL;
        }

        fpiece->parity = parity;
        if(i+1 == nr_blocks) {
            //Last block case
            // Compute remaining blocks
            size_t remaining = (file_size%(DEFAULT_BLK_SIZE+12));
            // 13...524 In theory
            remaining -= 12;
            fpiece->blk_size = remaining;
        }
        else {
            fpiece->blk_size = DEFAULT_BLK_SIZE;
        }
        fpiece->data = (void*)malloc(sizeof(char)*fpiece->blk_size);
        if(!(fpiece->data)) {
            Log(LOG_ERROR,"Unable to allocate memory to data buffer");
            fpiece->parity;
            for(int j=0;j<i;j++) {
                struct file_piece_t* piece = &(file->pieces[i]);
                free(piece->parity);
                free(piece->data);
            }
            free(file->pieces);
            free(file);
            return NULL;
        }
        count = fread(fpiece->data,1,fpiece->blk_size,file_handle);
        if(count != fpiece->blk_size) {
            Log(LOG_ERROR,"Unable to read data");
            for(int j=0;j<=i;j++) {
                struct file_piece_t* piece = &(file->pieces[i]);
                free(piece->parity);
                free(piece->data);
            }
            free(file->pieces);
            free(file);
            return NULL;
        }
        count = fread(fpiece->parity, 2,6,file_handle);   
        if(count!=6) {
            Log(LOG_ERROR,"Unable to read parity data");
            for(int j=0;j<=i;j++) {
                struct file_piece_t* piece = &(file->pieces[i]);
                free(piece->parity);
                free(piece->data);
            }
            free(file->pieces);
            free(file);
            return NULL;
        }
    }

    fclose(file_handle);
    return file;
}