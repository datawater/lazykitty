#include "workshy.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

const char* workshy_result_to_string(result_e result) {
    static const char* result_to_string[] = {
        "ok", "error"
    };

    return result_to_string[result];
}

int __workshy_main(int argc, char** argv) {
    argc--; argv++;

    if (argc > 0)
        printf(ANSI_COLOR_YELLOW"[WARNING]"ANSI_COLOR_RESET" workshy currently doens't accept command line arguments.\n");

    unsigned int passed = 0;

    printf(ANSI_COLOR_CYAN"[INFO]"ANSI_COLOR_RESET" Amount of tests: %d\n\n", __workshy_tests_amount);

    FILE* stdout_backup = stdout;
    FILE* stderr_backup = stderr;
    
    // TODO: Make this cross platform
    FILE* dev_null = fopen("/dev/null", "w");

    if (dev_null == NULL) {
        fprintf(stderr, "[workshy_err] Couldn't open '/dev/null'. error: %s\n", strerror(errno));
        return 1;
    }

    // TODO: workshy: Allow multi-threaded testing
    for (unsigned int i = 0; i < __workshy_tests_amount; ++i) {
        printf("Test N%d: ", i);

        // TODO: workshy: Add flag to disallow stdout blocking
        stdout_backup = stdout;
        stderr_backup = stderr;
        stdout = dev_null;
        stderr = dev_null;
        
        result_e result = __workshy_tests_list[i]();
        
        stdout = stdout_backup;
        stderr = stderr_backup;

        if (result == fail) {
            printf(ANSI_COLOR_RED"failed\n"ANSI_COLOR_RESET);
        } else {
            printf(ANSI_COLOR_GREEN"passed\n"ANSI_COLOR_RESET);
            passed++;
        }
    }
    
    printf(ANSI_COLOR_CYAN"\n[INFO]"ANSI_COLOR_RESET" Passed: %d/%d\n", passed, __workshy_tests_amount);

    if (passed == __workshy_tests_amount)
        printf(ANSI_COLOR_GREEN"[SUCCESS]"ANSI_COLOR_RESET" All tests passed! :)\n");
    else
        printf(ANSI_COLOR_RED"[FAIL]"ANSI_COLOR_RESET" Failed "ANSI_COLOR_RED"%d"ANSI_COLOR_RESET" test(s). :(\n", __workshy_tests_amount - passed);
    
    return 0;
}

void __workshy__register_test(result_e (*test_function)(void)) {    
    // O(n) insertion instead of O(1) because, ofc.
    for (unsigned int i = 0; i < __workshy_tests_amount; i++) {
        if (__workshy_tests_list[i] == test_function)
            return;
    }

    __workshy_tests_list[__workshy_tests_amount++] = test_function;
}