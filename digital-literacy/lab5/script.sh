# !/bin/bash

Benchmark() {
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "Flags and source:"
    echo $1
    g++ -Wall -O3 $1

    echo "Time:"
    time ./a.out

    echo "Size of executable on disk (in Bytes):"
    du -b ./a.out
}

if [[ $# -eq 1 ]]; then
    source=$1
    declare -a flags=(
        # "-O0"
        # "-Os"
        # "-O1"
        # "-O2"
        # "-O3"
        # "-O2 -march=native"
        # "-O3 -march=native"
        # "-O2 -march=native -funroll-loops"
        # "-O3 -march=native -funroll-loops"
        "-fipa-cp"
        "-fipa-cp-clone"
        "-fipa-bit-cp"
        "-fipa-vrp"
        "-fipa-pta"
        "-fipa-profile"
        "-fipa-pure-const"
        "-fipa-reference"
        "-fipa-reference-addressable"
        "-fipa-stack-alignment"
        "-fipa-icf"

        "-fprofile-generate"
        "-fprofile-use"
    )

    for f in "${flags[@]}"; do
        Benchmark "$f $source"
    done
fi
