#!/bin/bash
set -e

echo "[Compile] Building generators and solution..."
g++ -std=c++17 -O2 -pipe -static -s validator.cpp  -o validator
g++ -std=c++17 -O2 -pipe -static -s solution.cpp   -o solution
g++ -std=c++17 -O2 -pipe -static -s gen_sub1.cpp   -o gen_sub1
g++ -std=c++17 -O2 -pipe -static -s gen_sub2.cpp   -o gen_sub2
echo "[Compile] Done."

rm -rf tests
mkdir -p tests

gen_and_run() {
    local gen_bin=$1
    local type=$2
    local start=$3
    local end=$4

    for ((i=start; i<=end; i++)); do
        mkdir -p tests/test${i}
        ./${gen_bin} ${type} > tests/test${i}/input.in
        ./validator < tests/test${i}/input.in
        ./solution < tests/test${i}/input.in > tests/test${i}/output.out
        echo "[Gen] ${gen_bin} type=${type} -> test${i}"
    done
}

# Subtask 1 (20 tests)
echo "[Generate] Subtask 1"
gen_and_run gen_sub1 1  1 10
gen_and_run gen_sub1 2 11 14
gen_and_run gen_sub1 3 15 18
gen_and_run gen_sub1 4 19 20

# Subtask 2 (30 tests)
echo "[Generate] Subtask 2"
gen_and_run gen_sub2 1 21 30
gen_and_run gen_sub2 2 31 38
gen_and_run gen_sub2 3 39 45
gen_and_run gen_sub2 4 46 50

echo "✅ All test data generated successfully!"
