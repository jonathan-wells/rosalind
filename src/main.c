#include <stdio.h>
#include <string.h>

#include "cons.h"
#include "dna.h"
#include "fib.h"
#include "gc.h"
#include "grph.h"
#include "hamm.h"
#include "iprb.h"
#include "lcsm.h"
#include "prot.h"
#include "revc.h"
#include "rna.h"
#include "subs.h"

typedef struct {
    const char *puzzle;
    void (*run)(const char *filename);
} command_t;

static const command_t COMMAND[] = {
    {"dna", dna},   {"rna", rna},   {"revc", revc}, {"iprb", iprb},
    {"fib", fib},   {"gc", gc},     {"prot", prot}, {"subs", subs},
    {"hamm", hamm}, {"grph", grph}, {"cons", cons}, {"lcsm", lcsm}};

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
