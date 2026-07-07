#pragma once

typedef struct FastaSeqs {
    unsigned int nseqs;
    char **headers;
    char **sequences;
} fasta_t;

char *read_single_line_input(const char *filename);
fasta_t *read_fasta(const char *filename);
