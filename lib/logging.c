#include <stdio.h>
#include <stdlib.h>
#include <logging.h>
#include <stdarg.h>

short log_level = LOG_QUIET;

typedef short loglevel;

static char* log_string(loglevel level)
{
    switch (level)
    {
    case 0:
        return "[BUG]";
    case 1:
        return "[WARNING]";
    case 2:
        return "[ERROR]";
    case 3:
        Log(LOG_BUG,"This should not have been executed");
        exit(1);
    case 4:
        return "[TRACE]";
    case 5:
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
        Log(LOG_WARNING,"Invalid Log String passed");
        return;
    }

    if(level <= log_level) {
        printf("%10s|",log_string(level));
        va_list(args);
        va_start(args,format);
        printf(format,args);
        printf("\n");
    }
}