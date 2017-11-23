#define TARGET "Audit Tests"

#include <stdio.h>

#include <handlefile.h>
#include <logging.h>
#include <audit.h>
#include <port.h>
#include <test.h>
#include <bls.h>

void startup()
{
    INIT_TEST();
    log_level = LOG_TRACE;
}

int main(int argc, char *argv[])
{
    startup();
    
    struct file_t *f = get_file_blocks(argv[1]);

    tag_param_t params;


    struct keypair_t* kpair;
    Log(LOG_TRACE,"Line %d",__LINE__);
    kpair = generate_key_pair();
    struct public_key_t *pubkey = kpair->pub_key;
    struct private_key_t *pkey = kpair->pvt_key;
    //element_t g,pubkey;

    pairing_init_set_buf(kpair->pub_key->pairing, a1_param, strlen(a1_param));

    // element_init_Zr(pkey->,kpair->pub_key->pairing);
    // element_init_G1(params.alpha, kpair->pub_key->pairing);
    // element_init_G1(pubkey, kpair->pub_key->pairing);
    // element_init_G1(g, kpair->pub_key->pairing);

    // element_random(params.secret_x);
    // element_random(params.alpha);
    // element_random(g);

    // element_pow_zn(pubkey,g,params.secret_x);

    params.pairing = pkey->pairing;
    params.alpha = pkey->alpha;
    params.secret_x = pkey->x;

    set_tags(f,&params);


    struct query_t query_obj = {
        .query_length = 1,
    };
    query_obj.pairing   = pkey->pairing;
    query_obj.indices   = (uint32_t*)malloc(sizeof(uint32_t) * query_obj.query_length);
    query_obj.nu        = (struct element_s*)malloc(sizeof(struct element_s) * query_obj.query_length);

    query_obj.indices[0] = 0;
    query_obj.indices[1] = 1;
    query_obj.indices[2] = 2;

    for(int i=0;i<query_obj.query_length;i++) {
        element_init_Zr(query_obj.nu+i,pkey->pairing);
        element_random(query_obj.nu+i);
    }
    
    struct query_response_t* response = query(f,query_obj);
    //Log(LOG_TRACE,"Sigma:%B\nMu:%B\n",response->sigma,response->mu);

    int result = verify_storage(f,*response,query_obj,pkey->g,params.alpha,pubkey->v);
    Log(LOG_TRACE,"Response: %d\n",result);

    EXIT_TEST();

    return 0;
}