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
