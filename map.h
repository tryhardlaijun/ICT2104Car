#pragma once 
#include "coordinate.h"
#define MAX 100


coordinate* updateCoordinateToMap(coordinate* map, coordinate c);

int getTotalCoordinatesInMap(coordinate* map);

int isMapFullyExplored(coordinate* map);

coordinate* findCoordinateBasedOnXY(coordinate * map ,int x , int y);

void printMap(coordinate* map);

coordinate replicateLastPosition(coordinate* map);

int checkIfAlreadyInMap(coordinate* map , coordinate c);

int updateLoop(coordinate* mapCoordinate , coordinate* prevCoordinate);

coordinate* copyMap(coordinate* src);

void reset(coordinate** myPointer);

void updateCoordinatePaths(coordinate *c, int path);