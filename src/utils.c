#include <time.h>
#include <assert.h>
#include <sys/time.h>
#include <stdio.h>

#include "utils.h"

void format_current_time(char* output) {
    assert(output != NULL);

    struct timeval tv;
    struct tm* timeinfo;

    gettimeofday(&tv, NULL);
    timeinfo = localtime(&tv.tv_sec);

    int milliseconds = tv.tv_usec / 1000;

    sprintf(output, "%d-%02d-%02d %02d:%02d:%02d.%03d", 
            timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, 
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, milliseconds);
}
