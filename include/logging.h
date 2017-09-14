#pragma once

#include <stdio.h>

#define LOG_BUG     0
#define LOG_WARNING 1
#define LOG_ERROR   2
#define LOG_QUIET   3
#define LOG_TRACE   4
#define LOG_DEBUG   5

extern short log_level;

typedef short loglevel;

void Log(loglevel level,const char* format, ...);

static inline void set_loglevel(loglevel level) {
    log_level = level;
}
