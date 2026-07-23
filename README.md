# Rosalind puzzles
[![Smoke Test](https://github.com/jonathan-wells/rosalind/actions/workflows/meson_test.yaml/badge.svg)](https://github.com/jonathan-wells/rosalind/actions/workflows/meson_test.yaml)

[Rosalind](https://rosalind.info/) is an excellent resource for learning how to
implement algorithms on strings, trees, and graphs - you can think of it as
LeetCode for computational biology. Like LeetCode, solving puzzles in Rosalind
is neither necessary nor sufficient to become a successful computational
biologist, but it will deepen your understanding and provide you with practical
intuition into how some of the most important tools in genomics work under the
hood.

It is also a great way to learn a new language or brush off old skills. In this
run, I am targeting the puzzle [Linguistic Complexity of a
Genome](https://rosalind.info/ling), and solving puzzles in C.

### Install
```
meson setup build --prefix=$PWD
meson install -C build
```

### Usage
```
# <command> is a lower-case puzzle name, e.g. "dna".
bin/rosalind <command> <input_data>
```

### Progress

- [x] DNA
- [x] RNA
- [x] REVC
- [x] IPRB
- [x] FIB
- [x] GC
- [x] PROT
- [x] SUBS
- [x] HAMM
- [x] GRPH
- [x] CONS
- [x] LCSM
- [ ] TREE
- [ ] PROB
- [ ] INOD
- [ ] KMP
- [ ] TRIE
- [ ] LREP
- [ ] SUFF
- [ ] LING
