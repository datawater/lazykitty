#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "register.h"
#include <stdbool.h>
#include <stddef.h>

#ifndef WORKSHY_DEFAULT_AMOUNT_OF_TESTS
#define WORKSHY_DEFAULT_AMOUNT_OF_TESTS 128
#endif // WORKSHY_DEFAULT_AMOUNT_OF_TESTS

#ifndef WORKSHY_DEFAULT_AMOUNT_OF_BENCHMARKS
#define WORKSHY_DEFAULT_AMOUNT_OF_BENCHMARKS 128
#endif // WORKSHY_DEFAULT_AMOUNT_OF_TESTS

static int __workshy_benchmark_samples_amount = 100;

result_t new_result(void);
result_t new_result_error(char* error);
result_t new_result_ok(void);

int __workshy_main(int argc, char** argv);

#define CONCAT_1(x, y) x##y
#define CONCAT_2(x, y) CONCAT_1(x, y)
#define CONCAT_3(x) CONCAT_2(x, __COUNTER__)

void __workshy__register_test(result_t (*test_function)(void), char* function_name);
void __workshy__register_benchmark(void (*test_function)(void), char* function_name);

#define WORKSHY_TEST(function_name) \
    result_t function_name(void); \
    static void function_name##__runtime_marker(void) __attribute__((constructor)); \
    static void function_name##__runtime_marker(void) { \
        __workshy__register_test(function_name, #function_name); \
    } \
    result_t function_name(void)

#define WORKSHY_BENCHMARK(function_name) \
    void function_name(void); \
    static void function_name##__runtime_marker(void) __attribute__((constructor)); \
    static void function_name##__runtime_marker(void) { \
        __workshy__register_benchmark(function_name, #function_name); \
    } \
    void function_name(void) 

#define WORKSHY_RUN() \
    int main(int argc, char** argv) { \
        return __workshy_main(argc, argv); \
    } \

#define WORKSHY_BLACK_BOX(code_blox) \
    do { \
        __asm__ volatile("" ::: "memory"); \
        code_blox \
        __asm__ volatile("" ::: "memory"); \
    } while(0)

#ifdef __cplusplus
}
#endif // __cplusplus