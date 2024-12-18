#pragma once
#include "Board.h"
#include "Utils.h"
#include <windows.h>
using namespace std;
class Barrel 
{ private:
    int x, y;             
    int direction;        
    bool isFalling;       
    Board& board;         
    DWORD lastMoveTime;  
    int linesFallen; 
    bool canMoveTo(int newX, int newY) const; 
    void handlePlatformCollision();          

public:
    Barrel(Board& gameBoard,  int startX, int startY, int initialDirection);
    ~Barrel();
    bool exploded; 
    void explode();
    bool isColliding(const Barrel& other) const;
    void update();       
    void draw() const { gotoxy(x, y); cout << SYMBOL_BARREL; }
    void erase() const { gotoxy(x, y); cout << ' '; }
    int getDirection() const { return direction; }
    bool isOutOfBounds() const {return x < 0 || x >= COLS || y >= ROWS; }
    int getX() const{  return x;}
    int getY() const{ return y;}
    bool isExploded() const { return exploded; }

};


