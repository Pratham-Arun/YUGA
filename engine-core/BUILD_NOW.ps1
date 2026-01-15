# YUGA Engine - Simple Build Script
Write-Host "Building YUGA Engine..." -ForegroundColor Cyan

# Create build directory
if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Path "build" | Out-Null
}

# Configure
Write-Host "Configuring..." -ForegroundColor Yellow
cmake -B build -S .

# Build
Write-Host "Building..." -ForegroundColor Yellow
cmake --build build --config Release

# Check result
if (Test-Path "build/bin/Release/YUGAEngine.exe") {
    Write-Host "Build successful!" -ForegroundColor Green
    Write-Host "Running engine..." -ForegroundColor Cyan
    Start-Process "build/bin/Release/YUGAEngine.exe"
} elseif (Test-Path "build/bin/Debug/YUGAEngine.exe") {
    Write-Host "Build successful (Debug)!" -ForegroundColor Green
    Write-Host "Running engine..." -ForegroundColor Cyan
    Start-Process "build/bin/Debug/YUGAEngine.exe"
} else {
    Write-Host "Build failed or executable not found" -ForegroundColor Red
}
