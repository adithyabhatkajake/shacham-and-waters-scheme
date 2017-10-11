/* 
 * Copyright (C) Indian Statistical Institute, Applied Statistical Unit - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Adithya Bhat <dth.bht@gmail.com>, September 2017
 */

#pragma once

#include "logging.h"

void print_hex(unsigned char*,int);

void println(char*,...);

void print_pretty_line();

void print_block(char*,...);

char* hexstring(unsigned char*,int);
