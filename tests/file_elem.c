#include <stdio.h>
#include <stdlib.h>

#define TARGET "File element in Zp Tests"

#include <handlefile.h>
#include <logging.h>
#include <test.h>
#include <bls.h>

int main(int argc, char* argv[])
{
    /* code */
    INIT_TEST();

    log_level = LOG_TRACE;

    if(argc  !=  2) {
        fprintf(stderr,"Incorrect usage: %s <filename>\n",argv[0]);
        exit(1);
    }

    Log(LOG_TRACE,"%s:[%d]",__FUNCTION__,argc);

    pairing_t* pairing = malloc(sizeof(pairing_t));
    INIT_PAIRING(pairing);

    element_t g, h;
    element_t public_key, secret_key;
    element_t sig;

    element_init_Zr(g, *pairing);

    /*
     *  log_level = LOG_TRACE;
     */
    Log(LOG_TRACE,"%s",argv[1]);
    struct file_t* file = get_file_blocks(argv[1]);
    for(int i=0;i<file->nr_blocks;i++) {
        struct file_piece_t* fpiece = file->pieces+i;
        char *data = (char*)fpiece->data;
        mpz_t integer;
        mpz_init(integer);
        char* string = hexstring(data,fpiece->blk_size);
        int k = mpz_set_str(integer,string,16);
        if(k) {
            Log(LOG_ERROR,"Could not set long integer from file data");
            exit(1);
        }
        Log(LOG_TRACE,"Data[%s]",string,k);
        element_set_mpz(g,integer);
        element_printf("Element[%B]\n",g);
        free(string);
    }

    free(pairing);
    free(file);

    EXIT_TEST();

    return 0;
}
