#!/usr/bin/env python3
import os, sys, subprocess, time, platform, resource, psutil
from pathlib import Path

TIME_LIMIT = 1.0
MEM_LIMIT_MB = 256
MEM_LIMIT_BYTES = MEM_LIMIT_MB * 1024 * 1024

def find_compiler():
    for c in ["g++", "clang++"]:
        if subprocess.run(["which", c], capture_output=True).returncode == 0:
            return c
    return "g++"

def compile_cpp(src, output):
    compiler = find_compiler()
    print(f"[Compile] {src} -> {output} ({compiler})")
    result = subprocess.run([compiler, "-std=c++17", "-O2", "-pipe", "-s", src, "-o", output])
    if result.returncode != 0:
        print("❌ Compilation failed")
        sys.exit(1)

def run_with_limits(exec_path, input_path, output_path):
    start = time.time()
    with open(input_path, "r") as fin, open(output_path, "w") as fout:
        proc = subprocess.Popen([f"./{exec_path}"], stdin=fin, stdout=fout)
        pid = proc.pid
        peak_mem = 0

        try:
            while proc.poll() is None:
                try:
                    mem = psutil.Process(pid).memory_info().rss
                except psutil.NoSuchProcess:
                    break
                peak_mem = max(peak_mem, mem)
                if peak_mem > MEM_LIMIT_BYTES:
                    proc.kill()
                    return "MLE", time.time() - start, peak_mem / (1024*1024)
                if time.time() - start > TIME_LIMIT:
                    proc.kill()
                    return "TLE", TIME_LIMIT, peak_mem / (1024*1024)
                time.sleep(0.005)
        except KeyboardInterrupt:
            proc.kill()
            raise

        runtime = time.time() - start
        if platform.system() != "Windows":
            usage = resource.getrusage(resource.RUSAGE_CHILDREN)
            peak_mem = max(peak_mem, usage.ru_maxrss * 1024)  # ru_maxrss = KB
        return_code = proc.returncode

    if return_code != 0:
        return "RTE", runtime, peak_mem / (1024*1024)
    return "OK", runtime, peak_mem / (1024*1024)

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 check.py <solution.cpp or executable>")
        sys.exit(1)

    src = Path(sys.argv[1])
    exec_path = src.with_suffix("") if src.suffix == ".cpp" else src

    if src.suffix == ".cpp":
        compile_cpp(str(src), str(exec_path))
    elif not exec_path.exists():
        print(f"❌ Executable not found: {exec_path}")
        sys.exit(1)

    if Path("checker.cpp").exists():
        compile_cpp("checker.cpp", "checker")
    if not Path("checker").exists():
        print("❌ checker not found (need checker.cpp or checker binary).")
        sys.exit(1)

    if Path("validator.cpp").exists():
        compile_cpp("validator.cpp", "validator")

    test_dirs = sorted(Path("tests").glob("test*/"))
    if not test_dirs:
        print("❌ No test directories in ./tests/")
        sys.exit(1)
    os.makedirs("outputs", exist_ok=True)

    total, passed, failed = 0, 0, 0
    for d in test_dirs:
        total += 1
        base = d.name
        inp, exp = d / "input.in", d / "output.out"
        user_out = Path("outputs") / f"{base}_user.out"
        print(f"\n--- {base} ---")

        if not inp.exists() or not exp.exists():
            print("❌ Missing input or output")
            failed += 1
            continue

        status, runtime, mem = run_with_limits(exec_path, inp, user_out)

        if status == "OK":
            rc = subprocess.run(
                ["./checker", str(inp), str(user_out), str(exp)],
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL,
            ).returncode
            if rc != 0:
                status = "WA"

        print(f"{status:>4} | time={runtime:.2f}s | mem={mem:.2f}MB")
        if status == "OK":
            passed += 1
        else:
            failed += 1

    print(f"\nSummary: passed={passed} failed={failed} total={total}")
    print("Outputs saved to ./outputs/")

if __name__ == "__main__":
    main()