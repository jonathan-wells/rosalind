#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dna.h"
#include "rna.h"
#include "revc.h"
// #include "gc.h"

void read_single_line_input(const char *filename, char *buffer) {
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        fprintf(stderr, "Not able to open file %s.\n", filename);
        exit(1);
    }

    if (fgets(buffer, MAX_DNA_LEN, fptr) == NULL) {
        fprintf(stderr, "File is empty or unreadable.\n");
        exit(1);
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    fclose(fptr);
}

void dna(char *filename) {
    char dna_string[MAX_DNA_LEN];
    read_single_line_input(filename, dna_string);

    basecount_t bases = calc_base_freqs(dna_string);
    printf("%d %d %d %d\n", bases.a, bases.c, bases.g, bases.t);
}

void rna(char *filename) {
    char dna_string[MAX_DNA_LEN];
    read_single_line_input(filename, dna_string);

    char *rna_string = transcribe(dna_string);
    printf("%s\n", rna_string);
}

void revc(char *filename) {
    char dna_string[MAX_DNA_LEN];
    read_single_line_input(filename, dna_string);

    char *reverse_complement_string = reverse_complement(dna_string);
    printf("%s\n", reverse_complement_string);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Incorrect number of arguments: 2 != %d.\n", argc);
        return 1;
    }
    revc(argv[1]);
    return 0;
}
