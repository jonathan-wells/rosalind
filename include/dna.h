#pragma once

void load_dna(const char *filename, char *buffer);

typedef struct BaseCount {
    int a;
    int c;
    int g;
    int t;
} basecount_t;

basecount_t calc_base_freqs(char *dnastring);

void dna(const char *filename);
