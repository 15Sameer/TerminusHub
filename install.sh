#!/bin/bash

echo "Terminus Hub Installer"
echo "===================="
echo ""

# Detect OS
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="Linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    OS="MacOS"
elif [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "win32" ]]; then
    OS="Windows"
else
    OS="Unknown"
fi

echo "Detected OS: $OS"
echo ""

# Install dependencies based on OS
if [[ "$OS" == "Linux" ]]; then
    echo "Installing dependencies for Linux..."
    sudo apt update
    sudo apt install -y build-essential libncurses5-dev libncursesw5-dev make
    echo "Building from source..."
    make clean && make
    echo "Installation complete!"
    echo "Run './terminus' to start the game."

elif [[ "$OS" == "MacOS" ]]; then
    echo "Installing dependencies for MacOS..."
    if ! command -v brew &> /dev/null; then
        echo "Homebrew not found. Installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi
    brew install ncurses make gcc
    echo "Building from source..."
    make clean && make
    echo "Installation complete!"
    echo "Run './terminus' to start the game."

elif [[ "$OS" == "Windows" ]]; then
    echo "For Windows, we recommend using WSL (Windows Subsystem for Linux)."
    echo "If you have WSL installed, you can run this script inside WSL."
    echo "Otherwise, you can use the build.bat script included in the repository."
    echo ""
    echo "Would you like to run the build.bat script now? (y/n)"
    read -r response
    if [[ "$response" =~ ^([yY][eE][sS]|[yY])$ ]]; then
        cmd.exe /c build.bat
    else
        echo "You can manually run build.bat later."
    fi
else
    echo "Unsupported OS. Please build manually following the instructions in README.md"
    exit 1
fi