#!/usr/bin/env bash
set -uo pipefail  # không dừng khi lỗi, nhưng biến chưa khai báo sẽ báo lỗi

# Cấu hình
GXX="/opt/homebrew/bin/g++-15"   # đường dẫn g++-15 (thay nếu khác)
CXXFLAGS="-std=c++17 -O2 -pipe"
TIME_LIMIT=1      # seconds
MEM_LIMIT_MB=256
MEM_LIMIT_KB=$((MEM_LIMIT_MB*1024))

if [ $# -lt 1 ]; then
  echo "Usage: $0 <solution.cpp or executable>"
  exit 1
fi

SRC="$1"

# --- compile solution ---
if [[ "$SRC" == *.cpp ]]; then
  EXEC="${SRC%.cpp}"
  echo "[Compile] Compiling $SRC -> $EXEC"
  if ! "$GXX" $CXXFLAGS "$SRC" -o "$EXEC"; then
    echo "❌ Compile failed"
    exit 1
  fi
else
  EXEC="$SRC"
  if [ ! -x "$EXEC" ]; then
    echo "Error: $EXEC not found or not executable"
    exit 1
  fi
fi

# --- compile validator/checker nếu có (dùng cùng compiler) ---
if [ -f validator.cpp ]; then
  echo "[Compile] Compiling validator.cpp -> validator"
  "$GXX" $CXXFLAGS validator.cpp -o validator 2>/dev/null || true
fi
if [ -f checker.cpp ]; then
  echo "[Compile] Compiling checker.cpp -> checker"
  "$GXX" $CXXFLAGS checker.cpp -o checker 2>/dev/null || true
fi

# --- lấy danh sách test ---
# Hỗ trợ 2 cấu trúc:
# 1) tests/test01  (mỗi test là một file input, expected có thể tests/test01.out)
# 2) tests/test01/ (mỗi test là một thư mục chứa input.in & output.out)
tests=()

# nếu có folder tests/test*/
shopt -s nullglob
for d in tests/test*/; do
  tests+=("$d")
done
shopt -u nullglob

# nếu không có thư mục dạng trên, fallback: lấy file tests/test*
if [ ${#tests[@]} -eq 0 ]; then
  shopt -s nullglob
  for f in tests/test*; do
    if [ -f "$f" ]; then
      tests+=("$f")
    fi
  done
  shopt -u nullglob
fi

if [ ${#tests[@]} -eq 0 ]; then
  echo "No tests found in tests/. Run gen.sh first."
  exit 1
fi

# --- tạo thư mục outputs/ ---
mkdir -p outputs

pass=0; fail=0; total=0

for item in "${tests[@]}"; do
  # nếu là thư mục
  if [ -d "$item" ]; then
    d=${item%/}
    base=$(basename "$d")
    input="$d/input.in"
    expected="$d/output.out"
  else
    # nếu là file (ví dụ tests/test01)
    d="$item"
    base=$(basename "$d")
    input="$d"
    # tìm expected: ưu tiên $d.out hoặc $d.expected hoặc $d.answer
    if [ -f "${d}.out" ]; then
      expected="${d}.out"
    elif [ -f "${d}.expected" ]; then
      expected="${d}.expected"
    elif [ -f "${d}.answer" ]; then
      expected="${d}.answer"
    else
      expected=""
    fi
  fi

  userout="outputs/${base}_user.out"
  timefile=$(mktemp)
  stderrfile=$(mktemp)

  total=$((total+1))
  printf "\n--- %s ---\n" "$base"

  # --- check input/output tồn tại ---
  if [ ! -f "$input" ]; then
    echo "❌ Missing input: $input"
    fail=$((fail+1))
    rm -f "$timefile" "$stderrfile"
    continue
  fi
  if [ -z "$expected" ] || [ ! -f "$expected" ]; then
    echo "❌ Missing expected: $expected"
    fail=$((fail+1))
    rm -f "$timefile" "$stderrfile"
    continue
  fi

  # --- validator ---
  if [ -x ./validator ]; then
    if ! ./validator < "$input" > /dev/null 2>&1; then
      echo "❌ Validator failed for $base"
      fail=$((fail+1))
      rm -f "$timefile" "$stderrfile"
      continue
    fi
  fi

  # --- chạy solution ---
  # Hỗ trợ nhiều hệ: ưu tiên gtimeout+gtime nếu có, fallback về timeout hoặc chạy trực tiếp
  TIMEOUT_CMD="$(command -v gtimeout || command -v timeout || true)"
  GTIME_CMD="$(command -v gtime || command -v /usr/bin/time || true)"

  if [ -n "$TIMEOUT_CMD" ] && [ -n "$(command -v gtime)" ]; then
    # has gtimeout and gtime -> use both
    "$TIMEOUT_CMD" "${TIME_LIMIT}s" gtime -f "%e %M" -o "$timefile" ./"$EXEC" < "$input" > "$userout" 2> "$stderrfile"
  elif [ -n "$TIMEOUT_CMD" ] && [ -n "$GTIME_CMD" ]; then
    # has timeout and some time -> use timeout (no gtime format)
    "$TIMEOUT_CMD" "${TIME_LIMIT}s" ./"$EXEC" < "$input" > "$userout" 2> "$stderrfile"
  elif [ -n "$GTIME_CMD" ] && [ "$(basename "$GTIME_CMD")" = "gtime" ]; then
    # has gtime but no timeout: run gtime (no timeout)
    gtime -f "%e %M" -o "$timefile" ./"$EXEC" < "$input" > "$userout" 2> "$stderrfile"
  else
    # fallback: run executable directly (no time, no timeout)
    ./"$EXEC" < "$input" > "$userout" 2> "$stderrfile"
  fi

  exit_code=$?

  runtime="0.00"; memkb=0
  if [ -s "$timefile" ]; then
    read runtime memkb < "$timefile"
  fi
  memmb=$(awk "BEGIN{printf \"%.2f\", ${memkb}/1024}")

  status="OK"
  if [ $exit_code -eq 124 ]; then
    status="TLE"
  elif [ $exit_code -ne 0 ]; then
    status="RTE"
  fi
  if (( memkb > MEM_LIMIT_KB )); then
    status="MLE"
  fi

  # --- checker hoặc diff ---
  if [ "$status" = "OK" ]; then
    if [ -x ./checker ]; then
      ./checker "$input" "$userout" "$expected" > /dev/null 2> checker_err.txt
      chk_rc=$?
      if [ $chk_rc -ne 0 ]; then
        status="WA"
      fi
    else
      if ! diff -q <(tr -s ' \t\r\n' '\n' < "$userout") <(tr -s ' \t\r\n' '\n' < "$expected") >/dev/null; then
        status="WA"
      fi
    fi
    
  fi

  printf "%-4s | time=%ss | mem=%sMB\n" "$status" "$runtime" "$memmb"

  if [ "$status" = "OK" ]; then pass=$((pass+1)); else fail=$((fail+1)); fi

  rm -f "$timefile" "$stderrfile" checker_err.txt
done

echo
echo "Summary: passed=$pass failed=$fail total=$total"
echo "Outputs saved to ./outputs/"
