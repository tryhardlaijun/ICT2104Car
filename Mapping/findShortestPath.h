#pragma once 

#include "map.h"
#include "LinkedListPaths.h"


int countAmountOfRightTurns(int origin , int compare);

int changePathsByOrientationRight(int num);

int orientationUpdatePath(int orientOrigin, int orientCompare, int origin, int isReversible);

int findNumberOf1Bits(int num);

coordinate* findShortestPathInMap(coordinate* map , coordinate start);

