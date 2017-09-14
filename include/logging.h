#pragma once

#include <stdio.h>

enum log_level_t {
    LOG_BUG,
    LOG_WARNING,
    LOG_ERROR,
    LOG_QUIET,
    LOG_TRACE,
    LOG_DEBUG,
};

extern enum log_level_t log_level;

typedef enum log_level_t loglevel;

void Log(loglevel level,const char* format, ...);

static inline void set_loglevel(loglevel level) {
    log_level = level;
}
