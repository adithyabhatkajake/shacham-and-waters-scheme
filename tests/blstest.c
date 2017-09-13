#include <pbc/pbc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bls.h"

/**
 *  Program to verify BLS Signatures
 */

int main(int argc, char const *argv[])
{
    /* code */
    pairing_t pairing;
    char *param = 
    "type a1\n"
    "p 48512875896303752499712277254589628516419352188294521198189567511009073158115045361294839347099315898960045398524682007334164928531594799149100548036445760110913157420655690361891290858441360807158247259460501343449199712532828063940008683740048500980441989713739689655610578458388126934242630557397618776539259\n"
    "n 36203638728584889925158415861634051131656232976339194924022065306723188923966451762160327870969638730567198058600508960697138006366861790409776528385407283664860565239295291314844246909284597617282274074224254733917313218308080644731349763985110821627195514711746037056425804819692632040479575042834043863089\n"
    "l 1340";

    pairing_init_set_buf(pairing, param, strlen(param));

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
