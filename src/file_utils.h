#pragma once

typedef struct FastaSeq {
    char *header;
    char *sequence;
} fasta_t;

void read_single_line_input(const char *filename, char *buffer);
void read_fasta(const char *filename, char *buffer);
