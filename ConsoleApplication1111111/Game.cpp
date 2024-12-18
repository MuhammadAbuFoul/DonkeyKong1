#include "Game.h"
#include "Utils.h"
#include "Mario.h"
#include "Menu.h"
#include "Barrel.h"

#include <iostream>
#include <conio.h>  
#include <windows.h>
#include <cstdlib>

using namespace std;

Game::Game() : mario(board, *this, 7, 20), isRunning(false), lastSpawnTime(0), paused(false), isColoredTheme(false) 
{
    board.setMario(&mario);
    board.setGame(this);
}

void Game::endGame() 
{
    Utils::clearScreen();
    cout << "Game Over! Returning to the menu...\n";
    Sleep(1000);
    isRunning = false;  
}

void Game::checkVictoryCondition() 
{
    if (mario.getX() == PAULINE_X && mario.getY() == PAULINE_Y) 
    {
        Utils::clearScreen();
        cout << "Congratulations! Mario has rescued Pauline!\n";
        cout << "Returning to the main menu...\n";
        Sleep(3000); 
        isRunning = false; 
    }
}

void Game::run() 
{
    bool quit = false;
    Menu menu;
    while (!quit) 
    {
        Utils::clearScreen();
        cout << "=== Donkey Kong Game ===\n";
        cout << "1. Start New Game\n";
        cout << "8. Show Instructions\n";
        cout << "9. Exit\n";

        char choice;
        cin >> choice;

        switch (choice) 
        {
        case '1':
            selectTheme();
            startGame();
            break;
        case '8':
            Utils::clearScreen();
            menu.showInstructions();
            break;
        case '9':
            quit = true;
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

void Game::selectTheme()
{
    Utils::clearScreen();
    cout << "=== GAME SETTINGS ===\n";
    cout << "- Choose a theme!\n";
    cout << "  1. Default (No Colors)\n";
    cout << "  2. Colored Theme\n";

    char themeChoice;
    cin >> themeChoice;

    switch (themeChoice)
    {
    case '1':
        isColoredTheme = false;

        cout << "Default theme selected. No colors will be used.\n";
        break;
    case '2':
        isColoredTheme = true;
        cout << "Colored theme selected. Colors will be used in the game.\n";
        break;
    default:
        cout << "Invalid choice. Default theme will be used.\n";
        isColoredTheme = false;
    }

    Sleep(1000);
}

void Game::startGame() 
{
    Utils::clearScreen();
    board.resetBoard();
    board.displayBoard();
    mario.resetPosition(7,20);
    mario.resetLives(); 
    prevLives = mario.getLives(); 
    board.displayLives(prevLives); 
    barrels.clear(); 
    isRunning = true;
    lastSpawnTime = GetTickCount64(); 

    while (isRunning)  {

        for (size_t i = 0; i < barrels.size(); ++i) {
            barrels[i]->update();

            // Check for collisions with other barrels
            for (size_t j = i + 1; j < barrels.size(); ++j) {
                if (barrels[i]->isColliding(*barrels[j])) {
                    // Explode both barrels and remove them from the game
                    barrels[i]->explode();
                    barrels[j]->explode();
                    barrels.erase(barrels.begin() + j);
                    barrels.erase(barrels.begin() + i);
                    --i; // Adjust index after erasing
                    break;
                }
            }
        }



        if (paused) {
            Utils::clearScreen();
            cout << "Game paused, press ESC again to continue.\n";
            cout << "Press ESC to continue playing!\n";
            cout << "Use E to EXIT the game!\n";
           
            while (paused) {
                if (_kbhit()) {
                    char key = _getch();  

                    if (key == 27) { 
                        paused = false;  
                        Utils::clearScreen();
                        board.displayBoard(); 
                        mario.draw();
                        board.displayLives(prevLives);
                        break;
                    }
                    else if (key == 'E' || key == 'e') 
                    {
                        Utils::clearScreen();
                        cout << "Exiting to the main menu...\n";
                        Sleep(1500);  
                        isRunning = false;  
                        paused = false;
                        break; 
                        
                    }
                }

                Sleep(100); 
            }

            continue;  
        }

        mario.updateMovement();

        for (auto& barrel : barrels) 
        {
            barrel->update();
        }

        handleCollision();
        updateLivesDisplay();
        updateBarrels();

        if (GetTickCount64() - lastSpawnTime >= 4000) 
        { 
            int randomDirection = (rand() % 2 == 0) ? -1 : 1;  
            barrels.emplace_back(std::make_unique<Barrel>(board, 26, 2, randomDirection));
            lastSpawnTime = GetTickCount64();
        }

        if (_kbhit()) 
        {
            char input = _getch(); 
            handleInput(input);
        }

        Sleep(100); 
    }
}

void Game::updateBarrels() 
{
    for (auto it = barrels.begin(); it != barrels.end();) 
    {
        (*it)->update(); 

        if ((*it)->isOutOfBounds()) 
        {
            it = barrels.erase(it); 
        }
        else if ((*it)->isExploded()) 
        {
            it = barrels.erase(it);
        }
        else 
        {
            ++it;
        }
    }
}

void Game::updateLivesDisplay()
{
    if (prevLives != mario.getLives()) 
    {
        prevLives = mario.getLives();
        board.displayLives(prevLives);
    }
}

void Game::handleCollision() 
{
    for (const auto& barrel : barrels) 
    {
        if (barrel->getX() == mario.getX() && barrel->getY() == mario.getY()) 
        {
            mario.loseLife();  
            board.displayLives(mario.getLives());  

            if (mario.getLives() == 0) 
            {
                endGame();
            }
            else 
            {
                restartStage();  
            }
            return;
        }


        else  if (barrel->getX() == mario.getX()+1 && barrel->getY() == mario.getY()&& mario.movingLeft == true)
        {
            mario.loseLife(); 
            board.displayLives(mario.getLives());  

            if (mario.getLives() == 0) 
            {
                endGame();
            }
            else 
            {
                restartStage();  
            }
            return;


        }
        
        else  if (barrel->getX() == mario.getX()-1 && barrel->getY() == mario.getY()&& mario.movingRight == true)
        {
            mario.loseLife(); 
            board.displayLives(mario.getLives());  

            if (mario.getLives() == 0) 
            {
                endGame();
            }
            else 
            {
                restartStage();  
            }
            return;
        }
    }
}

void Game::restartStage() 
{
    isResettingStage = true;  // Pause barrel updates

    barrels.clear();  
    int randomDirection = (rand() % 2 == 0) ? -1 : 1;  
    barrels.emplace_back(std::make_unique<Barrel>(board, 26, 2, randomDirection));

    board.resetBoard();   
    board.displayBoard(); 

    mario.resetPosition(7, 22);  
    mario.stay();

    board.displayLives(mario.getLives());  
    isResettingStage = false;  // Pause barrel updates

}

void Game::handleInput(char input)
{
    switch (input) 
    {
    case 'a': case 'A': mario.moveLeft(); break;
    case 'd': case 'D': mario.moveRight(); break;
    case 'w': case 'W': mario.moveUp(); break;
    case 'x': case 'X': mario.moveDown(); break;
    case 's': case 'S': mario.stay(); break;
    case 27: 
        if (paused) 
        {
            paused = false;  
        }
        else 
        {
            paused = true;   
        }
        break;
    }
   
}
