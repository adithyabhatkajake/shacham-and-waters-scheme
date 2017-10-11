/* 
 * Copyright (C) Indian Statistical Institute, Applied Statistical Unit - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Adithya Bhat <dth.bht@gmail.com>, September 2017
 */

#pragma once

enum log_level_t {
    LOG_BUG,        
    /*  
     *  Use this log level to print BUGS 
     *  in the code, like sections of 
     *  programs that should never have 
     *  reached in the first place. 
     */
    LOG_WARNING,
    /*  
     *  Use this log level to print out
     *  warnings to the user like invalid
     *  values and print the course of 
     *  action the program decides to 
     *  take on your behalf.
     */
    LOG_ERROR,
    /*
     *  Use this log level to print out
     *  errors in the program like wrong
     *  values, null values, incorrect
     *  arguments and failures to allocate
     *  memory, etc.
     */
    LOG_QUIET,
    /*
     *  DO NOT USE THIS LOG LEVEL TO LOG
     *  This is the default Log level, 
     *  where the logs are limited to bugs, 
     *  warnings and errors only.
     *  Using this log level will raise a 
     *  WARNING.
     */
    LOG_TRACE,
    /*
     *  Use this log level to print the 
     *  trace of the program, which prints 
     *  out the function which is called 
     *  and it's arguments in the order 
     *  of execution.
     */
    LOG_DEBUG,
    /*
     *  Use this log level to print all
     *  the intermediate values produced by
     *  the program. 
     *  Useful for debugging the program.
     */
};

typedef enum log_level_t loglevel;

/* 
 *  The global log level variable used to 
 *  set the log level by the caller of 
 *  the library.
 */
extern loglevel log_level;  

/*
 */
void Log(loglevel level,const char* format, ...);

static inline void set_loglevel(loglevel level) {
    log_level = level;
}

static inline void logline(int line)
{
    Log(log_level,"Logging Line:%d\n",line);
}
