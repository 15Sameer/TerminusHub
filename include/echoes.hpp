// include/echoes.hpp
#pragma once

#include <string>
#include <map>
#include <set>

class Echoes {
public:
    Echoes();
    ~Echoes();

    // Run the ncurses‐based Echoes loop. Assumes ncurses is active.
    void startGameCurses();

    // Optional: set difficulty before starting
    void setDifficulty(int d);

private:
    // world state
    std::map<std::string, std::string> roomDescriptions;
    std::map<std::string, std::map<std::string, std::string>> roomExits;
    std::map<std::string, bool> puzzlesSolved;

    // player state
    std::string currentRoom;
    std::set<std::string> inventory;
    std::set<std::string> memoryFragments;

    // game logic
    bool gameOver;
    int difficulty;
    std::string riddleAnswer;

    // internal methods
    void initWorld();
    void processCommand(const std::string& cmd);
    void takeItem(const std::string& item);
    void useItem(const std::string& item);
    void readLog();
    void solvePuzzle();

    // helpers
    void checkGameOver();
    static std::string trim(const std::string& s);
};
