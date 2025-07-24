#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <ncurses.h>
#include <vector>
#include <string>

enum class TicTacToeAIMode {
    Random = 0,
    Perfect = 1
};

class TicTacToe {
private:
    char board[3][3];
    int currentPlayer; // 1 for X, 2 for O
    int difficulty;
    bool vsAI;
    bool gameOver;
    WINDOW* gameWin;
    TicTacToeAIMode aiMode;

    int scoreX; // Player 1 (X) score
    int scoreO; // Player 2 (O) or AI score

    void drawBoard();
    void drawStatus(const std::string& msg);
    bool isMovesLeft();
    int evaluate();
    int minimax(int depth, bool isMax);
    std::pair<int, int> findBestMove();
    std::pair<int, int> findRandomMove();
    void setAIMode(TicTacToeAIMode mode);
    TicTacToeAIMode getAIMode() const;
    void reset();
    void processMove(int cell);
    bool checkWin(char player);
    void showResult();

public:
    TicTacToe();
    ~TicTacToe();
    void setDifficulty(int d);
    void startGame();
    int getScoreX() const { return scoreX; }
    int getScoreO() const { return scoreO; }
};

#endif
