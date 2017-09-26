#include <stdio.h>

#include "logging.h"

static void print_all_logs()
{
    int k = 1;
    Log(LOG_BUG     , "Bug Logging"     );
    Log(LOG_WARNING , "Warning Logging" );
    Log(LOG_ERROR   , "Error Logging"   );
    Log(LOG_QUIET   , "Quiet Logging"   );
    Log(LOG_TRACE   , "Trace Logging"   );
    Log(LOG_DEBUG   , "Debug Logging"   );
}

int main(int argc, char const *argv[])
{
    /* code */
    for(loglevel i=LOG_QUIET;i<=(LOG_DEBUG);i++) {
        log_level = i;
        print_all_logs();
        printf("\n");
    }
    return 0;
}
