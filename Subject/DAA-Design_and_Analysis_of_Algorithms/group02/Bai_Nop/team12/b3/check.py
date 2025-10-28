#!/usr/bin/env python3
import os, sys, subprocess, time, platform, psutil

if platform.system() != "Windows":
    import resource

# ---------------------- Utility ----------------------
def compile_code(src, out_name):
    ext = os.path.splitext(src)[1]
    if ext == ".cpp":
        compiler = "clang++" if platform.system() == "Darwin" else "g++"
        cmd = [compiler, src, "-O2", "-std=c++17", "-o", out_name]
    elif ext == ".c":
        compiler = "clang" if platform.system() == "Darwin" else "gcc"
        cmd = [compiler, src, "-O2", "-std=c17", "-o", out_name]
    else:
        raise Exception(f"Unsupported file type: {src}")

    print(f"[Compile] {src} -> {out_name} ({compiler})")
    subprocess.check_call(cmd)

def get_memory_usage(pid):
    try:
        return psutil.Process(pid).memory_info().rss / 1024 / 1024
    except:
        return 0.0

def run_with_limits(executable, inp_file, out_file, time_limit=2.0, memory_limit_mb=256):
    with open(inp_file, "r") as fin, open(out_file, "w") as fout:
        start = time.time()
        if platform.system() != "Windows":
            def set_limits():
                resource.setrlimit(resource.RLIMIT_AS, (memory_limit_mb * 1024 * 1024, resource.RLIM_INFINITY))
                resource.setrlimit(resource.RLIMIT_CPU, (int(time_limit) + 1, resource.RLIM_INFINITY))
            proc = subprocess.Popen([executable], stdin=fin, stdout=fout, preexec_fn=set_limits)
        else:
            proc = subprocess.Popen([executable], stdin=fin, stdout=fout)

        peak = 0
        while proc.poll() is None:
            time.sleep(0.05)
            peak = max(peak, get_memory_usage(proc.pid))
            if time.time() - start > time_limit + 0.5:
                proc.kill()
                return ("TLE", time.time() - start, peak)
            if peak > memory_limit_mb:
                proc.kill()
                return ("MLE", time.time() - start, peak)

        code = proc.returncode
        return ("OK" if code == 0 else "RE", time.time() - start, peak)

# ---------------------- Main ----------------------
def main():
    if len(sys.argv) < 2:
        print("Usage: python check.py <solution.cpp>")
        return

    sol_src = sys.argv[1]
    sol_exec = "solution"
    compile_code(sol_src, sol_exec)

    if os.path.exists("checker.cpp"): compile_code("checker.cpp", "checker")
    if os.path.exists("validator.cpp"): compile_code("validator.cpp", "validator")

    # tìm input trong ./tests/**/input.in
    tests = []
    if os.path.isdir("tests"):
        for root, _, files in os.walk("tests"):
            if "input.in" in files:
                tests.append(os.path.join(root, "input.in"))
    else:
        tests = [f for f in os.listdir() if f.endswith(".inp")]

    if not tests:
        print("Không tìm thấy file test nào (.inp hoặc input.in).")
        return

    os.makedirs("outputs", exist_ok=True)

    total = len(tests)
    passed = 0
    failed = 0

    for inp in sorted(tests):
        test_name = os.path.basename(os.path.dirname(inp)) or os.path.splitext(os.path.basename(inp))[0]
        out = os.path.join("outputs", f"{test_name}.out")

        print(f"\n--- {test_name} ---")

        # validator
        if os.path.exists("validator"):
            val_rc = subprocess.run(["./validator" if platform.system() != "Windows" else "validator.exe"],
                                    stdin=open(inp),
                                    stdout=subprocess.DEVNULL,
                                    stderr=subprocess.DEVNULL).returncode
            if val_rc != 0:
                print("❌ Input không hợp lệ (validator lỗi).")
                failed += 1
                continue

        # chạy solution
        verdict, t, mem = run_with_limits(f"./{sol_exec}" if platform.system() != "Windows" else f"{sol_exec}.exe", inp, out)
        if verdict != "OK":
            print(f"{verdict} | time={t:.2f}s | mem={mem:.1f}MB")
            failed += 1
            continue

        # tìm output đúng
        ans_candidates = [os.path.join(os.path.dirname(inp), "output.out"),
                          os.path.splitext(inp)[0] + ".ans"]
        ans = next((a for a in ans_candidates if os.path.exists(a)), None)

        if not ans:
            print(f"⚠️ Không có file output mẫu cho {test_name}")
            continue

        # so sánh bằng checker
        if os.path.exists("checker"):
            cmd = ["./checker" if platform.system() != "Windows" else "checker.exe", inp, out, ans]
            rc = subprocess.run(cmd).returncode
            print(f"{'✅ OK' if rc == 0 else '❌ WA'} | time={t:.2f}s | mem={mem:.1f}MB")
            if rc == 0:
                passed += 1
            else:
                failed += 1
        else:
            with open(out) as f1, open(ans) as f2:
                if f1.read().strip() == f2.read().strip():
                    print(f"✅ OK | time={t:.2f}s | mem={mem:.1f}MB")
                    passed += 1
                else:
                    print(f"❌ WA | time={t:.2f}s | mem={mem:.1f}MB")
                    failed += 1

    # ---------------------------------------------------------
    # Tổng kết kết quả
    # ---------------------------------------------------------
    print("\n==================== Summary ====================")
    print(f"Tổng số test : {total}")
    print(f"✅ Passed     : {passed}")
    print(f"❌ Failed     : {failed}")
    print("=================================================")
    if total > 0:
        rate = passed / total * 100
        print(f"🎯 Tỉ lệ đúng : {rate:.2f}%")
    print("=================================================")

if __name__ == "__main__":
    main()
