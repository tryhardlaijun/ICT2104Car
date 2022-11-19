#pragma once 

#include<stdio.h>
#include<stdlib.h>

typedef struct coordinate
{
    //X coordiante of the car ( 4 btyes ) // highest +-127
    int x : 8;
    //Y coordiante of the car ( 4 btyes ) // highest +-127
    int y : 8;
    // 8 bit datatype. First 4 bit is pathavailables , last 4 bits is pathUnexplored.
    unsigned int paths : 8;
    // 1 = Last explored coordinate.
    unsigned int isLast : 1; // 1 bit
}coordinate; // 25 bits total.


coordinate initStartingCoordinate();

coordinate makeCoordinate(int x , int y, int paths, int isLast);

void printCoordinate(coordinate c);

void updateCoordinatePaths(coordinate* c , int path);

void updateCoordinateUnexploredPaths(coordinate* c , int path);

int checkIfCoordinateMatch(coordinate a, coordinate b);

void replicateCoordinate(coordinate* src , coordinate* dest);

void availToExploredPath(coordinate*c);

void resetUnexploredPath(coordinate*c);