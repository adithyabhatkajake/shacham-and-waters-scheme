#include <pbc/pbc.h>
#include <stdio.h>
#include <stdlib.h>

/**
 *  Program to verify BLS Signatures
 */

#define SIGN_OK 1
#define SIGN_FAIL 0

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

int main(int argc, char const *argv[])
{
    /* code */
    pairing_t pairing;
    char param[1024];
    size_t count = fread(param, 1, 1024, stdin);
    if (!count) {
        fprintf(stderr,"Error while reading the file");
        exit(1);
    }

    pairing_init_set_buf(pairing, param, count);

    element_t g, h;
    element_t public_key, secret_key;
    element_t sig;

    element_init_G2(g, pairing);
    element_init_G2(public_key, pairing);
    element_init_G1(h, pairing);
    element_init_G1(sig, pairing);

    element_init_Zr(secret_key, pairing);

    element_random(g);
    element_random(secret_key);

    element_pow_zn(public_key, g, secret_key);

    // MD5 sum of "hello"
    element_from_hash(h, (void*)"b1946ac92492d2347c6235b4d2611184", 32);
    
    element_pow_zn(sig, h, secret_key);

    printf("Signature Check:%s\n", 
    verify_signature(pairing,h,g,sig,public_key)==SIGN_OK?"Pass":"Failed");
    return 0;
}
