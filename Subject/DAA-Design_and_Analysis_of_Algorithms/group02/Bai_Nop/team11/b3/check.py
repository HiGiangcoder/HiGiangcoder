import os
import sys
import subprocess
import time
import difflib

TIME_LIMIT = 1.0  # seconds
MEM_LIMIT_MB = 256

def compile_cpp(src):
    exe = os.path.splitext(src)[0] + ".exe"
    print(f"[Compile] {src} -> {exe}")
    result = subprocess.run(
        ["g++", "-std=c++17", "-O2", "-pipe", "-s", src, "-o", exe],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    if result.returncode != 0:
        print("❌ Compile failed:")
        print(result.stderr)
        sys.exit(1)
    return exe

def run_with_timeout(cmd, input_file, output_file):
    with open(input_file, "r") as fin, open(output_file, "w") as fout:
        start = time.time()
        try:
            proc = subprocess.run(cmd, stdin=fin, stdout=fout, stderr=subprocess.PIPE, timeout=TIME_LIMIT)
            end = time.time()
            runtime = end - start
            return proc.returncode, runtime, proc.stderr.decode("utf-8")
        except subprocess.TimeoutExpired:
            return "TLE", TIME_LIMIT, ""

def main():
    if len(sys.argv) < 2:
        print("Usage: python check.py <solution.cpp or .exe>")
        return

    src = sys.argv[1]
    if src.endswith(".cpp"):
        exec_file = compile_cpp(src)
    else:
        exec_file = src
        if not os.path.exists(exec_file):
            print(f"❌ Executable not found: {exec_file}")
            return

    if not os.path.exists("tests"):
        print("❌ Folder 'tests' not found.")
        return

    os.makedirs("outputs", exist_ok=True)

    test_dirs = sorted([d for d in os.listdir("tests") if os.path.isdir(os.path.join("tests", d))])
    if not test_dirs:
        print("❌ No test folders found in 'tests/'.")
        return

    total = 0
    passed = 0

    for test_dir in test_dirs:
        input_path = os.path.join("tests", test_dir, "input.in")
        expected_path = os.path.join("tests", test_dir, "output.out")
        user_output = os.path.join("outputs", f"{test_dir}_user.out")

        print(f"\n--- {test_dir} ---")
        if not os.path.exists(input_path):
            print(f"❌ Missing input: {input_path}")
            continue
        if not os.path.exists(expected_path):
            print(f"❌ Missing output: {expected_path}")
            continue

        ret, runtime, stderr = run_with_timeout([f"./{exec_file}"], input_path, user_output)

        if ret == "TLE":
            print(f"TLE | time={runtime:.2f}s")
            continue
        elif ret != 0:
            print(f"RTE | exit={ret} | stderr={stderr.strip()}")
            continue

        with open(expected_path, "r") as fexp, open(user_output, "r") as fusr:
            exp = fexp.read().strip().split()
            usr = fusr.read().strip().split()
            if exp == usr:
                print(f"OK  | time={runtime:.2f}s")
                passed += 1
            else:
                print(f"WA  | time={runtime:.2f}s")
                diff = difflib.unified_diff(exp, usr, lineterm="")
                print("\n".join(diff))

        total += 1

    print(f"\nSummary: passed={passed} / total={len(test_dirs)}")
    print("Outputs saved to ./outputs/")

if __name__ == "__main__":
    main()
