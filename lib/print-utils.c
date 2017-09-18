#include <print-utils.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void print_hex(unsigned char* string, int len)
{
    for(int i=0;i<len;i++) 
    {
        printf("%02x",string[i]);
    }
    printf("\n");
}

void print_pretty_line()
{
    for(int i=0;i<40;i++)
        printf("-");

    printf("\n");
}

void print_block(char* format,...)
{
    print_pretty_line();
    va_list args;
    va_start(args,format);
    vprintf(format,args);
    va_end(args);
    printf("\n");
    print_pretty_line();
}

void println(char* format,...)
{
    va_list args;
    va_start(args,format);
    vprintf(format,args);
    va_end(args);
    printf("\n");
}

char* hexstring(unsigned char* bytes, int len)
{
    char* buffer    = malloc(sizeof(char)*((2*len)+1));
    char* temp      = buffer;
    for(int i=0;i<len;i++) {
        sprintf(temp,"%02x",bytes[i]);
        temp += 2;
    }
    *temp = '\0';
    return buffer;
}