#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include <handlefile.h>
#include <rslib.h>

static FILE* open_file(const char* filename)
{
    FILE *file = fopen(filename, "r");
    return file;
}

static void die(const char* error_msg)
{
    fprintf(stderr,"[Error]:%s\n",error_msg);
    exit(1);
}

static size_t get_file_size(FILE *file)
{
    long initial_pos = ftell(file);
    size_t filesize = -1;
    
    fseek(file,0,2);
    filesize = ftell(file);

    // Restoring file cursor to wherever it was
    fseek(file,initial_pos, SEEK_SET);

    return filesize;
}

static unsigned long long get_nr_blocks(size_t filesize)
{
    unsigned long long nr_blocks = (filesize/DEFAULT_BLK_SIZE)+1;
    if(filesize % DEFAULT_BLK_SIZE == 0)
        nr_blocks--;
    return nr_blocks;    
}

struct file_t* get_file_blocks(char *filename)
{
    FILE *file_handle = open_file(filename);

    if(!file_handle)
        die("Unable to open the file");
    
    size_t count = 0;
    char *buffer;
    struct file_t *file_info;

    buffer = (char *)malloc(DEFAULT_BLK_SIZE);
    if(!buffer)
        die("Unable to allocate buffer memory for reading the file");

    size_t filesize = get_file_size(file_handle);
    
    file_info = (struct file_t*)malloc(sizeof(struct file_t));
    file_info->nr_blocks = get_nr_blocks(filesize);

    file_info->pieces = (struct file_piece_t*)
        malloc(sizeof(struct file_piece_t)*
                (file_info->nr_blocks));
    
    file_info->nr_blocks = 0;

    while((count = fread(buffer, 1, DEFAULT_BLK_SIZE, file_handle)) != 0) {
        char *temp_data;
        temp_data = (char*)malloc(DEFAULT_BLK_SIZE);
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
    FILE* file_handle = fopen(filename, "wb");

    if(!file_handle)
        die("Unable to open the file");

    size_t count = 0;

    for(int i=0;i<file->nr_blocks;i++) {
        struct file_piece_t *fpiece;
        fpiece = file->pieces+i;
        count = fwrite((char*)fpiece->data,1,fpiece->blk_size,file_handle );
        
        if(count != fpiece->blk_size)
        die("Unable to write to file");
        
        count = fwrite(fpiece->parity,2,6,file_handle);
        
        if(count != 6)
            die("Unable to write to file");
    }

    fflush(file_handle);
    fclose(file_handle);
}

void generate_parity(struct file_t* f)
{
    struct rs_control *rs_decoder;
    rs_decoder = init_rs (10, 0x409, 0, 1, 6);

    for(int i=0;i<f->nr_blocks;i++) {
        struct file_piece_t *fp = f->pieces+i;
        
        for(int j=0;j<fp->blk_size;j++) {
            unsigned char *byte = fp->data+j;
        }

        char *parity_data;
        uint16_t *par = malloc(sizeof(uint16_t)*6);
        parity_data = (char*)par;
        memset(par, 0, sizeof(par));
    
        encode_rs8(rs_decoder, (unsigned char*)fp->data, fp->blk_size, par, 0);

        fp->parity = par;
    }
}

struct file_t* recover_file(const char* filename)
{
    FILE* file_handle = open_file(filename);

    if(!file_handle)
        die("Unable to open the file");

    size_t count = 0;

    size_t file_size = get_file_size(file_handle);

    unsigned long nr_blocks = (int)file_size/(DEFAULT_BLK_SIZE+12);
    if(file_size % (DEFAULT_BLK_SIZE+12) != 0) {
        nr_blocks++;
    }

    struct file_t *file = (struct file_t*)malloc(sizeof(struct file_t));
    file->nr_blocks = nr_blocks;
    file->pieces = (struct file_piece_t*)malloc(nr_blocks*sizeof(struct file_piece_t));

    for(int i=0;i<nr_blocks; i++) {
        
        struct file_piece_t *fpiece = &(file->pieces[i]);
        uint16_t* parity;
        parity = (uint16_t*)malloc(sizeof(uint16_t)*6);
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
        count = fread(fpiece->data,1,fpiece->blk_size,file_handle);
        count = fread(fpiece->parity, 2,6,file_handle);        
    }

    fclose(file_handle);
    return file;
}