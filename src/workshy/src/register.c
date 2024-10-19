#include "workshy.h"
#include "register.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

__workshy_test_function_ptr* workshy_tests_list = NULL;
char** workshy_test_function_name_list = NULL; 
static int workshy_tests_amount;
static int __workshy_tests_array_capacity;

__workshy_benchmark_function_ptr* workshy_benchmark_list;
char** workshy_benchmark_function_name_list; 
static int workshy_benchmark_amount;
static int __workshy_benchmark_array_capacity;

void safe_check_array_pointers() {
    if (workshy_tests_list == NULL) {
        workshy_tests_list = malloc(sizeof(__workshy_test_function_ptr) * WORKSHY_DEFAULT_AMOUNT_OF_TESTS);
        memset(workshy_tests_list, 0, sizeof(char*) * WORKSHY_DEFAULT_AMOUNT_OF_TESTS);
        assert(workshy_tests_list != NULL && "couldn't allocate memory\n");
    }

    if (workshy_test_function_name_list == NULL) {
        workshy_test_function_name_list = malloc(sizeof(char*) * WORKSHY_DEFAULT_AMOUNT_OF_TESTS);
        memset(workshy_test_function_name_list, 0, sizeof(char*) * WORKSHY_DEFAULT_AMOUNT_OF_TESTS);
        assert(workshy_test_function_name_list != NULL && "couldn't allocate memory\n");
    }

    if (workshy_tests_amount + 1 == __workshy_tests_array_capacity) {
        __workshy_tests_array_capacity *= 1.6;
        workshy_tests_list = realloc(workshy_tests_list, __workshy_tests_array_capacity);
        workshy_test_function_name_list = realloc(workshy_test_function_name_list, __workshy_tests_array_capacity);

        assert(workshy_tests_list != NULL && workshy_test_function_name_list != NULL && "couldn't allocate memory\n");
    }

    if (workshy_benchmark_list == NULL) {
        workshy_benchmark_list = malloc(sizeof(__workshy_benchmark_function_ptr) * WORKSHY_DEFAULT_AMOUNT_OF_BENCHMARKS);
        memset(workshy_benchmark_list, 0, sizeof(char*) * WORKSHY_DEFAULT_AMOUNT_OF_BENCHMARKS);
        assert(workshy_benchmark_list != NULL && "couldn't allocate memory\n");
    }

    if (workshy_benchmark_function_name_list == NULL) {
        workshy_benchmark_function_name_list = malloc(sizeof(char*) * WORKSHY_DEFAULT_AMOUNT_OF_BENCHMARKS);
        memset(workshy_benchmark_function_name_list, 0, sizeof(char*) * WORKSHY_DEFAULT_AMOUNT_OF_BENCHMARKS);
        assert(workshy_benchmark_function_name_list != NULL && "couldn't allocate memory\n");
    }

    if (workshy_benchmark_amount + 1 == __workshy_benchmark_array_capacity) {
        __workshy_benchmark_array_capacity *= 1.6;
        workshy_benchmark_list = realloc(workshy_benchmark_list, __workshy_benchmark_array_capacity);
        workshy_benchmark_function_name_list = realloc(workshy_benchmark_function_name_list, __workshy_benchmark_array_capacity);

        assert(workshy_benchmark_list != NULL && workshy_benchmark_function_name_list != NULL && "couldn't allocate memory\n");
    }
}

void __workshy__register_test(__workshy_test_function_ptr test_function, char* function_name) {
    safe_check_array_pointers();

    // O(n) insertion instead of O(1) because, ofc.
    for (int i = 0; i < workshy_tests_amount; i++) {
        if (workshy_tests_list[i] == test_function)
            return;
    }


    if (function_name == NULL) {
        assert(0 && "function_name is __workshy__register_test is null. something went horribly wrong");
    }

    workshy_tests_list[workshy_tests_amount] = test_function;
    workshy_test_function_name_list[workshy_tests_amount++] = function_name;
}

void __workshy__register_benchmark(__workshy_benchmark_function_ptr test_function, char* function_name) {
        safe_check_array_pointers();

    // O(n) insertion instead of O(1) because, ofc.
    for (int i = 0; i < workshy_benchmark_amount; i++) {
        if (workshy_benchmark_list[i] == test_function)
            return;
    }


    if (function_name == NULL) {
        assert(0 && "function_name is __workshy__register_benchmark is null. something went horribly wrong");
    }

    workshy_benchmark_list[workshy_benchmark_amount] = test_function;
    workshy_benchmark_function_name_list[workshy_benchmark_amount++] = function_name;
}

__workshy_test_function_ptr* __workshy_get_test_functions() {
    return workshy_tests_list;
}

char** __workshy_get_test_function_names() {
    return workshy_test_function_name_list;
}

int* __workshy_get_test_amount() {
    return (int*) &workshy_tests_amount;
}

__workshy_benchmark_function_ptr* __workshy_get_benchmark_functions() {
    return workshy_benchmark_list;
}

char** __workshy_get_benchmark_function_names() {
    return workshy_benchmark_function_name_list;
}

int* __workshy_get_benchmark_amount() {
    return (int*) &workshy_benchmark_amount;
}
