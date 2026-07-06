#pragma once

typedef struct FastaSeq {
    char *header;
    char *sequence;
} fasta_t;

char *read_single_line_input(const char *filename);
char **read_fasta(const char *filename);
