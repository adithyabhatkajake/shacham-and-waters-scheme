#include <stdlib.h>

#define TARGET "File block IO Tests"

#include <handlefile.h>
#include <logging.h>
#include <test.h>

static void usage(char *scriptname)
{
    fprintf(stderr, "Usage: <%s> <Filename>",scriptname);
}

int main(int argc, char *argv[])
{
    INIT_TEST();

    if(argc != 2) {
        fprintf(stderr, "[Error][1]: Incorrect Number of arguments\n");
        usage(argv[0]);
        exit(1);
    }
    struct file_t *f = get_file_blocks(argv[1]);
    for(int i=0;i<f->nr_blocks;i++) {
        struct file_piece_t fp = f->pieces[i];
        printf("Block:%d:%llu\n",i,fp.blk_size);
        for(int j=0;j<fp.blk_size;j++) {
            unsigned char *byte = fp.data+j;
            printf("%02x",*byte);
        }
        printf("\n");
    }
    free(f->pieces);
    free(f);
    
    EXIT_TEST();

    return 0;
}