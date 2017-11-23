/* 
 * Copyright (C) Indian Statistical Institute, Applied Statistical Unit - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Adithya Bhat <dth.bht@gmail.com>, September 2017
 */

#pragma once

/*
 *  handlefile.h
 *  Contains prototype declarations for file IO related 
 *  related operations performed by the library.   
 */

#include <pbc/pbc.h>    // For the element_t,pairing definitions
#include <stdint.h>     // For the uintXX declarations

#define DEFAULT_BLK_SIZE 16

struct file_t {
    struct file_piece_t*    pieces;     // An array of file_piece_t
    unsigned long long      nr_blocks;  // The number of file_piece_t blocks
};

struct tag_t {
    pairing_t   pairing;                // The pairing (p,g,G,GT,e) to which sigma belongs.
    element_t   sigma;                  // The Zr element sigma
    uint32_t    index;                  // The position to which the tag has been generated.
};

struct file_piece_t {
    unsigned long long      blk_size;   // The size of the current block piece
    struct tag_t*           tag;        // The tag generated for the current block
    uint16_t*               parity;     // The reed solomon parity generated for the block
    void*                   data;       // The actual data of the file
};

/*
 *  define function get_file_blocks():
 *  The function opens a filename, breaks it into blocks
 *  of DEFAULT_BLK_SIZE and sets up the corresponding 
 *  data structures and returns it to the caller.
 *  Useful for the first time processing of a file.
 *@param
 *  char*: Filename
 *  Pass a string containing the filename that is 
 *  resolvable in the environment of the program.
 *@return
 *  struct file_t*: File Type Structure
 *  Returns a file_t structure containing the entire file 
 *  broken down into file pieces.
 */
extern struct file_t* get_file_blocks(char*);

/*
 *  define function write_file():
 *  The function opens a filename, breaks it into blocks
 *  of DEFAULT_BLK_SIZE and sets up the corresponding 
 *  data structures and returns it to the caller.
 *  Useful for the first time processing of a file.
 *@param
 *  struct file_t*: file
 *  The file structure that will be stored by the peers 
 *  will have to written in their local storage. This 
 *  file structure will be written to the output file.
 *  const char*: Filename
 *  Pass a string containing the filename of the output 
 *  file that is resolvable in the environment of the 
 *  program.
 *@return
 *  Returns nothing. Errors will be logged out by the 
 *  function.
 */
extern void write_file(struct file_t*,const char*);

/*
 *  define function recover file():
 *  The function opens a filename, previously written 
 *  by write_file() and reproduces the file structure 
 *  from the binary file.
 *@param
 *  char*: Filename
 *  Pass a string containing the binary file's name 
 *  that is resolvable in the environment of the 
 *  program.
 *@return
 *  struct file_t*: File Type Structure
 *  Returns a file_t structure containing the entire file 
 *  broken down into file pieces.
 */
extern struct file_t* recover_file(const char*);

/*
 *  define function generate_parity():
 *  The function takes a file_t structure and generates 
 *  parity for the file's pieces and set's them to the 
 *  corresponding file piece' parity.
 *@param
 *  struct file_t*: file
 *  The file structure for whose blocks parity needs to 
 *  be generated.
 *@return
 *  struct file_t*: File Type Structure
 *  Returns a file_t structure containing the entire file 
 *  broken down into file pieces.
 */
extern void generate_parity(struct file_t*);