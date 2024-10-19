#include "benchmarks.h"
#include "fibonacci.h"

void benchmark_fibonacci(void) {
    WORKSHY_BLACK_BOX({
        volatile unsigned long long F = nth_fibonacci_number(67108864); 
    });
}