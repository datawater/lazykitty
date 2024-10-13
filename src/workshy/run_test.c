#include <assert.h>
#include <stdio.h>

#include "workshy.h"
#include "register.h"
#include "console.h"
#include "run_utils.h"
#include "run.h"

bool __workshy_run_test(__workshy_test_function_ptr function, char* function_name, int i) {
    printf("Test N%d %s: ", i, function_name);

    __workshy_block_stdout();
    __workshy_block_stderr();
        
    // TODO: workshy: refactor test running to fork the main process and call the test function from there, instead of raw-calling
    result_t result = function();

    __workshy_unblock_stdout();
    __workshy_unblock_stderr();

    if (result.result == fail) {
        printf(ANSI_COLOR_RED"failed\n"ANSI_COLOR_RESET);
        printf("Fail error string: %s\n\n", result.error);
    } else {
        printf(ANSI_COLOR_GREEN"passed\n"ANSI_COLOR_RESET);
        return true;
    }

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
        passed += __workshy_run_test(test_function_list[i], test_function_name_list[i], i);
    
    printf(ANSI_COLOR_CYAN"\n[INFO]"ANSI_COLOR_RESET" Passed: %d/%d\n", passed, tests_amount);

    if (passed == tests_amount)
        printf(ANSI_COLOR_GREEN"[SUCCESS]"ANSI_COLOR_RESET" All tests passed! :)\n");
    else
        printf(ANSI_COLOR_RED"[FAIL]"ANSI_COLOR_RESET" Failed "ANSI_COLOR_RED"%d"ANSI_COLOR_RESET" test(s). :(\n", tests_amount - passed);
}
