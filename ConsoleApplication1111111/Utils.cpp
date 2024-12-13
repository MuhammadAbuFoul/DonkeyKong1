#include "Utils.h"

// Move the console cursor to the specified (x, y) position
void gotoxy(int x, int y) {
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Static method to clear the console screen
void Utils::clearScreen()
{
    system("cls"); // Windows-specific clear command
}

// Alternative function for setting cursor position
void setCursorPosition(int x, int y) {
    gotoxy(x, y); // Reuses gotoxy for consistent behavior
}
