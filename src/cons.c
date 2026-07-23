#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cons.h"
#include "file_utils.h"
#include "utils.h"

void cons(const char *filename) {
    fasta_t *seqs = read_fasta(filename);
    profile_t *profile = build_profile(seqs);
    char *consensus = build_consensus(profile);
    printf("%s\n", consensus);

    char *bases = "ACGT\0";
    for (size_t i = 0; i < 4; i++) {
        printf("%c: ", bases[i]);
        for (size_t j = 0; j < profile->seqlen; j++) {
            // This extra if-else strips trailing whitespace to ensure exact
            // match to sample output.
            if (j == profile->seqlen - 1) {
                printf("%ld\n", profile->matrix[j][i]);
            } else {
                printf("%ld ", profile->matrix[j][i]);
            }
        }
    }
}

profile_t *build_profile(fasta_t *seqs) {
    size_t seqlen = strlen(seqs->sequences[0]);

    size_t **matrix = xmalloc(seqlen * sizeof(size_t *));
    for (size_t j = 0; j < seqlen; j++) {
        matrix[j] = xcalloc(4, sizeof(size_t));
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

    profile_t *profile = xmalloc(sizeof(profile_t));
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
    char *consensus_sequence = xcalloc(profile->seqlen + 1, 1);

    for (size_t i = 0; i < profile->seqlen; i++) {
        consensus_sequence[i] = topbase(profile->matrix[i]);
    }
    return consensus_sequence;
}
