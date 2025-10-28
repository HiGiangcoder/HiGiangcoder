#!/usr/bin/env python3
import os, subprocess, sys, shutil
from pathlib import Path

# ======================
# 🧩 Cấu hình ban đầu
# ======================
base_seed = int(sys.argv[1]) if len(sys.argv) > 1 else 2000
print(f"[Info] Base seed = {base_seed}")

# ======================
# 📂 Các file cần biên dịch
# ======================
sources = {
    "validator.cpp": "validator",
    "solution.cpp": "solution",
    "checker.cpp": "checker",
    "gen_sub1.cpp": "gen_hamilton",
}

# ======================
# 🏗️ Hàm biên dịch
# ======================
def compile_source(src, out):
    print(f"[Compile] {src} -> {out}")
    cmd = ["g++", "-O2", "-std=c++17y", src, "-o", out]
    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"❌ Compilation failed for {src}:\n{result.stderr}")
        sys.exit(1)

# ======================
# 🚀 Biên dịch từng file
# ======================
for src, out in sources.items():
    if not os.path.exists(src):
        print(f"⚠️ Warning: {src} not found, skipping.")
        continue
    compile_source(src, out)

# ======================
# 🧪 Tạo th
