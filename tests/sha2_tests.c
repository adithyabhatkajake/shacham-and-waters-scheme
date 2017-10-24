#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TARGET "SHA256 Tests"

#include <print-utils.h>
#include <logging.h>
#include <sha256.h>
#include <test.h>

#define TEST_ITEMS 6

static int byte_compare(unsigned char* src1,unsigned char* src2, int len)
{
    int i = 0;
    while(i < len) {
        int flag = src1[i]-src2[i];
        if(flag != 0) {
            printf("%u %u\n",src1[i],src2[i]);
            return flag;
        }
        i++;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    INIT_TEST();
    /* 
     *  You can add more entries to this test.
     *  Run `printf "Test string" > testfile.txt`
     *  Run `sha256sum testfile.txt`
     *  Paste the sha256 output generated and the corresponding inputs
     *      to the string arrays.
     */
    char* test_string[] = {
        "hello",
        "hello world",
        "",
        "9985674123",
        "9654\n",
        "\0\0"
    };
    // Generated using in built sha256 program 
    unsigned char* expected_hashes[] = {
        "2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824",
        "b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9",
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855", //Curiously 3 and 6 have the same hashes
        "1b8bbfe937bd041b1aef14d099062399ce5ddafdaeb1ab7d5ac58bcaa3be05f5",
        "3a1142b2271bffdc5d9d8040471544d1857be10f4f22546a8698ea7f8ca68f71",
        "96a296d224f285c67bee93c30f8a309157f0daa35dc5b87e410b78630a09cfc7"
    };
    int string_lengths[] = {
        5,11,0,10,5,2
    };
    
    for(int i=0;i<TEST_ITEMS;i++) {
        sha256_hash_t buffer[32];
        sha256(buffer,test_string[i],8*string_lengths[i]);
        //print_hex(buffer,32);
        //printf("%s\n",expected_hashes[i]);
        printf("Hashing Test[%d]:  ",i);
        char* string = hexstring((unsigned char*)buffer,32);
        printf("%s\n",byte_compare(expected_hashes[i],string,32)==0?"Passed":"Failed");
        free(string);
    }

    EXIT_TEST();

    return 0;
}
