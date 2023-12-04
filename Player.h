#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.
    
    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {STOP, UP, DOWN, LEFT, RIGHT};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        void getPlayerPos(objPosArrayList &returnPosArrayList); // Upgrade this in iteration 3.
        int getPlayerDir();
        void updatePlayerDir();
        void movePlayer(); //these are all methods; functions for the class
        void growPlayer(objPos lastpos);  
        void verifyPlayer(objPos previous); 
        void drawSnake();
        void removeSnake();
        int snakeLength(); 

    private:
        objPosArrayList* playerPosList;   // Upgrade this in iteration 3.       
        enum Dir myDir; //myDir is an attribute (variable)

        objPos* verify = new objPos;
    //   objPosArrayList* list_p = new objPosArrayList;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif