#include "GameMechs.h"

GameMechs::GameMechs() //constructor 1 (default bc nothing in brackets)
{
    //constructor needed: call an obj of this class, it does the f'n right away

    boardSizeX = 30;
    boardSizeY = 15;

    gameboard = new char*[boardSizeY];
    for(int i = 0; i<boardSizeY; i++)
    {
        gameboard[i] = new char[boardSizeX];
    }
    
    for(int i = 0; i<boardSizeY; i++)
    {
        for(int j = 0; j<boardSizeX; j++)
        {
            if(i==0 || i==boardSizeY-1 || j==0 || j==boardSizeX-1)       //if on edge
            {
                gameboard[i][j] = '#';  
            }
            else
            {
                gameboard[i][j] = ' ';
            }
        }
    }

    input = 0;

    score = 0;

    exitFlag = false;
    loseFlag = false;

}

GameMechs::GameMechs(int boardX, int boardY) //constructor 1 (if you put something in brackets it does this one)
{

    if (boardX < 10 )
    {
        boardSizeX = 30;
    }
    else 
    {
        boardSizeX = boardX;
    }

    if (boardY < 5 )
    {
        boardSizeY = 15;
    }
    else 
    {
        boardSizeY = boardY;
    }


    gameboard = new char*[boardSizeY];
    for(int i = 0; i<boardSizeY; i++)
    {
        gameboard[i] = new char[boardSizeX];
    }
    
    for(int i = 0; i<boardSizeY; i++)
    {
        for(int j = 0; j<boardSizeX; j++)
        {
            if(i==0 || i==boardSizeY-1 || j==0 || j==boardSizeX-1)       //if on edge
            {
                gameboard[i][j] = '#';  
            }
            else
            {
                gameboard[i][j] = ' ';
            }
            
        }
    }

    input = 0;

    score = 0;

    exitFlag = false;
    loseFlag = false;


}

// do you need a destructor? 
GameMechs::~GameMechs()
{
    for(int i = 0; i < boardSizeY; i++)
    {
        delete[] gameboard[i];
    }
    delete[] gameboard;

    delete this; 
}



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

void GameMechs::setLoseTrue()
{
    loseFlag = true;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore(int val)
{
    score += val;
}

void GameMechs::generateFood(objPosArrayList* blockoff)
{
    int i;
    objPos temp;
    bool snakeFlag;
    bool placeFlag = false;
    int posX;
    int posY;
    while (!placeFlag)
    {
        posY = (rand() % (boardSizeY-2))+1;
        posX = (rand() % (boardSizeX-2))+1;
        for(i = 0; i < blockoff->getSize();i++)
        {
            blockoff->getElement(temp, i);
            if(posX == temp.x && posY == temp.y)
            {
                snakeFlag = true;
            }
        }
        if(!snakeFlag)
        {
            foodPos.x = posX;
            foodPos.y = posY;
            foodPos.symbol = 'A';
            placeFlag = true;
        }
    }
    
}

void GameMechs::getFoodPos(objPos &returnPos, int index)
{
    foodPos.getObjPos(returnPos);
}




