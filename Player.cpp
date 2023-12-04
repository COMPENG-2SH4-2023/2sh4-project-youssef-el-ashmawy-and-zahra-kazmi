#include "Player.h"

Player::Player(GameMechs* thisGMRef, Food* foodPtr)
{ 
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2, '*');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
    FoodPtr = foodPtr;
    
}


Player::~Player()
{
    // delete any heap members here
    delete FoodPtr;
    delete playerPosList;
    
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
}

void Player::updatePlayerDir()
{ 
    // PPA3 input processing logic   
    switch (mainGameMechsRef->getInput()){
                case 'w':
            if (myDir != DOWN)
            {
                myDir = UP;
            }
            break;

        case 's':
            if (myDir != UP)
            {
                myDir = DOWN;
            }
            break;

        case 'a':
            if (myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;

        case 'd':
            if (myDir != LEFT )
            {
                myDir = RIGHT;
            }
            break;

        default:
            break;  
    } 
        
}

void Player::movePlayer()
{
    objPos first;
    playerPosList->getHeadElement(first);
    // PPA3 Finite State Machine logic
    switch(myDir){

        case LEFT:
            first.x--;
            break;

        case RIGHT:
            first.x++;
            break;

        case DOWN:
            first.y++;
            break;

        case UP:
            first.y--;
            break;

        default:
            break;
        }
        if (first.x < 1){
        first.x = mainGameMechsRef->getBoardSizeX() - 2;
        }
        else if (first.x >= mainGameMechsRef->getBoardSizeX()-1){
            first.x = 1;
        }

        if (first.y >= mainGameMechsRef->getBoardSizeY()-1) {
            first.y = 1;
        }
        else if (first.y < 1){
            first.y = mainGameMechsRef->getBoardSizeY() - 2;
        
        }

    
    objPos FoodPosition;
    FoodPtr->getFoodPos(FoodPosition);
    if (first.isPosEqual(&FoodPosition)) {
        playerPosList->insertHead(first);
        FoodPtr->generateFood(mainGameMechsRef, first);
    }
    else{
    playerPosList->insertHead(first);
    playerPosList-> removeTail();
    }
    int i;
    objPos playerTemp;

    for(int i = 1; i<playerPosList->getSize();i++){
        playerPosList->getElement(playerTemp, i);
        if(first.isPosEqual(&playerTemp)) {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
        }
    }
    

}