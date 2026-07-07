#include <stdlib.h>

#pragma once

typedef struct FastaSeqs {
    size_t nseqs;
    char **headers;
    char **sequences;
} fasta_t;

char *read_single_line_input(const char *filename);
fasta_t *read_fasta(const char *filename);
