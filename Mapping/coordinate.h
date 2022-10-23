#pragma once 

#include<stdio.h>
#include<stdlib.h>

typedef struct coordinate
{
    //X coordiante of the car
    unsigned int x;
    //Y coordiante of the car
    unsigned int y;
    // 3 bit datatype
    //Path available following by the bit orientation. 
    //E.g 101 -> Can turn left and right but cannot move forward ||  010 cannot turn but can move forward.
    unsigned int pathAvail : 3;
    // 3 bit datatype
    // Same as path Avail but bit is remove once it is "Explored"
    unsigned int pathUnexplored : 3;
    // 2 bit datatype
    //Orientaton of the car, relative to where is starts.
    // 0 = same orientation as the origin || 1 = left of origin || 2 back of origin || 3 Left of origin
    unsigned int orientation : 2;
    // 1 bit datatype
    // 1 = Last explored coordinate.
    unsigned int isLast : 1;
}coordinate;

coordinate initStartingCoordinate();

coordinate makeCoordinate(int x , int y, int pathAvail, int pathUnexplored, int orientation, int isLast);

