#pragma once 

#include "coordinate.h"

enum movement{YPlus, XPlus, YMinus, XMinus};
enum turns{NORTH, EAST, SOUTH, WEST};

int updateUnexploredPath(coordinate* c, int bitPosition);

int turnNextOrientationRight(int nextOrientation);

int turnNextOrientationLeft(int nextOrientation);

int updateXYCoordinate(coordinate* currentCoordinate, int movedDirection);

int getNextMove(coordinate* c);

void exploreNewCoordinate(coordinate*c,int movement);

void motorMove(int input);