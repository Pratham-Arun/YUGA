@echo off
echo.
echo ╔═══════════════════════════════════════════════════════╗
echo ║          🎮 YUGA Engine - Run Script 🎮             ║
echo ╚═══════════════════════════════════════════════════════╝
echo.

REM Check if executable exists
if not exist "build\bin\Release\YUGAEngine.exe" (
    echo ❌ Engine executable not found
    echo.
    echo Please build the engine first:
    echo    .\build-engine.bat
    echo.
    pause
    exit /b 1
)

echo ✓ Engine executable found
echo.
echo 🚀 Starting YUGA Engine...
echo.
echo ════════════════════════════════════════════════════════
echo.

REM Run the engine
build\bin\Release\YUGAEngine.exe

echo.
echo ════════════════════════════════════════════════════════
echo.
echo Engine closed.
echo.
pause
