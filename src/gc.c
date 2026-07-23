#include <stdio.h>
#include <string.h>

#include "gc.h"

float calc_gc_content(char *sequence) {
    unsigned int seqlen = strlen(sequence);
    unsigned int gc_count = 0;

    char *curr_base = sequence;
    while (*curr_base != '\0') {
        if (*curr_base == 'C' || *curr_base == 'G') {
            gc_count++;
        }
        curr_base++;
    }

    return 100.0 * (float)gc_count / (float)seqlen;
}

size_t gc_argmax(fasta_t *fasta_sequences) {
    float curr_max_gc = 0.0;
    size_t curr_max_i = 0;
    for (size_t i = 0; i < fasta_sequences->nseqs; i++) {
        float gc_freq = calc_gc_content(fasta_sequences->sequences[i]);
        if (gc_freq > curr_max_gc) {
            curr_max_gc = gc_freq;
            curr_max_i = i;
        }
    }
    return curr_max_i;
}

void gc(const char *filename) {
    fasta_t *fasta_seqs = read_fasta(filename);
    size_t top_gc_idx = gc_argmax(fasta_seqs);
    float gc_content = calc_gc_content(fasta_seqs->sequences[top_gc_idx]);
    printf("%s\n%f\n", fasta_seqs->headers[top_gc_idx], gc_content);
}
