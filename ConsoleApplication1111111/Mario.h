#pragma once
#include "Board.h"

// Enum to track Mario's state
enum MarioState {
    WALKING,
    CLIMBING,
    JUMPING,
    FALLING
};

class Mario {
private:
    int x, y;          // Mario's position (column and row)
    char symbol;       // Mario's symbol ('@')
    Board& board;      // Reference to the game board
    MarioState currentState; // Current state of Mario
    bool movingLeft;   // Flag for left movement
    bool movingRight;  // Flag for right movement

    // Helper functions
    void adjustStartingPosition();  // Adjust Mario's starting position
    bool canMoveTo(int newX, int newY);  // Check if Mario can move to a specific position
    bool isOnFloor() const;  // Check if Mario is standing on a floor
    bool isLadderTile(char tile) const;  // Check if a tile is a ladder tile
    void climbLadder();  // Handle ladder climbing logic
    void restoreTile(int oldX, int oldY);  // Restore ladder or floor tiles
    bool isAtBoundary(int newX) const;  // Check if Mario is at a boundary
    void performJump();  // Handle Mario's jumping logic
    bool isOnLadder() const; // Check if Mario is standing on a ladder
    void redrawLadder(); // Restore ladder tile when Mario moves

public:
    Mario(Board& gameBoard, int startX, int startY);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void stay();
    void updateMovement();
    void draw();
    void erase();
};
