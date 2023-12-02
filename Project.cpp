#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* gameData;
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
    MacUILib_init();
    MacUILib_clearScreen();
    gameData = new GameMechs();

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
    char input = gameData->getInput();
    gameData->setInput(0);

    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            case 27:  // exit
                gameData->setExitTrue();
                break;

            // Add more key processing here
            case 'w':
                dir = 'w';
                // if(direction != DOWN)
                // {
                //     direction = UP;
                // }
                break;
            case 'a':
                cout << "Left";
                dir = 'a';
                // if(direction != RIGHT)
                // {
                //     direction = LEFT;
                // }
                break;
            case 's':
                dir = 's';
                cout << "Down";

                // if(direction != UP)
                // {
                //     direction = DOWN;
                // }
                break;
            case 'd':
                cout << "Right";
                dir = 'd';
                // if(direction != LEFT)
                // {
                //     direction = RIGHT;
                // }
                break;
            case '+':
                cout << "Faster";
                dir = '+';
                // if(speed<5)
                // {
                //     speed++;
                // }
                break;
            case '-':
                cout << "Slower";
                dir = '-';
                // if(speed>1)
                // {
                //     speed--;
                // }
                break;
            case 'l':
                gameData->setLoseFlag();
            // Add more key processing here
            // Add more key processing here    


            default:
                break;
        }
        input = 0;
    }

}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    MacUILib_clearScreen();
    int x;
    int y;
    for(y=0;y<10;y++)       //Start from a y co-ordinate
    {
        for(x=0;x<20;x++)       //Print character at each x-co-ordinate
        {
            if(y==0 || y==9 || x==0 || x==19)       //if on edge
            {
                MacUILib_printf("#");  
            }
            else
            {
                MacUILib_printf(" ");
            }
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

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
    gameData->deleteGameMechs(gameData);
}
