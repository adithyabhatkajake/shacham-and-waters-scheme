#include <stdio.h>
#include <stdlib.h>
#include <logging.h>
#include <stdarg.h>

loglevel log_level = LOG_QUIET;

static char* log_string(loglevel level)
{
    switch (level)
    {
    case LOG_BUG:
        return "[BUG]";
    case LOG_WARNING:
        return "[WARNING]";
    case LOG_ERROR:
        return "[ERROR]";
    case LOG_QUIET:
        Log(LOG_BUG,"This should not have been executed");
        exit(1);
    case LOG_TRACE:
        return "[TRACE]";
    case LOG_DEBUG:
        return "[DEBUG]";
    default:
        Log(LOG_ERROR,"Invalid Log Level Passed");
        return NULL;
    }
}

void Log(loglevel level,const char* format, ...)
{
    /*
     *  Bug: Why would you call log() with QUIET 
     *      paramter?
     */
    if(level == LOG_QUIET) {
        Log(LOG_WARNING,"Log String LOG_QUIET must not be passed");
        return;
    }

    if(level <= log_level) {
        va_list args;

        printf("%-10s|",log_string(level));

        va_start(args,format);
        vprintf(format,args);
        va_end(args);

        printf("\n");
    }
}