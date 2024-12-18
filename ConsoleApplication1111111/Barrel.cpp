#include "Barrel.h"
#include "Utils.h"
#include"Game.h"
#include"Mario.h"

#include <cmath> 
#include <iostream>
#include <windows.h>

using namespace std;

Barrel::Barrel(Board& gameBoard, int startX, int startY, int initialDirection)
    : board(gameBoard), x(startX), y(startY), direction(initialDirection), isFalling(true), lastMoveTime(GetTickCount64()), linesFallen(0), exploded(false) 
{

}

Barrel::~Barrel() = default; 

bool Barrel::isColliding(const Barrel& other) const {
    if (x == other.getX() && y == other.getY()) {
        return true;
    }

    if (y == other.getY() && abs(x - other.getX()) == 1) { 
                                                         
        if ((direction == -1 && other.getDirection() == 1 && x > other.getX()) ||
            (direction == 1 && other.getDirection() == -1 && x < other.getX())) {
            return true;
        }
    }

    return false;
}

void Barrel::explode() 
{
    erase();
    exploded = true;
    board.setCell(y, x, ' ');  
    int marioX = board.getMario().getX();  
    int marioY = board.getMario().getY();  
    int distance = abs(x - marioX) + abs(y - marioY);
    if (distance <= 2)
    {
        board.getMario().loseLife();
        board.getGame().restartStage(); 
    }
}

void Barrel::update() 
{

    DWORD currentTime = GetTickCount64(); 
    const DWORD moveDelay = 15;        

   
    if (currentTime - lastMoveTime >= moveDelay){
        erase(); 

        if (isFalling) {
            if (canMoveTo(x, y + 1)) {
                y++;
                linesFallen++;
            }
            else  {
                if(linesFallen >=8) {
                    explode();
                    return;
                }
                isFalling = false; 
                linesFallen = 0;
            }
        }
        else  {
            char below = board.getCell(y + 1, x);
            if (below == SYMBOL_FLOOR_LEFT) {   direction = -1;    }
            else if (below == SYMBOL_FLOOR_RIGHT)  {  direction = 1; }
            else if (below == ' ') { isFalling = true;  }

     
            int nextX = x + direction;
            if (canMoveTo(nextX, y)) { x = nextX;}
            else if (board.getCell(y, x + 1) == SYMBOL_LADDER && direction == 1) { x += 2;}
            else if (board.getCell(y, x - 1) == SYMBOL_LADDER && direction == -1) { x -= 2;}
            else if (board.getCell(y, x - 1) == SYMBOL_DONKEY && direction == -1) { x -= 2;}
            else if (board.getCell(y, x + 1) == SYMBOL_DONKEY && direction == 1) { x += 2;}
            else if (board.getCell(y, x + 1) == SYMBOL_BOUNDARY && direction == 1) { direction *= -1;}
            else if (board.getCell(y, x - 1) == SYMBOL_BOUNDARY && direction == -1) { direction *= -1; }
            
        }
        draw(); 
        lastMoveTime = currentTime; 
    }
}

bool Barrel::canMoveTo(int newX, int newY) const 
{
    if (newX < 0 || newX >= COLS || newY < 0 || newY >= ROWS) { return false;}
    char targetCell = board.getCell(newY, newX);
    return targetCell == ' ';
}

void Barrel::handlePlatformCollision() 
{
    char below = board.getCell(y + 1, x);
    if (below == SYMBOL_FLOOR_LEFT) { direction = -1;   }
    else if (below == SYMBOL_FLOOR_RIGHT) { direction = 1; }
    else  {   isFalling = true; }
}
