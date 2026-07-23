#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../include/file_utils.h"
#include "../include/utils.h"

fasta_t *read_fasta(const char *filename) {
    FILE *fptr = fopen(filename, "r");
    if (!fptr) {
        perror("fopen");
        exit(1);
    }

    // Following block allocates new memory for fasta data
    size_t nseqs_cap = 2;
    char **seq_ptrs = xmalloc(nseqs_cap * sizeof(char *));
    char **hdr_ptrs = xmalloc(nseqs_cap * sizeof(char *));

    fasta_t *fasta_seqs = xmalloc(sizeof(fasta_t));
    *fasta_seqs =
        (fasta_t){.nseqs = 0, .headers = hdr_ptrs, .sequences = seq_ptrs};

    char *line = NULL;
    size_t line_capacity;
    char *seq_buffer = NULL;
    ssize_t line_len;
    size_t nseq_lines;
    size_t total_length = 0;

    while ((line_len = getline(&line, &line_capacity, fptr)) != -1) {
        if (line[0] == '>') {
            // Chomp newlines and header arrow.
            line[line_len - 1] = '\0';
            for (size_t i = 1; i < line_len; i++) {
                line[i - 1] = line[i];
            }
            fasta_seqs->headers[fasta_seqs->nseqs] = strdup(line);
            (fasta_seqs->nseqs)++;

            if (fasta_seqs->nseqs >= nseqs_cap) {
                nseqs_cap *= 2;
                fasta_seqs->headers =
                    xrealloc(fasta_seqs->headers, nseqs_cap * sizeof(char *));
                fasta_seqs->sequences =
                    xrealloc(fasta_seqs->sequences, nseqs_cap * sizeof(char *));
            }

            // Reset sequence buffer at each new header
            seq_buffer = NULL;
            total_length = 0;
            nseq_lines = 1;

        } else {
            line[line_len - 1] = '\0';
            if (nseq_lines == 1) {
                total_length = line_len;
                seq_buffer = xmalloc(total_length);
                strcpy(seq_buffer, line);
            } else {
                total_length += line_len;
                seq_buffer = xrealloc(seq_buffer, total_length);
                strcat(seq_buffer, line);
            }

            fasta_seqs->sequences[fasta_seqs->nseqs - 1] = seq_buffer;
            nseq_lines++;
        }
    }

    free(line);
    fclose(fptr);

    return fasta_seqs;
}

char *read_single_line_input(const char *filename) {
    struct stat st;
    stat(filename, &st);
    size_t fsize = st.st_size;

    char *buffer = xmalloc(fsize);

    FILE *fptr = fopen(filename, "r");
    if (!fptr) {
        perror("fopen");
        exit(1);
    }

    if (fgets(buffer, fsize, fptr) == NULL) {
        fprintf(stderr, "File is empty or malformed.\n");
        exit(1);
    }

    buffer[strcspn(buffer, "\n")] = '\0';
    fclose(fptr);

    return buffer;
}

char **read_multi_line_input(const char *filename) {
    FILE *fptr = fopen(filename, "r");
    if (!fptr) {
        perror("fopen");
        exit(1);
    }

    size_t capacity = 1;
    char **line_ptrs = xmalloc(capacity * sizeof(char *));

    char *line = NULL;
    size_t _lcap;
    ssize_t line_len;

    size_t idx = 0;
    while ((line_len = getline(&line, &_lcap, fptr)) != -1) {
        if (idx >= capacity) {
            capacity *= 2;
            line_ptrs = xrealloc(line_ptrs, capacity * sizeof(char *));
        }
        line[line_len - 1] = '\0';
        line_ptrs[idx] = strdup(line);
        idx++;
    }

    free(line);
    fclose(fptr);

    return line_ptrs;
}
