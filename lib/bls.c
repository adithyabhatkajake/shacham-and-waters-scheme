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

element_t* bls_hash(void* data, int length, pairing_t pairing)
{
    element_t* new_elem = malloc(sizeof(element_t));
    element_init_G1(*new_elem, pairing);
    element_from_hash(*new_elem,data,length);
    return new_elem;
}