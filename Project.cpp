#include <iostream>
#include <string>
#include <cstring>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include <time.h>
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* gameData;
Player* snake;
char dir = 0;
bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(gameData->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{

    int x,y;

    MacUILib_init();

    MacUILib_clearScreen();
    MacUILib_printf("Enter width of Game Board (if you press '0' it will be the default board size):\n");
    cin >> x;

    MacUILib_printf("Enter height of Game Board (if you press '0' it will be the default board size):\n");
    cin >> y;

    srand(time(NULL));
    MacUILib_clearScreen();
    MacUILib_Delay(500000);
    gameData = new GameMechs(x,y);
    snake = new Player(gameData);
    objPosArrayList temp;
    snake->getPlayerPos(temp);
    gameData->generateFood(&temp);

    while(!MacUILib_hasChar()) // Display an introductory message and wait for user input
    {
        MacUILib_clearScreen();
        MacUILib_Delay(500000000);

        MacUILib_printf("Hey!\nWelcome to a cool demo of a snake game :) \n(Created by Brayden Roberts & Diya Bahl)\nPress any key to continue");
        MacUILib_Delay(500000); 

    }
    
    MacUILib_clearScreen();
    
}

void GetInput(void)
{
   if(MacUILib_hasChar())
    {
        gameData->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    snake->updatePlayerDir();
    snake->movePlayer();
    
}

void DrawScreen(void)
{   // Get the position of the food and update it on the game board
    MacUILib_clearScreen();
    snake->drawSnake();
    int x;
    int y;
    objPos temp;
    gameData->getFoodPos(temp,1);
    gameData->gameboard[temp.y][temp.x] = temp.symbol;

    for(y=0;y<gameData->getBoardSizeY();y++)       //Start from a y co-ordinate
    {
        for(x=0;x<gameData->getBoardSizeX();x++)       //Print character at each x-co-ordinate
        {
            MacUILib_printf("%c", gameData->gameboard[y][x]);
        }
        MacUILib_printf("\n"); 
    }
    MacUILib_printf("\n%c", dir);
   
    MacUILib_printf("Use the 'WASD' controls to move the * (player).\nW = up, A = left, S = down, D = right.\nRemember that you lose the game if you run into yourself!\n");
   
    snake->removeSnake();
    gameData->gameboard[temp.y][temp.x] = ' ';
    // If the game has been lost, display a message
    if(gameData->getLoseFlagStatus())
    {
        MacUILib_clearScreen();
        MacUILib_printf("You lost :(");
        MacUILib_Delay(999999);
    }  
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
    gameData->~GameMechs();
}
