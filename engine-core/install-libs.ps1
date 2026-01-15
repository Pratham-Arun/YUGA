# YUGA Engine - Simple Library Installer
# Run as Administrator

Write-Host "`n╔════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║   YUGA Engine - Library Installation          ║" -ForegroundColor Cyan
Write-Host "╚════════════════════════════════════════════════╝`n" -ForegroundColor Cyan

# Check if running as Administrator
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)

if (-not $isAdmin) {
    Write-Host "ERROR: This script requires Administrator privileges" -ForegroundColor Red
    Write-Host "Please run PowerShell as Administrator and try again`n" -ForegroundColor Yellow
    exit 1
}

Write-Host "Running with Administrator privileges`n" -ForegroundColor Green

# 1. Install Chocolatey
Write-Host "1. Checking Chocolatey..." -ForegroundColor Yellow
if (!(Get-Command choco -ErrorAction SilentlyContinue)) {
    Write-Host "   Installing Chocolatey..." -ForegroundColor White
    Set-ExecutionPolicy Bypass -Scope Process -Force
    [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
    iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
    Write-Host "   Chocolatey installed" -ForegroundColor Green
} else {
    Write-Host "   Chocolatey already installed" -ForegroundColor Green
}

# 2. Install Git
Write-Host "`n2. Installing Git..." -ForegroundColor Yellow
choco install git -y
Write-Host "   Git installed" -ForegroundColor Green

# 3. Install vcpkg
Write-Host "`n3. Installing vcpkg..." -ForegroundColor Yellow
if (!(Test-Path C:\vcpkg)) {
    git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
    C:\vcpkg\bootstrap-vcpkg.bat
    C:\vcpkg\vcpkg integrate install
    Write-Host "   vcpkg installed" -ForegroundColor Green
} else {
    Write-Host "   vcpkg already installed" -ForegroundColor Green
}

# 4. Install Graphics Libraries
Write-Host "`n4. Installing graphics libraries..." -ForegroundColor Yellow
Write-Host "   This may take 5-10 minutes..." -ForegroundColor White
C:\vcpkg\vcpkg install glfw3:x64-windows glad:x64-windows glm:x64-windows
Write-Host "   Graphics libraries installed" -ForegroundColor Green

# 5. Install Asset Pipeline Libraries
Write-Host "`n5. Installing asset pipeline libraries..." -ForegroundColor Yellow
Write-Host "   Installing Assimp (model loading)..." -ForegroundColor White
C:\vcpkg\vcpkg install assimp:x64-windows
Write-Host "   Installing STB (image loading)..." -ForegroundColor White
C:\vcpkg\vcpkg install stb:x64-windows
Write-Host "   Asset pipeline libraries installed" -ForegroundColor Green

# 6. Install Physics & Audio Libraries
Write-Host "`n6. Installing physics and audio libraries..." -ForegroundColor Yellow
C:\vcpkg\vcpkg install bullet3:x64-windows openal-soft:x64-windows
Write-Host "   Physics and audio libraries installed" -ForegroundColor Green

# 7. Install ECS & Scripting Libraries
Write-Host "`n7. Installing ECS and scripting libraries..." -ForegroundColor Yellow
C:\vcpkg\vcpkg install entt:x64-windows lua:x64-windows
Write-Host "   ECS and scripting libraries installed" -ForegroundColor Green

# 8. Install UI Library
Write-Host "`n8. Installing UI library..." -ForegroundColor Yellow
C:\vcpkg\vcpkg install imgui[glfw-binding,opengl3-binding]:x64-windows
Write-Host "   UI library installed" -ForegroundColor Green

Write-Host "`n╔════════════════════════════════════════════════╗" -ForegroundColor Green
Write-Host "║          INSTALLATION COMPLETE!                ║" -ForegroundColor Green
Write-Host "╚════════════════════════════════════════════════╝`n" -ForegroundColor Green

Write-Host "Installed:" -ForegroundColor Yellow
Write-Host "   - Chocolatey" -ForegroundColor Green
Write-Host "   - Git" -ForegroundColor Green
Write-Host "   - vcpkg" -ForegroundColor Green
Write-Host "   - Graphics: GLFW, GLAD, GLM" -ForegroundColor Green
Write-Host "   - Assets: Assimp, STB Image" -ForegroundColor Green
Write-Host "   - Physics: Bullet3" -ForegroundColor Green
Write-Host "   - Audio: OpenAL" -ForegroundColor Green
Write-Host "   - ECS: EnTT" -ForegroundColor Green
Write-Host "   - Scripting: Lua" -ForegroundColor Green
Write-Host "   - UI: ImGui" -ForegroundColor Green

Write-Host "`nNext steps:" -ForegroundColor Yellow
Write-Host "   1. Restart your terminal" -ForegroundColor White
Write-Host "   2. cd engine-core" -ForegroundColor White
Write-Host "   3. .\build-engine.bat" -ForegroundColor White
Write-Host "   4. .\run-engine.bat`n" -ForegroundColor White

Write-Host "Ready to build YUGA Engine!`n" -ForegroundColor Magenta
