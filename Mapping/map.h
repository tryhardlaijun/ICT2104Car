#pragma once 

#include "coordinate.h"
#include "movement.h"

coordinate* updateCoordinateToMap(coordinate* map, coordinate c);

int getTotalCoordinatesInMap(coordinate* map);

void printMap(coordinate* map);

coordinate replicateLastPosition(coordinate* map);

int checkIfAlreadyInMap(coordinate* map , coordinate c);

coordinate* initMap();

int isMapFullyExplored(coordinate* map);

coordinate getPreviousCoordinate(coordinate c);

//Return null is not found. Return address of the coordinate found.
coordinate* findCoordinateBasedOnXY(coordinate* map , int x , int y);

//Update information if loop happens.
int updateLoop(coordinate* mapCoordinate , coordinate* currentCoordinate);

//Copy map into another memory loc
coordinate* copyMap(coordinate* src);

void reset(coordinate** myPointer);