#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "types.h"

void format_current_time(char* output);

#define UNUSED(x) ((void) (x))

#define __lazykitty_log_skeleton(name, args...) do {\
    char* time = malloc(sizeof(char) * 64);\
    assert(time != NULL);\
    memset(time, 0, sizeof(char) * 64);\
    format_current_time(time);\
    printf("%s " name " ", time);\
    printf(args); \
    free(time);\
} while(0)

#define lazykitty_log(args...)  __lazykitty_log_skeleton("[LOG] ", args)
#define lazykitty_info(args...) __lazykitty_log_skeleton("[INFO]", args)
#define lazykitty_warn(args...) __lazykitty_log_skeleton("[WARN]", args)

#define lazykitty_debug(args...) do {\
    printf("%s %s:%d [DEBUG] ", __func__, __FILE__, __LINE__);\
    printf(args); \
} while(0)

#define lazykitty_todo(args...) do {\
    printf("%s %s:%d [DEBUG] ", __func__, __FILE__, __LINE__);\
    printf(args);\
    fflush(stdout); \
    abort(); \
} while(0)

// https://stackoverflow.com/a/25108449
#define PRINTF_BINARY_PATTERN_INT8 "%c%c%c%c%c%c%c%c"
#define PRINTF_BYTE_TO_BINARY_INT8(i)    \
    (((i) & 0x80ll) ? '1' : '0'), \
    (((i) & 0x40ll) ? '1' : '0'), \
    (((i) & 0x20ll) ? '1' : '0'), \
    (((i) & 0x10ll) ? '1' : '0'), \
    (((i) & 0x08ll) ? '1' : '0'), \
    (((i) & 0x04ll) ? '1' : '0'), \
    (((i) & 0x02ll) ? '1' : '0'), \
    (((i) & 0x01ll) ? '1' : '0')

#define PRINTF_BINARY_PATTERN_INT16 \
    PRINTF_BINARY_PATTERN_INT8              PRINTF_BINARY_PATTERN_INT8
#define PRINTF_BYTE_TO_BINARY_INT16(i) \
    PRINTF_BYTE_TO_BINARY_INT8((i) >> 8),   PRINTF_BYTE_TO_BINARY_INT8(i)
#define PRINTF_BINARY_PATTERN_INT32 \
    PRINTF_BINARY_PATTERN_INT16             PRINTF_BINARY_PATTERN_INT16
#define PRINTF_BYTE_TO_BINARY_INT32(i) \
    PRINTF_BYTE_TO_BINARY_INT16((i) >> 16), PRINTF_BYTE_TO_BINARY_INT16(i)
#define PRINTF_BINARY_PATTERN_INT64    \
    PRINTF_BINARY_PATTERN_INT32             PRINTF_BINARY_PATTERN_INT32
#define PRINTF_BYTE_TO_BINARY_INT64(i) \
    PRINTF_BYTE_TO_BINARY_INT32((i) >> 32), PRINTF_BYTE_TO_BINARY_INT32(i)
