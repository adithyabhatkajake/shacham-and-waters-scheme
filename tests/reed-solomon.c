#include <stdio.h>
#include <rslib.h>
#include <string.h>

#define TARGET "Reed Solomon Tests"

#include <test.h>

static struct rs_control *rs_decoder;

int main() 
{

    INIT_TEST();

    rs_decoder = init_rs (10, 0x409, 0, 1, 6);

    int blocks = 32;
    unsigned char data8[blocks];
    char *parity_data;

    uint16_t par[6];
    parity_data = (char*)par;

    memset(par, 0, sizeof(par));

    printf("Initial Values\n");

    print_hex(data8, 32);    
    print_hex(parity_data,12);
    
    encode_rs8 (rs_decoder, data8, blocks, par, 0);
    
    printf("After encoding\n");

    print_hex(data8, 32);    
    print_hex(parity_data,12);

    /*
     * Create errors here
     */

    data8[blocks/2] += 5;
    data8[blocks/3] += 5;
    data8[blocks/4] += 5;

    printf("Before Decoding\n");

    print_hex(data8, 32);    
    print_hex(parity_data,12);


    int numerr;
    numerr = decode_rs8 (rs_decoder, data8, par, blocks, NULL, 0, NULL, 0, NULL);

    printf("Errors detected: %d\n",numerr);

    printf("After Decoding\n");
    
    print_hex(data8, 32);
    print_hex(parity_data,12);

    free_rs(rs_decoder);

    EXIT_TEST();

    return 0;
}