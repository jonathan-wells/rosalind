#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *complement(const char *dna_string) {
    int seqlen = strlen(dna_string);
    char *complement_string = malloc(seqlen + 1);

    if (complement_string == NULL) {
        perror("Failed to malloc complement_string");
        exit(1);
    }

    for (size_t i = 0; i < seqlen; i++) {
        const char base = dna_string[i];
        switch (base) {
        case 'A':
            complement_string[i] = 'T';
            break;
        case 'C':
            complement_string[i] = 'G';
            break;
        case 'G':
            complement_string[i] = 'C';
            break;
        case 'T':
            complement_string[i] = 'A';
            break;
        default:
            fprintf(stderr, "Invalid base encountered: %c\n", base);
            exit(1);
        }
    }

    complement_string[seqlen] = '\0';
    return complement_string;
}

char *reverse(const char *dna_string) {
    int seqlen = strlen(dna_string);
    char *reverse_string = malloc(seqlen + 1);

    if (reverse_string == NULL) {
        perror("Failed to malloc reverse_string");
        exit(1);
    }

    int j = seqlen - 1;
    for (size_t i = 0; i < seqlen; i++) {
        reverse_string[i] = dna_string[j];
        j--;
    }

    reverse_string[seqlen] = '\0';
    return reverse_string;
}

char *reverse_complement(const char *dna_string) {
    char *complement_string = complement(dna_string);
    char *reverse_complement_string = reverse(complement_string);
    free(complement_string);
    return reverse_complement_string;
}
