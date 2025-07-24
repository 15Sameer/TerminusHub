# Terminus Hub

A terminal-based game suite built with ncurses in C++.

## Description

Terminus Hub is a collection of classic games that run directly in your terminal. The suite includes:

1. **Snake** - Navigate a growing snake to eat food while avoiding walls and your own tail.
2. **Tetris** - Arrange falling blocks to create complete lines.
3. **Tic Tac Toe** - Classic X and O game with AI opponent.
4. **Hangman** - Word guessing game with ASCII art.
5. **Echoes of Forgotten Terminal** - Text-based adventure puzzle game with memory fragments to collect.

## Features

- Interactive main menu to launch different games
- Real-time animations using ncurses
- Color-coded interfaces for each game
- Score tracking for each game
- Adjustable difficulty levels (1-3)
- Cross-platform (Linux and WSL-compatible)
- Settings menu for game configuration

## Requirements

- C++17 compatible compiler (g++ or clang++)
- ncurses library
- Make

## Installation

### Quick Install (Any Platform):

Run this command in your terminal:

```bash
curl -fsSL https://raw.githubusercontent.com/15Sameer/TerminusHub/main/install-remote.sh | bash
```

or

```bash
wget -O- https://raw.githubusercontent.com/15Sameer/TerminusHub/main/install-remote.sh | bash
```

### Manual Installation:

#### On Ubuntu/Debian:

```bash
# Clone the repository
git clone https://github.com/15Sameer/TerminusHub.git
cd TerminusHub

# Run the installer script
./install.sh
```

#### On macOS:

```bash
# Clone the repository
git clone https://github.com/15Sameer/TerminusHub.git
cd TerminusHub

# Run the installer script
./install.sh
```

#### On Windows (WSL):

1. Install Windows Subsystem for Linux (Ubuntu)
2. Run the provided PowerShell script as administrator:

```powershell
.\install.ps1
```

Or use the batch file:

```cmd
build.bat
```

The scripts will:
- Check if WSL is installed
- Install required packages in WSL
- Build the project using the Makefile
- Create symbolic links for easy access

## Usage

### On Linux:

After building the project, run the executable:

```bash
./terminus
```

### On Windows (WSL):

After building with build.bat, you can run the game using:

```cmd
wsl -d Ubuntu
cd /mnt/c/Users/Sameer/Pictures/TerminusHub
./terminus
```

Or use the symbolic link you created:

```cmd
wsl -d Ubuntu
cd ~/TerminusHub
./terminus
```

Use the arrow keys to navigate the menu and Enter to select an option. Press 'q' to quit games or return to the main menu.

## Game Controls

### Snake
- Arrow keys: Change direction
- Q: Quit game

### Tetris
- Left/Right arrows: Move piece horizontally
- Up arrow: Rotate piece
- Down arrow: Soft drop
- Space: Hard drop
- Q: Quit game

### Tic Tac Toe
- Number keys (1-9): Place X or O
- Q: Quit game

### Hangman
- Letter keys (a-z): Guess a letter
- ?: Show hint (hard mode only)
- Q: Quit game

### Echoes of Forgotten Terminal
- Text commands: go, take, use, look, inventory, help, quit
- Example: "go north", "take keycard", "use toolkit"
- Collect memory fragments to uncover the story

## Project Structure

```
TerminusHub/
├── include/           # Header files
│   ├── snake.hpp
│   ├── tetris.hpp
│   ├── tictactoe.hpp
│   ├── hangman.hpp
│   └── echoes.hpp
├── src/              # Source files
│   ├── main.cpp
│   ├── snake.cpp
│   ├── tetris.cpp
│   ├── tictactoe.cpp
│   ├── hangman.cpp
│   └── echoes.cpp
├── build/            # Object files
├── build.bat         # Windows build script
├── Makefile          # Linux build script
├── terminus          # Executable binary
└── README.md
```

## Troubleshooting

### Terminal Size
Ensure your terminal window is at least 80x24 characters for the best experience.

### Color Issues
If colors don't display correctly, try running with the TERM environment variable set:
```bash
TERM=xterm-256color ./terminus
```

## GitHub Repository

This project is hosted on GitHub: [https://github.com/15Sameer/TerminusHub](https://github.com/15Sameer/TerminusHub)

## Contributing

Contributions are welcome! Here's how you can contribute:

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/your-feature-name`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin feature/your-feature-name`
5. Submit a pull request

## License

This project is open source and available under the MIT License.

## Acknowledgments

- ncurses library developers
- Classic game designers who inspired these implementations"# Trigger build" 
