#!/bin/bash
set -e

# =====================================
# ⚙️ CONFIG CƠ BẢN
# =====================================
base_seed=${1:-2025}        # Seed gốc, mặc định = 2025
project_root=$(dirname "$0") # Đường dẫn của script hiện tại
cd "$project_root"           # Di chuyển vào thư mục project

echo "[Info] Base seed = ${base_seed}"
echo "[Info] Working directory = $(pwd)"
echo "[Compile] Building generators, validator, solution..."

# =====================================
# ⚙️ COMPILE TẤT CẢ CÁC FILE CẦN THIẾT
# =====================================
mkdir -p bin
g++ -std=c++17 -O2 -pipe -static -s validator.cpp  -o bin/validator
g++ -std=c++17 -O2 -pipe -static -s solution.cpp   -o bin/solution
g++ -std=c++17 -O2 -pipe -static -s gen_sub1.cpp   -o bin/gen_sub1
g++ -std=c++17 -O2 -pipe -static -s gen_sub2.cpp   -o bin/gen_sub2
g++ -std=c++17 -O2 -pipe -static -s gen_sub3.cpp   -o bin/gen_sub3
echo "[Compile] ✅ Done."

# =====================================
# 🧹 DỌN THƯ MỤC TEST
# =====================================
rm -rf tests
mkdir -p tests

# Tổng số test
total_tests=60
pad_width=${#total_tests}  # padding động cho tên file test (vd test01, test002,...)

# =====================================
# 🧩 HÀM SINH TEST CHO MỖI SUBTASK
# =====================================
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

        echo "[Gen] ${gen_bin} type=${type} seed=${seed} -> ${test_name}"

        ./bin/${gen_bin} ${seed} ${type} > "tests/${test_name}/input.in"
        ./bin/validator < "tests/${test_name}/input.in" > /dev/null
        ./bin/solution < "tests/${test_name}/input.in" > "tests/${test_name}/output.out"
    done
}

# =====================================
# 🧱 SUBTASK 1 (n ≤ 10, m ≤ 20)
# =====================================
echo "[Generate] Subtask 1"
gen_and_run gen_sub1 1  1 10     # Normal
gen_and_run gen_sub1 2 11 13     # Special
gen_and_run gen_sub1 3 14 16     # Edge
gen_and_run gen_sub1 4 17 20     # Stress

# =====================================
# 🧱 SUBTASK 2 (n ≤ 1000)
# =====================================
echo "[Generate] Subtask 2"
gen_and_run gen_sub2 1 21 35     # Normal
gen_and_run gen_sub2 2 36 40     # Special
gen_and_run gen_sub2 3 41 45     # Edge
gen_and_run gen_sub2 4 46 50     # Stress

# =====================================
# 🧱 SUBTASK 3 (Full)
# =====================================
echo "[Generate] Subtask 3"
gen_and_run gen_sub3 1 51 55     # Normal
gen_and_run gen_sub3 2 56 57     # Special
gen_and_run gen_sub3 3 58 59     # Edge
gen_and_run gen_sub3 4 60 100     # Stress

echo "✅ All test data generated successfully with base seed ${base_seed}!"
