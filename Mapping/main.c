#include "map.h"
#include "LinkedListPaths.h"
#include "findShortestPath.h"


coordinate * getMap(){
    coordinate* map = NULL;
    int totalLines = getTotalLines();
    int* sensorArray = getSensorArrayFromText();
    coordinate* currentCoordinate = NULL;
    for(int i =0; i < totalLines; i++){
        //If at the very beginning.
        if(map == NULL){
            map = updateCoordinateToMap(map, initStartingCoordinate());
            updateCoordinatePaths(map,sensorArray[0]);
            getNextMove(map);
            currentCoordinate = map;
        }
        else{
            //get size of Map
            int lastPosition = getTotalCoordinatesInMap(map);

            //Replicate a coordinate like the previous map
            coordinate *nextCoordinate = malloc(sizeof(coordinate));
            replicateCoordinate(nextCoordinate,currentCoordinate);

            // Update current path
            updateCoordinatePaths(nextCoordinate , sensorArray[i]);

            // Update self orientation
            nextCoordinate -> selfOrientation = currentCoordinate -> nextOrientation;

            // Update Orientation
            getNextMove(nextCoordinate);


            // Assume car moed then Update where the current coordinate is
            updateXYCoordinate(currentCoordinate,nextCoordinate);
            // Update Unexplored Path for current path
            int pathRemain = updateUnexploredPath(currentCoordinate);
            //Add current coordinate to map if unexplored
            map = updateCoordinateToMap(map, *currentCoordinate);
            // Check if next coordinate has already been explored, -1 is not loop
            int isExplored = checkIfAlreadyInMap(map , *nextCoordinate);

            //if map explored. 
            if(isExplored != -1){
                printf("\n\n");
                coordinate * loopCoordinate = findCoordinateBasedOnXY(map, nextCoordinate->x , nextCoordinate->y);
                updateLoop(loopCoordinate,currentCoordinate);
                printf("Loop\n");
            }
            //Update previous Coordinate.
            currentCoordinate = nextCoordinate;
        }
    }
    return map;
}
int main(){
    coordinate* map = getMap();
    test(map);
    // printf("%d\n",orientationUpdatePath(1,0,1));
}
