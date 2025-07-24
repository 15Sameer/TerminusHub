
#include "tictactoe.hpp"
#include <cstring>
#include <algorithm>

TicTacToe::TicTacToe() : difficulty(1), vsAI(true), gameOver(false), aiMode(TicTacToeAIMode::Perfect) {
    scoreX = 0;
    scoreO = 0;
    reset();
}
void TicTacToe::setAIMode(TicTacToeAIMode mode) {
    aiMode = mode;
}

TicTacToeAIMode TicTacToe::getAIMode() const {
    return aiMode;
}

std::pair<int, int> TicTacToe::findRandomMove() {
    std::vector<std::pair<int, int>> moves;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == ' ')
                moves.push_back({i, j});
    if (moves.empty()) return {-1, -1};
    int idx = rand() % moves.size();
    return moves[idx];
}

TicTacToe::~TicTacToe() {}

void TicTacToe::reset() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = ' ';
    currentPlayer = 1;
    gameOver = false;
}

void TicTacToe::setDifficulty(int d) {
    difficulty = d;
}

void TicTacToe::drawBoard() {
    int win_y = (LINES-11)/2, win_x = (COLS-19)/2;
    clear();
    int basey = win_y + 2;
    attron(COLOR_PAIR(2) | A_BOLD);
    for (int i = 0; i < 3; ++i) {
        mvprintw(basey + i * 3, win_x + 4, " %c | %c | %c ", 
                  board[i][0], board[i][1], board[i][2]);
        if (i < 2)
            mvprintw(basey + i * 3 + 1, win_x + 4, "---+---+---");
    }
    attroff(COLOR_PAIR(2) | A_BOLD);
    refresh();
}

void TicTacToe::drawStatus(const std::string& msg) {
    int win_y = (LINES-11)/2, win_x = (COLS-19)/2;
    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(win_y + 9, win_x + 2, " %-15s", msg.c_str());
    attroff(COLOR_PAIR(2) | A_BOLD);
    refresh();
}

bool TicTacToe::isMovesLeft() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == ' ')
                return true;
    return false;
}

int TicTacToe::evaluate() {
    for (int row = 0; row < 3; ++row)
        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2]) {
            if (board[row][0] == 'X') return +10;
            else if (board[row][0] == 'O') return -10;
        }
    for (int col = 0; col < 3; ++col)
        if (board[0][col] == board[1][col] &&
            board[1][col] == board[2][col]) {
            if (board[0][col] == 'X') return +10;
            else if (board[0][col] == 'O') return -10;
        }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'X') return +10;
        else if (board[0][0] == 'O') return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'X') return +10;
        else if (board[0][2] == 'O') return -10;
    }
    return 0;
}

int TicTacToe::minimax(int depth, bool isMax) {
    int score = evaluate();
    if (score == 10 || score == -10) return score;
    if (!isMovesLeft()) return 0;
    if (depth > 4 && difficulty <= 2) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = std::max(best, minimax(depth+1, !isMax));
                    board[i][j] = ' ';
                }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = std::min(best, minimax(depth+1, !isMax));
                    board[i][j] = ' ';
                }
        return best;
    }
}

std::pair<int, int> TicTacToe::findBestMove() {
    int bestVal = 1000;
    int moveRow = -1, moveCol = -1;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(0, true);
                board[i][j] = ' ';
                if (moveVal < bestVal) {
                    moveRow = i;
                    moveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    return {moveRow, moveCol};
}

bool TicTacToe::checkWin(char player) {
    for (int i = 0; i < 3; ++i)
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return true;
    return false;
}

void TicTacToe::processMove(int cell) {
    int row = (cell - 1) / 3;
    int col = (cell - 1) % 3;
    if (cell >= 1 && cell <= 9 && board[row][col] == ' ') {
        board[row][col] = (currentPlayer == 1) ? 'X' : 'O';
        currentPlayer = 3 - currentPlayer;
    }
}

void TicTacToe::showResult() {
    drawBoard();
    int win_y = (LINES-11)/2, win_x = (COLS-19)/2;
    attron(COLOR_PAIR(7) | A_BOLD);
    if (checkWin('X')) {
        mvprintw(win_y + 7, win_x + 2, "X wins!");
        scoreX++;
    } else if (checkWin('O')) {
        mvprintw(win_y + 7, win_x + 2, "O wins!");
        scoreO++;
    } else {
        mvprintw(win_y + 7, win_x + 2, "It's a tie!");
    }
    attroff(COLOR_PAIR(7) | A_BOLD);
    mvprintw(win_y + 8, win_x + 2, "Score - X: %d  O: %d", scoreX, scoreO);
    mvprintw(win_y + 9, win_x + 2, "Press r to replay, q to quit...");
    refresh();
    int ch = getch();
    while (ch != 'r' && ch != 'q') ch = getch();
    if (ch == 'q') gameOver = true;
    else gameOver = false;
}

void TicTacToe::startGame() {
    nodelay(stdscr, FALSE);
    keypad(stdscr, TRUE);
    int win_y = (LINES-11)/2, win_x = (COLS-19)/2;
    // AI mode selection menu
    int aimode_sel = (int)aiMode;
    while (1) {
        clear();
        attron(COLOR_PAIR(2) | A_BOLD);
        box(stdscr, 0, 0);
        mvprintw(win_y, win_x, "== Select AI Difficulty ==");
        const char* modes[2] = {"Random (Easy)", "Perfect (Unbeatable)"};
        for (int i = 0; i < 2; ++i) {
            if (i == aimode_sel) attron(COLOR_PAIR(7) | A_BOLD);
            mvprintw(win_y+2+i, win_x+2, "%s", modes[i]);
            if (i == aimode_sel) attroff(COLOR_PAIR(7) | A_BOLD);
        }
        mvprintw(win_y+5, win_x+2, "Press Enter to confirm, Up/Down to select");
        attroff(COLOR_PAIR(2) | A_BOLD);
        refresh();
        int ch = getch();
        if (ch == KEY_UP || ch == 'w') aimode_sel = (aimode_sel + 1) % 2;
        else if (ch == KEY_DOWN || ch == 's') aimode_sel = (aimode_sel + 1) % 2;
        else if (ch == '\n' || ch == KEY_ENTER) break;
    }
    setAIMode((TicTacToeAIMode)aimode_sel);

    // Show instructions at the start
    clear();
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(win_y, win_x, "Tic Tac Toe Instructions:");
    attroff(COLOR_PAIR(3) | A_BOLD);
    mvprintw(win_y+1, win_x, "- You are X, AI (or Player 2) is O.");
    mvprintw(win_y+2, win_x, "- Press 1-9 to place your mark:");
    mvprintw(win_y+3, win_x, "  1 2 3");
    mvprintw(win_y+4, win_x, "  4 5 6");
    mvprintw(win_y+5, win_x, "  7 8 9");
    mvprintw(win_y+6, win_x, "- Press 'a' to toggle AI/human opponent.");
    mvprintw(win_y+7, win_x, "- Press 'q' to quit.");
    mvprintw(win_y+9, win_x, "Press any key to start...");
    refresh();
    getch();
    bool quit = false;
    while (!quit) {
        reset();
        drawBoard();
        drawStatus("1-9: move | q: quit");
        while (!gameOver) {
            drawBoard();
            // Show move mapping at the side for reference
            attron(COLOR_PAIR(3));
            mvprintw(win_y + 2, win_x + 20, "Keypad:");
            mvprintw(win_y + 3, win_x + 20, "1 2 3");
            mvprintw(win_y + 4, win_x + 20, "4 5 6");
            mvprintw(win_y + 5, win_x + 20, "7 8 9");
            attroff(COLOR_PAIR(3));
            if (currentPlayer == 1)
                drawStatus("Your turn (X)");
            else
                drawStatus(vsAI ? "AI's turn (O)" : "O's turn");
            if (currentPlayer == 2 && vsAI) {
                std::pair<int, int> move;
                if (aiMode == TicTacToeAIMode::Random) {
                    move = findRandomMove();
                } else {
                    move = findBestMove();
                }
                if (move.first != -1 && move.second != -1) {
                    board[move.first][move.second] = 'O';
                    currentPlayer = 1;
                    beep();
                }
            } else {
                int ch = getch();
                if (ch == 'q') { quit = true; gameOver = true; break; }
                if (ch == 'a') { vsAI = !vsAI; drawStatus("AI toggled."); continue; }
                if (ch >= '1' && ch <= '9') {
                    processMove(ch - '0');
                }
            }
            if (checkWin('X') || checkWin('O') || !isMovesLeft())
                gameOver = true;
        }
        showResult();
        if (gameOver && !quit) {
            // If user chose to replay, continue; if quit, break
            if (gameOver) quit = true;
        }
    }
}
