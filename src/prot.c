#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"
#include "prot.h"
#include "utils.h"

static const codontable_t CODONS[64] = {
    {"UUU", "F"}, {"CUU", "L"}, {"AUU", "I"}, {"GUU", "V"}, {"UUC", "F"},
    {"CUC", "L"}, {"AUC", "I"}, {"GUC", "V"}, {"UUA", "L"}, {"CUA", "L"},
    {"AUA", "I"}, {"GUA", "V"}, {"UUG", "L"}, {"CUG", "L"}, {"AUG", "M"},
    {"GUG", "V"}, {"UCU", "S"}, {"CCU", "P"}, {"ACU", "T"}, {"GCU", "A"},
    {"UCC", "S"}, {"CCC", "P"}, {"ACC", "T"}, {"GCC", "A"}, {"UCA", "S"},
    {"CCA", "P"}, {"ACA", "T"}, {"GCA", "A"}, {"UCG", "S"}, {"CCG", "P"},
    {"ACG", "T"}, {"GCG", "A"}, {"UAU", "Y"}, {"CAU", "H"}, {"AAU", "N"},
    {"GAU", "D"}, {"UAC", "Y"}, {"CAC", "H"}, {"AAC", "N"}, {"GAC", "D"},
    {"UAA", "*"}, {"CAA", "Q"}, {"AAA", "K"}, {"GAA", "E"}, {"UAG", "*"},
    {"CAG", "Q"}, {"AAG", "K"}, {"GAG", "E"}, {"UGU", "C"}, {"CGU", "R"},
    {"AGU", "S"}, {"GGU", "G"}, {"UGC", "C"}, {"CGC", "R"}, {"AGC", "S"},
    {"GGC", "G"}, {"UGA", "*"}, {"CGA", "R"}, {"AGA", "R"}, {"GGA", "G"},
    {"UGG", "W"}, {"CGG", "R"}, {"AGG", "R"}, {"GGG", "G"}};

void prot(const char *filename) {
    char *seq = read_single_line_input(filename);
    char *protseq = translate(seq);
    printf("%s\n", protseq);
    free(seq);
    free(protseq);
}

char *translate(const char *sequence) {
    size_t seqlen = strlen(sequence);
    char *protseq = xcalloc(seqlen / 3 + 1, 1);
    char codon[4];
    codon[3] = '\0';
    strncpy(codon, sequence, 3);

    for (size_t i = 0; i < seqlen - 3; i += 3) {
        for (size_t j = 0; j < 64; j++) {
            if (strcmp(CODONS[j].codon, codon) == 0) {
                strcat(protseq, CODONS[j].amino_acid);
                break;
            }
        }
        sequence += 3;
        strncpy(codon, sequence, 3);
    }

    // Chomp the stop codon "*"
    protseq[seqlen / 3 - 1] = '\0';
    return protseq;
}
