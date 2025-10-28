#!/bin/bash
set -e

base_seed=${1:-1000}
echo "[Info] Base seed = ${base_seed}"

echo "[Compile] Building generators and reference solution..."
g++ -std=c++17 -O2 -pipe -static -s gen_sub1.cpp   -o gen_sub1
g++ -std=c++17 -O2 -pipe -static -s gen_sub2.cpp   -o gen_sub2
g++ -std=c++17 -O2 -pipe -static -s gen_sub3.cpp   -o gen_sub3
g++ -std=c++17 -O2 -pipe -static -s validator.cpp  -o validator
g++ -std=c++17 -O2 -pipe -static -s solution.cpp   -o solution
echo "[Compile] Done."

rm -rf tests
mkdir -p tests

pad_width=3
test_counter=0

generate_many() {
    local gen_bin=$1
    local type=$2
    local count=$3
    local variant=${4:-}
    for ((i=0; i<count; ++i)); do
        test_counter=$((test_counter + 1))
        local test_name
        printf -v test_name "test%0${pad_width}d" "$test_counter"
        mkdir -p "tests/${test_name}"
        local seed=$((base_seed + test_counter))
        if [ -n "${variant}" ]; then
            "./${gen_bin}" "${type}" "${seed}" "${variant}" > "tests/${test_name}/input.in"
        else
            "./${gen_bin}" "${type}" "${seed}" > "tests/${test_name}/input.in"
        fi
        ./validator < "tests/${test_name}/input.in" > /dev/null
        ./solution < "tests/${test_name}/input.in" > "tests/${test_name}/output.out"
        if [ -n "${variant}" ]; then
            echo "[Gen] ${test_name} <- ${gen_bin} type=${type} variant=${variant} seed=${seed}"
        else
            echo "[Gen] ${test_name} <- ${gen_bin} type=${type} seed=${seed}"
        fi
    done
}

echo "[Generate] Subtask 1 (n<=10, m<=20)"
generate_many gen_sub1 1 8             # normal
generate_many gen_sub1 3 5              # edge
generate_many gen_sub1 4 7              # stress
generate_many gen_sub1 2 1 0            # special tie
generate_many gen_sub1 2 1 2            # special heavy
generate_many gen_sub1 2 1 3            # special disconnected
generate_many gen_sub1 2 1 4            # bfs trap
generate_many gen_sub1 2 1 5            # bfs killer
generate_many gen_sub1 2 1 6            # duplicate edges

echo "[Generate] Subtask 2 (n<=1000)"
generate_many gen_sub2 1 10             # normal
generate_many gen_sub2 3 8              # edge
generate_many gen_sub2 4 8              # stress
generate_many gen_sub2 2 1 0            # layered special
generate_many gen_sub2 2 1 2            # heavy special
generate_many gen_sub2 2 1 3            # disconnected
generate_many gen_sub2 2 1 4            # bfs chain trap
generate_many gen_sub2 2 1 5            # bfs killer variant
generate_many gen_sub2 2 1 6            # duplicate edges

echo "[Generate] Subtask 3 (full constraints)"
generate_many gen_sub3 1 12            # normal
generate_many gen_sub3 3 10              # edge
generate_many gen_sub3 4 12             # stress
generate_many gen_sub3 2 1 0            # trap special
generate_many gen_sub3 2 1 2            # heavy special
generate_many gen_sub3 2 1 3            # disconnected
generate_many gen_sub3 2 1 4            # bfs chain trap
generate_many gen_sub3 2 1 5            # bfs killer
generate_many gen_sub3 2 1 6            # heavy bfs trap
generate_many gen_sub3 2 1 7            # real bfs killer
generate_many gen_sub3 2 1 8            # duplicate edges

echo "✅ Generated ${test_counter} tests with base seed ${base_seed}"
