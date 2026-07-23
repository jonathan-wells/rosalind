#include <stdio.h>
#include <stdlib.h>

#include "fib.h"
#include "file_utils.h"

size_t fibonacci_rabbits_recursive(size_t n, size_t k) {
    if (n <= 0) {
        return 0;
    } else if (n > 0 && n <= 2) {
        return 1;
    } else {
        return fibonacci_rabbits_recursive(n - 1, k) +
               fibonacci_rabbits_recursive(n - 2, k) * k;
    }
}

size_t fibonacci_rabbits_dp(size_t n, size_t k) {
    if (n <= 0) {
        return 0;
    } else if (n > 0 && n <= 2) {
        return 1;
    }
    size_t memo[2];
    memo[0] = 1;
    memo[1] = 1;
    for (size_t i = 2; i < n; i++) {
        size_t new = memo[0] * k + memo[1];
        memo[0] = memo[1];
        memo[1] = new;
    }
    return memo[1];
}

void fib(const char *filename) {
    size_t n;
    size_t k;
    char *input_str = read_single_line_input(filename);
    sscanf(input_str, "%zu %zu", &n, &k);
    size_t fib = fibonacci_rabbits_dp(n, k);
    printf("%zu\n", fib);
}
