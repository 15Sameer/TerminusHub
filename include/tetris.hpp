#ifndef TETRIS_HPP
#define TETRIS_HPP

#include <ncurses.h>
#include <vector>

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;
const int SHAPE_SIZE = 4;
const int NUM_SHAPES = 7;

class Tetris {
private:
    std::vector<std::vector<int>> board;
    int currentShape, nextShape, rotation;
    int posX, posY;
    int score, linesCleared, difficulty;
    bool gameOver;

    std::vector<std::vector<std::vector<std::vector<bool>>>> shapes;

    WINDOW* gameWin;
    WINDOW* scoreWin;

    void initShapes();
    void resetGame();
    void rotateShape();
    void generateShape();
    bool checkCollision(int shape, int rot, int x, int y);
    void placeTetromino();
    void clearLines();
    void drawGame();
    void drawNext();
    int getFallSpeed();

public:
    Tetris();
    ~Tetris();
    void startGame();
    void setDifficulty(int diff);
};

#endif // TETRIS_HPP
