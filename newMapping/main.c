#include "coordinate.h"
#include "map.h"
#include "movement.h"
#include "car.h"
#include "generateMap.h"

int main()
{
    coordinate *map = NULL;
    coordinate start = initStartingCoordinate();
    car Car = {start, 0};
    int movement = 0;
    int sensorArray[] = {0b011, 0b001, 0b001, 0b010, 0b011,
                         0b011, 0b001, 0b010, 0b001, 0b001,
                         0b010, 0b001, 0b001, 0b001, 0b001};
    for (int i = 0; i < 15; i++)
    {
        coordinate *carC = &(Car.carCoordinate);
        int loopPosition = -1;
        if (map != NULL)
        {
            // Temp variable for carC
            coordinate tmp = *carC;
            // If code reach here means it has already reach the location.
            updateXYCoordinate(&tmp, movement);
            // -1 if not looped
            loopPosition = checkIfAlreadyInMap(map, tmp);
            if (loopPosition != -1)
            {
                printf("LOOPED\n");
                updateLoop(&map[loopPosition], carC);
            }
            *carC = tmp;
        }
        if (map != NULL && loopPosition != -1)
        {
        }
        else
        {
            int num1 = convertSensorDataToUnexploredPath(sensorArray[i], Car.orientation);
            int num2 = convertSensorDataToAvailPath(sensorArray[i], Car.orientation);
            // Update the sensor coordinate into the car.
            updateCoordinateAvailablePaths(carC, num1 + (num2 << 4));
            // Find out the next move.
            movement = getNextMove(carC);
            if (movement != Car.orientation)
            {
                Car.orientation = ChangeOrientation(Car.orientation, movement);
            }
            // Update the unexploredPath.
            updateUnexploredPath(carC, movement);
            // Update map.
            // Car moves Here
            /*

            */
            // Updae the XY coordinate.
            map = updateCoordinateToMap(map, *carC);
        }
        printCoordinate(*carC);
    }

    printf("\n");
    printMap(map);
    free(map);

    coordinate *testMap = getTestMap();
    printMap(testMap);
    generateMap(testMap);
    free(testMap);
}