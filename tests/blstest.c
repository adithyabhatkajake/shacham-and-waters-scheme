#include <pbc/pbc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lgging.h>

#include "bls.h"

/**
 *  Program to verify BLS Signatures
 */

int main(int argc, char const *argv[])
{
    /* code */
    pairing_t* pairing = init_pairing();

    element_t g, h;
    element_t public_key, secret_key;
    element_t sig;

    element_init_G2(g, *pairing);
    element_init_G2(public_key, *pairing);
    element_init_G1(h, *pairing);
    element_init_G1(sig, *pairing);

    element_init_Zr(secret_key, *pairing);

    element_random(g);
    element_random(secret_key);

    element_pow_zn(public_key, g, secret_key);

    // MD5 sum of "hello"
    element_from_hash(h, (void*)"b1946ac92492d2347c6235b4d2611184", 32);

    element_pow_zn(sig, h, secret_key);

    printf("Signature Check:%s\n", 
    verify_signature(*pairing,h,g,sig,public_key)==SIGN_OK?"Pass":"Failed");
    return 0;
}
