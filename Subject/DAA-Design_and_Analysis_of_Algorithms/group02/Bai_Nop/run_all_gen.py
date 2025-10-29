import os
import subprocess

LOG_FILE = "log.txt"

def run_all_gen_scripts(root="."):
    with open(LOG_FILE, "w") as log:
        for dirpath, _, filenames in os.walk(root):
            if "gen.sh" in filenames:
                gen_path = os.path.join(dirpath, "gen.sh")
                log.write(f"▶️ Running: {gen_path}\n")
                print(f"▶️ Running: {gen_path}")

                try:
                    result = subprocess.run(
                        ["bash", "gen.sh"],
                        cwd=dirpath,
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE,
                        text=True,
                        timeout=120
                    )
                    if result.returncode == 0:
                        log.write("✅ Success\n")
                        print("✅ Success")
                    else:
                        log.write(f"❌ Failed ({result.returncode}):\n{result.stderr}\n")
                        print("❌ Failed:", result.stderr.strip())
                except Exception as e:
                    log.write(f"💥 Error: {e}\n")
                    print(f"💥 Error: {e}")
                log.write("-" * 60 + "\n")

if __name__ == "__main__":
    run_all_gen_scripts(".")
