# ==========================
# gen.ps1 - Generate tests
# ==========================

param(
    [int]$base_seed = 1000
)

Write-Host "[Info] Base seed = $base_seed"
Write-Host "[Compile] Building generators and solution..."

g++ -std=c++17 -O2 -pipe -static -s validator.cpp -o validator.exe
g++ -std=c++17 -O2 -pipe -static -s solution.cpp -o solution.exe
g++ -std=c++17 -O2 -pipe -static -s gen_sub1.cpp -o gen_sub1.exe
g++ -std=c++17 -O2 -pipe -static -s gen_sub2.cpp -o gen_sub2.exe

Write-Host "[Compile] Done."

Remove-Item -Recurse -Force tests -ErrorAction SilentlyContinue
New-Item -ItemType Directory -Path tests | Out-Null

$total_tests = 50
$pad_width = ($total_tests.ToString()).Length

function Gen-And-Run($gen_bin, $type, $start, $end) {
    for ($i = $start; $i -le $end; $i++) {
        $test_name = ("test{0:D$pad_width}" -f $i)
        $dir = "tests/$test_name"
        New-Item -ItemType Directory -Force -Path $dir | Out-Null

        $seed = $base_seed + $i

        & "./$gen_bin.exe" $type $seed > "$dir/input.in"
        & ./validator.exe < "$dir/input.in" > $null
        & ./solution.exe < "$dir/input.in" > "$dir/output.out"

        Write-Host "[Gen] $gen_bin type=$type seed=$seed -> $test_name"
    }
}

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

Write-Host "✅ All test data generated successfully with base seed $base_seed!"
