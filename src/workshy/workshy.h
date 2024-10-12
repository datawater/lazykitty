#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdatomic.h>

typedef enum {
    ok, fail
} result_e;

#ifndef WORKSHY_MAX_AMOUNT_OF_TESTS
#define WORKSHY_MAX_AMOUNT_OF_TESTS 512
#endif // WORKSHY_MAX_AMOUNT_OF_TESTS

typedef result_e(*workshy_test_function_ptr)(void);

static workshy_test_function_ptr __workshy_tests_list[WORKSHY_MAX_AMOUNT_OF_TESTS];
static unsigned int __workshy_tests_amount;

int __workshy_main(int argc, char** argv);

#define CONCAT_1(x, y) x##y
#define CONCAT_2(x, y) CONCAT_1(x, y)
#define CONCAT_3(x) CONCAT_2(x, __COUNTER__)

void __workshy__register_test(result_e (*test_function)(void));

#define WORKSHY_TEST(function_name) \
    result_e function_name(void); \
    static void function_name##__runtime_marker(void) __attribute__((constructor)); \
    static void function_name##__runtime_marker(void) { \
        __workshy__register_test(function_name); \
    } \
    result_e function_name(void)

#define WORKSHY_MAIN_RUN_TESTS() \
    int main(int argc, char** argv) { \
        return __workshy_main(argc, argv); \
    } \

