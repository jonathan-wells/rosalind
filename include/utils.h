#pragma once

#include <stdlib.h>

typedef struct {
    size_t i;
    size_t j;
} index_t;

index_t *argmax(size_t m, size_t n, size_t **array_2d);
