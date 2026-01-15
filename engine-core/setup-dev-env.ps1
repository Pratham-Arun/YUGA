# YUGA Engine - Complete Development Environment Setup
# Installs all necessary tools for C++ game engine development

Write-Host "`n╔════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║   🛠️ YUGA Engine - Dev Environment Setup 🛠️   ║" -ForegroundColor Cyan
Write-Host "╚════════════════════════════════════════════════╝`n" -ForegroundColor Cyan

# Check if running as Administrator
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)

if (-not $isAdmin) {
    Write-Host "⚠️ This script requires Administrator privileges" -ForegroundColor Yellow
    Write-Host "Please run PowerShell as Administrator and try again`n" -ForegroundColor Yellow
    exit 1
}

Write-Host "✓ Running with Administrator privileges`n" -ForegroundColor Green

# 1. Install Chocolatey
Write-Host "1️⃣ Checking Chocolatey..." -ForegroundColor Yellow
if (!(Get-Command choco -ErrorAction SilentlyContinue)) {
    Write-Host "   Installing Chocolatey..." -ForegroundColor White
    Set-ExecutionPolicy Bypass -Scope Process -Force
    [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
    iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
    Write-Host "   ✓ Chocolatey installed" -ForegroundColor Green
} else {
    Write-Host "   ✓ Chocolatey already installed" -ForegroundColor Green
}

# 2. Install CMake
Write-Host "`n2️⃣ Installing CMake..." -ForegroundColor Yellow
choco install cmake -y
Write-Host "   ✓ CMake installed" -ForegroundColor Green

# 3. Install Git
Write-Host "`n3️⃣ Installing Git..." -ForegroundColor Yellow
choco install git -y
Write-Host "   ✓ Git installed" -ForegroundColor Green

# 4. Install Visual Studio Code
Write-Host "`n4️⃣ Installing Visual Studio Code..." -ForegroundColor Yellow
choco install vscode -y
Write-Host "   ✓ VS Code installed" -ForegroundColor Green

# 5. Install vcpkg
Write-Host "`n5️⃣ Installing vcpkg..." -ForegroundColor Yellow
if (!(Test-Path C:\vcpkg)) {
    git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
    C:\vcpkg\bootstrap-vcpkg.bat
    C:\vcpkg\vcpkg integrate install
    Write-Host "   ✓ vcpkg installed" -ForegroundColor Green
} else {
    Write-Host "   ✓ vcpkg already installed" -ForegroundColor Green
}

# 6. Install VS Code Extensions
Write-Host "`n6️⃣ Installing VS Code extensions..." -ForegroundColor Yellow
$extensions = @(
    "ms-vscode.cpptools",
    "ms-vscode.cmake-tools",
    "twxs.cmake",
    "eamodio.gitlens"
)

foreach ($ext in $extensions) {
    code --install-extension $ext --force
}
Write-Host "   ✓ Extensions installed" -ForegroundColor Green

# 7. Install Graphics Libraries
Write-Host "`n7️⃣ Installing graphics libraries..." -ForegroundColor Yellow
Write-Host "   This may take 5-10 minutes..." -ForegroundColor White
C:\vcpkg\vcpkg install glfw3:x64-windows glad:x64-windows glm:x64-windows stb:x64-windows
Write-Host "   ✓ Graphics libraries installed" -ForegroundColor Green

# Summary
Write-Host "`n╔════════════════════════════════════════════════╗" -ForegroundColor Green
Write-Host "║          ✓ SETUP COMPLETE! ✓                   ║" -ForegroundColor Green
Write-Host "╚════════════════════════════════════════════════╝`n" -ForegroundColor Green

Write-Host "📊 Installed Tools:" -ForegroundColor Yellow
Write-Host "   ✓ CMake" -ForegroundColor Green
Write-Host "   ✓ Git" -ForegroundColor Green
Write-Host "   ✓ Visual Studio Code" -ForegroundColor Green
Write-Host "   ✓ vcpkg" -ForegroundColor Green
Write-Host "   ✓ GLFW, GLAD, GLM, STB" -ForegroundColor Green

Write-Host "`n📝 Next steps:" -ForegroundColor Yellow
Write-Host "   1. Restart your terminal" -ForegroundColor White
Write-Host "   2. cd engine-core" -ForegroundColor White
Write-Host "   3. cmake -B build" -ForegroundColor White
Write-Host "   4. cmake --build build --config Release" -ForegroundColor White
Write-Host "   5. .\build\bin\Release\YUGAEngine.exe`n" -ForegroundColor White

Write-Host "🎉 Ready to build YUGA Engine!`n" -ForegroundColor Magenta
