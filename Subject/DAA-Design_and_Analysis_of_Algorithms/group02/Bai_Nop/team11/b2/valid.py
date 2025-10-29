import os
import subprocess

INPUT_DIR = "input"
VALIDATOR = "validator.exe"

for i in range(1, 101):
    infile = os.path.join(INPUT_DIR, f"test{i}.in")
    print(f"Checking {infile}...")
    result = subprocess.run([VALIDATOR], stdin=open(infile, "r"))
    if result.returncode == 0:
        print("   OK")
    else:
        print("   INVALID")
