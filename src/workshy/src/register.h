#pragma once

typedef enum {
    ok, fail, unknown
} result_e;

typedef struct {
    result_e result;
    char* error;
} result_t;

typedef result_t(*__workshy_test_function_ptr)(void);
typedef void(*__workshy_benchmark_function_ptr)(void);

__workshy_test_function_ptr* __workshy_get_test_functions();
char** __workshy_get_test_function_names();
int* __workshy_get_test_amount();

__workshy_benchmark_function_ptr* __workshy_get_benchmark_functions();
char** __workshy_get_benchmark_function_names();
int* __workshy_get_benchmark_amount();