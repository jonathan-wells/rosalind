#include <stdio.h>

#include "dna.h"

int main(int argc, char *argv[]) {

    char dnastring[1000];
    load_dna(argv[1], dnastring);

    basecount_t bases = calc_base_freqs(dnastring);
    printf("%d %d %d %d\n", bases.a, bases.c, bases.g, bases.t);

    return 0;
}
