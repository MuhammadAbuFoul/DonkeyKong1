#pragma once
#include "Menu.h"
#include "Board.h"

class Game {
private:
    Menu menu;     // Menu instance
    Board board;  // Game board instance
    bool isRunning;

public:
    Game();        // Constructor
    void run();    // Main game loop
    void startGame();  // Starts the game
};
