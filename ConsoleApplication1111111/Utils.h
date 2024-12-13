#pragma once
#include <windows.h>
#include <iostream>

// Utility to set the cursor position at (X, Y) in the console
void gotoxy(int x, int y);

class Utils {
public:
    // Clear the console screen for Windows
    static void clearScreen();
};

// Global utility function for setting cursor position (alternative to gotoxy)
void setCursorPosition(int x, int y);
