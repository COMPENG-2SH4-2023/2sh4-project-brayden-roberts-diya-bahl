#include "GameMechs.h"

// Constructor for GameMechs class (default constructor)
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
    // Initialize other class variables
    input = 0;

    score = 0;

    exitFlag = false;
    loseFlag = false;

}
// Constructor for GameMechs class (parameterized constructor)
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

// Destructor for GameMechs class 
GameMechs::~GameMechs()
{
    for(int i = 0; i < boardSizeY; i++)
    {
        delete[] gameboard[i];
    }
    delete[] gameboard;

    delete this; 
}


// Get the status of the exit flag
bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}
// Get the input value
char GameMechs::getInput()
{
    return input;
}
// Get the size of the game board in the X direction
int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}
// Get the size of the game board in the Y direction
int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}
// Set the exit flag to true
void GameMechs::setExitTrue()
{
    exitFlag = true;
}
// Set the input value
void GameMechs::setInput(char this_input)
{
    input = this_input;
}
// Clear the input value
void GameMechs::clearInput()
{
    input = 0;
}
// Set the lose flag to true
void GameMechs::setLoseTrue()
{
    loseFlag = true;
}
// Get the status of the lose flag
bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}
// Get the current score
int GameMechs::getScore()
{
    return score;
}
// Increment the score by a specified value
void GameMechs::incrementScore(int val)
{
    score += val;
}
// Generate a new food position that is not occupied by the snake
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
        for(i = 0; i < blockoff->getSize();i++) // Check if the generated position conflicts with any part of the snake
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
// Retrieve the objPos of the food and store it in returnPos
void GameMechs::getFoodPos(objPos &returnPos, int index)
{
    foodPos.getObjPos(returnPos);
}




