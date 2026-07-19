#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/file_utils.h"
#include "../include/hamm.h"

void hamm(const char *filename) {
    char **seqs = read_multi_line_input(filename);
    size_t hdist = hamming_dist(seqs[0], seqs[1]);
    printf("%ld\n", hdist);
}

size_t hamming_dist(const char *seq1, const char *seq2) {
    size_t m = strlen(seq1);
    size_t n = strlen(seq2);
    if (m != n) {
        fprintf(stderr, "Sequence lengths must match: %ld != %ld\n", m, n);
        exit(1);
    }

    size_t hdist = 0;
    for (size_t i = 0; i < m; i++) {
        if (seq1[i] != seq2[i]) {
            hdist++;
        }
    }
    return hdist;
}
