@echo off
REM Build script for Terminus Hub on Windows using WSL

echo Terminus Hub Build Script
echo ========================
echo.

REM Check if WSL is installed
where wsl >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo Error: Windows Subsystem for Linux (WSL) is not installed.
    echo Please install WSL by following these steps:
    echo 1. Open PowerShell as Administrator
    echo 2. Run: wsl --install
    echo 3. Restart your computer
    echo 4. Complete the Ubuntu setup when prompted
    echo.
    echo After installing WSL, run this script again.
    exit /b 1
)

echo Checking for required packages in WSL...
wsl bash -c "if ! dpkg -l | grep -q libncurses; then echo Installing ncurses library...; sudo apt update && sudo apt install -y build-essential libncurses5-dev libncursesw5-dev; fi"

echo.
echo Building Terminus Hub...
wsl bash -c "cd %~dp0 && make clean && make"

if %ERRORLEVEL% neq 0 (
    echo.
    echo Build failed. Please check the error messages above.
    exit /b 1
) else (
    echo.
    echo Build successful!
    echo.
    echo To run Terminus Hub, use WSL by typing:
    echo wsl -d Ubuntu
    echo Then navigate to this directory and run:
    echo cd /mnt/c/Users/Sameer/Pictures/TerminusHub
    echo ./terminus
    echo.
    echo Enjoy your games!
)

pause