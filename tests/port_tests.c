#include <port.h>

#define TARGET "Import/Export Test"

#include <test.h>

int main()
{
    log_level = LOG_TRACE;
    struct keypair_t* kpair;
    char* pvt_filename = "private-key.sig";
    char* pub_filename = "public-key.sig";
    
    kpair = generate_key_pair();
    export_pvt_key(kpair->pvt_key,pvt_filename);
    struct private_key_t* pkey = import_pvt_key(pvt_filename);
    export_public_key(kpair->pub_key,pub_filename);
    struct public_key_t* pubkey = import_public_key(pub_filename);

    // element_printf("PrivateKey\n%B\n%B\n%B\n",kpair->pvt_key->alpha,kpair->pvt_key->g,kpair->pvt_key->x);
    // element_printf("Public Key\n%B\n%B\n%B\n",kpair->pub_key->alpha,kpair->pub_key->g,kpair->pub_key->v);
    // element_printf("%B\n%B\n",pkey->x,kpair->pvt_key->x);
    // element_printf("%B\n%B\n",pubkey->v,kpair->pub_key->v);

    return 0;
}