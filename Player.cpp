#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerPosList = new objPosArrayList();

    objPos playerPos;

    playerPos.x = (*mainGameMechsRef).getBoardSizeX()/2;
    playerPos.y = (*mainGameMechsRef).getBoardSizeY()/2;
    playerPos.symbol = '*';

    playerPosList->insertHead(playerPos);

    verify->x = 0;
    verify->y = 0;
    verify->symbol = 0;

    //insert player head into list_p here
    /////////////

    myDir = STOP;

    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
    delete verify;
    verify = nullptr;

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
    //get tail element here
    /////////
    
    // PPA3 Finite State Machine logic

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

    if(checkSelfCollision(next.x, next.y))
    {
        mainGameMechsRef->setLoseTrue();
        mainGameMechsRef->setExitTrue();
    }

    if(checkFoodComsumption(next.x, next.y))
    {
        playerPosList->insertHead(next);
        mainGameMechsRef->generateFood(playerPosList);
        mainGameMechsRef->incrementScore(1);
    }
    else
    {
        playerPosList->insertHead(next);
        playerPosList->removeTail();
    }

}

bool Player::checkFoodComsumption(int nextX, int nextY)
{
    objPos food;
    mainGameMechsRef->getFoodPos(food, 0);
    if(food.x == nextX && food.y == nextY)
    {
        return true;
    }
    else
    {
       return false;
    }
}

bool Player::checkSelfCollision(int nextX, int nextY)
{
    int i;
    objPos playerSegment;
    for(i=1; i<playerPosList->getSize();i++)
    {
        playerPosList->getElement(playerSegment, i);
        if(playerSegment.x == nextX && playerSegment.y == nextY)
        {
            return true;
        }
    }
    return false;
}

/*
void Player::verifyPlayer(objPos previous)
{

    int i;

    for(i = 0; i < 5; i++)
    {
        (*mainGameMechsRef).getfoodpos(*verify, i);

        if(playerPos.isPosEqual(verify))
        {

            int j;
            if(verify->symbol == 'B')
            {
                for(j = 0; j < 3; j++)
                {
                    (*mainGameMechsRef).incrementScore(1);
                }

                growPlayer(previous);

            }

            else if(verify->symbol == 'S')
            {
                for(j = 0; j < 3; j++)
                {
                    (*mainGameMechsRef).subtractScore();
                }

                if((*mainGameMechsRef).getScore() < 0)
                {
                    (*mainGameMechsRef).setLoseTrue();
                }

                growPlayer(previous);
            }

            else if(verify->symbol == '-')
            {
                //remove tail here 
                ////////

                ///use get size via list_p here
                /////////
            }

            else 
            {
                (*mainGameMechsRef).incrementScore(1);
                growPlayer(previous);
            }


            //Regenerating Food

            (*mainGameMechsRef).generatefood(playerPos);
            break;

        }
    }


    // check if snake ate itself here
    /////////////////////////

}

void Player::growPlayer(objPos lastpos)
{
    /// insert tail into list_p here 
    /////////
}
*/
void Player::drawSnake()
{
    int i;
    objPos temp;
    for(i = 0; i < playerPosList->getSize(); i++)
    {
        playerPosList->getElement(temp, i);
        mainGameMechsRef->gameboard[temp.y][temp.x] = temp.symbol;
    }
}

void Player::removeSnake()
{
    objPos temp;
    int i;
    for(i = 0; i < playerPosList->getSize(); i++)
    {
        playerPosList->getElement(temp, i);
        mainGameMechsRef->gameboard[temp.y][temp.x] = ' ';
    }
}
/*
int Player::getPlayerDir()
{
    return (int)myDir;
}

int Player::snakeLength()
{
    //return size via getSize
}
*/
