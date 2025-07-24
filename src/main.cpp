// src/main.cpp
#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>

#include "snake.hpp"
#include "tetris.hpp"
#include "tictactoe.hpp"
#include "hangman.hpp"
#include "echoes.hpp"

void initColors() {
    start_color();
    use_default_colors();
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);      // Main menu
    init_pair(2, COLOR_WHITE, COLOR_MAGENTA);    // Tic Tac Toe
    init_pair(3, COLOR_GREEN, COLOR_BLACK);      // Snake
    init_pair(4, COLOR_CYAN, COLOR_BLUE);        // Tetris
    init_pair(5, COLOR_BLACK, COLOR_WHITE);      // Hangman
    init_pair(6, COLOR_BLACK, COLOR_CYAN);       // Echoes (new cyan background)
    init_pair(7, COLOR_YELLOW, COLOR_RED);       // Selected item / banners
    init_pair(8, COLOR_WHITE, COLOR_BLACK);      // Default
}

void clearFullScreen() {
    clear();
    refresh();
}

void drawMainMenu(WINDOW* menuWin, int highlight) {
    std::vector<std::string> items = {
        "Snake", "Tetris", "Tic Tac Toe", "Hangman",
        "Echoes of Forgotten Terminal", "Settings", "Exit"
    };

    wbkgd(menuWin, COLOR_PAIR(1));
    box(menuWin, 0, 0);
    wattron(menuWin, A_BOLD | COLOR_PAIR(1));
    mvwprintw(menuWin, 1, 4, "== Terminus Hub ==");
    wattroff(menuWin, A_BOLD | COLOR_PAIR(1));

    for (int i = 0; i < (int)items.size(); ++i) {
        if (i == highlight)
            wattron(menuWin, COLOR_PAIR(7) | A_BOLD);
        else
            wattron(menuWin, COLOR_PAIR(1));

        mvwprintw(menuWin, i + 3, 4, "%-30s", items[i].c_str());

        wattroff(menuWin, COLOR_PAIR(7) | A_BOLD);
        wattroff(menuWin, COLOR_PAIR(1));
    }
    wrefresh(menuWin);
}

void drawSettingsMenu(WINDOW* menuWin, int currentD, int sopt) {
    werase(menuWin);
    wbkgd(menuWin, COLOR_PAIR(1));
    box(menuWin, 0, 0);
    mvwprintw(menuWin, 1, 4, "== Settings ==");

    std::string diffLine = "Difficulty: " + std::to_string(currentD);
    if (sopt == 0) wattron(menuWin, COLOR_PAIR(7) | A_BOLD);
    mvwprintw(menuWin, 3, 4, "%s", diffLine.c_str());
    if (sopt == 0) wattroff(menuWin, COLOR_PAIR(7) | A_BOLD);

    if (sopt == 1) wattron(menuWin, COLOR_PAIR(7) | A_BOLD);
    mvwprintw(menuWin, 4, 4, "Back");
    if (sopt == 1) wattroff(menuWin, COLOR_PAIR(7) | A_BOLD);

    wrefresh(menuWin);
}

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    initColors();

    int highlight = 0, diff = 1;
    const int itemCount = 7;
    WINDOW* menuWin = newwin(15, 40, 3, 10);
    keypad(menuWin, TRUE);

    Snake snake;
    Tetris tetris;
    TicTacToe ttt;
    Hangman hangman;
    Echoes echoes;

    while (true) {
        clearFullScreen();
        drawMainMenu(menuWin, highlight);
        int ch = wgetch(menuWin);
        if (ch == 'q') break;
        else if (ch == KEY_UP)    highlight = (highlight + itemCount - 1) % itemCount;
        else if (ch == KEY_DOWN)  highlight = (highlight + 1) % itemCount;
        else if (ch == '\n') {
            clearFullScreen();
            switch (highlight) {
              case 0:
                snake.setDifficulty(diff);
                snake.startGame();
                break;
              case 1:
                tetris.setDifficulty(diff);
                tetris.startGame();
                break;
              case 2:
                ttt.setDifficulty(diff);
                ttt.startGame();
                break;
              case 3:
                hangman.setDifficulty(diff);
                hangman.startGame();
                break;
              case 4:
                // Run Echoes in the same ncurses session
                wbkgd(stdscr, COLOR_PAIR(6));
                echoes.setDifficulty(diff);
                echoes.startGameCurses();
                break;
              case 5: {
                int sopt = 0;
                while (true) {
                  clearFullScreen();
                  drawSettingsMenu(menuWin, diff, sopt);
                  int sch = wgetch(menuWin);
                  if (sch == KEY_UP || sch == 'w')   sopt = (sopt + 2 - 1) % 2;
                  else if (sch == KEY_DOWN || sch == 's') sopt = (sopt + 1) % 2;
                  else if (sch == '\n') {
                    if (sopt == 0) diff = diff % 3 + 1;
                    else break;
                  }
                  else if (sch == 'q') break;
                }
              } break;
              case 6:
                goto exit_loop;
            }
        }
    }

exit_loop:
    delwin(menuWin);
    endwin();
    return 0;
}
