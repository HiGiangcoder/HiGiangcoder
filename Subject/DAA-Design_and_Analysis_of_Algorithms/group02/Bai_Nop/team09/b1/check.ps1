# ==========================
# check.ps1 - fixed runtime input version
# ==========================
$ErrorActionPreference = "Stop"
$TIME_LIMIT = 1
$MEM_LIMIT_MB = 256

$SCRIPT_DIR = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $SCRIPT_DIR

if ($args.Count -lt 1) {
    Write-Host "Usage: ./check.ps1 <solution.cpp or exe>"
    exit 1
}

$SRC = $args[0]
$EXEC = ""

# --- Compile if .cpp ---
if ($SRC -like "*.cpp") {
    $EXEC = [System.IO.Path]::GetFileNameWithoutExtension($SRC)
    Write-Host "[Compile] Compiling $SRC -> $EXEC.exe"
    & g++ -std=c++17 -O2 -pipe -static -s $SRC -o "$EXEC.exe"
    if ($LASTEXITCODE -ne 0) {
        Write-Host "❌ Compile failed for $SRC"
        exit 1
    }
} else {
    $EXEC = $SRC
}

# --- Build validator/checker if needed ---
if (Test-Path "validator.cpp") {
    Write-Host "[Compile] validator.cpp -> validator.exe"
    & g++ -std=c++17 -O2 -pipe -static -s validator.cpp -o validator.exe
}
if (Test-Path "checker.cpp") {
    Write-Host "[Compile] checker.cpp -> checker.exe"
    & g++ -std=c++17 -O2 -pipe -static -s checker.cpp -o checker.exe
}

$testsDir = Join-Path $SCRIPT_DIR "tests"
$outputsDir = Join-Path $SCRIPT_DIR "outputs"
if (-not (Test-Path $outputsDir)) { New-Item -ItemType Directory -Path $outputsDir | Out-Null }

$tests = Get-ChildItem -Directory $testsDir | Sort-Object Name
$pass = 0; $fail = 0; $total = 0

foreach ($t in $tests) {
    $total++
    $base = $t.Name
    $input = Join-Path $t.FullName "input.in"
    $expected = Join-Path $t.FullName "output.out"
    $userout = Join-Path $outputsDir ("$base.out")

    Write-Host "`n--- $base ---"

    if (-not (Test-Path $input)) { Write-Host "❌ Missing input"; $fail++; continue }
    if (-not (Test-Path $expected)) { Write-Host "❌ Missing expected"; $fail++; continue }

    # --- Run solution with redirected stdin/stdout ---
    $exePath = if (Test-Path "$EXEC.exe") { "$SCRIPT_DIR\$EXEC.exe" } else { "$SCRIPT_DIR\$EXEC" }
    $psi = New-Object System.Diagnostics.ProcessStartInfo
    $psi.FileName = $exePath
    $psi.RedirectStandardInput = $true
    $psi.RedirectStandardOutput = $true
    $psi.RedirectStandardError = $true
    $psi.UseShellExecute = $false
    $psi.CreateNoWindow = $true

    $proc = New-Object System.Diagnostics.Process
    $proc.StartInfo = $psi

    $null = $proc.Start()
    $inputData = Get-Content -Raw $input
    $proc.StandardInput.Write($inputData)
    $proc.StandardInput.Close()

    $t0 = Get-Date
    while (-not $proc.HasExited) {
        if (((Get-Date) - $t0).TotalSeconds -gt $TIME_LIMIT) {
            $proc.Kill()
            $status = "TLE"
            break
        }
        Start-Sleep -Milliseconds 50
    }

    if (-not $status) {
        $status = if ($proc.ExitCode -ne 0) { "RTE" } else { "OK" }
    }

    $runtime = [math]::Round(((Get-Date) - $t0).TotalSeconds, 2)
    $outputData = $proc.StandardOutput.ReadToEnd()
    Set-Content -Value $outputData -Path $userout

    if ($status -eq "OK") {
        if (Test-Path "checker.exe") {
            & .\checker.exe $input $userout $expected | Out-Null
            if ($LASTEXITCODE -ne 0) { $status = "WA" }
        } else {
            $diff = Compare-Object (Get-Content $expected -Raw) (Get-Content $userout -Raw)
            if ($diff) { $status = "WA" }
        }
    }

    "{0,-4} | time={1:N2}s" -f $status, $runtime
    if ($status -eq "OK") { $pass++ } else { $fail++ }
}

Write-Host "`nSummary: passed=$pass failed=$fail total=$total"
