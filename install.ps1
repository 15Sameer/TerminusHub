# Terminus Hub PowerShell Installer

Write-Host "Terminus Hub Installer" -ForegroundColor Cyan
Write-Host "====================" -ForegroundColor Cyan
Write-Host ""

# Check if WSL is installed
$wslCheck = wsl --list 2>&1
if ($LASTEXITCODE -ne 0 -or $wslCheck -like "*Windows Subsystem for Linux has no installed distributions*") {
    Write-Host "Windows Subsystem for Linux (WSL) is not properly installed." -ForegroundColor Yellow
    Write-Host "Would you like to install WSL now? (y/n)"
    $installWSL = Read-Host
    
    if ($installWSL -eq "y" -or $installWSL -eq "Y") {
        Write-Host "Installing WSL..." -ForegroundColor Green
        Start-Process powershell -ArgumentList "-Command", "wsl --install" -Verb RunAs -Wait
        Write-Host "WSL installation initiated. You may need to restart your computer." -ForegroundColor Yellow
        Write-Host "After restarting, run this script again to continue installation." -ForegroundColor Yellow
        exit
    } else {
        Write-Host "WSL is required to run Terminus Hub. Installation aborted." -ForegroundColor Red
        exit
    }
}

# Check if Ubuntu is installed in WSL
$ubuntuCheck = wsl --list | Select-String "Ubuntu"
if (-not $ubuntuCheck) {
    Write-Host "Ubuntu distribution not found in WSL." -ForegroundColor Yellow
    Write-Host "Would you like to install Ubuntu now? (y/n)"
    $installUbuntu = Read-Host
    
    if ($installUbuntu -eq "y" -or $installUbuntu -eq "Y") {
        Write-Host "Installing Ubuntu..." -ForegroundColor Green
        wsl --install -d Ubuntu
        Write-Host "Ubuntu installation initiated. Please complete the setup when prompted." -ForegroundColor Yellow
        Write-Host "After setup is complete, run this script again to continue installation." -ForegroundColor Yellow
        exit
    } else {
        Write-Host "Ubuntu is required to run Terminus Hub. Installation aborted." -ForegroundColor Red
        exit
    }
}

# Create symbolic link in WSL home directory
Write-Host "Setting up Terminus Hub in WSL..." -ForegroundColor Green
wsl -e bash -c "mkdir -p ~/TerminusHub && ln -sf /mnt/c/Users/Sameer/Pictures/TerminusHub/* ~/TerminusHub/ && echo 'Symbolic link created.'"

# Run the build script
Write-Host "Building Terminus Hub..." -ForegroundColor Green
& "$PSScriptRoot\build.bat"

Write-Host ""
Write-Host "Installation complete!" -ForegroundColor Green
Write-Host "To run Terminus Hub, open WSL and type:" -ForegroundColor Cyan
Write-Host "cd ~/TerminusHub" -ForegroundColor White
Write-Host "./terminus" -ForegroundColor White
Write-Host ""
Write-Host "Would you like to run the game now? (y/n)"
$runNow = Read-Host

if ($runNow -eq "y" -or $runNow -eq "Y") {
    Write-Host "Starting Terminus Hub..." -ForegroundColor Green
    wsl -e bash -c "cd ~/TerminusHub && ./terminus"
}