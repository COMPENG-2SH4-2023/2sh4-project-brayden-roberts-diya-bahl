#include "objPosArrayList.h"

// Constructor for objPosArrayList class
objPosArrayList::objPosArrayList()
{
    sizeArray = 0;
    aList = new objPos[ARRAY_MAX_CAP]; // Allocate dynamic memory for the array with a maximum capacity
}

// Destructor for objPosArrayList class
objPosArrayList::~objPosArrayList()
{
    for(int i = 0; i < sizeArray; i++)
    {
        removeTail();
    }
}

// Get the current size of the array
int objPosArrayList::getSize()
{
    return sizeArray;
}

// Insert a new objPos at the head of the array
void objPosArrayList::insertHead(objPos thisPos)
{
    int i;

    for(i = sizeArray; i > 0; i--)
    {
        aList[i - 1].getObjPos(aList[i]);
    }

    thisPos.getObjPos(aList[0]);

    sizeArray++;
}

// Insert a new objPos at the tail of the array
void objPosArrayList::insertTail(objPos thisPos)
{
    thisPos.getObjPos(aList[sizeArray]);
    sizeArray++;
} 

// Remove the element at the head of the array
void objPosArrayList::removeHead()
{
    int i;

    for(i = 0; i < sizeArray - 1; i++)
    {
        aList[i + 1].getObjPos(aList[i]);
    }

    removeTail(); // Remove the tail to adjust the size
    
}

// Remove the element at the tail of the array
void objPosArrayList::removeTail()
{
    aList[sizeArray-1].setObjPos(0,0,0); // Set the tail element to a default objPos
    sizeArray--;
}

// Retrieve the objPos at the head of the array
void objPosArrayList::getHeadElement(objPos &returnPos)
{
    aList[0].getObjPos(returnPos);
}

// Retrieve the objPos at the tail of the array
void objPosArrayList::getTailElement(objPos &returnPos)
{
    aList[sizeArray-1].getObjPos(returnPos);
}

// Retrieve the objPos at a specific index in the array
void objPosArrayList::getElement(objPos &returnPos, int index)
{
    aList[index].getObjPos(returnPos);
}

