#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dna.h"

void load_dna(char *filename, char *buffer) {
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Not able to open the file.");
    }

    fgets(buffer, 1000, fptr);
    buffer[strcspn(buffer, "\n")] = '\0';
    fclose(fptr);
}

basecount_t calc_base_freqs(char *dnastring) {
    basecount_t bases = {0};

    const char *current_base = dnastring;

    while (*current_base != '\0') {
        switch (*current_base) {
            case ('A'):
                bases.a++;
                break;
            case ('C'):
                bases.c++;
                break;
            case ('G'):
                bases.g++;
                break;
            case ('T'):
                bases.t++;
                break;
            default:
                printf("Encountered invalid base %c\n", *current_base);
                exit(1);
        }
        current_base++;
    }

    return bases;
}
