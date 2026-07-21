#pragma once

#include <stdlib.h>

typedef struct {
    size_t i;
    size_t j;
} index_t;

void lcsm(const char *filename);
size_t **calc_lcs(const char *seq1, const char *seq2);
char *traceback(const char *seq1, const char *seq2, size_t **scores);
index_t *argmax(size_t m, size_t n, size_t **array_2d);
