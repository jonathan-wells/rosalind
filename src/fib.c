#include <stdlib.h>
#include <stdio.h>

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
