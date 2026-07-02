#include <stdio.h>

#include "dna.h"

int main() {
    basecount_t bases = calc_base_freqs("ACTG");
    printf("%d %d %d %d\n", bases.a, bases.c, bases.t, bases.g);

    return 0;
}
