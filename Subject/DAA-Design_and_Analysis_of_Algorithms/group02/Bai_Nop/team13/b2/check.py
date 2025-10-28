#!/usr/bin/env python3
import os
import sys
import subprocess
import time
import platform
from pathlib import Path

# Cài đặt giới hạn
TIME_LIMIT = 2.0  # Giây
MEM_LIMIT_MB = 512  # MB

def normalize_line_endings(text):
    """Chuẩn hóa line endings thành LF"""
    return text.replace('\r\n', '\n').replace('\r', '\n')

def compare_outputs(file1, file2):
    """So sánh 2 file, bỏ qua sự khác biệt về line endings và trailing whitespace"""
    try:
        with open(file1, 'r', encoding='utf-8') as f1, open(file2, 'r', encoding='utf-8') as f2:
            content1 = normalize_line_endings(f1.read().strip())
            content2 = normalize_line_endings(f2.read().strip())
            
            # Debug: in nội dung để kiểm tra
            print(f"  Expected: '{content1}' (len: {len(content1)})")
            print(f"  Actual:   '{content2}' (len: {len(content2)})")
            
            return content1 == content2
    except Exception as e:
        print(f"  Comparison error: {e}")
        return False

def find_compiler():
    """Tìm trình biên dịch C++"""
    for compiler in ["g++", "gcc", "clang++"]:
        try:
            result = subprocess.run(["where", compiler], capture_output=True, text=True)
            if result.returncode == 0:
                return compiler
        except:
            continue
    return "g++"

def compile_cpp(src, output):
    """Biên dịch file C++"""
    compiler = find_compiler()
    print(f"[Compile] {src} -> {output} ({compiler})")
    
    flags = ["-std=c++17", "-O2", "-pipe"]
    cmd = [compiler] + flags + [src, "-o", output]
    
    try:
        result = subprocess.run(cmd, check=True, capture_output=True, text=True)
        print(f"✅ Compiled successfully")
        return True
    except subprocess.CalledProcessError as e:
        print(f"❌ Compilation failed: {e.stderr}")
        return False

def run_with_limits(exec_path, input_path, output_path):
    """Chạy chương trình với giới hạn thời gian và bộ nhớ"""
    start_time = time.time()
    
    try:
        with open(input_path, "r") as fin, open(output_path, "w") as fout:
            process = subprocess.run(
                [f"./{exec_path}"],
                stdin=fin,
                stdout=fout,
                stderr=subprocess.PIPE,
                timeout=TIME_LIMIT,
                text=True
            )
            
            runtime = time.time() - start_time
            
            if process.returncode != 0:
                return "RTE", runtime, 0
            else:
                return "OK", runtime, 0
                
    except subprocess.TimeoutExpired:
        return "TLE", TIME_LIMIT, 0
    except Exception as e:
        return "RTE", time.time() - start_time, 0

def main():
    if len(sys.argv) < 2:
        print("Usage: python check.py <solution.cpp or executable>")
        sys.exit(1)

    src = Path(sys.argv[1])
    
    # Xác định đường dẫn executable
    if src.suffix == ".cpp":
        exec_path = src.with_suffix(".exe") if os.name == 'nt' else src.with_suffix("")
        if not compile_cpp(str(src), str(exec_path)):
            sys.exit(1)
    else:
        exec_path = src
        if not exec_path.exists():
            print(f"❌ Executable not found: {exec_path}")
            sys.exit(1)

    # Biên dịch checker nếu cần
    checker_path = Path("checker.exe" if os.name == 'nt' else "checker")
    if Path("checker.cpp").exists() and not checker_path.exists():
        if not compile_cpp("checker.cpp", str(checker_path)):
            print("⚠️  Could not compile checker, will use simple comparison")

    # Tìm test cases
    test_dirs = sorted(Path("tests").glob("test*"))
    if not test_dirs:
        print("❌ No test directories found in ./tests/")
        print("   Run 'python gen.py <seed>' first to generate tests")
        sys.exit(1)

    # Tạo thư mục outputs
    os.makedirs("outputs", exist_ok=True)

    print(f"\n🔍 Testing {exec_path} on {len(test_dirs)} test cases")
    print(f"⏱️  Time limit: {TIME_LIMIT}s")
    print("=" * 60)

    total, passed, failed = 0, 0, 0
    results = []

    for test_dir in test_dirs:
        total += 1
        base = test_dir.name
        inp = test_dir / "input.in"
        exp = test_dir / "output.out"
        user_out = Path("outputs") / f"{base}_user.out"

        print(f"\n--- {base} ---")

        if not inp.exists():
            print("❌ Missing input file")
            failed += 1
            results.append((base, "NO_INPUT", 0, 0))
            continue

        if not exp.exists():
            print("❌ Missing expected output file")
            failed += 1
            results.append((base, "NO_EXPECTED", 0, 0))
            continue

        # Chạy solution
        status, runtime, mem = run_with_limits(exec_path, inp, user_out)
        
        if status == "OK":
            # LUÔN dùng simple comparison để debug
            if compare_outputs(exp, user_out):
                final_status = "OK"
                passed += 1
            else:
                final_status = "WA"
                failed += 1
                
                # DEBUG: Hiển thị chi tiết sự khác biệt
                print(f"  ❌ Output mismatch detected!")
                
        else:
            final_status = status
            failed += 1

        print(f"{final_status:>4} | time={runtime:.2f}s")
        results.append((base, final_status, runtime, mem))

    # Hiển thị tổng kết
    print("\n" + "=" * 60)
    print("📊 FINAL RESULTS")
    print("=" * 60)
    
    for test_name, status, runtime, mem in results:
        print(f"{test_name}: {status} ({runtime:.2f}s)")
    
    print(f"\n✅ Passed: {passed}/{total}")
    print(f"❌ Failed: {failed}/{total}")
    
    if failed == 0:
        print("🎉 All tests passed!")
    else:
        print("💡 Check ./outputs/ for detailed outputs")

if __name__ == "__main__":
    main()