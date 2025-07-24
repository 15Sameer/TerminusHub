# GitHub Setup Instructions

This document provides instructions for pushing this project to your GitHub account.

## Prerequisites

- Git installed on your computer
- GitHub account (https://github.com/15Sameer)

## Steps to Push to GitHub

1. **Create a new repository on GitHub**

   - Go to https://github.com/new
   - Repository name: `TerminusHub`
   - Description: `A terminal-based game suite built with ncurses in C++`
   - Choose Public or Private visibility
   - Do NOT initialize with README, .gitignore, or license (we already have these files)
   - Click "Create repository"

2. **Initialize Git in your local project**

   Open a terminal/command prompt in your project directory and run:

   ```bash
   git init
   git add .
   git commit -m "Initial commit"
   ```

3. **Add the remote repository**

   ```bash
   git remote add origin https://github.com/15Sameer/TerminusHub.git
   ```

4. **Push to GitHub**

   ```bash
   git branch -M main
   git push -u origin main
   ```

5. **Verify the repository**

   - Go to https://github.com/15Sameer/TerminusHub to see your project on GitHub
   - Check that all files were uploaded correctly

## GitHub Actions

This project includes a GitHub Actions workflow file (`.github/workflows/release.yml`) that will automatically build the project and create releases when you push to the main branch.

To enable GitHub Actions:

1. Go to your repository on GitHub
2. Click on the "Actions" tab
3. Click "I understand my workflows, go ahead and enable them"

## Making the Game Accessible via a Single Command

Once your repository is set up on GitHub, users can install and run your game with a single command:

```bash
curl -fsSL https://raw.githubusercontent.com/15Sameer/TerminusHub/main/install-remote.sh | bash
```

Or using wget:

```bash
wget -O- https://raw.githubusercontent.com/15Sameer/TerminusHub/main/install-remote.sh | bash
```

This will download the repository, build the game, and set up an alias for easy access.