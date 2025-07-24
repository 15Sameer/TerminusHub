#!/bin/bash

echo "Terminus Hub Remote Installer"
echo "==========================="
echo ""

# GitHub repository information
REPO_OWNER="15Sameer"
REPO_NAME="TerminusHub"
BRANCH="main"

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

# Create temporary directory
TMP_DIR=$(mktemp -d)
cd "$TMP_DIR" || exit 1

# Download the repository
echo "Downloading Terminus Hub..."
if command -v curl &> /dev/null; then
    curl -L "https://github.com/$REPO_OWNER/$REPO_NAME/archive/refs/heads/$BRANCH.zip" -o terminus.zip
elif command -v wget &> /dev/null; then
    wget "https://github.com/$REPO_OWNER/$REPO_NAME/archive/refs/heads/$BRANCH.zip" -O terminus.zip
else
    echo "Error: Neither curl nor wget is installed. Please install one of them and try again."
    exit 1
fi

# Extract the repository
echo "Extracting files..."
if command -v unzip &> /dev/null; then
    unzip terminus.zip
else
    echo "Error: unzip is not installed. Please install it and try again."
    exit 1
fi

# Move to home directory
INSTALL_DIR="$HOME/TerminusHub"
echo "Installing to $INSTALL_DIR..."
mkdir -p "$INSTALL_DIR"
cp -r "$TMP_DIR/$REPO_NAME-$BRANCH"/* "$INSTALL_DIR"/

# Clean up temporary directory
cd ~ || exit 1
rm -rf "$TMP_DIR"

# Run the installer
cd "$INSTALL_DIR" || exit 1
chmod +x install.sh
./install.sh

echo ""
echo "Terminus Hub has been installed to $INSTALL_DIR"
echo "You can run the game by typing:"
echo "cd $INSTALL_DIR && ./terminus"

# Create an alias for easy access
echo "Would you like to create an alias 'terminus' to run the game? (y/n)"
read -r response
if [[ "$response" =~ ^([yY][eE][sS]|[yY])$ ]]; then
    echo "alias terminus='cd $INSTALL_DIR && ./terminus'" >> "$HOME/.bashrc"
    echo "Alias created! You can now run the game by simply typing 'terminus' in your terminal."
    echo "Please restart your terminal or run 'source ~/.bashrc' to use the alias."
fi