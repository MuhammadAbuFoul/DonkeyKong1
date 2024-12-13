#include "Mario.h"
#include "Utils.h"
#include <iostream>
using namespace std;

// Constructor: Initialize Mario's position
Mario::Mario(Board& gameBoard, int startX, int startY)
    : board(gameBoard), x(startX), y(startY), symbol(SYMBOL_MARIO),
    currentState(WALKING), movingLeft(false), movingRight(false) {
    adjustStartingPosition();
    draw();
}

// Adjust Mario's starting position
void Mario::adjustStartingPosition() {
    while (board.getCell(y, x) == SYMBOL_FLOOR_LEFT ||
        board.getCell(y, x) == SYMBOL_FLOOR_RIGHT ||
        board.getCell(y, x) == SYMBOL_FLOOR_STRAIGHT) {
        y--;
        if (y < 0) {
            y = 0;
            break;
        }
    }
}

// Render Mario at his current position
void Mario::draw() {
    gotoxy(x, y);
    cout << symbol;
}

// Clear Mario from his current position
void Mario::erase() {
    restoreTile(x, y);
    gotoxy(x, y);
    cout << ' ';
}

// Restore a ladder or floor tile
void Mario::restoreTile(int oldX, int oldY) {
    char tile = board.getCell(oldY, oldX);
    if (isLadderTile(tile) || tile == SYMBOL_FLOOR_LEFT || tile == SYMBOL_FLOOR_RIGHT || tile == SYMBOL_FLOOR_STRAIGHT) {
        gotoxy(oldX, oldY);
        cout << tile;
    }
}

// Validate if Mario can move to a target position
bool Mario::canMoveTo(int newX, int newY) {
    if (newX < 0 || newX >= COLS || newY < 0 || newY >= ROWS) {
        return false;
    }
    char targetCell = board.getCell(newY, newX);
    return targetCell == ' ' || targetCell == SYMBOL_LADDER;
}

// Check if a tile is a ladder tile
bool Mario::isLadderTile(char tile) const {
    return tile == SYMBOL_LADDER;
}

// Check if Mario is on a floor
bool Mario::isOnFloor() const {
    char below = board.getCell(y + 1, x);
    return below == SYMBOL_FLOOR_LEFT ||
        below == SYMBOL_FLOOR_RIGHT ||
        below == SYMBOL_FLOOR_STRAIGHT;
}

// Check if Mario is standing on a ladder
bool Mario::isOnLadder() const {
    char currentTile = board.getCell(y, x);
    return currentTile == SYMBOL_LADDER;
}

// Check if Mario is at a boundary
bool Mario::isAtBoundary(int newX) const {
    char targetCell = board.getCell(y, newX);
    return targetCell == SYMBOL_BOUNDARY;
}

// Redraw the ladder tile when Mario moves off it
void Mario::redrawLadder() {
    char below = board.getCell(y + 1, x);
    if (isLadderTile(below)) {
        gotoxy(x, y);
        cout << SYMBOL_LADDER;
    }
}

// Update Mario's movement and handle falling
void Mario::updateMovement() {
    if (!isOnFloor() && !isOnLadder()) {
        erase();
        y++;
        draw();
        currentState = FALLING;
        return;
    }

    if (movingLeft && canMoveTo(x - 1, y) && !isAtBoundary(x - 1)) {
        erase();
        x--;
        draw();
    }
    else if (movingRight && canMoveTo(x + 1, y) && !isAtBoundary(x + 1)) {
        erase();
        x++;
        draw();
    }
}

// Move Mario left
void Mario::moveLeft() {
    movingLeft = true;
    movingRight = false;
    currentState = WALKING;
}

// Move Mario right
void Mario::moveRight() {
    movingRight = true;
    movingLeft = false;
    currentState = WALKING;
}

// Stop Mario's movement
void Mario::stay() {
    movingLeft = false;
    movingRight = false;
}

// Handle Mario's climbing or jumping
void Mario::moveUp() {
    char above = board.getCell(y - 1, x);

    if (isLadderTile(above)) {
        climbLadder();
    }
    else if (isOnFloor()) {
        performJump();
    }
}

// Perform ladder climbing logic
void Mario::climbLadder() {
    erase();
    y -= 4;  // Skip the ceiling tiles above the ladder
    draw();
    currentState = CLIMBING;
}

// Move Mario down
void Mario::moveDown() {
    char below = board.getCell(y + 1, x);

    if (isLadderTile(below)) {
        erase();
        y++;
        draw();
        currentState = CLIMBING;
    }
}

// Perform Mario's jumping logic
void Mario::performJump() {
    int jumpHeight = 2;
    if (y - jumpHeight >= 0) {
        erase();
        y -= jumpHeight;
        draw();
        currentState = JUMPING;
    }
}
