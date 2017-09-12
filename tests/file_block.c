#include "handlefile.h"
#include <stdlib.h>
void main(int argc, char *argv[])
{
    if(argc != 2) {
        fprintf(stderr, "[Error][1]: Incorrect Number of arguments\n");
        exit(1);
    }
    struct file_t *f = get_file_blocks(argv[1]);
    free(f);
}