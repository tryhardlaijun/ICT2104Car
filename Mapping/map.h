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