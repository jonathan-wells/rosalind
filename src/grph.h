#include <stdlib.h>
#include <stdbool.h>

#include "file_utils.h"

bool has_overlap(const char *seq1, const char *seq2, unsigned int k);
size_t **calc_overlap_graph(fasta_t *fasta_seqs, unsigned int k);
