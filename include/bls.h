/* 
 * Copyright (C) Indian Statistical Institute, Applied Statistical Unit - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Adithya Bhat <dth.bht@gmail.com>, September 2017
 */

#pragma once

/*
 * bls.h
 * Contains function prototypes and data structures 
 *  used in BLS hashing, signatures and verification 
 *  in the program.
 */


#include <pbc/pbc.h>
#include <stdlib.h>
#include <string.h>

#define SIGN_OK     1
#define SIGN_FAIL   0

/*
 *  a1_param:
 *  A type of parameter specificed in the Stanford 
 *  Crypto Library that is symmetric and produces
 *  efficient pairings.
 */

#define a1_param "type a1\n"\
"p 48512875896303752499712277254589628516419352"\
"1882945211981895675110090731581150453612948393"\
"4709931589896004539852468200733416492853159479"\
"9149100548036445760110913157420655690361891290"\
"8584413608071582472594605013434491997125328280"\
"6394000868374004850098044198971373968965561057"\
"8458388126934242630557397618776539259\n"\
"n 36203638728584889925158415861634051131656232"\
"9763391949240220653067231889239664517621603278"\
"7096963873056719805860050896069713800636686179"\
"0409776528385407283664860565239295291314844246"\
"9092845976172822740742242547339173132183080806"\
"4473134976398511082162719551471174603705642580"\
"4819692632040479575042834043863089\n"\
"l 1340"

/*
 *  TO:DO
 *  1. Clean the paramters
 *  2. Add documentation
 */
int verify_signature(pairing_t pairing,
    element_t group1, element_t group2,
    element_t signature,
    element_t public_key);

/*
 *  A macro to initialize pairing to the correct
 *  curve.
 */    
#define INIT_PAIRING(pairing) (pairing_init_set_buf(*pairing, a1_param, strlen(a1_param)));

/*
 *  TO:DO
 *  1. Clean the paramters
 *  2. Add documentation
 */
struct element_s* bls_hash(void*,int,pairing_t);

/*
 *  define function bls_hash_int():
 *  The function creates an element e in G from the integer
 *  Refer to Shachams-and-waters paper for more information.
 *@param:
 *  uint32_t: The number to be hashed
 *  pairing_t: The pairing in which to perform the hashing
 *@return:
 *  Returns an element belonging to G1=G2=G for the 
 *  given integer.
 */
struct element_s* bls_hash_int(uint32_t,pairing_t);