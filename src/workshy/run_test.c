#include "workshy.h"
#include <stdio.h>

const char* workshy_result_to_string(result_e result) {
    static const char* result_to_string[] = {
        "ok", "error"
    };

    return result_to_string[result];
}

int __workshy_main(int argc, char** argv) {
    (void) argc; (void) argv;

    printf("Amount of tests: %d\n", __workshy_tests_amount);
    printf("First test: %p\n", (void*) __workshy_tests_list[0]);

    return 0;
}

void __workshy__register_test(result_e (*test_function)(void)) {    
    for (int i = 0; i < __workshy_tests_amount; i++) {
        if (__workshy_tests_list[i] == test_function)
            return;
    }

    __workshy_tests_list[__workshy_tests_amount++] = test_function;
}