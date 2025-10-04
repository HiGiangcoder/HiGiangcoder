#!/bin/bash
set -e

# =====================================
# 1️  Biên dịch chương trình cần kiểm tra
# =====================================
if [ $# -lt 1 ]; then
    echo "Usage: bash check.sh <file.cpp>"
    exit 1
fi

target_cpp=$1
target_bin="submission"

echo "[Compile] Compiling $target_cpp -> $target_bin"
g++ -std=c++17 -O2 -pipe -static -s "$target_cpp" -o "$target_bin"

# =====================================
# 2️  Cấu hình giới hạn
# =====================================
TIME_LIMIT=1.0     # giây
MEM_LIMIT=262144   # KB ~ 256 MB

echo "Starting tests (time limit: ${TIME_LIMIT}s, mem limit: ${MEM_LIMIT}KB)"

# =====================================
# 3️  Hàm đo thời gian + bộ nhớ và so sánh kết quả
# =====================================
run_test() {
    local id=$1
    local input="tests/test${id}/input.in"
    local expected="tests/test${id}/output.out"

    echo "--- Running test${id} ---"

    if [ ! -f "$input" ]; then
        echo "⚠️ Missing input file: $input"
        return
    fi

    # --- Chạy submission ---
    /usr/bin/time -f "%e %M" -o temp_usage.txt ./"$target_bin" < "$input" > temp_output.txt 2>/dev/null || true
    read runtime memused_kb < <(cat temp_usage.txt)
    rm -f temp_usage.txt

    memused_mb=$(echo "scale=2; $memused_kb / 1024" | bc)

    local status="✅ OK"

    # Kiểm tra giới hạn
    if (( $(echo "$runtime > $TIME_LIMIT" | bc -l) )); then
        status="❌ TLE (${runtime}s)"
    fi
    if (( $(echo "$memused_kb > $MEM_LIMIT" | bc -l) )); then
        status="❌ MLE (${memused_mb}MB)"
    fi

    # --- Chạy checker ---
    /usr/bin/time -f "%e %M" -o temp_usage_checker.txt ./checker "$input" "$expected" temp_output.txt >/dev/null 2>&1 || status="❌ WA"
    read checker_time checker_mem_kb < <(cat temp_usage_checker.txt)
    rm -f temp_usage_checker.txt

    checker_mem_mb=$(echo "scale=2; $checker_mem_kb / 1024" | bc)

    echo "$status | Time: ${runtime}s | Mem: ${memused_mb}MB | Checker: ${checker_time}s / ${checker_mem_mb}MB"

    rm -f temp_output.txt
}

# =====================================
# 4️ Chạy toàn bộ test và đo tổng thời gian
# =====================================
start_time=$(date +%s.%N)

for i in $(seq 1 50); do
    if [ -f "tests/test${i}/input.in" ]; then
        run_test $i
    else
        echo "⚠️ test${i} not found, skipping..."
    fi
done

end_time=$(date +%s.%N)
total_time=$(echo "$end_time - $start_time" | bc)

echo "✅ All tests completed in ${total_time}s."
