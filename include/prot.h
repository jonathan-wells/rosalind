#pragma once

typedef struct {
    char *codon;
    char *amino_acid;
} codontable_t;

void prot(const char *filename);
char *translate(const char *sequence);
