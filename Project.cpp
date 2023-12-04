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

    pFood = new Food();
    myGM = new GameMechs(30, 15);

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

    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();   

    bool drawn; 
    objPos grid(0, 0, '#');
    objPosArrayList* playerBody = player->getPlayerPos();
    objPos temp;
    objPos playerPosition;
    objPos FoodPos;

    // Draw the top and bottom borders
    for (int y = 0; y < myGM->getBoardSizeY(); y++) {
        for (int x = 0; x < myGM->getBoardSizeX(); x++) {
            drawn = false;
            for (int i=0; i< playerBody->getSize(); i++){
                playerBody->getElement(temp, i);
                if(temp.x == x && temp.y == y){
                    grid.setObjPos(y, x, temp.symbol);
                    drawn = true;
                    break;
                }
            }
            if(!drawn){
                if (y == 0 || y == myGM->getBoardSizeY() - 1 || x == 0 || x == myGM->getBoardSizeX() - 1) {
                grid.setObjPos(y, x, '#');
                }
                else {
                        pFood->getFoodPos(FoodPos);
                        if (y == FoodPos.y && x == FoodPos.x) {
                            grid.setObjPos(y, x, '^');
                        }
                        else {
                            grid.setObjPos(y, x, ' ');
                        }
                }
            }
            grid.getObjPos(grid);
            MacUILib_printf("%c", grid.getSymbol());
        }
        MacUILib_printf("\n");
    }
    for(int i =0; i < playerBody->getSize(); i++){
        playerBody -> getElement(temp, i);
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
    
    MacUILib_uninit();
}