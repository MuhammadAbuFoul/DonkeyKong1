#include "Menu.h"
#include <iostream>
using namespace std;

// Display the main menu options
void Menu::display() const {
    cout << "\n=== Donkey Kong Console Game ===\n";
    cout << "1. Start Game\n";
    cout << "2. Instructions\n";
    cout << "3. Quit\n";
}

// Get the user's menu choice
char Menu::getChoice() const {
    cout << "Enter your choice: ";
    char choice;
    cin >> choice;
    return choice;
}

// Display the instructions for the game
void Menu::showInstructions() const {
    cout << "\n=== Instructions ===\n";
    cout << "1. Use 'A' or 'a' to move left.\n";
    cout << "2. Use 'D' or 'd' to move right.\n";
    cout << "3. Use 'W' or 'w' to climb or jump up.\n";
    cout << "4. Use 'X' or 'x' to climb down.\n";
    cout << "5. Use 'S' or 's' to stop movement.\n";
    cout << "6. Your goal is to rescue Pauline ('$') while avoiding barrels ('O').\n";
    cout << "\nPress Enter to return to the menu...";
    cin.ignore();  // Ignore leftover input
    cin.get();     // Wait for Enter key
}
