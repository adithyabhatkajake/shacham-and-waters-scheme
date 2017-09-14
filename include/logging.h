#pragma once

#include <stdio.h>

#define LOG_BUG     0
#define LOG_ERROR   1
#define LOG_QUIET   2
#define LOG_TRACE   3
#define LOG_DEBUG   4

extern short log_level;

typedef short loglevel;

void log(loglevel level,const char* format, ...);

static inline void set_loglevel(loglevel level) {
    log_level = level;
}
