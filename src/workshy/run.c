#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "workshy.h"
#include "register.h"
#include "console.h"

bool run_test(__workshy_test_function_ptr function, char* function_name, int i) {
    FILE* stdout_backup = stdout;
    FILE* stderr_backup = stderr;

    FILE* dev_null = fopen("/dev/null", "w");

    if (dev_null == NULL) {
        fprintf(stderr, "[workshy_err] Couldn't open '/dev/null'. error: %s\n", strerror(errno));
        abort();
    }

    printf("Test N%d %s: ", i, function_name);

    // TODO: workshy: Add flag to disallow stdout blocking
    stdout_backup = stdout;
    stderr_backup = stderr;
    stdout = dev_null;
    stderr = dev_null;
        
    // TODO: workshy: refactor test running to fork the main process and call the test function from there, instead of raw-calling
    result_t result = function();
        
    stdout = stdout_backup;
    stderr = stderr_backup;

    if (result.result == fail) {
        printf(ANSI_COLOR_RED"failed\n"ANSI_COLOR_RESET);
        printf("Fail error string: %s\n\n", result.error);
    } else {
        printf(ANSI_COLOR_GREEN"passed\n"ANSI_COLOR_RESET);
        return true;
    }

    fclose(dev_null);
    return false;
}

void __workshy_run_tests() {
    int tests_amount = *__workshy_get_test_amount();
    char** test_function_name_list = __workshy_get_test_function_names();
    __workshy_test_function_ptr* test_function_list = __workshy_get_test_functions();

    int passed = 0;

    printf(ANSI_COLOR_CYAN"[INFO]"ANSI_COLOR_RESET" Amount of tests: %d\n\n", tests_amount);

    // TODO: workshy: Allow multi-threaded testing
    for (int i = 0; i < tests_amount; ++i)
        passed += run_test(test_function_list[i], test_function_name_list[i], i);
    
    printf(ANSI_COLOR_CYAN"\n[INFO]"ANSI_COLOR_RESET" Passed: %d/%d\n", passed, tests_amount);

    if (passed == tests_amount)
        printf(ANSI_COLOR_GREEN"[SUCCESS]"ANSI_COLOR_RESET" All tests passed! :)\n");
    else
        printf(ANSI_COLOR_RED"[FAIL]"ANSI_COLOR_RESET" Failed "ANSI_COLOR_RED"%d"ANSI_COLOR_RESET" test(s). :(\n", tests_amount - passed);
}

void __workshy_run_benches() {
    // int bench_amount = *__workshy_get_benchmark_amount();
    // char** bench_function_name_list = __workshy_get_benchmark_function_names();
    // __workshy_benchmark_function_ptr* bench_function_list = __workshy_get_benchmark_functions();

    // printf(ANSI_COLOR_CYAN"[INFO]"ANSI_COLOR_RESET" Amount of benchmarks: %d\n\n", bench_amount);

    // TODO
}