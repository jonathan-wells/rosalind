#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/file_utils.h"
#include "../include/utils.h"
#include "../include/lcsm.h"
#include "../include/revc.h"
#include "../include/grph.h"

void lcsm(const char *filename) {
    fasta_t *seqs = read_fasta(filename);
    char **subs = generate_substrings(seqs->sequences[0]);

    size_t n = strlen(seqs->sequences[0]);
    size_t nsubs = (n * (n + 1)) / 2;

    for (size_t i = 0; i < nsubs; i++) {
        size_t count = 0;
        for (size_t j = 0; j < seqs->nseqs; j++) {
            if (strstr(seqs->sequences[j], subs[i]) != NULL) {
                count++;
            }
        }
        if (count == seqs->nseqs) {
            printf("%s\n", subs[i]);
            exit(0);
        }
    }
}

char **_substrings_helper(
    const char *seq,
    char **substrings,
    size_t seqlen,
    size_t substrings_idx
) {
    if (seq[0] == '\0') {
        return substrings;
    }

    size_t i = seqlen;
    while (i >= 1) {
        char *sub = malloc(seqlen + 1);
        strcpy(sub, seq);
        sub[i] = '\0';
        substrings[substrings_idx] = sub;
        i--;
        substrings_idx++;
    }

    return _substrings_helper( ++seq, substrings, --seqlen, substrings_idx);
}

char **generate_substrings(const char *seq) {
    size_t n = strlen(seq);
    size_t nsubstrings = (n * (n + 1)) / 2;

    char **substrings = malloc(nsubstrings * sizeof(char *));
    if (!substrings) {
        perror("malloc");
        exit(1);
    }

    _substrings_helper(seq, substrings, n, 0);
    qsort(substrings, nsubstrings, sizeof(char *), compare_strlen);
    return substrings;
}


/* Read two FASTA sequences and print their longest common substring.
 * Including this because I misread the problem and spent 30 mins solving the
 * problem for a pair of sequences, rather than a set of k seqs. */
void lcsm_pair(const char *filename) {
    fasta_t *seqs = read_fasta(filename);
    size_t **scores = calc_lcs_pair(seqs->sequences[0], seqs->sequences[1]);
    char *lcs = traceback_pair(seqs->sequences[0], seqs->sequences[1], scores);
    printf("%s\n", lcs);
}

/* Build the DP scores table of common-suffix lengths for seq1 and seq2. */
size_t **calc_lcs_pair(const char *seq1, const char *seq2) {
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
char *traceback_pair(const char *seq1, const char *seq2, size_t **scores) {
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
