#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"
#include "subs.h"
#include "utils.h"

size_t *find_substrings(const char *substring, const char *string) {
    size_t array_size = 1;
    size_t *array = xmalloc(array_size * sizeof(size_t));

    size_t m = strlen(substring);
    size_t n = strlen(string);
    size_t i = 0;
    size_t j = 1;

    // Tracks the number of matches and returns if len sub > string
    array[0] = 0;
    if (m == 0 || m > n) {
        return array;
    }

    for (const char *p = string; *p != '\0'; p++) {
        if (i > n - m) {
            break;
        }

        if (strncmp(p, substring, m) == 0) {
            // First check if array capacity needs to grow
            if (j == array_size) {
                array_size *= 2;
                array = xrealloc(array, array_size * sizeof(size_t));
            }

            array[j] = i + 1;
            array[0]++;
            j++;
        }
        i++;
    }

    // Free excess array capacity
    array = xrealloc(array, (array[0] + 1) * sizeof(size_t));

    return array;
}

void subs(const char *filename) {
    char **seqs = read_multi_line_input(filename);
    size_t *matches = find_substrings(seqs[1], seqs[0]);
    size_t nmatches = matches[0];
    for (size_t i = 1; i <= nmatches; i++) {
        printf("%zu ", matches[i]);
    }
    printf("\n");
}
