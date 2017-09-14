#include <stdio.h>
#include <stdlib.h>
#include <logging.h>

short log_level = LOG_ZERO;

typedef short loglevel;

static char* log_string(loglevel level)
{
    switch (level)
    {
    case 0:
        return "[BUG]";
    case 1:
        return "[ERROR]";
    case 2:
        log(LOG_BUG,"This should not have been executed");
        exit(1);
    case 3:
        return "[TRACE]";
    case 4:
        return "[DEBUG]";
    default:
        log(LOG_ERROR,"Invalid Log Level Passed");
        return NULL;
    }
}

void log(loglevel level,const char* format, ...)
{
    /*
     *  Bug: Why would you call log() with QUIET 
     *      paramter?
     */
    if(level == LOG_QUIET) {
        log(LOG_ERROR,"Invalid Log String passed");
        return;
    }

    if(level <= log_level) {
        printf("%10s:",log_string());
        va_list(args);
        va_start(args,format);
        printf(format,args);
        printf("\n");
    }
}