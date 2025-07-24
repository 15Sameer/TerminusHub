// include/snake.hpp
#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <ncurses.h>
#include <deque>
#include <utility>

class Snake {
public:
    // You can still supply custom size, or rely on defaults.
    Snake(int h = 24, int w = 48);
    ~Snake();

    void setDifficulty(int d);
    void startGame();

private:
    int height, width;                               // order #1-2
    int score;                                       // order #3
    int foodY, foodX;                                // order #4-5
    int direction;                                   // order #6
    int difficulty;                                  // order #7
    std::deque<std::pair<int,int>> snake;            // order #8
    WINDOW* gameWin;                                 // order #9 (unused but declared)
    bool gameOver;                                   // order #10

    void reset();
    void placeFood();
    void drawGame();
    void processInput(int ch);
    void update();
};

#endif // SNAKE_HPP
