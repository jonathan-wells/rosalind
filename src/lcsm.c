#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/file_utils.h"
#include "../include/lcsm.h"

void lcsm(const char *filename) {
    fasta_t *seqs = read_fasta(filename);
    size_t **scores = calc_lcs(seqs->sequences[0], seqs->sequences[1]);
    char *lcs = traceback(seqs->sequences[0], seqs->sequences[1], scores);
    printf("%s\n", lcs);
}

size_t **calc_lcs(const char *seq1, const char *seq2) {
    size_t m = strlen(seq1);
    size_t n = strlen(seq2);
    size_t **scores = malloc((m + 1) * sizeof(size_t *));
    if (!scores) {
        perror("malloc");
        exit(1);
    }
    for (size_t i = 0; i <= m; i++) {
        scores[i] = calloc(n + 1, sizeof(size_t));
        if (!scores[i]) {
            perror("calloc");
            exit(1);
        }
    }

    return scores;
}

char *traceback(const char *seq1, const char *seq2, size_t **scores) {

}
