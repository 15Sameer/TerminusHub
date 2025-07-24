// src/echoes.cpp
#include "echoes.hpp"
#include <ncurses.h>
#include <algorithm>

// Trim leading/trailing whitespace
std::string Echoes::trim(const std::string &s) {
    size_t st = s.find_first_not_of(" \t\r\n");
    if (st == std::string::npos) return "";
    size_t en = s.find_last_not_of(" \t\r\n");
    return s.substr(st, en - st + 1);
}

Echoes::Echoes() : gameOver(false), difficulty(1) {
    initWorld();
}
Echoes::~Echoes() = default;

void Echoes::setDifficulty(int d) {
    difficulty = (d >= 1 && d <= 3) ? d : 1;
}

void Echoes::initWorld() {
    roomDescriptions = {
        {"Core",    "You awaken in the Core Room of the forgotten system. Screens flicker with static."},
        {"Hall",    "A dim hallway stretches before you, humming faintly with corrupted energy."},
        {"Archive", "The Archive holds corrupted logs; faint whispers echo in the digital mist."},
        {"Vault",   "A sealed Vault door blocks your way. A keypad glows faintly."},
        {"Memory",  "Memory fragments pulse faintly here. You sense pieces of your lost identity."}
    };
    roomExits = {
        {"Core",    {{"north","Hall"}}},
        {"Hall",    {{"south","Core"},{"east","Archive"},{"west","Vault"}}},
        {"Archive", {{"west","Hall"}}},
        {"Vault",   {{"east","Hall"},{"north","Memory"}}},
        {"Memory",  {{"south","Vault"}}}
    };
    puzzlesSolved = {{"VaultDoor",false}, {"ArchivePuzzle",false}};
    currentRoom = "Core";
    inventory.clear();
    memoryFragments.clear();
    riddleAnswer = "echo";
    gameOver = false;
}

void Echoes::startGameCurses() {
    // Set cyan background / black text
    wbkgd(stdscr, COLOR_PAIR(6));
    clear(); refresh();

    // ----- Instruction Screen -----
    int row = 1;
    attron(A_BOLD);
    mvprintw(row++, 4, "Echoes of the Forgotten Terminal");
    attroff(A_BOLD);
    row++;
    mvprintw(row++, 2, "Story Plot:");
    mvprintw(row++, 4, "You awaken in the Core of an ancient AI system,");
    mvprintw(row++, 4, "its memories corrupted by a virus. Each room holds");
    mvprintw(row++, 4, "fragments of your identity—or deadly traps.");
    row++;
    mvprintw(row++, 2, "Your Mission:");
    mvprintw(row++, 4, "1) Recover at least one MEMORY FRAGMENT in the Memory room.");
    mvprintw(row++, 4, "2) Solve the Archive riddle to learn the Vault code.");
    mvprintw(row++, 4, "3) Enter the code to retrieve the POWER CELL from the Vault.");
    mvprintw(row++, 4, "4) Return to the Core and 'use power cell' to escape.");
    row++;
    mvprintw(row++, 2, "How to Play:");
    mvprintw(row++, 4, "- Navigate: 'go north/south/east/west'");
    mvprintw(row++, 4, "- Inspect: 'look around'");
    mvprintw(row++, 4, "- Pick up: 'take memory fragment' in Memory");
    mvprintw(row++, 4, "- Read clue: 'read log' in Archive");
    mvprintw(row++, 4, "- Solve riddle: 'solve puzzle', then type answer");
    mvprintw(row++, 4, "- Unlock Vault: 'enter code aether'");
    mvprintw(row++, 4, "- Use cell: 'use power cell' in Core");
    mvprintw(row++, 4, "- Show items: 'inventory'");
    mvprintw(row++, 4, "- Quit anytime: 'q'");
    row += 2;
    mvprintw(row++, 4, "Press any key to begin...");
    refresh();
    getch();

    // ----- Main Game Loop with real‑time echo -----
    char buf[128];
    while (true) {
        wbkgd(stdscr, COLOR_PAIR(6));
        clear();

        // Display room
        mvprintw(0, 0, "[%s]", currentRoom.c_str());
        mvprintw(1, 0, "%s", roomDescriptions[currentRoom].c_str());

        // Exits
        mvprintw(3, 0, "Exits:");
        int cx = 7;
        for (auto &e : roomExits[currentRoom]) {
            mvprintw(3, cx, "%s ", e.first.c_str());
            cx += e.first.size() + 1;
        }

        // Inventory count
        mvprintw(5, 0, "(Inventory: %zu items)", inventory.size());

        // Prompt
        mvprintw(LINES-2, 0, "> ");
        refresh();

        // Enable echo & cursor for real‑time typing
        echo();
        curs_set(1);
        move(LINES-2, 2);
        getnstr(buf, sizeof(buf));
        noecho();
        curs_set(0);

        std::string cmd = trim(buf);
        std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

        // Quit immediately
        if (cmd == "q") return;

        processCommand(cmd);
        checkGameOver();

        // Win check
        if (inventory.count("power cell") && !memoryFragments.empty()) {
            wbkgd(stdscr, COLOR_PAIR(7));
            clear();
            attron(A_BOLD);
            mvprintw(LINES/2 - 1, (COLS-20)/2, "Memories Flood Back!");
            attroff(A_BOLD);
            mvprintw(LINES/2 + 1, (COLS-28)/2, "Use the power cell to finally escape.");
            refresh();
            napms(2000);
            return;
        }
    }
}

// --- command handlers (unchanged) ---
void Echoes::processCommand(const std::string &cmd) {
    if (cmd == "help") {
        wbkgd(stdscr, COLOR_PAIR(6));
        clear();
        mvprintw(1,0,
            "Type 'q' at any prompt to quit.\n\n"
            "Commands:\n"
            "  look around\n"
            "  go <direction>\n"
            "  take memory fragment\n"
            "  read log\n"
            "  solve puzzle\n"
            "  enter code <code>\n"
            "  use power cell\n"
            "  inventory\n"
        );
        mvprintw(LINES-1,0,"Press any key...");
        refresh(); getch();
    }
    else if (cmd == "look around") {
        mvprintw(7,0,"%s", roomDescriptions[currentRoom].c_str());
        mvprintw(LINES-1,0,"Press any key...");
        refresh(); getch();
    }
    else if (cmd.rfind("go ",0)==0) {
        std::string d = cmd.substr(3);
        auto &ex = roomExits[currentRoom];
        if (ex.count(d)) {
            currentRoom = ex[d];
            mvprintw(7,0,"You move %s.", d.c_str());
        } else {
            mvprintw(7,0,"Cannot go %s.", d.c_str());
        }
        mvprintw(LINES-1,0,"Press any key...");
        refresh(); getch();
    }
    else if (cmd.rfind("take ",0)==0) {
        takeItem(cmd.substr(5));
    }
    else if (cmd.rfind("use ",0)==0) {
        useItem(cmd.substr(4));
    }
    else if (cmd == "read log") {
        readLog();
    }
    else if (cmd == "solve puzzle") {
        solvePuzzle();
    }
    else if (cmd.rfind("enter code ",0)==0) {
        std::string code = cmd.substr(11);
        if (currentRoom=="Vault") {
            if (code=="aether") {
                puzzlesSolved["VaultDoor"]=true;
                inventory.insert("power cell");
                mvprintw(7,0,"Vault unlocked! You retrieve a power cell.");
            } else {
                mvprintw(7,0,"Incorrect code.");
            }
        } else {
            mvprintw(7,0,"No keypad here.");
        }
        mvprintw(LINES-1,0,"Press any key...");
        refresh(); getch();
    }
    else if (cmd=="inventory") {
        clear();
        if (inventory.empty()) {
            mvprintw(1,0,"Inventory is empty.");
        } else {
            mvprintw(1,0,"Inventory:");
            int r=2;
            for (auto &i:inventory)
                mvprintw(r++,0,"- %s", i.c_str());
        }
        mvprintw(LINES-1,0,"Press any key...");
        refresh(); getch();
    }
    else {
        mvprintw(7,0,"Unrecognized command.");
        mvprintw(LINES-1,0,"Press any key...");
        refresh(); getch();
    }
}

void Echoes::takeItem(const std::string &item) {
    if (currentRoom=="Memory" && item=="memory fragment") {
        if (memoryFragments.insert("frag1").second) {
            inventory.insert(item);
            mvprintw(7,0,"You take a memory fragment.");
        } else {
            mvprintw(7,0,"Already collected.");
        }
    } else {
        mvprintw(7,0,"Cannot take %s here.", item.c_str());
    }
    mvprintw(LINES-1,0,"Press any key...");
    refresh(); getch();
}

void Echoes::useItem(const std::string &item) {
    if (!inventory.count(item)) {
        mvprintw(7,0,"You don't have %s.", item.c_str());
    }
    else if (item=="power cell" && currentRoom=="Core") {
        mvprintw(7,0,"You power up the Core. Escape initiated!");
    } else {
        mvprintw(7,0,"Nothing happens.");
    }
    mvprintw(LINES-1,0,"Press any key...");
    refresh(); getch();
}

void Echoes::readLog() {
    if (currentRoom=="Archive" && !puzzlesSolved["ArchivePuzzle"]) {
        mvprintw(7,0,"\"Memory fragments unlock your lost self.");
        mvprintw(8,0," The vault code is 'aether'.\"");
    } else {
        mvprintw(7,0,"Nothing to read here.");
    }
    mvprintw(LINES-1,0,"Press any key...");
    refresh(); getch();
}

void Echoes::solvePuzzle() {
    if (currentRoom=="Archive" && !puzzlesSolved["ArchivePuzzle"]) {
        mvprintw(7,0,"Riddle: 'I speak without a mouth and hear without ears...'");
        mvprintw(8,0,"Answer: ");
        echo(); curs_set(1);
        char ans[64]; getnstr(ans,64);
        noecho(); curs_set(0);
        std::string a = trim(ans);
        std::transform(a.begin(),a.end(),a.begin(),::tolower);
        if (a == riddleAnswer) {
            puzzlesSolved["ArchivePuzzle"]=true;
            mvprintw(10,0,"Correct! The archive reveals its secrets.");
        } else {
            mvprintw(10,0,"Incorrect.");
        }
    } else {
        mvprintw(7,0,"No puzzle here.");
    }
    mvprintw(LINES-1,0,"Press any key...");
    refresh(); getch();
}

void Echoes::checkGameOver() {
    // no-op here since we handle win in startGameCurses()
}
