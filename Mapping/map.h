#pragma once 

#include<stdio.h>
#include<stdlib.h>
#include "coordinate.h"
#define MAX 1000


coordinate* updateCoordinateToMap(coordinate* Map, coordinate c);

int getTotalCoordinatesInMap(coordinate* Map);

void printMap(coordinate* Map);

coordinate replicateLastPosition(coordinate* Map);