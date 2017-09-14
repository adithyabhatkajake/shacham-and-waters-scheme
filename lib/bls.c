#include <pbc/pbc.h>
#include <bls.h>
#include <string.h>

//element_t g,h,secret_key, public_key;

int verify_signature(pairing_t pairing,
    element_t group1, element_t group2,
    element_t signature,
    element_t public_key)
{
    element_t temp1, temp2;

    element_init_GT(temp1, pairing);
    element_init_GT(temp2, pairing);

    pairing_apply(temp1, signature, group2, pairing);
    pairing_apply(temp2, group1, public_key, pairing);
    return element_cmp(temp1, temp2)?SIGN_FAIL:SIGN_OK;
}

struct bls_keypair* bls_keypair_gen(void)
{
    struct bls_keypair* keypair = malloc(sizeof(struct bls_keypair));
    
    return keypair;
}