#pragma once
#include <windows.h>
#include <iostream>
#include "Board.h"




// Generalized utility function to check if a move is valid
bool canMoveTo(const Board& board, int newX, int newY, bool ignoreLadders = false);

// Utility to set the cursor position at (X, Y) in the console
void gotoxy(int x, int y);


class Utils {
public:
    static void clearScreen() {  system("cls");} 
    
};
