#!/usr/bin/env python3
import os
import subprocess
import sys
from pathlib import Path
import shutil

# =========================
# Lấy seed từ tham số đầu
# =========================
base_seed = int(sys.argv[1]) if len(sys.argv) > 1 else 1000
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
compile_flags = ["-std=c++17", "-O2", "-pipe", "-s"]
if not CXX.startswith("clang"):
    compile_flags.append("-static")

# --- Danh sách file ---
sources = {
    "validator.cpp": "validator",
    "solution.cpp": "solution",
    "gen_sub1.cpp": "gen_sub1",
    "gen_sub2.cpp": "gen_sub2",
    "gen_sub3.cpp": "gen_sub3",
}

# --- Biên dịch ---
for src, out in sources.items():
    cmd = [CXX] + compile_flags + [src, "-o", out]
    subprocess.run(cmd, check=True)

print("[Compile] Done.")

# =========================
# Tạo thư mục test
# =========================
tests_dir = Path("tests")
if tests_dir.exists():
    import shutil
    shutil.rmtree(tests_dir)
tests_dir.mkdir()

total_tests = 100
pad_width = len(str(total_tests))

# ===========================================
# Hàm sinh test với seed cố định cho mỗi test
# ===========================================
def gen_and_run(gen_bin, type_id, start, end):
    for i in range(start, end + 1):
        test_name = f"test{i:0{pad_width}d}"
        test_dir = tests_dir / test_name
        test_dir.mkdir(parents=True, exist_ok=True)

        seed = base_seed + i

        input_file = test_dir / "input.in"
        output_file = test_dir / "output.out"

        # Sinh input
        with open(input_file, "w") as fin:
            subprocess.run([f"./{gen_bin}", str(type_id), str(seed)], stdout=fin, check=True)

        # Validate
        subprocess.run(["./validator"], stdin=open(input_file, "r"), check=True)

        # Run solution
        with open(input_file, "r") as fin, open(output_file, "w") as fout:
            subprocess.run(["./solution"], stdin=fin, stdout=fout, check=True)

        print(f"[Gen] {gen_bin} type={type_id} seed={seed} -> {test_name}")


# =========================
# Sinh dữ liệu
# =========================
print("[Generate] Subtask 1")
gen_and_run("gen_sub1", 1, 1, 5)
gen_and_run("gen_sub1", 2, 6, 10)
gen_and_run("gen_sub1", 3, 11, 15)
gen_and_run("gen_sub1", 4, 16, 20)
gen_and_run("gen_sub1", 5, 21, 25)
gen_and_run("gen_sub1", 6, 26, 30)

print("[Generate] Subtask 2")
gen_and_run("gen_sub2", 1, 31, 35)
gen_and_run("gen_sub2", 2, 36, 40)
gen_and_run("gen_sub2", 3, 41, 45)
gen_and_run("gen_sub2", 4, 46, 50)
# gen_and_run("gen_sub2", 5, 51, 55)
gen_and_run("gen_sub2", 6, 56, 60)

print("[Generate] Subtask 3")
gen_and_run("gen_sub3", 1, 61, 70)
gen_and_run("gen_sub3", 2, 71, 75)
gen_and_run("gen_sub3", 3, 76, 80)
gen_and_run("gen_sub3", 4, 81, 85)
gen_and_run("gen_sub3", 5, 86, 90)
gen_and_run("gen_sub3", 6, 91, 100)

print(f"✅ All test data generated successfully with base seed {base_seed}!")
