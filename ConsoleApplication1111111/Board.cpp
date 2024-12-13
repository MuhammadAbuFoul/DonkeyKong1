#include "Board.h"
#include "Utils.h"
#include <iostream>
#include <cstring>

using namespace std;

Board::Board() {
    resetBoard();
}

void Board::resetBoard() {
    for (int i = 0; i < ROWS; ++i) {
        memcpy(currentBoard[i], originalBoard[i], COLS);
        currentBoard[i][COLS] = '\0'; // Null-terminate each row
    }
}

void Board::displayBoard() {
    for (int i = 0; i < ROWS; ++i) {
        gotoxy(0, i); // Use `gotoxy` to position rows correctly
        cout << currentBoard[i]; // Print the board row by row
    }
}

char Board::getCell(int row, int col) const {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        return currentBoard[row][col];
    }
    return '\0'; // Return null character for out-of-bounds access
}

void Board::setCell(int row, int col, char value) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        currentBoard[row][col] = value;
    }
}
