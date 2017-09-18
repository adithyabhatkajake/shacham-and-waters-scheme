#include <stdio.h>
#include <stdlib.h>

#include <handlefile.h>
#include <logging.h>
#include <bls.h>

static inline char* hexstring(unsigned char* bytes, int len)
{
    char* buffer    = malloc(sizeof(char)*((2*len)+1));
    char* temp      = buffer;
    for(int i=0;i<len;i++) {
        sprintf(temp,"%02x",bytes[i]);
        temp += 2;
    }
    *temp = '\0';
    return buffer;
}

int main(int argc, char* argv[])
{
    /* code */
    if(argc  !=  2) {
        fprintf(stderr,"Incorrect usage: %s <filename>\n",argv[0]);
        exit(1);
    }

    pairing_t* pairing = init_pairing();

    element_t g, h;
    element_t public_key, secret_key;
    element_t sig;

    element_init_Zr(g, *pairing);

    log_level = LOG_TRACE;

    struct file_t* file = get_file_blocks(argv[1]);
    for(int i=0;i<file->nr_blocks;i++) {
        struct file_piece_t* fpiece = file->pieces+i;
        char *data = (char*)fpiece->data;
        mpz_t integer;
        mpz_init(integer);
        char* string = hexstring(data,fpiece->blk_size);
        int k = mpz_set_str(integer,string,16);
        Log(LOG_TRACE,"%s\n%d",string,k);
        element_set_mpz(g,integer);
        element_printf("%B\n",g);
        free(string);
    }
    free(pairing);
    free(file);

    return 0;
}
