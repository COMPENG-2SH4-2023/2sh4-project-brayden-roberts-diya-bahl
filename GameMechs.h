#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input; //attributes tend to be private
        bool exitFlag;
        
        bool loseFlag;
        int score;
        
        int boardSizeX;
        int boardSizeY;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs();

        bool getExitFlagStatus();
        void setExitTrue();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();

        void setLoseTrue();
        bool getLoseFlagStatus();

        int getScore();
        void incrementScore(int val);
        void subtractScore();

        void generatefood(objPos blockoff); //blockoff = a position, so that when it generates food, it doesn't put it in that blockoff position
        //blockoff = placeholder for the position where the player currently is
        void getfoodpos(objPos &returnPos, int index); //finding where an element from the index is on the gameboard & storing the address of that in returnPos

        char **gameboard;

};

#endif