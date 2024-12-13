#pragma once
#include <iostream>
#include <cstring>

const int ROWS = 25;
const int COLS = 80;

const char SYMBOL_MARIO = '@';
const char SYMBOL_DONKEY = '&';
const char SYMBOL_BARREL = 'O';
const char SYMBOL_PAULINE = '$';
const char SYMBOL_LADDER = 'H';
const char SYMBOL_FLOOR_LEFT = '<';
const char SYMBOL_FLOOR_RIGHT = '>';
const char SYMBOL_FLOOR_STRAIGHT = '=';
const char SYMBOL_BOUNDARY = 'Q';


class Board {
private:
    char currentBoard[ROWS][COLS + 1];
    const char* originalBoard[ROWS] = {
        "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ",
        "Q                                                           $                Q",
        "Q    [OOOO_ &                                    ========================    Q",
        "Q      ========                                                     H        Q",    
        "Q                                                                   H        Q",
        "Q                                                                   H        Q",
        "Q   ======================================================   ============    Q",
        "Q         H                            H                                     Q",
        "Q         H                            H                                     Q",
        "Q         H                            H                                     Q",
        "Q  >>>>>>>>>>>>    <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<              Q",
        "Q                                                         H                  Q",
        "Q                                                         H                  Q",
        "Q      ===================================         <<<<<<<<<<<<<<<<<<<<<     Q",
        "Q                                                                            Q",
        "Q                    ===========================================             Q",
        "Q                                                           H                Q",
        "Q   >>>>>>>>>>>>>>>                                         H                Q",
        "Q                                                           H                Q",
        "Q                >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>         Q",
        "Q                    H                                                       Q",
        "Q                    H                                                       Q",
        "Q                    H                                                       Q",
        "Q============================================================================Q",
        "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"
    };



public:


    Board();
    void resetBoard();
    void displayBoard();
    char getCell(int row, int col) const;
    void setCell(int row, int col, char value);
};
