#!/usr/bin/env python3
"""
gen.py -- Python rewrite of the original gen.sh
Usage: python gen.py [base_seed]
Default base_seed = 2025
"""

import os
import sys
import shutil
import subprocess
from pathlib import Path

# --- Config (giữ giống bản bash) ---
DEFAULT_BASE_SEED = 2025
TOTAL_TESTS = 50

# Try to use g++-15 like original; fallback to g++
CANDIDATE_COMPILERS = ["g++-15", "g++"]
COMPILER = None
for c in CANDIDATE_COMPILERS:
    if shutil.which(c):
        COMPILER = c
        break
if COMPILER is None:
    print("Error: no g++ compiler found in PATH (tried g++-15, g++)")
    sys.exit(1)

# Flags from original script (kept)
FLAGS = ["-std=c++17", "-O2", "-pipe", "-s", "-Wl,-rpath,/opt/homebrew/lib"]

# Executable extension on Windows
EXE_EXT = ".exe" if os.name == "nt" else ""

def compile_if_present(src, out_name):
    """Compile src (cpp) to out_name (no extension) if src exists."""
    src_path = Path(src)
    if not src_path.exists():
        return False
    out_file = out_name + EXE_EXT
    cmd = [COMPILER] + FLAGS + [str(src_path), "-o", out_file]
    print(f"[Compile] {' '.join(cmd)}")
    try:
        subprocess.run(cmd, check=True)
        print(f"[Compile] {src} -> {out_file} OK")
        return True
    except subprocess.CalledProcessError:
        print(f"❌ Compile failed: {src}")
        sys.exit(1)

def run_cmd_to_file(cmd_list, stdout_path):
    """Run command and redirect stdout to file; raise on error."""
    with open(stdout_path, "w", encoding="utf-8") as fout:
        subprocess.run(cmd_list, stdout=fout, check=True)

def run_validator(input_path):
    """Run ./validator on input_path (if validator exists)."""
    exe = "validator" + EXE_EXT
    if not Path(exe).exists():
        return True
    try:
        with open(input_path, "r", encoding="utf-8") as fin:
            subprocess.run([f"./{exe}" if os.name != "nt" else exe], stdin=fin, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, check=True)
        return True
    except subprocess.CalledProcessError:
        return False

def run_solution_and_write_output(solution_exec, input_path, output_path):
    """Run solution on input_path and write to output_path."""
    # solution_exec can be 'solution' (compiled) or path to exe passed by user
    exe = solution_exec
    if os.name != "nt" and not exe.startswith("./") and not Path(exe).exists():
        # try with ./ prefix for POSIX
        exe = "./" + exe
    try:
        with open(input_path, "r", encoding="utf-8") as fin, open(output_path, "w", encoding="utf-8") as fout:
            subprocess.run([exe], stdin=fin, stdout=fout, stderr=subprocess.PIPE, check=True)
        return True
    except subprocess.CalledProcessError as e:
        print(f"❌ Runtime error while running {exe} on {input_path}:")
        stderr = e.stderr.decode("utf-8") if e.stderr else ""
        print(stderr)
        return False

def main():
    base_seed = int(sys.argv[1]) if len(sys.argv) > 1 else DEFAULT_BASE_SEED
    print(f"[Info] Base seed = {base_seed}")
    print("[Compile] Building...")

    # Compile components (if the files exist)
    compile_if_present("validator.cpp", "validator")
    compile_if_present("solution.cpp", "solution")
    compile_if_present("brute.cpp", "brute")
    compile_if_present("gen.cpp", "gen")

    print("[Compile] Done.")

    tests_dir = Path("tests")
    if tests_dir.exists():
        # remove existing tests directory
        import shutil
        shutil.rmtree(tests_dir)
    tests_dir.mkdir(parents=True, exist_ok=True)

    total_tests = TOTAL_TESTS
    pad_width = len(str(total_tests))

    # determine gen executable name
    gen_exec = "gen" + EXE_EXT
    if not Path(gen_exec).exists():
        print(f"Warning: {gen_exec} not found. Make sure gen was compiled earlier.")
        # still continue if user wants to run different flow
    solution_exec = "solution" + EXE_EXT
    if not Path(solution_exec).exists():
        print(f"Warning: {solution_exec} not found. Ensure solution executable is available if you want outputs generated.")

    def gen_and_run(gen_bin, typ, start, end):
        nonlocal base_seed, pad_width
        for i in range(start, end + 1):
            test_name = f"test{str(i).zfill(pad_width)}"
            test_folder = tests_dir / test_name
            test_folder.mkdir(parents=True, exist_ok=True)

            seed = base_seed + i
            input_file = test_folder / "input.in"
            expected_file = test_folder / "output.out"

            # run gen: command: ./gen type seed
            gen_cmd = [f"./{gen_bin}" if os.name != "nt" else gen_bin, str(typ), str(seed)]
            print(f"-> Generating {test_name} with: {' '.join(gen_cmd)}")
            try:
                with open(input_file, "w", encoding="utf-8") as fout:
                    subprocess.run(gen_cmd, stdout=fout, check=True)
            except subprocess.CalledProcessError:
                print(f"❌ Generation failed for {test_name} (cmd: {' '.join(gen_cmd)})")
                sys.exit(1)

            # run validator
            ok_val = run_validator(str(input_file))
            if not ok_val:
                print(f"❌ Validator failed for {test_name}")
                sys.exit(1)

            # run solution to create expected output
            if Path(solution_exec).exists():
                ok_run = run_solution_and_write_output(solution_exec if os.name == "nt" else f"./{solution_exec}", str(input_file), str(expected_file))
                if not ok_run:
                    print(f"❌ solution failed on {test_name} when creating expected output")
                    sys.exit(1)
            else:
                print(f"⚠️  solution executable not found; skipping creation of {expected_file}")

            print(f"[Gen] {gen_bin} type={typ} seed={seed} -> {test_name}")

    print("[Generate] Tests")
    # ranges as in original
    gen_and_run(gen_exec, 1, 1, 20)   # 20 Normal cases
    gen_and_run(gen_exec, 2, 21, 35)  # 15 Special
    gen_and_run(gen_exec, 3, 36, 45)  # 10 Edge
    gen_and_run(gen_exec, 4, 46, 50)  # 5 Stress

    print(f"✅ All test data generated successfully with base seed {base_seed}!")

if __name__ == "__main__":
    main()
