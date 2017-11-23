/* 
 * Copyright (C) Indian Statistical Institute, Applied Statistical Unit - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Adithya Bhat <dth.bht@gmail.com>, September 2017
 */

#pragma once

/*
 * audit.h
 * Contains function prototypes and data structures 
 *  used in auditing and verifying storage blocks.
 */

#include <pbc/pbc.h>    // For the pairing, element_t definitions.
#include <stdint.h>     // For uint32_t definitions.

#include "handlefile.h" // For struct file_piece_t definitions

enum audit_result {
    PASS,
    FAIL,
};

struct __tag_param {
    struct file_piece_t* fpiece;    // An encoded file segment.
    struct pairing_s*            pairing;   // The pairing (p,g,G,GT,e).
    struct element_s*            alpha;     // A generator of G.
    struct element_s*            secret_x;  // A secret value x in Zp.
    uint32_t             index;     // The spatial position of the file block.
};

typedef struct __tag_param tag_param_t;

/*
 *  define function generate_tag():
 *  The function generates a tag structure for a Reed
 *  Solomon encoded file, that will be used to verify 
 *  the contents of the file and for auditing 
 *  challenges.
 *@param
 *  tag_param_t: Parameters
 *  To generate the cryptographic tag for the file,
 *  some cryptographic parameters need to be provided.
 *@return
 *  tag_t: Tag
 *  It returns a tag_t structure holding the tag value
 *  sigma for the file block.
 */
struct tag_t* generate_tag(tag_param_t*);

/*
 *  define function set_tags():
 *  The function takes a file_t structure and generates 
 *  tags for the file's pieces and set's them to the 
 *  corresponding file piece' sigma.
 *@param
 *  struct file_t*: file
 *  The file structure for whose blocks tags need to 
 *  be generated.
 *  tag_param_t*: parameters
 *  The parameters to generate the tag
 *@return
 *  Returns nothing. Errors will be logged by the 
 *  function.
 */
void set_tags(struct file_t* file, tag_param_t* params);

struct query_t {
    uint32_t            query_length;   // Number of query tests
    uint32_t*           indices;        // An array of indices
    struct pairing_s*   pairing;        // The pairing in which the operations are performed
    struct element_s*   nu;             // An array of nu elements
};

struct query_response_t {
    struct pairing_s*   pairing;        // The pairing used
    element_t           sigma;          // The sigma for the query
    element_t           mu;             // The mu for the query
};

/*
 *  define function query():
 *  The function takes a file information structure
 *  and a query parameter to build and perform query
 *  on the file.
 *  It basically takes (i,vi) in Q, and generates a 
 *  sigma and nu for the query.
 *@param
 *  struct file_t*: file
 *  The file structure pointer for whose blocks the 
 *  query needs to be generated.
 *  struct query_t: query
 *  The query parameters to generate the tag on the
 *  file.
 *@return
 *  struct query_response_t*:
 *  Given the file and the query, the function returns
 *  a response to the query with (sigma,nu)
 */
struct query_response_t* query(struct file_t* file,struct query_t query);

/*
 *  TO:DO
 *  1. Clean the paramters
 *  2. Add documentation
 */
enum audit_result verify_storage(struct file_t*, struct query_response_t,struct query_t,element_t,element_t,element_t);