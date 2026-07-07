#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "file_utils.h"

fasta_t *read_fasta(const char *filename) {
    struct stat st;
    stat(filename, &st);
    size_t fsize = st.st_size;

    FILE *fptr = fopen(filename, "r");
    if (!fptr) { perror("fopen"); exit(1); }

    size_t nseqs = 0;
    size_t nseqs_cap = 1;
    char **seq_ptrs = malloc(sizeof(char *));
    char **hdr_ptrs = malloc(sizeof(char *));
    if (!hdr_ptrs || !seq_ptrs) { perror("malloc"); exit(1); }

    char *line = NULL;
    size_t line_capacity = 0;
    ssize_t n;

    while ((n = getline(&line, &line_capacity, fptr)) != -1) {
        if (line[0] == '>') {
            // Think I have to take into account possiblity of long headers
            line[n - 1] = '\0';
            hdr_ptrs[nseqs] = line;
            nseqs++;

            if (nseqs >= nseqs_cap) {
                nseqs_cap *= 2;
                char **hdr_tmp = realloc(hdr_ptrs, nseqs_cap * sizeof(char *));
                char **seq_tmp = realloc(seq_ptrs, nseqs_cap * sizeof(char *));
                if (!hdr_tmp || !seq_tmp) { perror("realloc"); exit(1); }
                hdr_ptrs = hdr_tmp;
                seq_ptrs = seq_tmp;
            }
            printf("%ld, %s\n", n, line);
        } else {
            // TODO: Handle potentially very long seqs.
            continue;
        }
    }

    fasta_t *fasta_seqs = malloc(sizeof(fasta_t));
    *fasta_seqs = (fasta_t){
        .nseqs = nseqs,
        .headers = hdr_ptrs,
        .sequences = seq_ptrs
    };
    return fasta_seqs;
}

char *read_single_line_input(const char *filename) {
    struct stat st;
    stat(filename, &st);
    size_t fsize = st.st_size;

    char *buffer = malloc(fsize);
    if (!buffer) { perror("malloc"); exit(1); }

    FILE *fptr = fopen(filename, "r");
    if (!fptr) { perror("fopen"); exit(1); }

    if (fgets(buffer, fsize, fptr) == NULL) {
        fprintf(stderr, "File is empty or malformed.\n");
        exit(1);
    }

    buffer[strcspn(buffer, "\n")] = '\0';
    fclose(fptr);
    return buffer;
}
