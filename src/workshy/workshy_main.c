#include <stdio.h>
#include <string.h>
#include "workshy.h"
#include "run.h"

void __workshy_run_help() {
    printf("workshy <command> [options]\n\n");
    
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

    bool is_help = strcmp(*argv, "-h") == 0 || strcmp(*argv, "--help") == 0 
                || strcmp(*argv, "help") == 0 || strcmp(*argv, "h") == 0;

    bool is_test = strcmp(*argv, "test") == 0 || strcmp(*argv, "t") == 0;
    bool is_bench = strcmp(*argv, "bench") == 0 || strcmp(*argv, "b") == 0 || strcmp(*argv, "benchmark") == 0;
    
    if (is_help) {
        __workshy_run_help();
        return 0;
    }

    if (is_test) {
        __workshy_run_tests();
        return 0;
    }

    if (is_bench) {
        __workshy_run_benches();
        return 0;
    }

    fprintf(stderr, "[workshy_fail] Unknown command line option: '%s'. Run `workshy --help` for help.\n", *argv);
    
    return 1;
}