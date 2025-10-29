#!/bin/bash
set -e

base_seed=${1:-2025}
echo "[Info] Base seed = ${base_seed}"

echo "[Compile] Building..."
# Nhớ thay g++-15 bằng phiên bản của bạn và thêm cờ cho macOS nếu cần
COMPILER="g++"
FLAGS="-std=c++17 -O2 -pipe -s -Wl,-rpath,/opt/homebrew/lib"

$COMPILER $FLAGS validator.cpp  -o validator
$COMPILER $FLAGS solution.cpp   -o solution
$COMPILER $FLAGS brute.cpp      -o brute
$COMPILER $FLAGS gen.cpp        -o gen
echo "[Compile] Done."

rm -rf tests
mkdir -p tests

total_tests=50
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
        # Dùng solution.cpp hoặc brute.cpp để sinh đáp án đều được
        ./solution < "tests/${test_name}/input.in" > "tests/${test_name}/output.out"

        echo "[Gen] ${gen_bin} type=${type} seed=${seed} -> ${test_name}"
    done
}

# 50 tests, không chia subtask
echo "[Generate] Tests"
gen_and_run gen 1  1 20   # 20 Normal cases
gen_and_run gen 2 21 35   # 15 Special cases (có đường đi)
gen_and_run gen 3 36 45   # 10 Edge cases (không có đường đi)
gen_and_run gen 4 46 50   # 5 Stress cases (đồ thị đầy đủ)

echo "✅ All test data generated successfully with base seed ${base_seed}!"