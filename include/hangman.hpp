#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>

class Hangman {
private:
    int difficulty;
    bool gameOver;
    int wrongGuesses;
    int score;

    std::string secretWord;
    std::string displayWord;
    std::string currentCategory;
    std::set<char> guessedLetters;

    std::map<std::string, std::vector<std::string>> categories;
    std::map<std::string, std::vector<std::string>> sessionCategories;

    std::map<std::string, std::string> wordHintsEasy;
    std::map<std::string, std::string> wordHintsMedium;
    std::map<std::string, std::string> wordHintsHard;

    void loadWords();
    void drawWord();

public:
    Hangman();
    ~Hangman();

    void setDifficulty(int d);
    void startGame();
    bool makeGuess(char letter);
    bool isGameOver() const;
    bool hasWon() const;
    int getWrongGuesses() const;
    std::string getSecretWord() const;
    std::string getDisplayWord() const;
    std::string getCurrentCategory() const;
    std::set<char> getGuessedLetters() const;
    int getScore() const;
    void resetScore();

    void selectCategory();
    void drawHangman();
};
