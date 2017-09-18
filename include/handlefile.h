#pragma once

#include <stdio.h>
#include <stdint.h>
#include <pbc/pbc.h>

#define DEFAULT_BLK_SIZE 128

struct file_piece_t {
    void                 *data;
    unsigned long long   blk_size;
    uint16_t             *parity;
};

struct file_t {
    struct file_piece_t *pieces; // An array of file_piece_t
    unsigned long long  nr_blocks;
};

extern struct file_t* get_file_blocks(char*);

extern void write_file(struct file_t*,const char*);
extern struct file_t* recover_file(const char*);

extern void generate_parity(struct file_t*);
