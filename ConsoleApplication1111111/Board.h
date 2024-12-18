#pragma once

#include <iostream>
#include <cstring>


class Mario;
class Game;

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
    Mario* mario; 
    Game* game; 
    char currentBoard[ROWS][COLS + 1];
    const char* originalBoard[ROWS] = {
//       01234567890123456789012345678901234567890123456789012345678901234567890123456789
        "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ",
        "Q                                                                              Q",
        "Q                                                                $             Q",
        "Q                       &                           ========================   Q",    
        "Q                  <============>                                  H           Q",
        "Q                                                                  H           Q",
        "Q                                                                  H           Q",
        "Q   =========>>>>=========     ==========================================      Q",
        "Q         H                            H                                       Q",
        "Q         H                            H                                       Q",
        "Q     =>>>>>>>>>=        =<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<=            Q",
        "Q             H                                            H                   Q",
        "Q             H                                            H                   Q",
        "Q      ============             ==========         =<<<<<<<<<<<<<<<<<<<<=      Q",
        "Q                                                                              Q",
        "Q                 ======     ====================================              Q",
        "Q                                                           H                  Q",
        "Q   =>>>>>>>>>>>>>>>=                                       H                  Q",
        "Q                                                           H                  Q",
        "Q               ====>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>=====   Q",
        "Q                    H                                                H        Q",
        "Q                    H                                                H        Q",
        "Q                    H                                                H        Q",
        "Q==============================================================================Q",
        "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"
    };



public:
    Board();

    void resetBoard();

    void displayBoard();
  
    char getCell(int row, int col) const { if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {  return currentBoard[row][col];} return '\0';}

    void setCell(int row, int col, char value) {if (row >= 0 && row < ROWS && col >= 0 && col < COLS) { currentBoard[row][col] = value; } }
  
   void displayLives(int lives); 

    void setMario(Mario* marioRef) {  mario = marioRef; }

    void setGame(Game* gameRef) {   game = gameRef; }
    
    Mario& getMario() const  { return *mario; }

    Game& getGame() const { return *game; }


};
