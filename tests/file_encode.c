#include <stdlib.h>
#include <string.h>

#define TARGET "File encoding Tests"

#include <handlefile.h>
#include <logging.h>
#include <rslib.h>
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

    struct rs_control *rs_decoder;
    rs_decoder = init_rs (10, 0x409, 0, 1, 6);
    
    struct file_t *f = get_file_blocks(argv[1]);
    for(int i=0;i<f->nr_blocks;i++) {
        struct file_piece_t fp = f->pieces[i];
        printf("Block:%d\n",i);
        for(int j=0;j<fp.blk_size;j++) {
            unsigned char *byte = fp.data+j;
            printf("%02x",*byte);
        }
        printf("\n");

        char *parity_data;
        uint16_t *par = malloc(sizeof(uint16_t)*6);
        parity_data = (char*)par;
        memset(par, 0, sizeof(par));
    
        encode_rs8(rs_decoder, (unsigned char*)fp.data, fp.blk_size, par, 0);
    
        printf("Parity bits:\n");
        for (int i = 0; i < 12; i++)
            printf("%02x", (unsigned char)parity_data[i]);
        printf("\n");

        free(par);
    }

    //free(f->pieces);
    free(f);

    EXIT_TEST();

    return 0;
}