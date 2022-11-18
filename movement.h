#pragma once 

#include "coordinate.h"

enum movement{YPlus, XPlus, YMinus, XMinus};
enum turns{FORWARD, RIGHT, REVERSE, LEFT};

int updateUnexploredPath(coordinate* c, int bitPosition);

int turnNextOrientationRight(int nextOrientation);

int turnNextOrientationLeft(int nextOrientation);

int updateXYCoordinate(coordinate* currentCoordinate, int movedDirection);

int getNextMove(coordinate* c);

void exploreNewCoordinate(coordinate*c,int movement);