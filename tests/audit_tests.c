#define TARGET "Audit Tests"

#include <stdio.h>

#include <handlefile.h>
#include <logging.h>
#include <audit.h>
#include <test.h>
#include <bls.h>

void startup()
{
    INIT_TEST();
    log_level = LOG_QUIET;
}

int main(int argc, char *argv[])
{
    startup();
    
    struct file_t *f = get_file_blocks(argv[1]);

    tag_param_t params;
    element_t g,pubkey;

    pairing_init_set_buf(params.pairing, a1_param, strlen(a1_param));

    element_init_Zr(params.secret_x,params.pairing);
    element_init_G1(params.alpha,params.pairing);
    element_init_G1(pubkey,params.pairing);
    element_init_G1(g,params.pairing);

    element_random(params.secret_x);
    element_random(params.alpha);
    element_random(g);

    element_pow_zn(pubkey,g,params.secret_x);

    set_tags(f,&params);

    struct query_t query_obj = {
        .query_length = 1,
    };
    query_obj.pairing   = params.pairing;
    query_obj.indices   = (uint32_t*)malloc(sizeof(uint32_t) * query_obj.query_length);
    query_obj.nu        = (struct element_s*)malloc(sizeof(struct element_s) * query_obj.query_length);

    query_obj.indices[0] = 0;
    query_obj.indices[1] = 1;

    for(int i=0;i<query_obj.query_length;i++) {
        element_init_Zr(query_obj.nu+i,params.pairing);
        element_random(query_obj.nu+i);
    }
    
    struct query_response_t* response = query(f,query_obj);
    element_printf("Sigma:%B\nMu:%B\n",response->sigma,response->mu);

    int result = verify_storage(f,*response,query_obj,g,params.alpha,pubkey);
    printf("Response: %d\n",result);

    EXIT_TEST();

    return 0;
}