#include <stdbool.h>
// #include <stdlib.h>

#include "file_utils.h"

typedef struct OverlapGraph {
    size_t nedges;
    char ***edges;
} overlap_graph_t;

bool has_overlap(const char *seq1, const char *seq2, unsigned int k);
overlap_graph_t *calc_overlap_graph(fasta_t *fasta_seqs, unsigned int k);

void grph(const char *filename);
