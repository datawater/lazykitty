#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "workshy.h"
#include "register.h"
#include "console.h"
#include "run_utils.h"
#include "run.h"

// Dirty, dirty macros. they even leave artifacts
#define __fork_process_and_error_check(pid_variable_name_to_set) \
    int pid_variable_name_to_set = fork(); \
    if (pid_variable_name_to_set < 0) { \
        fprintf(stderr, "[workshy_err] Couldn't fork self.\n"); \
        abort(); \
    } \

#define run_function_in_another_process_without_args(function, pid_variable_name_to_set, result_type, result_name) \
    __fork_process_and_error_check(pid_variable_name_to_set) \
    result_type result_name; \
    if (pid_variable_name_to_set == 0) { \
        result_name = function(); \
    } \
    (void) a;

#define run_function_in_another_process_with_args(function, pid_variable_name_to_set, result_type, result_name, args...) \
    __fork_process_and_error_check(pid_variable_name_to_set) \
    result_type result_name; \
    if (pid_variable_name_to_set == 0) { \
        result_name = function(args); \
    } \
    (void) a;

int warm_up_bench(__workshy_benchmark_function_ptr function) {
    for (;;)
        function();

    return 0;
}

long double time_function(__workshy_benchmark_function_ptr function) {
    struct timespec start, end;
    long long seconds, nanoseconds;

    clock_gettime(CLOCK_MONOTONIC, &start);

    function();

    clock_gettime(CLOCK_MONOTONIC, &end);

    seconds = end.tv_sec - start.tv_sec;
    nanoseconds = end.tv_nsec - start.tv_nsec;

    if (nanoseconds < 0) {
        seconds -= 1;
        nanoseconds += 1000000000;
    }

    return seconds + nanoseconds * (long double) 1e-9;
}

// TODO: workshy: move to less platform-dependand code for timing, process forking, etc.
void __workshy_run_bench(__workshy_benchmark_function_ptr function, char* function_name) {
    (void) function; (void) function_name;

    printf(ANSI_COLOR_CYAN"[INFO]"ANSI_COLOR_RESET" started benchmarking function `%s`\n", function_name);
    printf("warming up for 2s...\n");
    fflush(stdout);
    
    __workshy_block_stdout();
    __workshy_block_stderr();

    run_function_in_another_process_with_args(warm_up_bench, pid, int, a, function);

    sleep(2);
    kill(pid, SIGKILL);
    wait(NULL);

    __workshy_unblock_stdout();

    printf("gathering %d samples...\n", __workshy_benchmark_samples_amount);

    long double* samples = malloc(sizeof(long double) * __workshy_benchmark_samples_amount);
    assert(samples != NULL && "[workshy_error] could't allocate memory for sample gathering.\n");
    memset(samples, 0, sizeof(long double) * __workshy_benchmark_samples_amount);

    // TODO: workshy: dynamically calculate __workshy_benchmark_samples_amount instead of using a static
    __workshy_block_stdout();
    for (int i = 0; i < __workshy_benchmark_samples_amount; i++) {
        samples[i] = time_function(function);
    }
    __workshy_unblock_stdout();

    // TODO: workshy: cache past results into a custom directory like `.__workshy_benches`. Compare current results to past ones. 
    // TODO: workshy: offer more analysis for samples
    long double average = 0.0f;
    for (int i = 0; i < __workshy_benchmark_samples_amount; i++)
        average += samples[i];

    average /= __workshy_benchmark_samples_amount;

    printf("average time taken: %Lfs\n\n", average);
}

void __workshy_run_benches() {
    int bench_amount = *__workshy_get_benchmark_amount();
    char** bench_function_name_list = __workshy_get_benchmark_function_names();
    __workshy_benchmark_function_ptr* bench_function_list = __workshy_get_benchmark_functions();

    printf(ANSI_COLOR_CYAN"[INFO]"ANSI_COLOR_RESET" Amount of benchmarks: %d\n\n", bench_amount);

    for (int i = 0; i < bench_amount; ++i)
        __workshy_run_bench(bench_function_list[i], bench_function_name_list[i]);
}