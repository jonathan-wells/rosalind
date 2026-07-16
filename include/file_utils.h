#include <stdlib.h>

#pragma once

typedef struct FastaSeqs {
    size_t nseqs;
    char **headers;
    char **sequences;
} fasta_t;

fasta_t *read_fasta(const char *filename);
char *read_single_line_input(const char *filename);
char **read_multi_line_input(const char *filename);
