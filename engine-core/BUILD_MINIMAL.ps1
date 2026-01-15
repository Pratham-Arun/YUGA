#!/usr/bin/env pwsh
# Minimal YUGA C++ Engine Build Script
# Builds a simplified version without external dependencies

Write-Host ""
Write-Host "╔═══════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║                                                           ║" -ForegroundColor Cyan
Write-Host "║      🔧 YUGA C++ Engine - Minimal Build                  ║" -ForegroundColor Cyan
Write-Host "║                                                           ║" -ForegroundColor Cyan
Write-Host "╚═══════════════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host ""

# Check for CMake
Write-Host "📦 Checking for CMake..." -ForegroundColor Yellow
try {
    $cmakeVersion = cmake --version 2>&1 | Select-String "cmake version" | Select-Object -First 1
    Write-Host "✅ Found: $cmakeVersion" -ForegroundColor Green
} catch {
    Write-Host "❌ CMake not found!" -ForegroundColor Red
    Write-Host "   Please install CMake from: https://cmake.org/download/" -ForegroundColor Yellow
    exit 1
}

# Check for C++ Compiler
Write-Host ""
Write-Host "🔨 Checking for C++ Compiler..." -ForegroundColor Yellow

$compilerFound = $false

# Check for MSVC
try {
    $vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vsWhere) {
        Write-Host "✅ Found Visual Studio" -ForegroundColor Green
        $compilerFound = $true
    }
} catch {}

# Check for MinGW
if (-not $compilerFound) {
    try {
        $gccVersion = g++ --version 2>&1 | Select-Object -First 1
        Write-Host "✅ Found: $gccVersion" -ForegroundColor Green
        $compilerFound = $true
    } catch {}
}

if (-not $compilerFound) {
    Write-Host "❌ No C++ compiler found!" -ForegroundColor Red
    Write-Host ""
    Write-Host "Please install one of:" -ForegroundColor Yellow
    Write-Host "  • Visual Studio 2022 (Recommended)" -ForegroundColor White
    Write-Host "    https://visualstudio.microsoft.com/" -ForegroundColor Gray
    Write-Host "  • MinGW-w64" -ForegroundColor White
    Write-Host "    https://www.mingw-w64.org/" -ForegroundColor Gray
    Write-Host ""
    Write-Host "After installation, run this script again." -ForegroundColor Yellow
    exit 1
}

# Create build directory
Write-Host ""
Write-Host "📁 Creating build directory..." -ForegroundColor Yellow
if (Test-Path "build") {
    Remove-Item -Recurse -Force "build"
}
New-Item -ItemType Directory -Path "build" | Out-Null
Write-Host "✅ Build directory created" -ForegroundColor Green

# Configure with CMake
Write-Host ""
Write-Host "⚙️  Configuring CMake..." -ForegroundColor Yellow
Set-Location "build"

try {
    cmake .. 2>&1 | Out-Null
    if ($LASTEXITCODE -eq 0) {
        Write-Host "✅ CMake configuration successful" -ForegroundColor Green
    } else {
        throw "CMake configuration failed"
    }
} catch {
    Write-Host "❌ CMake configuration failed!" -ForegroundColor Red
    Write-Host "   Check CMakeLists.txt for errors" -ForegroundColor Yellow
    Set-Location ..
    exit 1
}

# Build
Write-Host ""
Write-Host "🔨 Building YUGA Engine..." -ForegroundColor Yellow
Write-Host "   This may take a few minutes..." -ForegroundColor Gray

try {
    cmake --build . --config Release 2>&1 | Out-Null
    if ($LASTEXITCODE -eq 0) {
        Write-Host "✅ Build successful!" -ForegroundColor Green
    } else {
        throw "Build failed"
    }
} catch {
    Write-Host "❌ Build failed!" -ForegroundColor Red
    Write-Host "   Check compiler errors above" -ForegroundColor Yellow
    Set-Location ..
    exit 1
}

Set-Location ..

# Check for executable
Write-Host ""
Write-Host "🔍 Checking for executable..." -ForegroundColor Yellow
$exePath = "build/bin/Release/YUGAEngineMinimal.exe"
if (-not (Test-Path $exePath)) {
    $exePath = "build/bin/YUGAEngineMinimal.exe"
}

if (Test-Path $exePath) {
    Write-Host "✅ Executable found: $exePath" -ForegroundColor Green
    Write-Host ""
    Write-Host "╔═══════════════════════════════════════════════════════════╗" -ForegroundColor Green
    Write-Host "║                                                           ║" -ForegroundColor Green
    Write-Host "║      ✨ BUILD SUCCESSFUL! ✨                              ║" -ForegroundColor Green
    Write-Host "║                                                           ║" -ForegroundColor Green
    Write-Host "╚═══════════════════════════════════════════════════════════╝" -ForegroundColor Green
    Write-Host ""
    Write-Host "Run the engine:" -ForegroundColor Cyan
    Write-Host "  .\$exePath" -ForegroundColor White
    Write-Host ""
} else {
    Write-Host "⚠️  Executable not found in expected location" -ForegroundColor Yellow
    Write-Host "   Check build/bin/ directory" -ForegroundColor Gray
}

Write-Host "Done!" -ForegroundColor Green
Write-Host ""
