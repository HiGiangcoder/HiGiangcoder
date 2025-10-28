import os


for file in os.listdir():
    os.system(f"echo {file}")
    os.system(f"cat {file}")