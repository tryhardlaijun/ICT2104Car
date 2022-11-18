#include "coordinate.h"

typedef struct car
{
    coordinate carCoordinate;
    int orientation : 4;
    
}car; // 25 bits total.

int convertSensorDataToAvailPath(int num, int orientation);

int convertSensorDataToUnexploredPath(int num, int orientation);

int turnNextOrientationLeft(int nextOrientation);

int turnNextOrientationRight(int nextOrientation);

int ChangeOrientation(int orientCar, int orientMovement);