#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/cons.h"
#include "../include/file_utils.h"

void cons(const char *filename) {
    fasta_t *seqs = read_fasta(filename);
    profile_t *profile = build_profile(seqs);
    char *consensus = build_consensus(profile);
    printf("%s\n", consensus);

    char *bases = "ACGT\0";
    for (size_t i = 0; i < 4; i++) {
        printf("%c: ", bases[i]);
        for (size_t j = 0; j < profile->seqlen; j++) {
            printf("%ld ", profile->matrix[j][i]);
        }
        printf("\n");
    }
}

profile_t *build_profile(fasta_t *seqs) {
    size_t seqlen = strlen(seqs->sequences[0]);

    size_t **matrix = malloc(seqlen * sizeof(size_t *));
    if (!matrix) {
        perror("malloc");
        exit(1);
    }
    for (size_t j = 0; j < seqlen; j++) {
        matrix[j] = calloc(4, sizeof(size_t));
        if (!matrix[j]) {
            perror("calloc");
            exit(1);
        }
    }

    char *bases = "ACGT\0";
    for (size_t j = 0; j < seqlen; j++) {
        for (size_t i = 0; i < seqs->nseqs; i++) {
            for (size_t k = 0; k < 4; k++) {
                if (seqs->sequences[i][j] == bases[k]) {
                    matrix[j][k]++;
                }
            }
        }
    }

    profile_t *profile = malloc(sizeof(profile_t));
    if (!profile) {
        perror("malloc");
        exit(1);
    }
    *profile = (profile_t){seqlen, matrix};
    return profile;
}

size_t topbase(size_t *array) {
    char *bases = "ACGT\0";
    size_t curr_max = 0;
    size_t i_max = 0;

    for (int i = 0; i < 4; i++) {
        if (array[i] > curr_max) {
            curr_max = array[i];
            i_max = i;
        }
    }

    return bases[i_max];
}

char *build_consensus(profile_t *profile) {
    char *consensus_sequence = calloc(profile->seqlen + 1, 1);
    if (!consensus_sequence) {
        perror("calloc");
        exit(1);
    }

    for (size_t i = 0; i < profile->seqlen; i++) {
        consensus_sequence[i] = topbase(profile->matrix[i]);
    }
    return consensus_sequence;
}
