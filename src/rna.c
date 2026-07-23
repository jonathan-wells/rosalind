#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/file_utils.h"
#include "../include/rna.h"
#include "../include/utils.h"

char *transcribe(const char *dna_string) {
    size_t seqlen = strlen(dna_string);
    char *rna_string = xmalloc(seqlen + 1);

    for (size_t i = 0; i < seqlen; i++) {
        char base = dna_string[i];
        if (base == 'A' || base == 'C' || base == 'G') {
            rna_string[i] = base;
        } else if (base == 'T') {
            rna_string[i] = 'U';
        } else {
            fprintf(stderr, "Encountered invalid base %c\n", base);
            exit(1);
        }
    }

    rna_string[seqlen] = '\0';
    return rna_string;
}

void rna(const char *filename) {
    char *dna_string = read_single_line_input(filename);
    char *rna_string = transcribe(dna_string);
    printf("%s\n", rna_string);
}
