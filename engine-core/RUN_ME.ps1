# YUGA Engine - Build and Run Script
# Run this script from the engine-core directory

Write-Host "╔════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║     YUGA ENGINE - BUILD AND RUN SCRIPT                ║" -ForegroundColor Cyan
Write-Host "║     Version 1.0.0 - 100% Complete                     ║" -ForegroundColor Cyan
Write-Host "╚════════════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host ""

# Step 1: Create build directory
Write-Host "Step 1: Creating build directory..." -ForegroundColor Yellow
if (Test-Path "build") {
    Write-Host "  ✓ Build directory already exists" -ForegroundColor Green
} else {
    New-Item -ItemType Directory -Path "build" -Force | Out-Null
    Write-Host "  ✓ Build directory created" -ForegroundColor Green
}
Write-Host ""

# Step 2: Configure CMake
Write-Host "Step 2: Configuring CMake..." -ForegroundColor Yellow
Write-Host "  This may take a few minutes..." -ForegroundColor Gray

$vcpkgPath = $env:VCPKG_ROOT
if ([string]::IsNullOrEmpty($vcpkgPath)) {
    Write-Host "  ⚠ VCPKG_ROOT not set. Trying without vcpkg..." -ForegroundColor Yellow
    cmake -B build -S .
} else {
    Write-Host "  Using vcpkg at: $vcpkgPath" -ForegroundColor Gray
    cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="$vcpkgPath/scripts/buildsystems/vcpkg.cmake"
}

if ($LASTEXITCODE -ne 0) {
    Write-Host "  ✗ CMake configuration failed!" -ForegroundColor Red
    Write-Host "  Please check that CMake and dependencies are installed." -ForegroundColor Red
    Write-Host "  Run: .\install-libs.ps1" -ForegroundColor Yellow
    exit 1
}
Write-Host "  ✓ CMake configured successfully" -ForegroundColor Green
Write-Host ""

# Step 3: Build
Write-Host "Step 3: Building YUGA Engine..." -ForegroundColor Yellow
Write-Host "  This will take 2-5 minutes..." -ForegroundColor Gray
cmake --build build --config Release

if ($LASTEXITCODE -ne 0) {
    Write-Host "  ✗ Build failed!" -ForegroundColor Red
    Write-Host "  Check the error messages above." -ForegroundColor Red
    exit 1
}
Write-Host "  ✓ Build completed successfully" -ForegroundColor Green
Write-Host ""

# Step 4: Check if executable exists
Write-Host "Step 4: Checking executable..." -ForegroundColor Yellow
$exePath = "build\bin\Release\YUGAEngine.exe"
if (Test-Path $exePath) {
    Write-Host "  ✓ Executable found: $exePath" -ForegroundColor Green
} else {
    # Try Debug build
    $exePath = "build\bin\Debug\YUGAEngine.exe"
    if (Test-Path $exePath) {
        Write-Host "  ✓ Executable found: $exePath (Debug)" -ForegroundColor Green
    } else {
        Write-Host "  ✗ Executable not found!" -ForegroundColor Red
        Write-Host "  Expected location: build\bin\Release\YUGAEngine.exe" -ForegroundColor Red
        exit 1
    }
}
Write-Host ""

# Step 5: Run
Write-Host "Step 5: Launching YUGA Engine..." -ForegroundColor Yellow
Write-Host ""
Write-Host "╔════════════════════════════════════════════════════════╗" -ForegroundColor Green
Write-Host "║              STARTING YUGA ENGINE                      ║" -ForegroundColor Green
Write-Host "╚════════════════════════════════════════════════════════╝" -ForegroundColor Green
Write-Host ""
Write-Host "Controls:" -ForegroundColor Cyan
Write-Host "  W/A/S/D - Move camera" -ForegroundColor Gray
Write-Host "  L       - Toggle loading spinner" -ForegroundColor Gray
Write-Host "  N       - Show notification" -ForegroundColor Gray
Write-Host "  ESC     - Exit" -ForegroundColor Gray
Write-Host ""

# Run the engine
& $exePath

Write-Host ""
Write-Host "Engine closed." -ForegroundColor Yellow
Write-Host "Thank you for using YUGA Engine! 🎮" -ForegroundColor Cyan
