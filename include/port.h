/* 
 * Copyright (C) Indian Statistical Institute, Applied Statistical Unit - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Adithya Bhat <dth.bht@gmail.com>, September 2017
 */

#pragma once

#include <pbc/pbc.h>

#define G1_LEN_COMPRESSED 131
#define G1_LEN 260
#define ZR_LEN 128

struct public_key_t {
    struct pairing_s* pairing;
    element_t alpha;
    element_t v;            // v = g^x
    element_t g;
};

struct private_key_t {
    struct pairing_s* pairing;
    element_t alpha;
    element_t x;
    element_t g;
};

struct keypair_t {
    struct public_key_t* pub_key;
    struct private_key_t* pvt_key;
};

struct file_t* import_file(const char*);
void export_file(struct file_t*,const char*);
struct public_key_t* import_public_key(const char*);
void export_public_key(struct public_key_t*, const char* filename);
struct private_key_t* import_pvt_key(const char*);
void export_pvt_key(struct private_key_t*, const char* filename);
struct keypair_t* generate_key_pair();

void free_public_key(struct public_key_t*);
void free_private_key(struct private_key_t*);
void free_keypair(struct keypair_t*);