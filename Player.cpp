#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;

    playerPos.x = (*mainGameMechsRef).getBoardSizeX()/2;
    playerPos.y = (*mainGameMechsRef).getBoardSizeY()/2;
    playerPos.symbol = 'x';

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

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    playerPos.getObjPos(returnPos);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char move = (*mainGameMechsRef).getInput(); 

    switch (move)
    {
        case '\b':
            (*mainGameMechsRef).setExitTrue();
        
        case ' ':
            (*mainGameMechsRef).setExitTrue();
            break;
        
        case 'w':
            if(myDir != DOWN)
            {
                myDir = UP;
            }
            break;
        
        case 'd':
            if(myDir != LEFT)
            {
                myDir = RIGHT;
            }
        
        case 's':
            if(myDir != UP)
            {
                myDir = DOWN;
            }
        
        case 'a':
            if(myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;
    }       

    (*mainGameMechsRef).clearInput();
}

void Player::movePlayer()
{
    
    objPos previous;
    //get tail element here
    /////////
    
    // PPA3 Finite State Machine logic

    switch(myDir)
    {
        case UP:
            playerPos.y--;

            if(playerPos.y < 0)
            {
                playerPos.y = (*mainGameMechsRef).getBoardSizeY() -1;
            }
            
            break;

        case RIGHT:
            playerPos.x++;

            if(playerPos.x >= (*mainGameMechsRef).getBoardSizeX())
            {
                playerPos.x = 0;
            }

            break;

        case DOWN:
            playerPos.y++;

            if(playerPos.y >= (*mainGameMechsRef).getBoardSizeY())
            {
                playerPos.y = 0;
            }
            
            break;

        case LEFT:
            playerPos.x--;

            if(playerPos.x < 0)
            {
                playerPos.x = (*mainGameMechsRef).getBoardSizeX() - 1;
            }

            break;
    
    }

    
    //insert & remove tail here
    ////////

    verifyPlayer(previous);

    printSnake();


}


void Player::verifyPlayer(objPos previous)
{

    int i;

    for(i = 0; i < 5; i++)
    {
        (*mainGameMechsRef).getfoodpos(*verify, i);

        if(playerPos.isPosEqual(verify))
        {

            int j;
            if(verify->symbol == ':)')
            {
                for(j = 0; j < 3; j++)
                {
                    (*mainGameMechsRef).incrementScore();
                }

                growPlayer(previous);

            }

            else if(verify->symbol == ':(')
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
                (*mainGameMechsRef).incrementScore();
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

void Player::printSnake()
{
    int i;

    for( i = 0; i < (*mainGameMechsRef).getBoardSizeY(); i++)
    {
        list_p->getElement((*verify), i);
        (*mainGameMechsRef).gameboard[verify->y][verify->x]; ////
    }
}

int Player::getPlayerDir()
{
    return (int)myDir;
}

int Player::snakeLength()
{
    //return size via getSize
}








