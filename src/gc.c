#include <stdio.h>
#include <string.h>
#include "gc.h"

float calc_gc_content(char *sequence) {
    unsigned int seqlen = strlen(sequence);
    unsigned int gc_count = 0;

    char *curr_base = sequence;
    while (*curr_base != '\0') {
        if (*curr_base == 'C' || *curr_base == 'G') {
            gc_count++;
        }
        curr_base++;
    }

    return (float)gc_count / (float)seqlen;
}
