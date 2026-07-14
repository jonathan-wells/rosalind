#include <stdio.h>
#include <string.h>

#include "file_utils.h"
#include "dna.h"
#include "rna.h"
#include "gc.h"
#include "iprb.h"
#include "revc.h"
#include "subs.h"
#include "grph.h"
#include "fib.h"

void dna(const char *filename) {
    char *dna_string = read_single_line_input(filename);
    basecount_t bases = calc_base_freqs(dna_string);
    printf("%d %d %d %d\n", bases.a, bases.c, bases.g, bases.t);
}

void rna(const char *filename) {
    char *dna_string = read_single_line_input(filename);
    char *rna_string = transcribe(dna_string);
    printf("%s\n", rna_string);
}

void revc(const char *filename) {
    char *dna_string = read_single_line_input(filename);
    char *reverse_complement_string = reverse_complement(dna_string);
    printf("%s\n", reverse_complement_string);
}

void gc(const char *filename) {
    fasta_t *fasta_seqs = read_fasta(filename);
    size_t top_gc_idx = gc_argmax(fasta_seqs);
    float gc_content = calc_gc_content(fasta_seqs->sequences[top_gc_idx]);
    printf("%s\n%f\n", fasta_seqs->headers[top_gc_idx], gc_content);
}

void subs(const char *filename) {
    char **seqs = read_multi_line_input(filename);
    size_t *matches = find_substrings(seqs[1], seqs[0]);
    size_t nmatches = matches[0];
    for (size_t i = 1; i <= nmatches; i++) {
        printf("%ld ", matches[i]);
    }
    printf("\n");
}

void grph(const char *filename) {
    fasta_t *fasta_seqs = read_fasta(filename);
    size_t k = 3;
    overlap_graph_t *ograph = calc_overlap_graph(fasta_seqs, k);
    for (size_t i = 0; i < ograph->nedges; i++) {
        char *hdr1 = ograph->edges[i][0];
        char *hdr2 = ograph->edges[i][1];
        printf("%s %s\n", hdr1, hdr2);
    }
}

void iprb(const char *filename) {
    int k; int m; int n;
    char* input_str = read_single_line_input(filename);
    sscanf(input_str, "%d %d %d", &k, &m, &n);
    double p_dom_phenotype = prob_dominant_phenotype(k, m, n);
    printf("%f\n", p_dom_phenotype);
}

void fib(const char *filename) {
    size_t n; size_t k;
    char* input_str = read_single_line_input(filename);
    sscanf(input_str, "%ld %ld", &n, &k);
    size_t fib = fibonacci_rabbits_recursive(n, k);
    printf("%ld\n", fib);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Incorrect number of arguments: 2 != %d.\n", argc);
        return 1;
    }
    fib(argv[1]);
    return 0;
}
