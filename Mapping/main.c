#include "map.h"
#include "printMap.h"

coordinate *getMap()
{
    coordinate *map = NULL;
    int totalLines = getTotalLines();
    int *sensorArray = getSensorArrayFromText();
    coordinate *previousCoordinate = NULL;
    for (int i = 0; i < totalLines; i++)
    {
        // If at the very beginning.
        if (map == NULL)
        {
            map = updateCoordinateToMap(map, initStartingCoordinate());
            updateCoordinatePaths(map, sensorArray[0]);
            getNextMove(map);
            previousCoordinate = map;
        }
        else
        {
            // get size of Map
            int lastPosition = getTotalCoordinatesInMap(map);

            // Replicate a coordinate like the previous map
            coordinate *currentCoordinate = malloc(sizeof(coordinate));
            replicateCoordinate(currentCoordinate, previousCoordinate);

            // Update current path
            updateCoordinatePaths(currentCoordinate, sensorArray[i]);

            // Update Orientation
            getNextMove(currentCoordinate);

            // Update self orientation
            currentCoordinate->selfOrientation = previousCoordinate->nextOrientation;

            // Assume car moed then Update where the current coordinate is
            updateXYCoordinate(previousCoordinate, currentCoordinate);

            // Update Unexplored Path for current path
            int pathRemain = updateUnexploredPath(previousCoordinate);

            // Check if next coordinate has already been explored
            int isExplored = checkIfAlreadyInMap(map, *currentCoordinate);

            // Check if map has been explored, -1 is not loop
            if (isExplored == -1)
            {
                // Unexplored
                // Add current coordinate to map if unexplored
                map = updateCoordinateToMap(map, *currentCoordinate);
            }
            else
            {
                printf("\n\n");
                coordinate *loopCoordinate = findCoordinateBasedOnXY(map, currentCoordinate->x, currentCoordinate->y);
                printCoordinate(*loopCoordinate);
                printCoordinate(*previousCoordinate);
                updateLoop(loopCoordinate, previousCoordinate);
                printf("Loop\n");
            }
            // Update previous Coordinate.
            previousCoordinate = currentCoordinate;
        }
    }
    return map;
}

int main()
{
    coordinate *map = getMap();
    printMap(map);
    generateMap(map);
    if (isMapFullyExplored(map) != -1)
    {
        int lastPosition = getTotalCoordinatesInMap(map);
        // coordinate z = getPreviousCoordinate();
        // printf("\n\n");
        // printCoordinate(map[lastPosition]);
    }
    else
    {
        printf("Complete");
    }
}