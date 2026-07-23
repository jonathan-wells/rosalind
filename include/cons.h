#pragma once

#include <stdlib.h>

#include "file_utils.h"

typedef struct {
    size_t seqlen;
    size_t **matrix;
} profile_t;

void cons(const char *filename);
profile_t *build_profile(fasta_t *seqs);
char *build_consensus(profile_t *profile);
size_t topbase(size_t *array);
char *consensus(fasta_t *seqs);
