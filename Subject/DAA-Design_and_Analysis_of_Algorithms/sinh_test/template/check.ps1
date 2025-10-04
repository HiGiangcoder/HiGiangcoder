# ==========================
# check.ps1 - Judge script
# ==========================
# Usage: ./check.ps1 solution.cpp  hoặc ./check.ps1 solution.exe

$ErrorActionPreference = "Stop"

$TIME_LIMIT = 1      # seconds
$MEM_LIMIT_MB = 256
$MEM_LIMIT_KB = $MEM_LIMIT_MB * 1024

if ($args.Count -lt 1) {
    Write-Host "Usage: ./check.ps1 <solution.cpp or executable>"
    exit 1
}

$SRC = $args[0]
$EXEC = ""

# --- Compile nếu là .cpp ---
if ($SRC -like "*.cpp") {
    $EXEC = [System.IO.Path]::GetFileNameWithoutExtension($SRC)
    Write-Host "[Compile] Compiling $SRC -> $EXEC.exe"
    g++ -std=c++17 -O2 -pipe -static -s $SRC -o "$EXEC.exe"
} else {
    $EXEC = $SRC
    if (-not (Test-Path $EXEC)) {
        Write-Host "Error: $EXEC not found or not executable"
        exit 1
    }
}

# --- Compile validator/checker nếu có ---
if (Test-Path "validator.cpp") {
    g++ -std=c++17 -O2 -pipe -static -s validator.cpp -o validator.exe | Out-Null
}
if (Test-Path "checker.cpp") {
    g++ -std=c++17 -O2 -pipe -static -s checker.cpp -o checker.exe | Out-Null
}

# --- Lấy danh sách test ---
$tests = Get-ChildItem -Directory "tests" | Where-Object { $_.Name -match "^test" }

if ($tests.Count -eq 0) {
    Write-Host "No tests found in tests/. Run gen.ps1 first."
    exit 1
}

$pass = 0
$fail = 0
$total = 0

foreach ($t in $tests) {
    $total++
    $base = $t.Name
    $input = "$($t.FullName)/input.in"
    $expected = "$($t.FullName)/output.out"
    $userout = "$($t.FullName)/output_user.out"

    Write-Host "`n--- $base ---"

    if (-not (Test-Path $input)) {
        Write-Host "❌ Missing input: $input"
        $fail++
        continue
    }
    if (-not (Test-Path $expected)) {
        Write-Host "❌ Missing expected: $expected"
        $fail++
        continue
    }

    # --- Validator ---
    if (Test-Path "./validator.exe") {
        & ./validator.exe < $input 2>$null | Out-Null
        if ($LASTEXITCODE -ne 0) {
            Write-Host "❌ Validator failed for $base"
            $fail++
            continue
        }
    }

    # --- Run solution ---
    $timeStart = [DateTime]::Now
    try {
        $p = Start-Process "./$EXEC.exe" -RedirectStandardInput $input `
            -RedirectStandardOutput $userout -NoNewWindow -PassThru
        if (-not $p.WaitForExit($TIME_LIMIT * 1000)) {
            $p.Kill()
            $exit_code = 124  # TLE
        } else {
            $exit_code = $p.ExitCode
        }
    } catch {
        $exit_code = 1  # RTE
    }
    $timeEnd = [DateTime]::Now
    $runtime = ($timeEnd - $timeStart).TotalSeconds

    # --- Memory (approximate, không chính xác tuyệt đối như /usr/bin/time) ---
    $memMB = [math]::Round((Get-Process -Id $p.Id -ErrorAction SilentlyContinue).PeakWorkingSet64 / 1MB, 2)

    $status = "OK"
    if ($exit_code -eq 124) { $status = "TLE" }
    elseif ($exit_code -ne 0) { $status = "RTE" }
    elseif ($memMB -gt $MEM_LIMIT_MB) { $status = "MLE" }

    # --- Checker ---
    if ($status -eq "OK") {
        if (Test-Path "./checker.exe") {
            & ./checker.exe $input $userout $expected > $null 2> checker_err.txt
            if ($LASTEXITCODE -ne 0) { $status = "WA" }
        } else {
            $diff = Compare-Object (Get-Content $expected) (Get-Content $userout)
            if ($diff) { $status = "WA" }
        }
    }

    "{0,-4} | time={1:N2}s | mem={2:N2}MB" -f $status, $runtime, $memMB

    if ($status -eq "OK") { $pass++ } else { $fail++ }
}

Write-Host "`nSummary: passed=$pass failed=$fail total=$total"
