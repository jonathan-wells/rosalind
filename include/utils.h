#pragma once

#include <stdlib.h>

typedef struct {
    size_t i;
    size_t j;
} index_t;

void *xmalloc(size_t size);
void *xcalloc(size_t len, size_t size);
void *xrealloc(void *ptr, size_t size);
index_t *argmax(size_t m, size_t n, size_t **array_2d);
int compare_strlen(const void * a, const void * b);
