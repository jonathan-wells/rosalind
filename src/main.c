#include <stdio.h>
#include <string.h>

#include "../include/dna.h"
#include "../include/fib.h"
#include "../include/gc.h"
#include "../include/grph.h"
#include "../include/iprb.h"
#include "../include/prot.h"
#include "../include/revc.h"
#include "../include/rna.h"
#include "../include/subs.h"

typedef struct {
    const char *puzzle;
    void (*run)(const char *filename);
} command_t;

static const command_t COMMAND[] = {
    {"dna", dna},    {"rna", rna},   {"revc", revc},
    {"gc", gc},      {"prot", prot}, {"subs", subs},
    {"grphs", grph}, {"iprb", iprb}, {"fib", fib}};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Incorrect number of arguments: 2 != %d.\n", argc);
        return 1;
    }

    const char *puzzle = argv[1];
    const char *filename = argv[2];

    size_t ncommands = sizeof(COMMAND) / sizeof(COMMAND[0]);
    for (size_t i = 0; i < ncommands; i++) {
        if (strcmp(puzzle, COMMAND[i].puzzle) == 0) {
            COMMAND[i].run(filename);
            return 0;
        }
    }

    fprintf(stderr, "Puzzle name not recognized: \"%s\".\n", puzzle);
    return 1;
}
