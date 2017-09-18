#include <stdio.h>
#include <gmp.h>
#include <pbc/pbc.h>

#include <sha256.h>
#include <audit.h>
#include <bls.h>
#include <handlefile.h>
#include <print-utils.h>
#include <logging.h>

struct tag_t* generate_tag(tag_param_t* tag_params)
{
    struct file_piece_t*    fpiece      = tag_params->fpiece;
    int                     index       = tag_params->index;

    struct tag_t* tag;
    element_t* new_elem,f_i;
    char* string;
    mpz_t integer;
    
    tag             = malloc(sizeof(struct tag_t));
    tag->index      = tag_params->index;
    
    string          = hexstring((unsigned char*)(fpiece->data),(int)fpiece->blk_size);
    new_elem        = bls_hash(fpiece->data,fpiece->blk_size,tag_params->pairing); // new_elem = H(i)
    
    //Log(LOG_TRACE,"string:%s",string);
    element_init_G1(tag->sigma,tag_params->pairing);
    element_init_Zr(f_i,tag_params->pairing);
    mpz_init_set_str(integer,string,16);
    //gmp_printf("integer,%Zx\n",integer);
    element_set_mpz(f_i,integer);
    element_pow_zn(tag_params->alpha,tag_params->alpha,f_i); // alpha = alpha^F[i]
    element_mul(*new_elem,*new_elem,tag_params->alpha); // new_elem = H(i).(alpha^F[i])
        
    element_pow_zn(*new_elem,*new_elem,tag_params->secret_x); //new_elem = (H(i).(alpha^F[i]))^x

    element_init_same_as(tag->sigma,*new_elem);
    element_set(tag->sigma,*new_elem);

    return tag;
}