#pragma once

#include <stdio.h>

struct file_piece_t {
    struct file_t       *file_head;
    unsigned long long   nr_blocks;
};

struct file_t {
    void                *data;
    unsigned long long  blk_size;
};

extern struct file_t* get_file_blocks(char*);
