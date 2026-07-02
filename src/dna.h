#pragma once

void load_dna(char *filename, char *buffer);

typedef struct BaseCount {
    int a;
    int c;
    int g;
    int t;
} basecount_t;

basecount_t calc_base_freqs(char *dnastring);
