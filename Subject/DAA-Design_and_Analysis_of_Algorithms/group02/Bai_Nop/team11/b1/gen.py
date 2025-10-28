import os, time, platform

NUM_TESTS = 100
SUB1_COUNT = 30     # số test cho subtask 1
GEN1 = "gen_sub1"
GEN2 = "gen_sub2"
SOL = "brute"
TESTS_DIR = "tests"

# Nếu là Windows thì thêm .exe
if platform.system() == "Windows":
    GEN1 += ".exe"
    GEN2 += ".exe"
    SOL += ".exe"

os.makedirs(TESTS_DIR, exist_ok=True)

# Xóa file cũ

# Sinh test
for i in range(1, NUM_TESTS + 1):
    TEST_DIR = f"{TESTS_DIR}/test{i}"
    os.makedirs(TEST_DIR, exist_ok=True)
    if i <= SUB1_COUNT:
        gen = GEN1
    else:
        gen = GEN2

    print(f"[{i}] Generating with {gen}...")

    os.system(f"./{gen} {i} > {TEST_DIR}/input.in")

    start = time.time()
    os.system(f"./{SOL} < {TEST_DIR}/input.in > {TEST_DIR}/output.out")
    elapsed = time.time() - start

    print(f"     Done in {elapsed:.3f}s")
