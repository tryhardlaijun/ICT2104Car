#pragma once 

#include "map.h"
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

// 1 true, 0 false
int checkIfCoordinateMatch(coordinate a, coordinate b);


//Update information if loop happens.
int updateLoop(coordinate* mapCoordinate , coordinate* previousCoordinate);