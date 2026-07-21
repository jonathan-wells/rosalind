#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/file_utils.h"
#include "../include/lcsm.h"
#include "../include/revc.h"

/* Read two FASTA sequences and print their longest common substring. */
void lcsm(const char *filename) {
    fasta_t *seqs = read_fasta(filename);
    size_t **scores = calc_lcs(seqs->sequences[0], seqs->sequences[1]);
    char *lcs = traceback(seqs->sequences[0], seqs->sequences[1], scores);
    printf("%s\n", lcs);
}

/* Build the DP scores table of common-suffix lengths for seq1 and seq2. */
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

    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 1; j <= n; j++) {
            if (seq1[i - 1] == seq2[j - 1]) {
                scores[i][j] = scores[i - 1][j - 1] + 1;
            }
        }
    }

    return scores;
}

/* Recover the longest common substring from the DP scores table. */
char *traceback(const char *seq1, const char *seq2, size_t **scores) {
    size_t m = strlen(seq1);
    size_t n = strlen(seq2);
    index_t *index = argmax(m, n, scores);

    size_t i = index->i;
    size_t j = index->j;
    size_t lcs_len = scores[i][j];

    char *lcs = calloc(lcs_len + 1, 1);
    if (!lcs) {
        perror("calloc");
        exit(1);
    }

    while (scores[i][j] != 0) {
        lcs[lcs_len - 1] = seq1[i - 1];
        lcs_len--;
        i--;
        j--;
    }
    free(index);

    return reverse(lcs);
}

/* Return the (i, j) index of the maximum value in array_2d (caller frees). */
index_t *argmax(size_t m, size_t n, size_t **array_2d) {
    index_t *index = malloc(sizeof(index_t));
    if (!index) {
        perror("malloc");
        exit(1);
    }
    *index = (index_t){ 0, 0 };

    size_t currmax = 0;
    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
            if (array_2d[i][j] >= currmax) {
                currmax = array_2d[i][j];
                index->i = i;
                index->j = j;
            }
        }
    }
    return index;
}
