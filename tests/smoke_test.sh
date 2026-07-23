#!/usr/bin/env bash
declare -a puzzles=(
    dna
    rna
    revc
    iprb
    fib
    gc
    prot
    subs
    hamm
    grph
    cons
    lcsm
)
for p in ${puzzles[@]}; do
    diffline=$(
        diff \
        --ignore-blank-lines \
        --ignore-space-change \
        <(bin/rosalind $p "data/sample/${p}_in.txt") \
        "data/sample/${p}_out.txt"
    )

    return_code=$?
    if [[ $return_code -eq 1 ]]; then
        echo "Failed puzzle: ${p}"
        echo "${diffline}"
        exit 1
    fi
done
echo "Passed"
