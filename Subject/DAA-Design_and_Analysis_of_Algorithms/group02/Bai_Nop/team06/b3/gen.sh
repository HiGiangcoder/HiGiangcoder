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
# gen_and_run() {
#     local gen_bin=$1
#     local type=$2
#     local start=$3
#     local end=$4

#     for ((i=start; i<=end; i++)); do
#         # Tên test có padding động
#         local test_name
#         test_name=$(printf "test%0${pad_width}d" "$i")

#         mkdir -p "tests/${test_name}"

#         # Seed cố định = base_seed + i
#         local seed=$((base_seed + i))

#         ./${gen_bin} ${type} ${seed} > "tests/${test_name}/input.in"
#         ./validator < "tests/${test_name}/input.in"
#         ./solution < "tests/${test_name}/input.in" > "tests/${test_name}/output.out"

#         echo "[Gen] ${gen_bin} type=${type} seed=${seed} -> ${test_name}"
#     done
# }

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

        echo "⚙️  Generating ${test_name} with ${gen_bin} (type=${type}, seed=${seed})"

        # --- Generate input ---
        if ! ./${gen_bin} ${type} ${seed} > "tests/${test_name}/input.in" 2> "tests/${test_name}/gen_err.log"; then
            echo "❌ Generator ${gen_bin} failed for ${test_name}"
            cat "tests/${test_name}/gen_err.log"
            exit 1
        fi

        # --- Validate ---
        if ! ./validator < "tests/${test_name}/input.in" > /dev/null 2> "tests/${test_name}/val_err.log"; then
            echo "❌ Validator failed for ${test_name}"
            head -n 10 "tests/${test_name}/input.in"
            cat "tests/${test_name}/val_err.log"
            exit 1
        fi

        # --- Generate output ---
        if ! ./solution < "tests/${test_name}/input.in" > "tests/${test_name}/output.out" 2> "tests/${test_name}/sol_err.log"; then
            echo "❌ Solution crashed on ${test_name}"
            head -n 10 "tests/${test_name}/input.in"
            cat "tests/${test_name}/sol_err.log"
            exit 1
        fi

        echo "[Gen] ✅ ${test_name} (type=${type}, seed=${seed})"
    done
}

# Subtask 1 (20 tests)
echo "[Generate] Subtask 1"
gen_and_run gen_sub1 1  1 20
gen_and_run gen_sub1 2 21 34
gen_and_run gen_sub1 3 35 68
gen_and_run gen_sub1 4 69 100

echo "✅ All test data generated successfully with base seed ${base_seed}!"
