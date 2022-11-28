#pragma once 

#include "coordinate.h"
#include "map.h"
#include "movement.h"

typedef struct car
{
    coordinate carCoordinate;
    int orientation : 4;
    
}car; // 25 bits total.

int turnNextOrientationRight(int nextOrientation);

int turnNextOrientationLeft(int nextOrientation);

int convertSensorDataToUnexploredPath(int num, int orientation);

int convertSensorDataToAvailPath(int num, int orientation);

int ChangeOrientation(int orientCar, int orientMovement);

void moveCarAccordingToPath(coordinate* map, car* Car);

void modifyOrientation(car* Car);