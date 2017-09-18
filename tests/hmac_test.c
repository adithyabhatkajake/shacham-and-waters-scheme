#include <hmac-sha256.h>
#include <string.h>
#include <stdio.h>
#include <print-utils.h>

int main(int argc, char const *argv[])
{
    /* code */
    char* key = "blah";
    char dest_buf[32];
    for(int i=0;i<32;i++) {
        dest_buf[i] = 0;
    }
    char* msg = "This is the message";
    hmac_sha256(dest_buf,key,4,msg,strlen(msg));
    print_hex(dest_buf,32);
    //print_hex("a",1);
    return 0;
}
