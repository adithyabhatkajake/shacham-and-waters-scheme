#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "handlefile.h"

#define DEFAULT_BLK_SIZE 1024

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

    printf("%llu bytes in %s\n",get_file_size(file_handle),filename);
    file_info = (struct file_t*)malloc(sizeof(struct file_t));
    while((count = fread(buffer, 1, DEFAULT_BLK_SIZE, file_handle)) != 0) {
        file_info->blk_size += count;
    }
    printf("%llu bytes in %s\n",file_info->blk_size,filename);
    
    free(buffer);
    return file_info;
}
