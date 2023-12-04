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
        char input;
        bool exitFlag;
        bool loseflag;
        int score;

        int boardSizeX;
        int boardSizeY;

    public:

        // constructor
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); // destructor


        // Getter and Setter for Exit Flag
        bool getExitFlagStatus();
        void setExitTrue();

        // Getter and Setter for Lose Flag
        bool getLoseFlagStatus();
        void setLoseFlag();

        // Getter and Setter for Input
        char getInput();
        void setInput(char this_input);
        void clearInput();

        // Getter methods for Board Size
        int getBoardSizeX();
        int getBoardSizeY();

        // Getter and Setter for Score
        int getScore();
        void incrementScore(); // assume this increases by 1 for now but later might change
};

#endif