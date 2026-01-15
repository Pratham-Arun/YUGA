# Build YUGA Engine with Workflow System

Write-Host "╔════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║   YUGA ENGINE - AI-POWERED WORKFLOW BUILD             ║" -ForegroundColor Cyan
Write-Host "╚════════════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host ""

# Use the complete CMakeLists
Write-Host "Step 1: Preparing build configuration..." -ForegroundColor Yellow
Copy-Item "CMakeLists_Complete.txt" "CMakeLists.txt" -Force
Write-Host "  ✓ Using complete configuration with Workflow system" -ForegroundColor Green
Write-Host ""

# Create build directory
Write-Host "Step 2: Creating build directory..." -ForegroundColor Yellow
if (-not (Test-Path "build_workflow")) {
    New-Item -ItemType Directory -Path "build_workflow" | Out-Null
}
Write-Host "  ✓ Build directory ready" -ForegroundColor Green
Write-Host ""

# Configure
Write-Host "Step 3: Configuring CMake..." -ForegroundColor Yellow
cmake -B build_workflow -S . 2>&1 | Out-Null
if ($LASTEXITCODE -eq 0) {
    Write-Host "  ✓ Configuration successful" -ForegroundColor Green
} else {
    Write-Host "  ✗ Configuration failed" -ForegroundColor Red
    exit 1
}
Write-Host ""

# Build
Write-Host "Step 4: Building YUGA Engine with Workflow..." -ForegroundColor Yellow
Write-Host "  This may take 1-2 minutes..." -ForegroundColor Gray
cmake --build build_workflow --config Release 2>&1 | Out-Null
if ($LASTEXITCODE -eq 0) {
    Write-Host "  ✓ Build successful!" -ForegroundColor Green
} else {
    Write-Host "  ✗ Build failed" -ForegroundColor Red
    Write-Host "  Check build_workflow/ for details" -ForegroundColor Yellow
    exit 1
}
Write-Host ""

# Check executable
Write-Host "Step 5: Checking executable..." -ForegroundColor Yellow
$exePath = "build_workflow/bin/Release/YUGAEngineWorkflow.exe"
if (Test-Path $exePath) {
    Write-Host "  ✓ Executable found!" -ForegroundColor Green
    Write-Host ""
    
    # Run
    Write-Host "╔════════════════════════════════════════════════════════╗" -ForegroundColor Green
    Write-Host "║        LAUNCHING YUGA WORKFLOW DEMO                    ║" -ForegroundColor Green
    Write-Host "╚════════════════════════════════════════════════════════╝" -ForegroundColor Green
    Write-Host ""
    Write-Host "Watch the complete AI-powered workflow in action!" -ForegroundColor Cyan
    Write-Host ""
    
    & $exePath
    
    Write-Host ""
    Write-Host "Demo complete! 🎉" -ForegroundColor Green
} else {
    Write-Host "  ✗ Executable not found" -ForegroundColor Red
    Write-Host "  Expected: $exePath" -ForegroundColor Yellow
}
