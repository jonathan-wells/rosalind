#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/file_utils.h"
#include "../include/grph.h"

/**
 * @brief Checks for length k overlap between suffix of seq1 and prefix of seq2.
 *
 * This function takes all suffixes of seq1 and compares them to prefixes of
 * seq2, for all prefix-suffix pairs with length equal to k.
 *
 * @param seq1 The sequence from which suffixes will be compared.
 * @param seq2 The sequence from which prefixes will be compared.
 * @param k The length of suffixes and prefixes.
 */
bool has_overlap(const char *seq1, const char *seq2, unsigned int k) {
    if (strcmp(seq1, seq2) == 0) {
        return 0;
    }
    size_t m = strlen(seq1);
    const char *sfx = seq1 + m - k;
    if (strncmp(sfx, seq2, k) == 0) {
        return 1;
    }
    return 0;
}

overlap_graph_t *calc_overlap_graph(fasta_t *fasta_seqs, unsigned int k) {
    size_t array_size = 1;
    char ***array = malloc(array_size * sizeof(size_t));
    if (!array) {
        perror("malloc");
        exit(1);
    }

    overlap_graph_t *ograph = malloc(sizeof(overlap_graph_t));
    *ograph = (overlap_graph_t){.nedges = 0, .edges = array};
    if (!ograph) {
        perror("malloc");
        exit(1);
    }

    for (size_t i = 0; i < fasta_seqs->nseqs; i++) {
        for (size_t j = 0; j < fasta_seqs->nseqs; j++) {
            if (i == j) {
                continue;
            }
            bool overlap = has_overlap(fasta_seqs->sequences[i],
                                       fasta_seqs->sequences[j], k);
            if (!overlap) {
                continue;
            }

            if (ograph->nedges == array_size) {
                array_size *= 2;
                char ***tmp_array =
                    realloc(ograph->edges, array_size * sizeof(size_t));
                if (!tmp_array) {
                    perror("realloc");
                    exit(1);
                }
                ograph->edges = tmp_array;
            }

            char **edge = malloc(2 * sizeof(char *));
            if (!edge) {
                perror("malloc");
                exit(1);
            }
            edge[0] = fasta_seqs->headers[i];
            edge[1] = fasta_seqs->headers[j];
            ograph->edges[ograph->nedges] = edge;
            ograph->nedges++;
        }
    }
    return ograph;
}

void grph(const char *filename) {
    fasta_t *fasta_seqs = read_fasta(filename);
    size_t k = 3;
    overlap_graph_t *ograph = calc_overlap_graph(fasta_seqs, k);
    for (size_t i = 0; i < ograph->nedges; i++) {
        char *hdr1 = ograph->edges[i][0];
        char *hdr2 = ograph->edges[i][1];
        printf("%s %s\n", hdr1, hdr2);
    }
}
