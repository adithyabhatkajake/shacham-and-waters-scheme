#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TARGET "File IO Tests"

#include <handlefile.h>
#include <rslib.h>
#include <test.h>

static void usage(char *scriptname)
{
    fprintf(stderr, "Usage: <%s> <Filename>",scriptname);
}

static bool file_compare(struct file_t f1, struct file_t f2)
{
    if(f1.nr_blocks != f2.nr_blocks) {
        return false;
    }

    for(int i=0;i<f1.nr_blocks;i++) {
        struct file_piece_t fpiece1,fpiece2;
        fpiece1 = f1.pieces[i];
        fpiece2 = f2.pieces[i];

        if(fpiece1.blk_size != fpiece2.blk_size) {
            return false;
        }
 
        for(int j=0;j<6;j++) {
            if(fpiece1.parity[j]!=fpiece2.parity[j])
                return false;
        }

        for(int j=0;j<fpiece1.blk_size;j++) {
            char *byte1,*byte2;
            byte1 = fpiece1.data+j;
            byte2 = fpiece2.data+j;
            if(*byte1 != *byte2)
                return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{

    INIT_TEST();

    if(argc != 2) {
        fprintf(stderr, "[Error][1]: Incorrect Number of arguments\n");
        usage(argv[0]);
        exit(1);
    }

    struct file_t *f = get_file_blocks(argv[1]);
    generate_parity(f);
    
    char output_file[strlen(argv[1])+strlen("-TEST")+1];
    strcpy(output_file,argv[1]);
    strcat(output_file,"-TEST");
    
    write_file(f,output_file);
    printf("Output written to \"%s\"\n",output_file);

    printf("File Blocks: %llu\n",f->nr_blocks);

    struct file_t *f2 = recover_file(output_file);
    printf("Original File Blocks: %llu\n"
        "Recovered File Blocks:%llu\n",
        f->nr_blocks, f2->nr_blocks);
    printf("Big Result(Drum rolls:%s)\n",file_compare(*f,*f2)==true?"true":"false");

    EXIT_TEST();

    return 0;
}