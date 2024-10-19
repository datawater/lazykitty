#pragma once

static unsigned long long nth_fibonacci_number(int n) {
    unsigned long long a, b, c;
    a = 0;
    b = 1;
    c = 1;

    if (n == 0) return n;
    if (n == 1) return b;
    if (n == 2) return c;

    for (int i = 0; i < n - 1; i++) {
        c = a + b;
        a = b;
        b = c;
    }

    return c;
}