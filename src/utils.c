#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/* Return the (i, j) index of the maximum value in array_2d (caller frees). */
index_t *argmax(size_t m, size_t n, size_t **array_2d) {
    index_t *index = malloc(sizeof(index_t));
    if (!index) {
        perror("malloc");
        exit(1);
    }
    *index = (index_t){0, 0};

    size_t currmax = 0;
    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
            if (array_2d[i][j] >= currmax) {
                currmax = array_2d[i][j];
                index->i = i;
                index->j = j;
            }
        }
    }
    return index;
}

int compare_strlen(const void * a, const void * b) {
    const char *sa = *(char **)a;
    const char *sb = *(char **)b;
    return (int)strlen(sb) - (int)strlen(sa);
}
