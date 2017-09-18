#pragma once
#include <pbc/pbc.h>

struct __tag_param {
    pairing_t pairing;
    element_t alpha;
    struct file_piece_t *fpiece;
    int index;
    element_t secret_x;
};

typedef struct __tag_param tag_param_t;

struct tag_t {
    pairing_t pairing;
    int index;
    element_t sigma;
};

struct tag_t* generate_tag(tag_param_t*);

struct _setup {
    pairing_t pairing;
    element_t g;
};

