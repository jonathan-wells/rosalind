#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "file_utils.h"

fasta_t *read_fasta(const char *filename) {
    FILE *fptr = fopen(filename, "r");
    if (!fptr) { perror("fopen"); exit(1); }

    // Following block allocates new memory for fasta data
    size_t nseqs_cap = 2;
    char **seq_ptrs = malloc(nseqs_cap * sizeof(char *));
    if (!seq_ptrs) { perror("malloc"); exit(1); }
    char **hdr_ptrs = malloc(nseqs_cap * sizeof(char *));
    if (!hdr_ptrs) { perror("malloc"); exit(1); }

    fasta_t *fasta_seqs = malloc(sizeof(fasta_t));
    *fasta_seqs = (fasta_t){
        .nseqs = 0,
        .headers = hdr_ptrs,
        .sequences = seq_ptrs
    };

    char *line = NULL;
    size_t line_capacity;
    char *seq_buffer = NULL;
    ssize_t line_len;
    size_t nseq_lines;
    size_t total_length = 0;

    while ((line_len = getline(&line, &line_capacity, fptr)) != -1) {
        if (line[0] == '>') {
            // Think I have to take into account possiblity of long headers
            line[line_len - 1] = '\0';  // To chomp newline
            fasta_seqs->headers[fasta_seqs->nseqs] = strdup(line);
            (fasta_seqs->nseqs)++;

            if (fasta_seqs->nseqs >= nseqs_cap) {
                nseqs_cap *= 2;
                char **hdr_tmp = realloc(fasta_seqs->headers, nseqs_cap * sizeof(char *));
                if (!hdr_tmp) { perror("realloc"); exit(1); }
                char **seq_tmp = realloc(fasta_seqs->sequences, nseqs_cap * sizeof(char *));
                if (!seq_tmp) { perror("realloc"); exit(1); }
                fasta_seqs->headers = hdr_tmp;
                fasta_seqs->sequences = seq_tmp;
            }

            // Reset sequence buffer at each new header
            seq_buffer = NULL;
            total_length = 0;
            nseq_lines = 1;

        } else {
            line[line_len - 1] = '\0';
            if (nseq_lines == 1) {
                total_length = line_len;
                seq_buffer = malloc(total_length);
                if (!seq_buffer) { perror("malloc"); exit(1); }
                strcpy(seq_buffer, line);
            } else {
                total_length += line_len;
                char *line_tmp = realloc(seq_buffer, total_length);
                if (!line_tmp) { perror("realloc"); exit(1); }
                seq_buffer = line_tmp;
                strcat(seq_buffer, line);
            }

            fasta_seqs->sequences[fasta_seqs->nseqs-1] = seq_buffer;
            nseq_lines++;
        }
    }
    free(line);

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
