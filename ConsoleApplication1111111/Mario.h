#pragma once
#include "Board.h"
#include <windows.h>

class Game;  
enum  MarioState {
    STANDING,
    WALKING_LEFT,
    WALKING_RIGHT,
    CLIMBING,
    JUMPING,
    FALLING
};

class Mario {
private:
    Game& game;  // Reference to the Game class
    Board& board;      // Reference to the game board

    int x, y;         
    char symbol;       
    MarioState currentState; 
    
    int lives;
    int fallDistance;  
    int fallStartY;    
    bool isFalling;   

    void adjustStartingPosition();  
    bool canMoveTo(int newX, int newY);  
    bool isOnFloor() const { char below = board.getCell(y + 1, x);
        return below == SYMBOL_FLOOR_LEFT ||  below == SYMBOL_FLOOR_RIGHT ||  below == SYMBOL_FLOOR_STRAIGHT; }  
    bool isLadderTile(char tile) const { return tile == SYMBOL_LADDER; }  
    void climbLadder() {  erase();  y -= 4;  draw();  currentState = CLIMBING; }
    void restoreTile(int oldX, int oldY);  
    bool isAtBoundary(int newX) const;  
    void performJump();  
    bool isOnLadder() const   {  char currentTile = board.getCell(y, x); return currentTile == SYMBOL_LADDER; }
    void redrawLadder(); 
    void checkFallDamage();  
   
public:
    Mario(Board& gameBoard, Game& gameInstance, int startX, int startY,int startLives=3);
    bool movingLeft;   
    bool movingRight; 

    void moveUp();
    void moveDown();
    void updateMovement();
    void draw();
    void erase();
    void resetPosition(int startX, int startY) { erase();  x = startX;  y = startY;  adjustStartingPosition(); draw(); }    
    void loseLife();
    void moveLeft()
    {
        movingLeft = true;
        movingRight = false;
        currentState = WALKING_LEFT;
    }
    void moveRight()
    {
        movingRight = true;
        movingLeft = false;
        currentState = WALKING_RIGHT;
    }
    void stay()
    {
        movingLeft = false;
        movingRight = false;
        currentState = STANDING;
    }
    int getLives() const  {  return lives;}
    void resetLives() { lives = 3; }
    int getX() const {
        return x;
    } 
    int getY() const {
        return y;
    }  // Get Mario's Y position

};
