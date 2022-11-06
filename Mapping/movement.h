#pragma once 

#include "movement.h"
#include "file.h"
#include "coordinate.h"


int updateUnexploredPath(coordinate* c);

int turnNextOrientationRight(int nextOrientation);

int turnNextOrientationLeft(int nextOrientation);

//To Delete
// int getAbsoluteMovement(int coordinateOrientation , int nextMove);

int updateXYCoordinate(coordinate* previousCoordinate, coordinate* currentCoordinate);

int getNextMove(coordinate* c);

