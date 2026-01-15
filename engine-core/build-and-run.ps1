# YUGA Engine - Build and Run Script
Write-Host "================================" -ForegroundColor Cyan
Write-Host "  YUGA Engine - Build & Run" -ForegroundColor Cyan
Write-Host "================================" -ForegroundColor Cyan
Write-Host ""

# Check if build directory exists
if (-not (Test-Path "build")) {
    Write-Host "Creating build directory..." -ForegroundColor Yellow
    New-Item -ItemType Directory -Path "build" | Out-Null
}

# Navigate to build directory
Set-Location build

Write-Host "Configuring CMake..." -ForegroundColor Yellow
cmake .. -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"

if ($LASTEXITCODE -ne 0) {
    Write-Host "CMake configuration failed!" -ForegroundColor Red
    Write-Host "Make sure vcpkg is installed and VCPKG_ROOT is set" -ForegroundColor Red
    Set-Location ..
    exit 1
}

Write-Host ""
Write-Host "Building YUGA Engine..." -ForegroundColor Yellow
cmake --build . --config Release

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed!" -ForegroundColor Red
    Set-Location ..
    exit 1
}

Write-Host ""
Write-Host "================================" -ForegroundColor Green
Write-Host "  Build Successful!" -ForegroundColor Green
Write-Host "================================" -ForegroundColor Green
Write-Host ""

# Check if executable exists
if (Test-Path "bin/Release/YUGAEngine.exe") {
    Write-Host "Running YUGA Engine..." -ForegroundColor Cyan
    Write-Host ""
    & "bin/Release/YUGAEngine.exe"
} elseif (Test-Path "bin/YUGAEngine.exe") {
    Write-Host "Running YUGA Engine..." -ForegroundColor Cyan
    Write-Host ""
    & "bin/YUGAEngine.exe"
} else {
    Write-Host "Executable not found!" -ForegroundColor Red
    Write-Host "Looking for: bin/Release/YUGAEngine.exe or bin/YUGAEngine.exe" -ForegroundColor Red
}

Set-Location ..
