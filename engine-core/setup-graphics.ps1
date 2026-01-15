# YUGA Engine - Graphics Setup Script
# Automatically installs GLFW and GLAD using vcpkg

Write-Host "`n╔════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║   🎨 YUGA Engine - Graphics Setup Script 🎨   ║" -ForegroundColor Cyan
Write-Host "╚════════════════════════════════════════════════╝`n" -ForegroundColor Cyan

$vcpkgPath = "C:\vcpkg"
$vcpkgExists = Test-Path $vcpkgPath

if ($vcpkgExists) {
    Write-Host "✓ vcpkg found at $vcpkgPath" -ForegroundColor Green
} else {
    Write-Host "⚠ vcpkg not found. Installing..." -ForegroundColor Yellow
    Write-Host "This may take 5-10 minutes...`n" -ForegroundColor Yellow
    
    # Clone vcpkg
    Write-Host "1. Cloning vcpkg..." -ForegroundColor White
    git clone https://github.com/Microsoft/vcpkg.git $vcpkgPath
    
    if (-not $?) {
        Write-Host "✗ Failed to clone vcpkg" -ForegroundColor Red
        exit 1
    }
    
    # Bootstrap
    Write-Host "2. Bootstrapping vcpkg..." -ForegroundColor White
    & "$vcpkgPath\bootstrap-vcpkg.bat"
    
    if (-not $?) {
        Write-Host "✗ Failed to bootstrap vcpkg" -ForegroundColor Red
        exit 1
    }
    
    # Integrate with Visual Studio
    Write-Host "3. Integrating with Visual Studio..." -ForegroundColor White
    & "$vcpkgPath\vcpkg.exe" integrate install
    
    Write-Host "✓ vcpkg installed successfully!`n" -ForegroundColor Green
}

# Install GLFW and GLAD
Write-Host "Installing graphics libraries..." -ForegroundColor Yellow
Write-Host "  • GLFW (windowing)" -ForegroundColor White
Write-Host "  • GLAD (OpenGL loader)`n" -ForegroundColor White

& "$vcpkgPath\vcpkg.exe" install glfw3:x64-windows glad:x64-windows

if ($?) {
    Write-Host "`n✓ Graphics libraries installed successfully!" -ForegroundColor Green
} else {
    Write-Host "`n✗ Failed to install libraries" -ForegroundColor Red
    exit 1
}

# Update CMakeLists.txt
Write-Host "`nUpdating CMakeLists.txt..." -ForegroundColor Yellow

$cmakeFile = "CMakeLists.txt"
$cmakeContent = Get-Content $cmakeFile -Raw

if ($cmakeContent -notmatch "CMAKE_TOOLCHAIN_FILE") {
    $toolchainLine = "`nset(CMAKE_TOOLCHAIN_FILE `"$vcpkgPath/scripts/buildsystems/vcpkg.cmake`")`n"
    $cmakeContent = $cmakeContent -replace "(project\(YUGAEngine.*\))", "`$1$toolchainLine"
    
    $cmakeContent | Set-Content $cmakeFile
    Write-Host "✓ CMakeLists.txt updated" -ForegroundColor Green
} else {
    Write-Host "✓ CMakeLists.txt already configured" -ForegroundColor Green
}

# Summary
Write-Host "`n╔════════════════════════════════════════════════╗" -ForegroundColor Green
Write-Host "║          ✓ SETUP COMPLETE! ✓                   ║" -ForegroundColor Green
Write-Host "╚════════════════════════════════════════════════╝`n" -ForegroundColor Green

Write-Host "📝 Next steps:" -ForegroundColor Yellow
Write-Host "  1. Uncomment OpenGL code in source files" -ForegroundColor White
Write-Host "  2. Build: cmake -B build" -ForegroundColor White
Write-Host "  3. Compile: cmake --build build --config Release" -ForegroundColor White
Write-Host "  4. Run: .\build\bin\Release\YUGAEngine.exe`n" -ForegroundColor White

Write-Host "📚 See SETUP_GRAPHICS.md for detailed instructions`n" -ForegroundColor Cyan
