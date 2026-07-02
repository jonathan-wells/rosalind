#pragma once

typedef struct BaseCount {
    int a;
    int c;
    int t;
    int g;
} basecount_t;

basecount_t calc_base_freqs(char *dnastring);
