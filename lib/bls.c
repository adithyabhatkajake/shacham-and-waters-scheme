#include <pbc/pbc.h>
#include <string.h>

#include <sha256.h>
#include <bls.h>
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

struct element_s* bls_hash(void* data, int length, pairing_t pairing)
{
    struct element_s* new_elem = (struct element_s*)malloc(sizeof(element_t));
    element_init_G1(new_elem, pairing);
    element_from_hash(new_elem,data,length);
    return new_elem;
}

struct element_s* bls_hash_int(uint32_t value,pairing_t pairing)
{
    struct element_s* ret;
    char int_str[11]; 
    /*
     * 11 because 2^33 has 10 digits.
     * 1 extra for the null termination.
     */
    
    int len = sprintf(int_str,"%llu",value);
    ret = bls_hash((void*)int_str,len,pairing);
    return ret; 
    
}