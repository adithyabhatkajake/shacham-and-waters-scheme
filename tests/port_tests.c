#define TARGET "Import/Export Test"

#include <handlefile.h>
#include <audit.h>
#include <port.h>
#include <test.h>

int main(int argc, char* argv[])
{
    log_level = LOG_TRACE;
    struct keypair_t* kpair;
    struct file_t *f = get_file_blocks(argv[1]);
    char* pvt_filename = "private-key.sig";
    char* pub_filename = "public-key.sig";
    char* file_test    = "file.dat";

    tag_param_t params;

    kpair = generate_key_pair();

    params.pairing = kpair->pvt_key->pairing;
    params.alpha = kpair->pvt_key->alpha;
    params.secret_x = kpair->pvt_key->x;

    set_tags(f,&params);

    export_pvt_key(kpair->pvt_key,pvt_filename);
    struct private_key_t* pkey = import_pvt_key(pvt_filename);
    export_public_key(kpair->pub_key,pub_filename);
    struct public_key_t* pubkey = import_public_key(pub_filename);
    export_file(f,file_test);
    struct file_t* f2 = import_file(file_test);

    element_printf("PrivateKey\n%B\n%B\n%B\n",kpair->pvt_key->alpha,kpair->pvt_key->g,kpair->pvt_key->x);
    element_printf("Public Key\n%B\n%B\n%B\n",kpair->pub_key->alpha,kpair->pub_key->g,kpair->pub_key->v);
    element_printf("%B\n%B\n",pkey->x,kpair->pvt_key->x);
    element_printf("%B\n%B\n",pubkey->v,kpair->pub_key->v);

    free_keypair(kpair);
    free(kpair);

    return 0;
}