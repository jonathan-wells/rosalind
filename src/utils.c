#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void *xmalloc(size_t size) {
    void *buffer = malloc(size);
    if (!buffer) {
        perror("malloc");
        exit(1);
    }
    return buffer;
}

void *xcalloc(size_t len, size_t size) {
    void *buffer = calloc(len, size);
    if (!buffer) {
        perror("calloc");
        exit(1);
    }
    return buffer;
}

void *xrealloc(void *ptr, size_t size) {
    void *buffer = realloc(ptr, size);
    if (!buffer) {
        perror("realloc");
        exit(1);
    }
    return buffer;
}

/* Return the (i, j) index of the maximum value in array_2d (caller frees). */
index_t *argmax(size_t m, size_t n, size_t **array_2d) {
    index_t *index = (index_t *)xmalloc(sizeof(index_t));
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

/* Return the length difference between two strings. */
int compare_strlen(const void * a, const void * b) {
    const char *sa = *(char **)a;
    const char *sb = *(char **)b;
    return (int)strlen(sb) - (int)strlen(sa);
}
