#pragma once
#include "Board.h"
#include "Mario.h"
#include "Barrel.h"

#include <vector>
#include <memory>
#include <windows.h>

using namespace std;
constexpr int PAULINE_X = 66; // Pauline's X-coordinate
constexpr int PAULINE_Y = 2;  // Pauline's Y-coordinate


class Game {
private:
    Board board;                              // Game board
    Mario mario;                              // Mario character
    vector<unique_ptr<Barrel>> barrels; // List of barrels
    bool isRunning;                           // Game loop state
    bool paused;  // To track if the game is paused
    int prevLives;                           // Previous lives for display
    DWORD lastSpawnTime;                      // Time of last barrel spawn

    // Helper methods
    void updateBarrels();                     // Updates all barrels
    void handleInput(char input);             // Handles user input
    void updateLivesDisplay();                 // Updates the lives display
    void handleCollision();                  // Check collisions and handle logic
 
public:
    Game();                                   // Constructor

    void selectTheme();   // Secondary menu for theme selection

    void run();                                 // Main game loop
    void startGame();                          // Starts a new game
    void restartStage();                      // Restart the stage logic
    void endGame();                          // Handles Game Over
    void checkVictoryCondition();           // Checks if Mario has reached Pauline
    bool isResettingStage;  // Flag to indicate stage reset
    bool isColoredTheme; // Tracks if the game uses a colored theme



};
