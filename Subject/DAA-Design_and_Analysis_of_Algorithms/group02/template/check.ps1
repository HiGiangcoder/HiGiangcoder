# ==========================
# check.ps1 - Judge script
# ==========================
# Usage: ./check.ps1 solution.cpp  hoặc ./check.ps1 solution.exe
# Phiên bản PowerShell — tương thích Windows (PowerShell 5.1+ / pwsh)

$ErrorActionPreference = "Stop"

# Config
$TIME_LIMIT = 1      # seconds
$MEM_LIMIT_MB = 256

# Set working dir to script folder
$SCRIPT_DIR = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $SCRIPT_DIR

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
    & g++ -std=c++17 -O2 -pipe -static -s $SRC -o "$EXEC.exe"
    if ($LASTEXITCODE -ne 0) {
        Write-Host "❌ Compile failed for $SRC"
        exit 1
    }
} else {
    $EXEC = $SRC
    if (-not (Test-Path $EXEC)) {
        Write-Host "Error: $EXEC not found or not executable"
        exit 1
    }
}

# --- Compile validator/checker nếu có ---
if (Test-Path "validator.cpp") {
    Write-Host "[Compile] Building validator.cpp -> validator.exe"
    & g++ -std=c++17 -O2 -pipe -static -s validator.cpp -o validator.exe | Out-Null
}
if (Test-Path "checker.cpp") {
    Write-Host "[Compile] Building checker.cpp -> checker.exe"
    & g++ -std=c++17 -O2 -pipe -static -s checker.cpp -o checker.exe | Out-Null
}

# --- Get tests ---
$testsDir = Join-Path $SCRIPT_DIR "tests"
if (-not (Test-Path $testsDir)) {
    Write-Host "No tests found in tests/. Run gen.ps1 first."
    exit 1
}
$tests = Get-ChildItem -Directory $testsDir | Where-Object { $_.Name -match "^test" } | Sort-Object Name
if ($tests.Count -eq 0) {
    Write-Host "No tests found in tests/. Run gen.ps1 first."
    exit 1
}

# --- Prepare outputs folder ---
$outputsDir = Join-Path $SCRIPT_DIR "outputs"
if (-not (Test-Path $outputsDir)) {
    New-Item -ItemType Directory -Path $outputsDir | Out-Null
} else {
    # clean existing files in outputs (keep folder)
    Get-ChildItem -Path $outputsDir -File -ErrorAction SilentlyContinue | Remove-Item -Force -ErrorAction SilentlyContinue
}

$pass = 0
$fail = 0
$total = 0

foreach ($t in $tests) {
    $total++
    $base = $t.Name
    $input = Join-Path $t.FullName "input.in"
    $expected = Join-Path $t.FullName "output.out"
    # user output now goes to outputs/<testname>.out
    $userout = Join-Path $outputsDir ("{0}.out" -f $base)

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

    # --- Validator (if exist) ---
    $validatorPath = Join-Path $SCRIPT_DIR "validator.exe"
    if (Test-Path $validatorPath) {
        $tmpOut = [System.IO.Path]::GetTempFileName()
        $tmpErr = [System.IO.Path]::GetTempFileName()
        try {
            $pv = Start-Process -FilePath $validatorPath -ArgumentList @() `
                -RedirectStandardInput $input -RedirectStandardOutput $tmpOut -RedirectStandardError $tmpErr `
                -NoNewWindow -PassThru
            if (-not $pv.WaitForExit(5000)) {
                try { Stop-Process -Id $pv.Id -Force -ErrorAction SilentlyContinue } catch {}
                Write-Host "❌ Validator timed out for $base"
                $fail++
                continue
            }
            if ($pv.ExitCode -ne 0) {
                $err = Get-Content -Raw $tmpErr -ErrorAction SilentlyContinue
                Write-Host "❌ Validator failed for $base (exit=$($pv.ExitCode))"
                if ($err) { Write-Host "Validator stderr: $err" }
                $fail++
                continue
            }
        } finally {
            Remove-Item -Force -ErrorAction SilentlyContinue $tmpOut, $tmpErr
        }
    }

    # --- Run solution with memory/time measurement ---
    $timeStart = Get-Date
    $exit_code = 0
    $memMB = 0.00
    try {
        $exePath = Join-Path $SCRIPT_DIR $EXEC
        if (-not (Test-Path $exePath) -and (Test-Path "$exePath.exe")) {
            $exePath = "$exePath.exe"
        }
        # ensure exists
        if (-not (Test-Path $exePath)) {
            Write-Host "Error: executable not found: $exePath"
            $fail++
            continue
        }

        # Start process redirecting stdin from file and stdout directly to outputs/<test>.out
        $tmpErr2 = [System.IO.Path]::GetTempFileName()
        $proc = Start-Process -FilePath $exePath -ArgumentList @() `
            -RedirectStandardInput $input -RedirectStandardOutput $userout -RedirectStandardError $tmpErr2 `
            -NoNewWindow -PassThru

        # Poll memory while running, track peak
        $memPeak = 0.0
        $startTime = Get-Date
        while (-not $proc.HasExited) {
            Start-Sleep -Milliseconds 50
            try {
                $pinfo = Get-Process -Id $proc.Id -ErrorAction SilentlyContinue
                if ($pinfo) {
                    $memNow = [math]::Round(($pinfo.WorkingSet64 / 1MB), 2)
                    if ($memNow -gt $memPeak) { $memPeak = $memNow }
                }
            } catch {
                # ignore
            }
            if (((Get-Date) - $startTime).TotalSeconds -gt $TIME_LIMIT) {
                try { Stop-Process -Id $proc.Id -Force -ErrorAction SilentlyContinue } catch {}
                $exit_code = 124
                break
            }
        }

        # If process still not exited, wait small time for cleanup
        if (-not $proc.HasExited) {
            $proc.WaitForExit(2000)  # give a little time
        }

        # read possible stderr for debugging (optional)
        $stderrText = ""
        try { $stderrText = Get-Content -Raw $tmpErr2 -ErrorAction SilentlyContinue } catch {}
        Remove-Item -Force -ErrorAction SilentlyContinue $tmpErr2

        if ($exit_code -ne 124) {
            # get exit code if available
            try { $exit_code = $proc.ExitCode } catch { $exit_code = $exit_code }
        }

        # Determine final mem: try PeakWorkingSet64, else use sampled peak
        try {
            $peak = 0
            try { $peak = $proc.PeakWorkingSet64 } catch {}
            if ($peak -gt 0) {
                $memMB = [math]::Round(($peak / 1MB), 2)
            } else {
                $memMB = $memPeak
            }
        } catch {
            $memMB = $memPeak
        }

        # if process produced stderr and runtime error, show small hint
        if ($exit_code -ne 0 -and $stderrText) {
            Write-Host "Note: program stderr (truncated):"
            $stderrText.Substring(0, [math]::Min($stderrText.Length, 400)) | Write-Host
        }
    } catch {
        $exit_code = 1
        $memMB = 0.0
    }
    $timeEnd = Get-Date
    $runtime = ([math]::Round((($timeEnd - $timeStart).TotalSeconds), 2))

    # --- Decide status ---
    $status = "OK"
    if ($exit_code -eq 124) { $status = "TLE" }
    elseif ($exit_code -ne 0) { $status = "RTE" }
    elseif ($memMB -gt $MEM_LIMIT_MB) { $status = "MLE" }

    # --- Checker ---
    if ($status -eq "OK") {
        $checkerPath = Join-Path $SCRIPT_DIR "checker.exe"
        if (Test-Path $checkerPath) {
            & $checkerPath $input $userout $expected | Out-Null
            if ($LASTEXITCODE -ne 0) { $status = "WA" }
        } else {
            $diff = Compare-Object (Get-Content $expected -Raw) (Get-Content $userout -Raw)
            if ($diff) { $status = "WA" }
        }
    }

    "{0,-4} | time={1:N2}s | mem={2:N2}MB" -f $status, $runtime, $memMB

    if ($status -eq "OK") { $pass++ } else { $fail++ }
}

Write-Host "`nSummary: passed=$pass failed=$fail total=$total"
