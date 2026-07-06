#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>


typedef struct FastaSeq {
    char *header;
    char *sequence;
} fasta_t;

void read_fasta(const char *filename) {}

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
