#include "Game.h"
#include "Utils.h"
#include "Mario.h"
#include <iostream>
#include <conio.h>  // For _kbhit and _getch
#include <windows.h>
using namespace std;

// Constructor: Initializes the game state
Game::Game() : isRunning(true) {}

// Main game loop
void Game::run() {
    while (isRunning) {
        Utils::clearScreen();   // Clear the screen before showing the menu
        menu.display();         // Display the menu options
        char choice = menu.getChoice();

        switch (choice) {
        case '1':
            startGame();        // Start the game
            break;
        case '2':
            menu.showInstructions();  // Show instructions
            break;
        case '3':
            cout << "Exiting game. Goodbye!\n";
            isRunning = false;  // Exit the game loop
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            Sleep(1000);  // Wait briefly to let the user see the message
            break;
        }
    }
}

// Starts the game
void Game::startGame() {
    Utils::clearScreen();      // Clear the screen
    board.resetBoard();        // Reset the board to its initial state
    board.displayBoard();      // Display the board

    Mario mario(board, 7, 20); // Create Mario at the initial position
    bool inGame = true;

    // In-game loop
    while (inGame) {
        mario.updateMovement();  // Handle Mario's movement and interactions
        if (_kbhit()) {          // Detect user input
            char input = _getch();
            switch (input) {
            case 'a': case 'A': mario.moveLeft(); break;  // Move left
            case 'd': case 'D': mario.moveRight(); break; // Move right
            case 'w': case 'W': mario.moveUp(); break;    // Jump or climb up
            case 'x': case 'X': mario.moveDown(); break;  // Climb down
            case 's': case 'S': mario.stay(); break;      // Stop movement
            case 27:  // ESC key to exit the game
                inGame = false;
                break;
            default:
                cout << "Invalid key. Try again.\n";
                break;
            }
        }
        Sleep(100);  // Control game speed
    }
}
