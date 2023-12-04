#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    exitFlag = false;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    exitFlag = false; 
    boardSizeX = boardX; 
    boardSizeY = boardY;
}

// do you need a destructor?
GameMechs::~GameMechs()
{
//     Perform cleanup if needed
}


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar())
    {
        char input = MacUILib_getChar();
        setInput(input);

        if(input == 27) 
        {
            setExitTrue();
        }

    }

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


bool GameMechs::getLoseFlagStatus()
{
    return loseflag;
}

void GameMechs::setLoseFlag()
{
    loseflag = true;
}
