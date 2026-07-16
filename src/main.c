#include <stdio.h>
#include <string.h>

#include "dna.h"
#include "rna.h"
#include "gc.h"
#include "iprb.h"
#include "revc.h"
#include "subs.h"
#include "grph.h"
#include "fib.h"


typedef struct {
    const char *puzzle;
    void (*run)(const char *filename);
} command_t;

static const command_t COMMAND[] = {
    { "dna", dna },
    { "rna", rna },
    { "revc", revc },
    { "gc", gc },
    { "subs", subs },
    { "grphs", grph },
    { "iprb", iprb },
    { "fib", fib }
};

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
