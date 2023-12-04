#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"  
#include "Player.h" 
#include "Food.h" 
#include "objPosArrayList.h"


using namespace std;

#define DELAY_CONST 100000

Player* player;
Food* pFood;
GameMechs* myGM;




void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{
    Initialize();

    while(!myGM->getExitFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs(30, 15);
    pFood = new Food();

    objPos playerPosition{-100,-100, '^'};
    player = new Player(myGM, pFood);
    pFood->generateFood(myGM, playerPosition);

}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    player->updatePlayerDir(); 
    player->movePlayer();
    myGM->clearInput();
    int i;

    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();   
    bool drawn; 
    objPos grid(0, 0, '#');
    objPosArrayList* playerBody = player->getPlayerPos();
    objPos tempBody;
    objPos playerPosition;
    objPos FoodPos;

    // Draw the top and bottom borders
    for (int i = 0; i < myGM->getBoardSizeY(); i++) {
        for (int j = 0; j < myGM->getBoardSizeX(); j++) {
            drawn = false;
            for (int k=0; k< playerBody->getSize(); k++){
                playerBody->getElement(tempBody, k);
                if(tempBody.x == j && tempBody.y == i){
                    grid.setObjPos(i, j, tempBody.symbol);
                    drawn = true;
                    break;
                }
            }
            if(!drawn){
                if (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1) {
                grid.setObjPos(i, j, '#');
                }
                else {
                        pFood->getFoodPos(FoodPos);
                        if (i == FoodPos.y && j == FoodPos.x) {
                            grid.setObjPos(i, j, '^');
                        }
                        else {
                            grid.setObjPos(i, j, ' ');
                        }
                }
            }
            grid.getObjPos(grid);
            MacUILib_printf("%c", grid.getSymbol());
        }
        MacUILib_printf("\n");
    }
    for(int x =0; x < playerBody->getSize(); x++){
        playerBody -> getElement(tempBody, x);
    }
    pFood->getFoodPos(FoodPos);
    MacUILib_printf("\nScore: %d", playerBody->getSize() - 1);
    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();  
    
    delete myGM;
    delete player;
    delete pFood;
    MacUILib_uninit();
}