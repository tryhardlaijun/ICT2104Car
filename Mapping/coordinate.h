#pragma once 

#include<stdio.h>
#include<stdlib.h>

typedef struct coordinate
{
    //X coordiante of the car ( 4 btyes )
    unsigned int x : 8;
    //Y coordiante of the car ( 4 btyes )
    unsigned int y : 8;
    // 3 bit datatype
    //Path available following relative to where the car is facing. 
    //E.g 101 -> Can turn left and right but cannot move forward ||  010 cannot turn but can move forward.
    unsigned int pathAvail : 3; // 3 Bits
    // 3 bit datatype
    // Same as path Avail but bit is remove once it is "Explored"
    unsigned int pathUnexplored : 3; // 3 Bits
    // 2 bit datatype
    //Orientaton of the car after its next move.(Absoulute)
    //Absolute meaning relative to where is starts rather than the car original orientation
    // 0 = same  as the origin || 1 = left of origin || 2 back of origin || 3 Left of origin
    unsigned int nextOrientation : 2; //2 Bits
    // 1 bit datatype
    // 1 = Last explored coordinate.
    unsigned int isLast : 1; // 1 bit
    
}coordinate;

coordinate initStartingCoordinate();

coordinate makeCoordinate(int x , int y, int pathAvail, int pathUnexplored, int nextOrientation, int isLast);

void printCoordinate(coordinate c);

void updateCoordinatePaths(coordinate* c , int path);