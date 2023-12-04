#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    arrList = new objPos[ARRAY_MAX_CAP];
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList()
{
    delete[] arrList;
}

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity){
        return;
    }
    for (int i =listSize; i>0;i--){
        arrList[i].setObjPos(arrList[i-1]);
    }
    arrList[0].setObjPos(thisPos);
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity){
        return;
    }
    arrList[listSize].setObjPos(thisPos);
    listSize++;
}

void objPosArrayList::removeHead()
{
    if (listSize > 0) {
        for (int i = 0; i < listSize - 1; i++) {
            arrList[i].setObjPos(arrList[i + 1]);
        }
        listSize--;
    }
}

void objPosArrayList::removeTail()
{
    if (listSize > 0) {
        arrList[listSize - 1].setObjPos(0, 0, 0);
        listSize--;
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(arrList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(arrList[listSize-1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{

    if(index >= 0 && index < listSize && listSize > 0){
        returnPos.x = arrList[index].x;
        returnPos.y = arrList[index].y;
        returnPos.symbol = arrList[index].symbol;
    }
}