#include "Utils.h"


bool canMoveTo(const Board& board, int newX, int newY, bool ignoreLadders)
{
    if (newX < 0 || newX >= COLS || newY < 0 || newY >= ROWS) 
    {
        return false; 
    }
    char targetCell = board.getCell(newY, newX);


    if (ignoreLadders)
    {
        return targetCell == ' ';
    }

    return targetCell == ' ' || targetCell == SYMBOL_LADDER;
}

void gotoxy(int x, int y) 
{
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void setCursorPosition(int x, int y) 
{  gotoxy(x, y);  }

