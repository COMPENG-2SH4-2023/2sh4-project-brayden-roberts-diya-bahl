#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include <time.h>

using namespace std;

#define DELAY_CONST 100000

GameMechs* gameData;
Player* snake;
char dir = 0;


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
    srand(time(NULL));
    MacUILib_init();
    MacUILib_clearScreen();
    gameData = new GameMechs();
    snake = new Player(gameData);
    objPos temp;
    snake->getPlayerPos(temp);
    gameData->generateFood(temp);

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
{
    MacUILib_clearScreen();
    int x;
    int y;
    objPos temp;
    objPos temp2;
    snake->getPlayerPos(temp);
    gameData->getFoodPos(temp2, 1);
    gameData->gameboard[temp.y][temp.x] = temp.symbol;
    gameData->gameboard[temp2.y][temp2.x] = temp2.symbol;

    for(y=0;y<gameData->getBoardSizeY();y++)       //Start from a y co-ordinate
    {
        for(x=0;x<gameData->getBoardSizeX();x++)       //Print character at each x-co-ordinate
        {
            MacUILib_printf("%c", gameData->gameboard[y][x]);
        }
        MacUILib_printf("\n"); 
    }
    MacUILib_printf("\n%c", dir);
    if(gameData->getLoseFlagStatus() == false)
    {
        MacUILib_printf("You did not lose");
    }
    else
    {
        MacUILib_printf("You lose");
    }

    gameData->gameboard[temp.y][temp.x] = ' ';
    gameData->gameboard[temp2.y][temp2.x] = ' ';
    
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
