#include <stdio.h>

#include <logging.h>
#include <bls.h>
#include <audit.h>
#include <handlefile.h>

void main(int argc, char *argv[])
{
    log_level = LOG_DEBUG;
    struct file_t *f = get_file_blocks(argv[1]);
    //pairing_t* pairing = init_pairing();

    
    tag_param_t params = {
        .index = 1,
        .fpiece = f->pieces+1,
    };
    
    pairing_init_set_buf(params.pairing, a1_param, strlen(a1_param));

    element_init_G1(params.alpha,params.pairing);
    element_init_Zr(params.secret_x,params.pairing);

    element_random(params.alpha);
    element_random(params.secret_x);


    struct tag_t* tag = generate_tag(&params);
    element_printf("Sigma:%B\nTag index: %d\n",tag->sigma,tag->index);

}