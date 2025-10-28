# ==========================
# gen.ps1 - Generate tests
# ==========================
# Usage: ./gen.ps1 [base_seed]
# Example: ./gen.ps1 1234

param(
    [int]$base_seed = 1000
)

$ErrorActionPreference = "Stop"

# --- Lấy thư mục gốc của script ---
$SCRIPT_DIR = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $SCRIPT_DIR

Write-Host "[Info] Base seed = $base_seed"
Write-Host "[Info] Working directory = $SCRIPT_DIR"
Write-Host "[Compile] Building generators and solution..."

# --- Compile tất cả chương trình cần thiết ---
$to_build = @(
    @{src="validator.cpp"; out="validator.exe"},
    @{src="solution.cpp"; out="solution.exe"},
    @{src="gen_sub1.cpp"; out="gen_sub1.exe"},
    @{src="gen_sub2.cpp"; out="gen_sub2.exe"}
)

foreach ($b in $to_build) {
    $src_path = Join-Path $SCRIPT_DIR $b.src
    $out_path = Join-Path $SCRIPT_DIR $b.out
    if (Test-Path $src_path) {
        Write-Host "  Compiling $($b.src)..."
        g++ -std=c++17 -O2 -pipe -static -s $src_path -o $out_path
    } else {
        Write-Host "  ⚠️  Warning: $($b.src) not found."
    }
}

Write-Host "[Compile] Done."

# --- Dọn và tạo lại thư mục tests ---
$tests_dir = Join-Path $SCRIPT_DIR "tests"
if (Test-Path $tests_dir) {
    Remove-Item -Recurse -Force $tests_dir
}
New-Item -ItemType Directory -Path $tests_dir | Out-Null

$total_tests = 50
$pad_width = $total_tests.ToString().Length

# --- Hàm chạy generator, validator, và solution ---
function Gen-And-Run($gen_bin, $type, $start, $end) {
    for ($i = $start; $i -le $end; $i++) {
        $test_name = ("test{0:D$pad_width}" -f $i)
        $dir = "tests/$test_name"
        New-Item -ItemType Directory -Force -Path $dir | Out-Null

        $seed = $base_seed + $i
        $input_file = "$dir/input.in"
        $output_file = "$dir/output.out"

        # Sinh input
        & "./$gen_bin.exe" $type $seed | Set-Content $input_file

        # Kiểm tra input
        $valid = Get-Content $input_file | & ./validator.exe
        if ($LASTEXITCODE -ne 0) {
            Write-Host "[Error] Validation failed for $test_name" -ForegroundColor Red
            exit 1
        }

        # Chạy solution và ghi output
        Get-Content $input_file | & ./solution.exe | Set-Content $output_file

        Write-Host "[Gen] $gen_bin type=$type seed=$seed -> $test_name"
    }
}


# --- Sinh dữ liệu ---
Write-Host "[Generate] Subtask 1"
Gen-And-Run "gen_sub1" 1 1 10
Gen-And-Run "gen_sub1" 2 11 14
Gen-And-Run "gen_sub1" 3 15 18
Gen-And-Run "gen_sub1" 4 19 20

Write-Host "[Generate] Subtask 2"
Gen-And-Run "gen_sub2" 1 21 30
Gen-And-Run "gen_sub2" 2 31 38
Gen-And-Run "gen_sub2" 3 39 45
Gen-And-Run "gen_sub2" 4 46 50

Write-Host "`n✅ All test data generated successfully with base seed $base_seed!"
