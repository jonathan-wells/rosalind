#pragma once

#include <stdlib.h>

void lcsm(const char *filename);

void lcsm_pair(const char *filename);
size_t **calc_lcs_pair(const char *seq1, const char *seq2);
char *traceback_pair(const char *seq1, const char *seq2, size_t **scores);
