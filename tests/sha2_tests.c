#include <string.h>

#include <logging.h>
#include <sha2.h>

#define TEST_ITEMS 6

int main(int argc, char const *argv[])
{
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
    char* expected_hashes[] = {
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
        SHA256_CTX	ctx256;
        SHA256_Init(&ctx256);
        char buffer[256];
        SHA256_Update(&ctx256, test_string[i],string_lengths[i]);
        SHA256_End(&ctx256, buffer);
        printf("Hashing Test[%d]:  ",i);
        printf("%s\n",strcmp(expected_hashes[i],buffer)==0?"Passed":"Failed");
    }

    return 0;
}
