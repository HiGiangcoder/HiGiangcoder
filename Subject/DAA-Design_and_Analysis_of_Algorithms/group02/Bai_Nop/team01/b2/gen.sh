#!/bin/bash
set -e

# =========================
# Lấy seed từ tham số đầu
# =========================
base_seed=${1:-1000}   # nếu không truyền thì mặc định 1000

echo "[Info] Base seed = ${base_seed}"

echo "[Compile] Building generators and solution..."
g++ -std=c++17 -O2 -pipe validator.cpp  -o validator
g++ -std=c++17 -O2 -pipe solution.cpp   -o solution
g++ -std=c++17 -O2 -pipe gen_sub1.cpp   -o gen_sub1
g++ -std=c++17 -O2 -pipe gen_sub2.cpp   -o gen_sub2
g++ -std=c++17 -O2 -pipe gen_sub3.cpp   -o gen_sub3
echo "[Compile] Done."

rm -rf tests
mkdir -p tests

# Tổng số test dự kiến
total_tests=100

# Tính số chữ số cần padding, ví dụ:
# 9 -> 1, 50 -> 2, 123 -> 3
pad_width=${#total_tests}

# ===========================================
# Hàm sinh test với seed cố định cho mỗi test
# ===========================================
gen_and_run() {
    local gen_bin=$1
    local type=$2
    local start=$3
    local end=$4

    for ((i=start; i<=end; i++)); do
        # Tên test có padding động
        local test_name
        test_name=$(printf "test%0${pad_width}d" "$i")

        mkdir -p "tests/${test_name}"

        # Seed cố định = base_seed + i
        local seed=$((base_seed + i))

        ./${gen_bin} ${type} ${seed} > "tests/${test_name}/input.in"
        ./validator < "tests/${test_name}/input.in"
        ./solution < "tests/${test_name}/input.in" > "tests/${test_name}/output.out"

        echo "[Gen] ${gen_bin} type=${type} seed=${seed} -> ${test_name}"
    done
}


# 5 25 25 35

# Subtask 1 (20 tests)
echo "[Generate] Subtask 1"
gen_and_run gen_sub1 1  1 2
gen_and_run gen_sub1 2 3 5
gen_and_run gen_sub1 3 6 10
gen_and_run gen_sub1 4 11 20

# Subtask 2 (30 tests)
echo "[Generate] Subtask 2"
gen_and_run gen_sub2 1 21 22
gen_and_run gen_sub2 2 23 30
gen_and_run gen_sub2 3 31 37
gen_and_run gen_sub2 4 38 50

# Subtask 3 (50 tests)
echo "[Generate] Subtask 3"
gen_and_run gen_sub3 1 51 53
gen_and_run gen_sub3 2 54 66
gen_and_run gen_sub3 3 67 80
gen_and_run gen_sub3 4 81 100

echo "✅ All test data generated successfully with base seed ${base_seed}!"
