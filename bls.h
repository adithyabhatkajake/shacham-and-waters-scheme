#pragma once

#include <pbc/pbc.h>
#define SIGN_OK 1
#define SIGN_FAIL 0

int verify_signature(pairing_t pairing,
    element_t group1, element_t group2,
    element_t signature,
    element_t public_key);
