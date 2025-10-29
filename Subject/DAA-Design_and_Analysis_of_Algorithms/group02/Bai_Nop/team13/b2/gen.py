#!/usr/bin/env python3
import os
import subprocess
import sys
from pathlib import Path
import shutil
import time

# =========================
# Lấy seed từ tham số đầu
# =========================
if len(sys.argv) < 2:
    print("Usage: python3 gen.py <base_seed>")
    sys.exit(1)

base_seed = int(sys.argv[1])
print(f"[Info] Base seed = {base_seed}")

# =========================
# Biên dịch các chương trình
# =========================

# --- Chọn compiler phù hợp ---
CXX = None
for compiler in ["g++", "clang++", "g++-14", "g++-13", "g++-12"]:
    if shutil.which(compiler):
        CXX = compiler
        break

if CXX is None:
    print("❌ Không tìm thấy trình biên dịch C++ (g++ hoặc clang++).")
    sys.exit(1)

print(f"[Info] Using C++ compiler: {CXX}")

# --- Thiết lập flag phù hợp ---
compile_flags = ["-std=c++17", "-O2", "-pipe"]
if not CXX.startswith("clang"):
    compile_flags.append("-static")

# --- Danh sách file ---
sources = {
    "validator.cpp": "validator",
    "solution.cpp": "solution",
    "brute.cpp": "brute",
    "checker.cpp": "checker",
    "gen_sub1.cpp": "gen_sub1",
    "gen_sub2.cpp": "gen_sub2",
}

# --- Biên dịch ---
print("\n[Compile] Compiling programs...")
for src, out in sources.items():
    if not Path(src).exists():
        print(f"❌ Missing source file: {src}")
        continue
        
    cmd = [CXX] + compile_flags + [src, "-o", out]
    try:
        result = subprocess.run(cmd, check=True, capture_output=True, text=True)
        print(f"✅ Compiled {src} -> ./{out}")
    except subprocess.CalledProcessError as e:
        print(f"❌ Failed to compile {src}:")
        print(f"Error: {e.stderr}")
        sys.exit(1)
        
print("[Compile] Done.")

# =========================
# Tạo thư mục test
# =========================
tests_dir = Path("tests")
if tests_dir.exists():
    shutil.rmtree(tests_dir)
tests_dir.mkdir()

# ===========================================
# Hàm sinh test với seed cố định cho mỗi test
# ===========================================
def gen_and_run(gen_bin, type_id, start, end, subtask_name, timeout=30):
    """
    Tạo input và chạy lời giải brute-force để tạo đáp án chuẩn.
    """
    print(f"\n[Generate] {subtask_name}")
    
    for i in range(start, end + 1):
        test_name = f"test{i:02d}"
        test_dir = tests_dir / test_name
        test_dir.mkdir(parents=True, exist_ok=True)

        seed = base_seed + i

        input_file = test_dir / "input.in"
        answer_file = test_dir / "output.out"

        # 1. Sinh input
        try:
            with open(input_file, "w") as fin:
                result = subprocess.run(
                    [f"./{gen_bin}", str(type_id), str(seed)], 
                    stdout=fin, 
                    stderr=subprocess.PIPE,
                    check=True,
                    timeout=10
                )
        except subprocess.CalledProcessError as e:
            print(f"❌ Generator failed for {test_name}: {e.stderr.decode().strip()}")
            continue
        except subprocess.TimeoutExpired:
            print(f"❌ Generator timeout for {test_name}")
            continue

        # 2. Validate Input
        try:
            result = subprocess.run(
                ["./validator"], 
                stdin=open(input_file, "r"), 
                capture_output=True,
                text=True,
                timeout=5
            )
            if result.returncode != 0:
                print(f"❌ Validation failed for {test_name}: {result.stderr.strip()}")
                continue
        except subprocess.TimeoutExpired:
            print(f"❌ Validation timeout for {test_name}")
            continue

        # 3. Run BRUTE-FORCE solution để tạo đáp án
        try:
            start_time = time.time()
            with open(input_file, "r") as fin, open(answer_file, "w") as fout:
                result = subprocess.run(
                    ["./brute"], 
                    stdin=fin, 
                    stdout=fout, 
                    stderr=subprocess.PIPE,
                    timeout=timeout
                )
                if result.returncode != 0:
                    print(f"❌ Brute-force RTE for {test_name}: {result.stderr.decode().strip()}")
                    continue
                    
            exec_time = time.time() - start_time
            if exec_time > timeout * 0.8:
                print(f"⚠️  Brute-force slow for {test_name}: {exec_time:.2f}s")
                
        except subprocess.TimeoutExpired:
            print(f"❌ Brute-force timeout for {test_name}")
            # Tạo answer mặc định cho test timeout
            with open(answer_file, "w") as fout:
                fout.write("-1\n")
            continue

        print(f"✅ Generated {test_name} (type={type_id}, seed={seed})")

# =========================
# Sinh dữ liệu
# =========================

# Subtask 1: n <= 10 (30 test cases)
gen_and_run("gen_sub1", 1, 1, 10, "Subtask 1 - Normal (n<=10)", timeout=10)
gen_and_run("gen_sub1", 2, 11, 20, "Subtask 1 - Special (fixed weight)", timeout=10)
gen_and_run("gen_sub1", 3, 21, 30, "Subtask 1 - Edge (dense graph)", timeout=10)

# Subtask 2: n <= 1000 (40 test cases)  
gen_and_run("gen_sub2", 1, 31, 45, "Subtask 2 - Normal (n<=1000)", timeout=30)
gen_and_run("gen_sub2", 2, 46, 60, "Subtask 2 - Special (multiple paths)", timeout=30)
gen_and_run("gen_sub2", 3, 61, 70, "Subtask 2 - Edge (grid graph)", timeout=30)
gen_and_run("gen_sub2", 4, 71, 80, "Subtask 2 - Stress (large graph)", timeout=30)

# Subtask 3: Full constraints (30 test cases)
gen_and_run("gen_sub2", 1, 81, 90, "Subtask 3 - Full constraints 1", timeout=60)
gen_and_run("gen_sub2", 2, 91, 100, "Subtask 3 - Full constraints 2", timeout=60)

print(f"✅ All test data generated successfully with base seed {base_seed}!")