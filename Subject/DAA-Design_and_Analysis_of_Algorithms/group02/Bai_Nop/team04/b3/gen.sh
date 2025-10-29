#!/bin/bash
set -e

base_seed=${1:-2024}
echo "[Info] Base seed = ${base_seed}"

echo "[Compile] Building generators and reference solution..."
g++ -std=c++17 -O2 -pipe -static -s gen.cpp        -o gen
g++ -std=c++17 -O2 -pipe -static -s validator.cpp  -o validator
g++ -std=c++17 -O2 -pipe -static -s solution.cpp   -o solution
echo "[Compile] Done."

rm -rf tests
mkdir -p tests

total_tests=100
pad_width=${#total_tests}

generate() {
    local gen_bin=$1
    local type=$2
    local start=$3
    local end=$4
    for ((i=start; i<=end; ++i)); do
        local test_name
        printf -v test_name "test%0${pad_width}d" "$i"
        mkdir -p "tests/${test_name}"
        local seed=$((base_seed + i))
        "./${gen_bin}" "${type}" "${seed}" > "tests/${test_name}/input.in"
        ./validator < "tests/${test_name}/input.in" > /dev/null
        ./solution < "tests/${test_name}/input.in" > "tests/${test_name}/output.out"
        echo "[Gen] ${gen_bin} type=${type} seed=${seed} -> ${test_name}"
    done
}

echo "[Generate] Hamilton path cases"
generate gen 0  1 20  # random Hamiltonian
generate gen 1 21 30  # disconnected
generate gen 2 31 40  # clique
generate gen 3 41 50  # greedy trap
generate gen 4 51 60  # star / no Hamilton
generate gen 5 61 70  # edge cases small n
generate gen 6 71 80  # bfs trap random
generate gen 7 81 85  # bfs heavy chain
generate gen 8 86 90  # bfs random heavy
generate gen 9 91 100 # dense no Hamilton

echo "✅ Generated ${total_tests} tests with base seed ${base_seed}"
