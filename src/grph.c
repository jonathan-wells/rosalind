#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "file_utils.h"

/**
 * @brief Checks for overlap between suffix of seq1 and prefix of seq2.
 *
 * This function takes all suffixes of seq1 and compares them to prefixes of
 * seq2, for all prefix-suffix pairs with length greater than or equal to k.
 *
 * @param seq1 The sequence from which suffixes will be compared.
 * @param seq2 The sequence from which prefixes will be compared.
 * @param k The minimum length of suffixes and prefixes.
 */
bool has_overlap(const char *seq1, const char *seq2, unsigned int k) {
    if (strcmp(seq1, seq2) == 0) { return 0; }
    size_t m = strlen(seq1);
    size_t i = 1;
    for (const char *p = seq1 + 1; *p != '\0'; p++) {
        if (i > m - k) { return 0; }
        // printf("%s\n%s\n%ld %ld\n\n", p, seq2, i, x);
        if (strncmp(p, seq2, m - i) == 0) {
            return 1;
        }
        i++;
    }
    return 0;
}
// 012345678
// AAAAGACGT
//      ACGTCTTTT

size_t **calc_overlap_graph(fasta_t *fasta_seqs, unsigned int k) {
    size_t array_size = 1;
    size_t **array = malloc(array_size * sizeof(size_t));
    if (!array) { perror("malloc"); exit(1); }

    size_t npairs = 0;
    array[0] = &npairs;  // First element stores the address of length of array
    for (size_t i = 0; i < fasta_seqs->nseqs; i++) {
        for (size_t j = 0; j < fasta_seqs->nseqs; j++) {
            if (i == j) { continue; }
            bool overlap = has_overlap(
                fasta_seqs->sequences[i],
                fasta_seqs->sequences[j],
                k
            );
            if (!overlap) {
                continue;
            }
            npairs++;

            if (*array[0] == array_size) {
                array_size *= 2;
                size_t **tmp_array = realloc(array, array_size * sizeof(size_t));
                if (!tmp_array) { perror("realloc"); exit(1); }
                array = tmp_array;
            }

            size_t *pair = malloc(2 * sizeof(size_t));
            if (!pair) { perror("malloc"); exit(1); }
            pair[0] = i;
            pair[1] = j;
            array[npairs] = pair;
        }
    }
    return array;
}
