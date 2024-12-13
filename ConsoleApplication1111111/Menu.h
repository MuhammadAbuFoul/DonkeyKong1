#pragma once

class Menu {
public:
    void display() const;           // Displays the menu options
    char getChoice() const;         // Gets the user's menu choice
    void showInstructions() const;  // Displays the instructions for the game
};
