#include "Player.h"

// Constructor for the Player class
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerPosList = new objPosArrayList();

    objPos playerPos;

    playerPos.x = (*mainGameMechsRef).getBoardSizeX()/2;
    playerPos.y = (*mainGameMechsRef).getBoardSizeY()/2;
    playerPos.symbol = '*';

    playerPosList->insertHead(playerPos);
   

    myDir = STOP;

}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPosArrayList &returnPosArrayList)
{
    // return the reference to the playerPos arrray list
    int i;
    objPos temp;
    for(i = 0; i < playerPosList->getSize(); i++)
    {
        playerPosList->getElement(temp, i);
        returnPosArrayList.insertTail(temp);
    }
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char move = (*mainGameMechsRef).getInput();
    mainGameMechsRef->clearInput();

    //setting keyboard inputs to directions 

    switch (move)
    {
        case '\b':
            (*mainGameMechsRef).setExitTrue();
        
        case ' ':
            (*mainGameMechsRef).setExitTrue();
            break;
        
        case 'w':
        case 'W':
            if(myDir != DOWN)
            {
                myDir = UP;
            }
            break;
        
        case 'd':
        case 'D':
            if(myDir != LEFT)
            {
                myDir = RIGHT;
            }
            break;
        
        case 's':
        case 'S':
            if(myDir != UP)
            {
                myDir = DOWN;
            }
            break;
        
        case 'a':
        case 'A':
            if(myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;
    }       
}

void Player::movePlayer()
{
    objPos previous;
    playerPosList->getHeadElement(previous);
    objPos next;
    next = previous;
    
    // PPA3 Finite State Machine logic

    //setting wrap around conditions

    switch(myDir)
    {
        case UP:
            next.y = previous.y - 1;
            if(next.y == 0)
            {
                next.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            
            break;

        case RIGHT:
            next.x = previous.x + 1;
            if(next.x == mainGameMechsRef->getBoardSizeX() - 1)
            {
                next.x = 1;
            }

            break;

        case DOWN:
            next.y = previous.y + 1;
            if(next.y == mainGameMechsRef->getBoardSizeY() - 1)
            {
                next.y = 1;
            }

            break;

        case LEFT:
            next.x = previous.x - 1;
            if(next.x == 0)
            {
                next.x = mainGameMechsRef->getBoardSizeX() - 2;
            }

            break;
        default:
            break;
    }

    // Check if the snake has collided with itself at the next position

    if(checkSelfCollision(next.x, next.y))
    {
        // If self-collision is detected:

        mainGameMechsRef->setLoseTrue(); // Set the game state to indicate that the player has lost
        mainGameMechsRef->setExitTrue(); // Set the game state to indicate that the game should exit
    }

    // Check if the snake is consuming food at the next position

    if(checkFoodComsumption(next.x, next.y))
    {
        // If food consumption is detected:

        playerPosList->insertHead(next); // Add the next position to the front of the snake's position list
        mainGameMechsRef->generateFood(playerPosList); // Generate a new food position and update the game board
        mainGameMechsRef->incrementScore(1);
    }
    else
    {
        // If no food consumption is detected:

        playerPosList->insertHead(next); // Add the next position to the front of the snake's position list
        playerPosList->removeTail(); // Remove the tail position to maintain the snake's length
    }

}

// Function to check if the snake consumes food at the specified position

bool Player::checkFoodComsumption(int nextX, int nextY)
{
    objPos food;
    mainGameMechsRef->getFoodPos(food, 0);
    if(food.x == nextX && food.y == nextY) // Check if the next position matches the position of the food
    {
        return true;
    }
    else
    {
       return false;
    }
}

// Function to check for self-collision of the snake

bool Player::checkSelfCollision(int nextX, int nextY)
{
    int i;
    objPos playerSegment;
    for(i=1; i<playerPosList->getSize();i++)
    {
        playerPosList->getElement(playerSegment, i);
        if(playerSegment.x == nextX && playerSegment.y == nextY) // Check if the next position matches the position of any segment of the snake
        {
            return true;
        }
    }
    return false;
}

// Function to draw the snake on the game board
void Player::drawSnake()
{
    int i;
    objPos temp;
    for(i = 0; i < playerPosList->getSize(); i++)
    {
        playerPosList->getElement(temp, i);
        mainGameMechsRef->gameboard[temp.y][temp.x] = temp.symbol; // Set the corresponding symbol on the game board to represent the snake
    }
}

// Function to remove the snake from the game board
void Player::removeSnake()
{
    objPos temp;
    int i;
    for(i = 0; i < playerPosList->getSize(); i++)
    {
        playerPosList->getElement(temp, i);
        mainGameMechsRef->gameboard[temp.y][temp.x] = ' '; // Set the corresponding symbol on the game board to an empty space, removing the snake
    }
}
