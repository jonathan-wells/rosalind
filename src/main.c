#include <stdio.h>

#include "file_utils.h"
#include "dna.h"
#include "rna.h"
#include "revc.h"
#include "gc.h"

void dna(char *filename) {
    char *dna_string = read_single_line_input(filename);
    basecount_t bases = calc_base_freqs(dna_string);
    printf("%d %d %d %d\n", bases.a, bases.c, bases.g, bases.t);
}

void rna(char *filename) {
    char *dna_string = read_single_line_input(filename);
    char *rna_string = transcribe(dna_string);
    printf("%s\n", rna_string);
}

void revc(char *filename) {
    char *dna_string = read_single_line_input(filename);
    char *reverse_complement_string = reverse_complement(dna_string);
    printf("%s\n", reverse_complement_string);
}

void gc(char *filename) {
    fasta_t *fasta_seqs = read_fasta(filename);
    size_t top_gc_idx = gc_argmax(fasta_seqs);
    float gc_content = calc_gc_content(fasta_seqs->sequences[top_gc_idx]);
    printf("%s\n%f\n", fasta_seqs->headers[top_gc_idx], gc_content);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Incorrect number of arguments: 2 != %d.\n", argc);
        return 1;
    }
    gc(argv[1]);
    return 0;
}
