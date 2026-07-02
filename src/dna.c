#include <stdio.h>
#include <stdlib.h>

#include "dna.h"

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
            case ('T'):
                bases.t++;
                break;
            case ('G'):
                bases.g++;
                break;
            default:
                printf("Encountered invalid base %c\n", *current_base);
                exit(1);
        }
        current_base++;
    }

    return bases;
}
