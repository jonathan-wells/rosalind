#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "subs.h"

size_t *find_substrings(const char *substring, const char *string) {
    size_t array_size = 1;
    size_t *array = malloc(array_size * sizeof(size_t));
    if (!array) { perror("malloc"); exit(1); }

    size_t m = strlen(substring); size_t n = strlen(string);
    size_t i = 0; size_t j = 1;

    // Tracks the number of matches and returns if len sub > string
    array[0] = 0;
    if (m == 0 || m > n) { return array; }

    for (const char *p = string; *p != '\0'; p++) {
        if (i > n - m) {
            break;
        }

        if (strncmp(p, substring, m) == 0) {
            // First check if array capacity needs to grow
            if (j == array_size) {
                array_size *= 2;
                size_t *tmp_array = realloc(array, array_size * sizeof(size_t));
                if (!tmp_array) { perror("realloc"); exit(1); }
                array = tmp_array;
            }

            array[j] = i + 1;
            array[0]++;
            j++;
        }
        i++;
    }

    // Free excess array capacity
    size_t *tmp_array = realloc(array, (array[0] + 1) * sizeof(size_t));
    if (!tmp_array) { perror("realloc"); exit(1); }
    array = tmp_array;

    return array;
}
