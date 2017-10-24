#define TARGET "BLS Tests"

#include <pbc/pbc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <logging.h>
#include <test.h>
#include <bls.h>

/**
 *  Program to verify BLS Signatures
 */

int main(int argc, char const *argv[])
{
    /* code */
    INIT_TEST();
    log_level = LOG_DEBUG;

    pairing_t pairing;
    INIT_PAIRING(&pairing);

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
    printf("Pairing is symmetric?:%d\n",pairing_is_symmetric(pairing));

    element_pow_zn(sig, h, secret_key);

    element_printf("g is %B\n",g);
    element_printf("h is %B\n",h);
    element_printf("Public Key is %B\n",public_key);
    element_printf("Private Key is %B\n",secret_key);
    element_printf("Signature is %B\n",sig);

    printf("Signature Check:%s\n", 
    verify_signature(pairing,h,g,sig,public_key)==SIGN_OK?"Pass":"Failed");

    EXIT_TEST();
    return 0;
}
