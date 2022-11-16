#include "map.h"
#include "LinkedListPaths.h"
#include "findShortestPath.h"


coordinate * getMap(){
    coordinate* map = NULL;
    int totalLines = getTotalLines();
    int* sensorArray = getSensorArrayFromText();
    coordinate currentCoordinate = initStartingCoordinate();
    coordinate previousCoordinate = currentCoordinate;
    //Replicate a coordinate like the previous map
    coordinate *prevCoordinate = NULL;
    for(int i =0; i < totalLines; i++){
        //If at the very beginning.
        if(map == NULL){
            map = updateCoordinateToMap(map, initStartingCoordinate());
            updateCoordinatePaths(map, sensorArray[i]);
            replicateCoordinate(map,&currentCoordinate);
            // Update NEXT Orientation
            getNextMove(map);
            updateUnexploredPath(map);
            map->isReversible = 0;
            printCoordinate(*map);
        }
        else {
           // Update self orientation
            currentCoordinate.selfOrientation = currentCoordinate.nextOrientation;
            
            // Update current path
            updateCoordinatePaths(&currentCoordinate , sensorArray[i]);
            // Update NEXT Orientation
            getNextMove(&currentCoordinate);
            updateUnexploredPath(&currentCoordinate);
            // Assume car moved then Update where the current coordinate is
            updateXYCoordinate(&currentCoordinate);
            
            printCoordinate(currentCoordinate);
            // Check if next coordinate has already been explored, -1 is not loop
            int isExplored = checkIfAlreadyInMap(map , currentCoordinate);

            //if map explored. 
            if(isExplored != -1){
                printf("\n\n");
                coordinate * loopCoordinate = findCoordinateBasedOnXY(map, currentCoordinate.x , currentCoordinate.y);
                updateLoop(loopCoordinate,&previousCoordinate);
                printf("Loop\n");
            }
            else{
                //Add current coordinate to map if unexplored
                map = updateCoordinateToMap(map, currentCoordinate);
            }
            previousCoordinate = currentCoordinate;
        }
    }
    return map;
}
int main(){
    coordinate* map = getMap();
    printf("\n\n\n");
    printMap(map);
    findShortestPathInMap(map, map[0]);
    // int x = orientationUpdatePath(3,0,5);  
    // printf("%d\n",x);
    // printf("%d\n",orientationUpdatePath(1,0,1));
}
