#include "Board.h"
#include "Game.h"
#include "Utils.h"

#include <iostream>
#include <cstring>
#include<windows.h>

using namespace std;

Board::Board() {
    resetBoard();
}

void Board::displayLives(int lives) {

    if (game->isColoredTheme) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        gotoxy(4, 2);
        cout << "LIVES: ";


        if (lives == 1) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << lives << " ";

        }
        else if (lives == 2) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << lives << " ";

        }
        else {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << lives << " ";

        }

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout.flush();

    }
    else {
        {
            gotoxy(4, 2);
            cout << "LIVES: " << lives << " ";
            cout.flush();
        }
    } 

}

void Board::resetBoard() 
{
    for (int i = 0; i < ROWS; ++i) 
    {
        memcpy(currentBoard[i], originalBoard[i], COLS);
        currentBoard[i][COLS] = '\0'; 
    }
}

void Board::displayBoard() 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < ROWS; ++i) 
    {
        gotoxy(0, i);

        for (int j = 0; j < COLS; ++j)
        {
            char cell = currentBoard[i][j];
            if (game->isColoredTheme) 
            {
                  if (cell == SYMBOL_LADDER) SetConsoleTextAttribute(hConsole, 3);
                else if (cell == SYMBOL_PAULINE) SetConsoleTextAttribute(hConsole, 2);
                else if (cell == SYMBOL_DONKEY) SetConsoleTextAttribute(hConsole, 12);
                else if (cell == SYMBOL_BOUNDARY) SetConsoleTextAttribute(hConsole, 50);
                else if  (cell == SYMBOL_FLOOR_STRAIGHT ) SetConsoleTextAttribute(hConsole, 6);
                else if (cell == SYMBOL_FLOOR_LEFT || cell == SYMBOL_FLOOR_RIGHT ) SetConsoleTextAttribute(hConsole,14);
                else SetConsoleTextAttribute(hConsole, 7);
            }
            cout << cell;
        }
    }

    SetConsoleTextAttribute(hConsole, 7); 
}


