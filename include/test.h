/* 
 * Copyright (C) Indian Statistical Institute, Applied Statistical Unit - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Adithya Bhat <dth.bht@gmail.com>, September 2017
 */

#pragma once

#ifdef TARGET
#define INIT_TEST() do { \
    printf("Running %s Test:\n",TARGET);\
}\
while(0)
#endif

#ifdef TARGET
#define EXIT_TEST() do {\
    printf("%s Test completed successfully.\n",TARGET);\
}\
while(0)
#endif