#include <stdio.h>
#include <string.h>
#include "register.h"
#include "workshy.h"
#include "run.h"

void __workshy_run_help() {
    printf("workshy <command> [specific benchmark/test to run] [options]\n\n");
    
    printf("commands:\n");
    printf("\ttest | t                 runs the tests\n");
    printf("\tbenchmark | bench | b    runs the benchmarks\n");
    printf("\thelp | h                 prints this help command\n\n");
    
    printf("options:\n");
    printf("\t--help | -h      prints this help command\n");
}

int __workshy_main(int argc, char** argv) {
    argc--; argv++;

    if (argc == 0)
        __workshy_run_tests();

    bool is_test = false;
    bool is_bench = false;

    for (int i = 0; i < argc; i++) {
        bool is_help = strcmp(argv[i], "-h")   == 0 || strcmp(argv[i], "--help") == 0 
                    || strcmp(argv[i], "help") == 0 || strcmp(argv[i], "h") == 0;
        
        if (is_help) {
            __workshy_run_help();
            return 0;
        }

        bool is_test_rn  = strcmp(*argv, "test") == 0 || strcmp(*argv, "t") == 0;
        bool is_bench_rn = strcmp(*argv, "bench") == 0 || strcmp(*argv, "b") == 0 || strcmp(*argv, "benchmark") == 0;
    

        if (is_test_rn) {
            is_test = is_test_rn;
            continue;
        }

        if (is_bench_rn) {
            is_bench = is_bench_rn;
            continue;
        }

        if (*argv[i] == '-') {
            fprintf(stderr, "[workshy_fail] Unknown command line option: '%s'. Run `workshy --help` for help.\n", *argv);
            return 1;
        }

        bool in_tests = false;
        int x = -1;

        __workshy_test_function_ptr* test_functions = __workshy_get_test_functions();
        char** test_function_names = __workshy_get_test_function_names();

        __workshy_benchmark_function_ptr* benchmark_functions = __workshy_get_benchmark_functions();
        char** benchmark_function_names = __workshy_get_benchmark_function_names();

        for (int j = 0; j < *__workshy_get_test_amount(); j++) {
            if (strcmp(test_function_names[j], argv[i]) != 0)
                continue;

            in_tests = true;
            x = j;
        }

        for (int j = 0; !in_tests && j < *__workshy_get_benchmark_amount(); j++) {
            if (strcmp(test_function_names[j], argv[i]) != 0)
                continue;

            x = j;
        }

        if (in_tests == false && x == -1) {
            fprintf(stderr, "[workshy_warn] Neither benchmark or test could be found with the name `%s`", argv[i]);
        } else if (in_tests == true) {
            __workshy_run_test(test_functions[x], test_function_names[x], x);
            break;
        } else {
            __workshy_run_bench(benchmark_functions[x], benchmark_function_names[x]);
            break;
        }
    }

    if (is_test) {
        __workshy_run_tests();
        return 0;
    }

    if (is_bench) {
        __workshy_run_benches();
        return 0;
    }
    
    return 0;
}