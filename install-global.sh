#!/bin/bash

echo "Terminus Hub Global Installer"
echo "==========================="
echo ""

# Check if running as root
if [ "$(id -u)" -ne 0 ]; then
    echo "This script must be run as root. Please use sudo."
    exit 1
fi

# Build the project if not already built
if [ ! -f "./terminus" ]; then
    echo "Building Terminus Hub..."
    make clean && make
fi

# Install to /usr/local/bin
echo "Installing Terminus Hub globally..."
INSTALL_DIR="/usr/local/share/terminus-hub"
mkdir -p "$INSTALL_DIR"
cp -r * "$INSTALL_DIR"/

# Create a symlink in /usr/local/bin
ln -sf "$INSTALL_DIR/terminus" /usr/local/bin/terminus

echo ""
echo "Terminus Hub has been installed globally."
echo "You can now run the game from anywhere by typing 'terminus'."