#!/bin/bash

# Array of test file prefixes
tests=("k1" "k2" "k3" "k4" "k5" "k6" "k7" "k8")

# Compile the program with trees.c
gcc -o codifica codifica.c main.c trees.c

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Loop through each test file
for test in "${tests[@]}"; do
    # Check if the input text file exists
    if [ ! -f "${test}.txt" ]; then
        echo "Input file ${test}.txt does not exist"
        continue
    fi
    
    # Compress the text file to binary
    ./codifica "${test}.txt" "${test}.bin"
    
    # Check if the binary file was created
    if [ ! -f "${test}.bin" ]; then
        echo "Binary file ${test}.bin was not created"
        continue
    fi
    
    # Decompress the binary file back to text
    ./codifica "${test}.bin" "${test}.out.txt"
    
    # Check if the output text file was created
    if [ ! -f "${test}.out.txt" ]; then
        echo "Output file ${test}.out.txt was not created"
        continue
    fi
    
    # Generate hexdumps for generated binary files
    hexdump -C "${test}.bin" > "generated_${test}.bin.hex"
    
    # Generate hexdumps for reference binary files
    if [ ! -f "reference_${test}.bin" ]; then
        echo "Reference binary file reference_${test}.bin does not exist"
        continue
    fi
    
    hexdump -C "reference_${test}.bin" > "reference_${test}.bin.hex"
    
    # Compare hexdumps
    diff "generated_${test}.bin.hex" "reference_${test}.bin.hex"
    
    # Output the result of the comparison
    if [ $? -eq 0 ]; then
        echo "${test}: PASS"
    else
        echo "${test}: FAIL"
    fi
done
