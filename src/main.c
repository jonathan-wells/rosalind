#include <stdio.h>

#include "dna.h"
// #include "rna.h"

void dna(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Incorrect number of arguments.\n");
        return;
    }

    char dnastring[MAX_DNA_LEN];
    load_dna(argv[1], dnastring);

    basecount_t bases = calc_base_freqs(dnastring);
    printf("%d %d %d %d\n", bases.a, bases.c, bases.g, bases.t);
}

int main(int argc, char *argv[]) {
    dna(argc, argv);
    return 0;
}
