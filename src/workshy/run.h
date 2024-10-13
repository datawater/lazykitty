#pragma once

#include "register.h"

void __workshy_run_tests();
void __workshy_run_benches();
bool __workshy_run_test(__workshy_test_function_ptr function, char* function_name, int i);
void __workshy_run_bench(__workshy_benchmark_function_ptr function, char* function_name);