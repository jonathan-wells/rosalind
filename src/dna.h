#pragma once

#define MAX_DNA_LEN 1000

void load_dna(const char *filename, char *buffer);

typedef struct BaseCount {
    int a;
    int c;
    int g;
    int t;
} basecount_t;

basecount_t calc_base_freqs(char *dnastring);
