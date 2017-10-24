/* 
 * Copyright (C) Indian Statistical Institute, Applied Statistical Unit - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Adithya Bhat <dth.bht@gmail.com>, September 2017
 */

#pragma once

#include "logging.h"

/*
 *  define function print_hex():
 *  The function prints a byte sequence in hexadecimal 
 *  format
 *@param
 *  char*:
 *  The byte sequence to be printed
 *  int:
 *  The length of the byte sequence
 */
void print_hex(unsigned char*,int);

/*
 *  define function println():
 *  The function prints the format string in a line.
 *  All format strings supported by pbc and normal
 *  printf can be used.
 *@param
 *  char*: The format string
 *  The format string to be printed.
 *Ex.
 *  println("g is %B",g);
 */
void println(char*,...);

/*
 *  define function print_pretty_line():
 *  Prints a pretty line like this:
 *  ====================================
 */
void print_pretty_line();

/*
 *  define function print_block():
 *  The function prints special content in a block as 
 *  follows:
 *Ex.
 *  print_block("This is a test message");
 *  =================================================
 *  This is a test message
 *  =================================================
 * 
 *@param
 *  char*: Format string
 *  The format string containing pbc defined and normal print
 *  type literals.
 */
void print_block(char*,...);

/*
 *  define function hexstring():
 *  The function takes a file_t structure and generates 
 *  parity for the file's pieces and set's them to the 
 *  corresponding file piece' parity.
 *@param
 *  unsigned char*: byte sequence 
 *  The byte sequence to be converted into hexadecimal
 *  string
 *  int: number of bytes
 *  The size of the byte sequence
 *@return
 *  char*: 
 *  Returns a string (char*) pointer containing the 
 *  hexadecimal string
 */
char* hexstring(unsigned char*,int);
