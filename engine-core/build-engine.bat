@echo off
echo.
echo ╔═══════════════════════════════════════════════════════╗
echo ║         🔨 YUGA Engine - Build Script 🔨            ║
echo ╚═══════════════════════════════════════════════════════╝
echo.

REM Check if CMake is available
where cmake >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ❌ CMake not found in PATH
    echo.
    echo Please restart your terminal or add CMake to PATH:
    echo    C:\Program Files\CMake\bin
    echo.
    pause
    exit /b 1
)

echo ✓ CMake found
cmake --version
echo.

echo 🔧 Step 1: Configuring build...
echo.
cmake -B build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ⚠️  Configuration failed. This is likely because vcpkg libraries are not installed.
    echo.
    echo To install dependencies, run:
    echo    .\setup-dev-env.ps1
    echo.
    echo Or build without external libraries for now.
    pause
    exit /b 1
)

echo.
echo ✓ Configuration complete
echo.

echo 🔨 Step 2: Building (Release)...
echo This may take a few minutes...
echo.
cmake --build build --config Release
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ❌ Build failed
    echo Check the error messages above
    pause
    exit /b 1
)

echo.
echo ╔═══════════════════════════════════════════════════════╗
echo ║            ✅ BUILD SUCCESSFUL! ✅                    ║
echo ╚═══════════════════════════════════════════════════════╝
echo.
echo 🎮 To run the engine:
echo    .\build\bin\Release\YUGAEngine.exe
echo.
echo 📚 Documentation:
echo    • QUICK_REFERENCE.md - API reference
echo    • BUILD_AND_RUN.md - Build guide
echo.
pause
