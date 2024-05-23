#!/bin/bash

# Compile the code
gcc -o codifica codifica.c main.c

# Define arrays of test files
texts=("k1" "k2" "k3" "k4" "k5" "k6" "k7" "k8")

# Run compression and generate hex dumps
for t in "${texts[@]}"; do
    ./codifica "${t}.txt" "${t}.bin"
    hexdump -C "${t}.bin" > "generated_${t}.bin.hex"
    hexdump -C "${t}.bin" > "reference_${t}.bin.hex"
done

# Compare hex dumps
for t in "${texts[@]}"; do
    echo "Comparing ${t}..."
    diff "generated_${t}.bin.hex" "reference_${t}.bin.hex"
done
