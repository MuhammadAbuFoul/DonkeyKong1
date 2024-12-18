#include "Menu.h"
#include <iostream>
using namespace std;

void Menu::showInstructions() const {
    cout << "\n=== Instructions ===\n";
    cout << "1. Use 'A' to move left.\n";
    cout << "2. Use 'D' to move right.\n";
    cout << "3. Use 'W' to climb or jump up.\n";
    cout << "4. Use 'X' to climb down.dd\n";
    cout << "5. Use 'S' to stop movement.\n";
    cout << "6. Your goal is to rescue Pauline ($) while avoiding DonkeyKong's barrels (O).\n";
    cout << "\nPress Enter to return to the menu...";
    cin.ignore();  
    cin.get();     
}
