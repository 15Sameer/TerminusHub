
#include "tetris.hpp"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

// Increase board size
#undef BOARD_HEIGHT
#undef BOARD_WIDTH
#define BOARD_HEIGHT 24
#define BOARD_WIDTH 16
Tetris::Tetris() : score(0), linesCleared(0), difficulty(1), gameOver(false) {
    shapes.resize(NUM_SHAPES);
    for (int i = 0; i < NUM_SHAPES; ++i) {
        shapes[i].resize(4);
        for (int j = 0; j < 4; ++j) {
            shapes[i][j].resize(SHAPE_SIZE);
            for (int k = 0; k < SHAPE_SIZE; ++k)
                shapes[i][j][k].resize(SHAPE_SIZE, false);
        }
    }
    // Dynamically size the board
    board.resize(BOARD_HEIGHT, std::vector<int>(BOARD_WIDTH, 0));
    initShapes();
    srand(static_cast<unsigned>(time(0)));
}

Tetris::~Tetris() {}

void Tetris::setDifficulty(int diff) {
    difficulty = diff;
}

void Tetris::initShapes() {
    shapes[0][0][1][0] = shapes[0][0][1][1] = shapes[0][0][1][2] = shapes[0][0][1][3] = true;
    shapes[0][1][0][2] = shapes[0][1][1][2] = shapes[0][1][2][2] = shapes[0][1][3][2] = true;
    shapes[0][2][2][0] = shapes[0][2][2][1] = shapes[0][2][2][2] = shapes[0][2][2][3] = true;
    shapes[0][3][0][1] = shapes[0][3][1][1] = shapes[0][3][2][1] = shapes[0][3][3][1] = true;

    shapes[1][0][0][0] = shapes[1][0][1][0] = shapes[1][0][1][1] = shapes[1][0][1][2] = true;
    shapes[1][1][0][1] = shapes[1][1][0][2] = shapes[1][1][1][1] = shapes[1][1][2][1] = true;
    shapes[1][2][1][0] = shapes[1][2][1][1] = shapes[1][2][1][2] = shapes[1][2][2][2] = true;
    shapes[1][3][0][1] = shapes[1][3][1][1] = shapes[1][3][2][1] = shapes[1][3][2][0] = true;

    shapes[2][0][0][2] = shapes[2][0][1][0] = shapes[2][0][1][1] = shapes[2][0][1][2] = true;
    shapes[2][1][0][1] = shapes[2][1][1][1] = shapes[2][1][2][1] = shapes[2][1][2][2] = true;
    shapes[2][2][1][0] = shapes[2][2][1][1] = shapes[2][2][1][2] = shapes[2][2][2][0] = true;
    shapes[2][3][0][0] = shapes[2][3][0][1] = shapes[2][3][1][1] = shapes[2][3][2][1] = true;

    shapes[3][0][0][0] = shapes[3][0][0][1] = shapes[3][0][1][0] = shapes[3][0][1][1] = true;
    shapes[3][1][0][0] = shapes[3][1][0][1] = shapes[3][1][1][0] = shapes[3][1][1][1] = true;
    shapes[3][2][0][0] = shapes[3][2][0][1] = shapes[3][2][1][0] = shapes[3][2][1][1] = true;
    shapes[3][3][0][0] = shapes[3][3][0][1] = shapes[3][3][1][0] = shapes[3][3][1][1] = true;

    shapes[4][0][0][1] = shapes[4][0][0][2] = shapes[4][0][1][0] = shapes[4][0][1][1] = true;
    shapes[4][1][0][1] = shapes[4][1][1][1] = shapes[4][1][1][2] = shapes[4][1][2][2] = true;
    shapes[4][2][1][1] = shapes[4][2][1][2] = shapes[4][2][2][0] = shapes[4][2][2][1] = true;
    shapes[4][3][0][0] = shapes[4][3][1][0] = shapes[4][3][1][1] = shapes[4][3][2][1] = true;

    shapes[5][0][0][1] = shapes[5][0][1][0] = shapes[5][0][1][1] = shapes[5][0][1][2] = true;
    shapes[5][1][0][1] = shapes[5][1][1][1] = shapes[5][1][1][2] = shapes[5][1][2][1] = true;
    shapes[5][2][1][0] = shapes[5][2][1][1] = shapes[5][2][1][2] = shapes[5][2][2][1] = true;
    shapes[5][3][1][0] = shapes[5][3][0][1] = shapes[5][3][1][1] = shapes[5][3][2][1] = true;

    shapes[6][0][0][0] = shapes[6][0][0][1] = shapes[6][0][1][1] = shapes[6][0][1][2] = true;
    shapes[6][1][0][2] = shapes[6][1][1][1] = shapes[6][1][1][2] = shapes[6][1][2][1] = true;
    shapes[6][2][1][0] = shapes[6][2][1][1] = shapes[6][2][2][1] = shapes[6][2][2][2] = true;
    shapes[6][3][0][1] = shapes[6][3][1][0] = shapes[6][3][1][1] = shapes[6][3][2][0] = true;
}

void Tetris::resetGame() {
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        if ((int)board.size() < BOARD_HEIGHT) board.resize(BOARD_HEIGHT);
        if ((int)board[i].size() < BOARD_WIDTH) board[i].resize(BOARD_WIDTH);
        for (int j = 0; j < BOARD_WIDTH; ++j)
            board[i][j] = 0;
    }
    score = linesCleared = 0;
    currentShape = rand() % NUM_SHAPES;
    nextShape = rand() % NUM_SHAPES;
    rotation = 0;
    posX = BOARD_WIDTH / 2 - 2;
    posY = 0;
    gameOver = false;
}

void Tetris::rotateShape() {
    int newRot = (rotation + 1) % 4;
    if (!checkCollision(currentShape, newRot, posX, posY))
        rotation = newRot;
}

void Tetris::generateShape() {
    currentShape = nextShape;
    nextShape = rand() % NUM_SHAPES;
    rotation = 0;
    posX = BOARD_WIDTH / 2 - 2;
    posY = 0;
    if (checkCollision(currentShape, rotation, posX, posY))
        gameOver = true;
}

bool Tetris::checkCollision(int shape, int rot, int x, int y) {
    for (int i = 0; i < SHAPE_SIZE; ++i)
        for (int j = 0; j < SHAPE_SIZE; ++j)
            if (shapes[shape][rot][i][j]) {
                int nx = x + j;
                int ny = y + i;
                if (nx < 0 || nx >= BOARD_WIDTH || ny < 0 || ny >= BOARD_HEIGHT)
                    return true;
                if (board[ny][nx])
                    return true;
            }
    return false;
}

void Tetris::placeTetromino() {
    for (int i = 0; i < SHAPE_SIZE; ++i)
        for (int j = 0; j < SHAPE_SIZE; ++j)
            if (shapes[currentShape][rotation][i][j]) {
                int nx = posX + j;
                int ny = posY + i;
                if (ny >= 0 && ny < BOARD_HEIGHT && nx >= 0 && nx < BOARD_WIDTH)
                    board[ny][nx] = currentShape + 1;
            }
}

void Tetris::clearLines() {
    int lines = 0;
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        bool full = true;
        for (int j = 0; j < BOARD_WIDTH; ++j)
            if (!board[i][j]) {
                full = false;
                break;
            }
        if (full) {
            lines++;
            for (int k = i; k > 0; --k)
                for (int j = 0; j < BOARD_WIDTH; ++j)
                    board[k][j] = board[k - 1][j];
            for (int j = 0; j < BOARD_WIDTH; ++j)
                board[0][j] = 0;
        }
    }
    linesCleared += lines;
    score += lines * 100;
    if (lines > 0) beep();
}

void Tetris::drawGame() {
    int y = (LINES - BOARD_HEIGHT - 2) / 2;
    int x = (COLS - BOARD_WIDTH - 2) / 2;
    clear();
    // Draw border
    attron(COLOR_PAIR(7));
    for (int i = 0; i <= BOARD_WIDTH + 1; ++i) {
        mvaddch(y, x + i, '#'); // Top
        mvaddch(y + BOARD_HEIGHT + 1, x + i, '#'); // Bottom
    }
    for (int i = 1; i <= BOARD_HEIGHT; ++i) {
        mvaddch(y + i, x, '#'); // Left
        mvaddch(y + i, x + BOARD_WIDTH + 1, '#'); // Right
    }
    attroff(COLOR_PAIR(7));
    // Draw board
    attron(COLOR_PAIR(4));
    for (int i = 0; i < BOARD_HEIGHT; ++i)
        for (int j = 0; j < BOARD_WIDTH; ++j)
            if (board[i][j])
                mvaddch(y + 1 + i, x + 1 + j, '#');
    // Draw current shape
    attron(COLOR_PAIR(4) | A_BOLD);
    for (int i = 0; i < SHAPE_SIZE; ++i)
        for (int j = 0; j < SHAPE_SIZE; ++j)
            if (shapes[currentShape][rotation][i][j]) {
                int nx = posX + j;
                int ny = posY + i;
                if (ny >= 0 && ny < BOARD_HEIGHT && nx >= 0 && nx < BOARD_WIDTH)
                    mvaddch(y + 1 + ny, x + 1 + nx, '*');
            }
    attroff(COLOR_PAIR(4) | A_BOLD);
    refresh();
}

void Tetris::drawNext() {
    int y = (LINES - BOARD_HEIGHT - 2) / 2;
    int x = (COLS - BOARD_WIDTH - 2) / 2 + BOARD_WIDTH + 4;
    attron(COLOR_PAIR(8));
    mvprintw(y + 1, x, "Score: %d", score);
    mvprintw(y + 2, x, "Lines: %d", linesCleared);
    mvprintw(y + 4, x, "Next:");
    for (int i = 0; i < SHAPE_SIZE; ++i) {
        for (int j = 0; j < SHAPE_SIZE; ++j) {
            if (shapes[nextShape][0][i][j])
                mvaddch(y + 6 + i, x + 2 + j, '*');
        }
    }
    attroff(COLOR_PAIR(8));
    refresh();
}

int Tetris::getFallSpeed() {
    int base = 600;
    int speed = base - 100 * (difficulty - 1) - 10 * (linesCleared / 10);
    if (speed < 60) speed = 60;
    return speed;
}

void Tetris::startGame() {
    clear();
    refresh();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    resetGame();
    drawGame();
    drawNext();

    int tick = 0;
    int fallSpeed = getFallSpeed();

    int y = (LINES - BOARD_HEIGHT - 2) / 2;
    int x = (COLS - BOARD_WIDTH - 2) / 2;
    mvprintw(y + BOARD_HEIGHT + 2, x, "q: quit");
    refresh();

    while (!gameOver) {
        int ch = getch();
        if (ch == 'q') { gameOver = true; break; }
        else if (ch == KEY_LEFT && !checkCollision(currentShape, rotation, posX - 1, posY))
            posX--;
        else if (ch == KEY_RIGHT && !checkCollision(currentShape, rotation, posX + 1, posY))
            posX++;
        else if (ch == KEY_UP) rotateShape();
        else if (ch == KEY_DOWN && !checkCollision(currentShape, rotation, posX, posY + 1))
            posY++;
        if (++tick * 15 > fallSpeed) {
            if (!checkCollision(currentShape, rotation, posX, posY + 1))
                posY++;
            else {
                placeTetromino();
                clearLines();
                generateShape();
            }
            tick = 0;
            fallSpeed = getFallSpeed();
        }
        drawGame();
        drawNext();
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
    attron(COLOR_PAIR(7) | A_BOLD);
    mvprintw(y + BOARD_HEIGHT/2, x + 2, "Game Over!");
    mvprintw(y + BOARD_HEIGHT/2 + 1, x + 2, "Score: %d", score);
    mvprintw(y + BOARD_HEIGHT - 2, x + 2, "Press any key...");
    attroff(COLOR_PAIR(7) | A_BOLD);
    nodelay(stdscr, FALSE);
    getch();
}
