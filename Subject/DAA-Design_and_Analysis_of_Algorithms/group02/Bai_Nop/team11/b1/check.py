import os, time, subprocess, platform

NUM_TESTS = 100
SUB1_COUNT = 30
TIME_LIMIT_SUB1 = 1.0   # seconds for small tests
TIME_LIMIT_SUB2 = 2.0   # seconds for large tests

GEN1 = "gen_sub1"
GEN2 = "gen_sub2"
BRUTE = "solution"
SUBMIT = "test"
INPUT_DIR = "input"
OUTPUT_DIR = "output"
SUB_OUTPUT_DIR = "sub_output"

if platform.system() == "Windows":
    GEN1 += ".exe"; GEN2 += ".exe"; BRUTE += ".exe"; SUBMIT += ".exe"

os.makedirs(SUB_OUTPUT_DIR, exist_ok=True)

ok = wa = tle = rte = miss = invalid = 0

def abs_path(name):
    return os.path.abspath(name)

for i in range(1, NUM_TESTS + 1):
    infile = os.path.join(INPUT_DIR, f"test{i}.in")
    correct_out = os.path.join(OUTPUT_DIR, f"test{i}.out")
    sub_out = os.path.join(SUB_OUTPUT_DIR, f"test{i}.out")

    print(f"[{i}] ", end="")

    if not os.path.isfile(infile) or not os.path.isfile(correct_out):
        print("MISSING")
        miss += 1
        continue

    # choose timeout by subtask
    timeout = TIME_LIMIT_SUB1 if i <= SUB1_COUNT else TIME_LIMIT_SUB2

    # run submission
    try:
        start = time.time()
        with open(infile, "rb") as fin, open(sub_out, "wb") as fout:
            proc = subprocess.run([abs_path(SUBMIT)], stdin=fin, stdout=fout, stderr=subprocess.PIPE, timeout=timeout)
        elapsed = time.time() - start
    except subprocess.TimeoutExpired:
        print(f"Time Limit Exceed ({timeout:.2f}s)")
        tle += 1
        if os.path.exists(sub_out): os.remove(sub_out)
        continue
    except FileNotFoundError:
        print("SUB_NOT_FOUND")
        miss += 1
        break

    if proc.returncode != 0:
        print(f"Runtime Error ({elapsed:.3f}s)")
        rte += 1
        continue

    # compare ignoring whitespace
    try:
        with open(correct_out, "r", errors="ignore") as f1, open(sub_out, "r", errors="ignore") as f2:
            ok_flag = (f1.read().split() == f2.read().split())
    except Exception:
        print("ERR_READ")
        miss += 1
        continue

    if ok_flag:
        print(f"ACCEPTED ({elapsed:.3f}s)")
        ok += 1
    else:
        print(f"WRONG ANSWER ({elapsed:.3f}s)")
        wa += 1

print(f"\nSUMMARY: ACCEPTED={ok} WRONG ANSWER={wa} Time Limit Exceed={tle} Runtime Error={rte} MISSING={miss}")
