/* 
 * Copyright (C) Indian Statistical Institute, Applied Statistical Unit - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Adithya Bhat <dth.bht@gmail.com>, September 2017
 */

#pragma once

#include <print-utils.h>

/*
 * Testing Guidelines:
 * 1. `#define TARGET "Description of the test File"` Define the TARGET 
 *      with a string description.
 * 2. `#include <test.h>` in all the test files.
 * 3. Call `INIT_TEST();` in the first line of main.
 * 4. Call `EXIT_TEST();` just before returning the status code.
 * 5. Make corresponding changes in the testing makefile.
 */

#ifdef TARGET
#define INIT_TEST() do { \
    print_block("Running %s Test:\n",TARGET);\
}\
while(0)
#endif

#ifdef TARGET
#define EXIT_TEST() do {\
    print_block("%s completed successfully.",TARGET);\
}\
while(0)
#endif