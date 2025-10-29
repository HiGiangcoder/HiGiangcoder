#!/bin/bash
set -e

base_seed=${1:-2024}
echo "[Info] Base seed = ${base_seed}"

echo "[Compile] Building generators, validator, and solution..."
# Nhớ thay g++-15 bằng phiên bản của bạn và thêm cờ cho macOS nếu cần
COMPILER="g++"
FLAGS="-std=c++17 -O2 -pipe -s -Wl,-rpath,/opt/homebrew/lib"

$COMPILER $FLAGS validator.cpp  -o validator
$COMPILER $FLAGS solution.cpp   -o solution
$COMPILER $FLAGS gen_sub1.cpp   -o gen_sub1
$COMPILER $FLAGS gen_sub2.cpp   -o gen_sub2
$COMPILER $FLAGS gen_sub3.cpp   -o gen_sub3
echo "[Compile] Done."

rm -rf tests
mkdir -p tests

total_tests=100
pad_width=${#total_tests}

gen_and_run() {
    local gen_bin=$1
    local type=$2
    local start=$3
    local end=$4

    for ((i=start; i<=end; i++)); do
        local test_name
        test_name=$(printf "test%0${pad_width}d" "$i")
        mkdir -p "tests/${test_name}"

        local seed=$((base_seed + i))
        ./${gen_bin} ${type} ${seed} > "tests/${test_name}/input.in"
        ./validator < "tests/${test_name}/input.in"
        ./solution < "tests/${test_name}/input.in" > "tests/${test_name}/output.out"

        echo "[Gen] ${gen_bin} type=${type} seed=${seed} -> ${test_name}"
    done
}

# Subtask 1 (10 tests)
echo "[Generate] Subtask 1"
gen_and_run gen_sub1 1  1  2  # Normal
gen_and_run gen_sub1 2  3  5   # Disconnected
gen_and_run gen_sub1 3  5  6   # Multi-edge
# gen_and_run gen_sub1 4  7 10   # Stress

# Subtask 2 (20 tests)
echo "[Generate] Subtask 2"
gen_and_run gen_sub2 1 11 15  # Normal
gen_and_run gen_sub2 2 16 21  # Disconnected
gen_and_run gen_sub2 3 22 26  # Long path
gen_and_run gen_sub2 4 27 30  # Stress

# Subtask 3 (70 tests)
echo "[Generate] Subtask 3"
gen_and_run gen_sub3 1 31 44 # Normal Random
gen_and_run gen_sub3 2 45 58  # Overflow Test
gen_and_run gen_sub3 3 59 71 # Greedy Trap
gen_and_run gen_sub3 4 72 100  # Greedy Trap


echo "✅ All test data generated successfully with base seed ${base_seed}!"