#include "Mario.h"
#include "Game.h"
#include "Utils.h"
#include <iostream>
#include <windows.h>
using namespace std;

Mario::Mario(Board& gameBoard, Game& gameInstance, int startX, int startY,int startLives)
    : board(gameBoard), game(gameInstance), x(startX), y(startY), symbol(SYMBOL_MARIO),
    currentState(STANDING), movingLeft(false), movingRight(false),lives(startLives), fallStartY(startY), isFalling(false) 
{
    adjustStartingPosition();
    draw();
}

void Mario::loseLife() { if (lives > 0)    lives--;  else if (lives == 0)  game.endGame(); }

void Mario::adjustStartingPosition()
{
    while (board.getCell(y, x) == SYMBOL_FLOOR_LEFT ||
        board.getCell(y, x) == SYMBOL_FLOOR_RIGHT ||
        board.getCell(y, x) == SYMBOL_FLOOR_STRAIGHT)
    {
        y--;
        if (y < 0) 
        {
            y = 0;
            break;
        }
    }
}

void Mario::draw() 
{
    if (game.isColoredTheme)
    {
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 2);
        gotoxy(x, y);
        cout << symbol;
        SetConsoleTextAttribute(hConsole, 7);
    }
    else
    {
        gotoxy(x, y);
        cout << symbol;
    }
}

void Mario::erase() 
{
    char currentTile = board.getCell(y, x);
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (currentTile == SYMBOL_LADDER)
    {

        gotoxy(x, y);
        if(game.isColoredTheme)
            SetConsoleTextAttribute(hConsole, 3);
        cout << SYMBOL_LADDER;  
    }
    else 
    {
        gotoxy(x, y);
        cout << ' '; 
    }
}

void Mario::restoreTile(int oldX, int oldY) 
{
    char tile = board.getCell(oldY, oldX);
    if (isLadderTile(tile) || tile == SYMBOL_FLOOR_LEFT || tile == SYMBOL_FLOOR_RIGHT || tile == SYMBOL_FLOOR_STRAIGHT)
    {
        gotoxy(oldX, oldY);
        cout << tile;
    }
}

bool Mario::canMoveTo(int newX, int newY) { return ::canMoveTo(board, newX, newY); }

bool Mario::isAtBoundary(int newX) const { 
    char targetCell = board.getCell(y, newX);
    return targetCell == SYMBOL_BOUNDARY;
}

void Mario::redrawLadder() {
    char below = board.getCell(y + 1, x);
    if (isLadderTile(below)) 
    { gotoxy(x, y);
      cout << SYMBOL_LADDER;
    }
}

void Mario::updateMovement() 
{
    if (!isOnFloor() && !isOnLadder()) 
    {
        if (!isFalling) {  
            isFalling = true;
            fallStartY = y;  
        }
        erase();
        y++; 
        draw();
        currentState = FALLING;
        return;
    }

    if (isFalling && isOnFloor()) {
        checkFallDamage();  
        isFalling = false;  
    }

    char tileR = board.getCell(y, x + 1);         
    if (isLadderTile(tileR) && currentState == WALKING_RIGHT) {
        erase();
        x += 2;
        draw();

    }
    char tileL = board.getCell(y, x -1 );
    if (isLadderTile(tileL) && currentState == WALKING_LEFT)  {
        erase();
        x -= 2;
        draw();
    }


    else if (movingLeft &&  canMoveTo(x - 1, y)&& !isAtBoundary(x - 1)) {
        erase();
        x--;
        draw();
    }
    else if (movingRight && canMoveTo(x + 1, y) && !isAtBoundary(x + 1))  {
        erase();
        x++;
        draw();
    }
       game.checkVictoryCondition();
}

void Mario::checkFallDamage() 
{
    int fallDistance = fallStartY - y;
    fallDistance *= -1;

    if (fallDistance >= 5)  {
        loseLife();  
        game.restartStage(); 
    }
}

void Mario::moveUp() 
{
    char above = board.getCell(y - 1, x);
    char rightTile= board.getCell(y, x+1);
    char leftTile = board.getCell(y, x-1);

    if (isLadderTile(above) || isLadderTile(rightTile) || isLadderTile(leftTile)) { climbLadder(); }
    else if (isOnFloor()) { performJump(); } 
    
}

void Mario::moveDown()
{
    char below = board.getCell(y + 2, x);
    char belowToRight = board.getCell(y + 2, x + 1);
    char belowToLeft = board.getCell(y + 2, x - 1);

    if (isLadderTile(below)){
        erase();
        y += 3;
        x++;
        draw();
        currentState = CLIMBING;
    }

    else if (isLadderTile(belowToRight) || isLadderTile(belowToLeft)) {
        erase();
        y += 3;
        draw();
        currentState = CLIMBING;
    }
    

}

void Mario::performJump()
{
    int jumpHeight = 2; 
    char above1 = board.getCell(y - 1, x); 
    char above2 = board.getCell(y - 2, x);

    if (above1 == SYMBOL_FLOOR_LEFT || above1 == SYMBOL_FLOOR_RIGHT || above1 == SYMBOL_FLOOR_STRAIGHT || above1 == SYMBOL_BOUNDARY ) return;
    
    if (y - jumpHeight >= 0) {
        if (above2 == SYMBOL_FLOOR_LEFT || above2 == SYMBOL_FLOOR_RIGHT || above2 == SYMBOL_FLOOR_STRAIGHT || above2 == SYMBOL_LADDER || above2 == SYMBOL_BOUNDARY){
            erase();
            y--; 
            draw();
        }
        else  {
           erase();
           y -= jumpHeight; 

            if (currentState == WALKING_RIGHT) {
                if (canMoveTo(x + 2, y)) { x += 2; } }
            else if (currentState == WALKING_LEFT) 
            {
                if (canMoveTo(x - 2, y)) { x -= 2; }
                 else if (currentState == STANDING) return;
            }

            draw(); 
            currentState = JUMPING; 
        }
    }
}
