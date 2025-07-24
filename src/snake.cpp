// src/snake.cpp
#include "snake.hpp"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

Snake::Snake(int h, int w)
    : height(h)
    , width(w)
    , score(0)
    , foodY(0)
    , foodX(0)
    , direction(KEY_RIGHT)
    , difficulty(1)
    , snake()
    , gameWin(nullptr)
    , gameOver(false)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    reset();
}

Snake::~Snake() {}

void Snake::setDifficulty(int d) {
    difficulty = (d >= 1 && d <= 3) ? d : 1;
}

void Snake::reset() {
    gameOver = false;
    score = 0;
    direction = KEY_RIGHT;
    snake.clear();
    // Start in center
    snake.emplace_back(height/2, width/2);
    placeFood();
}

void Snake::placeFood() {
    while (true) {
        int y = std::rand() % height;
        int x = std::rand() % width;
        bool onSnake = false;
        for (auto &p : snake) {
            if (p.first == y && p.second == x) {
                onSnake = true;
                break;
            }
        }
        if (!onSnake) {
            foodY = y;
            foodX = x;
            return;
        }
    }
}

void Snake::drawGame() {
    int y0 = (LINES - height)  / 2;
    int x0 = (COLS  - width)   / 2;
    clear();

    // Border
    attron(COLOR_PAIR(7));
    for (int i = 0; i < width+2; ++i) {
        mvaddch(y0,           x0 + i, '#');
        mvaddch(y0 + height +1, x0 + i, '#');
    }
    for (int i = 1; i <= height; ++i) {
        mvaddch(y0 + i, x0,           '#');
        mvaddch(y0 + i, x0 + width+1, '#');
    }
    attroff(COLOR_PAIR(7));

    // Score
    attron(A_BOLD|COLOR_PAIR(8));
    mvprintw(y0, x0+2, " Score: %d ", score);
    attroff(A_BOLD|COLOR_PAIR(8));

    // Food
    attron(COLOR_PAIR(8));
    mvaddch(y0+1+foodY, x0+1+foodX, '@');
    attroff(COLOR_PAIR(8));

    // Snake
    for (auto &p : snake) {
        mvaddch(y0+1+p.first, x0+1+p.second, 'O');
    }

    mvprintw(y0 + height + 2, x0+1, "Press q to quit");
    refresh();
}

void Snake::processInput(int ch) {
    if ((ch == KEY_UP    || ch == 'w') && direction != KEY_DOWN)  direction = KEY_UP;
    else if ((ch == KEY_DOWN  || ch == 's') && direction != KEY_UP)    direction = KEY_DOWN;
    else if ((ch == KEY_LEFT  || ch == 'a') && direction != KEY_RIGHT) direction = KEY_LEFT;
    else if ((ch == KEY_RIGHT || ch == 'd') && direction != KEY_LEFT)  direction = KEY_RIGHT;
    else if (ch == 'q') gameOver = true;
}

void Snake::update() {
    auto [hy, hx] = snake.front();
    switch (direction) {
        case KEY_UP:    hy--; break;
        case KEY_DOWN:  hy++; break;
        case KEY_LEFT:  hx--; break;
        case KEY_RIGHT: hx++; break;
    }

    // Collision
    if (hy<0 || hy>=height || hx<0 || hx>=width) gameOver = true;
    for (auto &p : snake) {
        if (p.first==hy && p.second==hx) gameOver = true;
    }

    snake.emplace_front(hy, hx);
    if (hy==foodY && hx==foodX) {
        score += 10;
        beep();
        placeFood();
    } else {
        snake.pop_back();
    }
}

void Snake::startGame() {
    reset();
    drawGame();

    int delay = 150 - 25*(difficulty-1);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    while (!gameOver) {
        int ch = getch();
        processInput(ch);
        update();
        drawGame();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    // Game Over banner
    attron(COLOR_PAIR(7)|A_BOLD);
    int y0 = (LINES - height)/2;
    int x0 = (COLS  - width )/2;
    mvprintw(y0 + height/2,     x0 + (width-9)/2,  "Game Over!");
    mvprintw(y0 + height/2 + 1, x0 + (width-13)/2, "Final Score: %d", score);
    mvprintw(y0 + height - 1,   x0+1,               "Press any key...");
    attroff(COLOR_PAIR(7)|A_BOLD);
    nodelay(stdscr, FALSE);
    getch();
}
