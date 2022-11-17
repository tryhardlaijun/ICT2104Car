#include "map.h"
#include "LinkedListPaths.h"
#include "findShortestPath.h"
#include "printMap.h"

    // coordinate currentCoordinate = initStartingCoordinate();
    // coordinate previousCoordinate = currentCoordinate;
void readPath(coordinate* shortestPath){
    
    int lastPosition = getTotalCoordinatesInMap(shortestPath);
    printf("Shift to orientation %d \n", shortestPath[0].selfOrientation);
    for(int i = 0; i < lastPosition-1; i++){
        int curr = shortestPath[i].selfOrientation;
        int next = shortestPath[i+1].selfOrientation;
        while(curr != next){
            curr = readShortestPath(curr, next);
        }
        printf("Go forward\n");
    }
}

coordinate* getShortestPath(coordinate*  map,coordinate* currentCoordinate){
        coordinate * shortTestPath = findShortestPathInMap(map, *currentCoordinate);
        printf("\n\n\n");
        printMap(shortTestPath);
        readPath(shortTestPath);

    return shortTestPath;
}

    int shortestPathFoundFlag = 0;
coordinate * exploreMap (coordinate* map, int sensedData, coordinate * currentCoordinate , coordinate * previousCoordinate, int* isLoopOrDeadEnd){
    //Replicate a coordinate like the previous map
    if(map == NULL){
        map = updateCoordinateToMap(map, initStartingCoordinate());
        updateCoordinatePaths(map,sensedData);
        replicateCoordinate(map,currentCoordinate);
        // Update NEXT Orientation
        getNextMove(map);
        updateUnexploredPath(map);
        map->isReversible = 0;
        printCoordinate(*map);
    }
    else {
        //Update path completed.
        coordinate * previous = findCoordinateBasedOnXY(map, currentCoordinate->x , currentCoordinate->y);
        updateUnexploredPath(previous);

        if (shortestPathFoundFlag == 1) {
            previous = previousCoordinate;
        }
        shortestPathFoundFlag = 0;
        // Assume car moved then Update where the current coordinate is
        updateXYCoordinate(currentCoordinate);
        // Update current path
        updateCoordinatePaths(currentCoordinate , sensedData);
        // Update NEXT Orientation
        getNextMove(currentCoordinate);
        // Check if next coordinate has already been explored, -1 is not loop
        int isExplored = checkIfAlreadyInMap(map , *currentCoordinate);
        //if map explored. 
        if(isExplored != -1 || currentCoordinate->pathAvail == 0){
            coordinate *inputCoordinate = NULL;
            if(isExplored != -1){
                printf("\n\n");
                coordinate * loopCoordinate = findCoordinateBasedOnXY(map, currentCoordinate->x , currentCoordinate->y);
                updateLoop(loopCoordinate,previousCoordinate);
                inputCoordinate = loopCoordinate;
                printf("Loop\n");
                map = updateCoordinateToMap(map, *inputCoordinate);
            }
            else{
                printf("DeadEnd\n");
            }
            int isFullyExplored = isMapFullyExplored(map);
            if(isFullyExplored != -1 &&  isFullyExplored != -2){
                coordinate * shortestPath = getShortestPath(map,inputCoordinate);
                *currentCoordinate = (replicateLastPosition(shortestPath));
                getNextMove(currentCoordinate);
                currentCoordinate->selfOrientation = currentCoordinate->nextOrientation;
                // coordinate * tmp = findCoordinateBasedOnXY(map, currentCoordinate->x,currentCoordinate -> y);
                // zaf - findCoordinateBasedOnXY returns coordinate from original map, when path updates, it changes the original too and printing wouldn't work
                coordinate *copiedMap = copyMap(map);
                coordinate * tmp = findCoordinateBasedOnXY(copiedMap, currentCoordinate->x,currentCoordinate -> y);
                currentCoordinate->isLast = 0;
                shortestPathFoundFlag = 1;
                *tmp = *currentCoordinate;
                tmp->isLast = 0;
                // updateXYCoordinate(currentCoordinate);
                // map = updateCoordinateToMap(map, *currentCoordinate);
                free(shortestPath);
            }else{
                map = updateCoordinateToMap(map, *currentCoordinate);
            }

        }
        else{
            //Add current coordinate to map if unexplored
            map = updateCoordinateToMap(map, *currentCoordinate);
        }
        // Update self orientation
        currentCoordinate->selfOrientation = currentCoordinate->nextOrientation;
        printCoordinate(*currentCoordinate);
        *previousCoordinate = *currentCoordinate;
    }
    return map;
}

coordinate * getMap(){
    coordinate* map = NULL;
    int totalLines = getTotalLines();
    int* sensorArray = getSensorArrayFromText();
    int isTheEnd = 0;
    coordinate currentCoordinate = initStartingCoordinate();
    coordinate previousCoordinate = initStartingCoordinate();
    //Replicate a coordinate like the previous map
    for(int i =0; i < totalLines; i++){
        //If at the very beginning.
       map = exploreMap(map,sensorArray[i],&currentCoordinate, &previousCoordinate, &isTheEnd);
    }
    free(sensorArray);
    return map;
}

int main(){
    coordinate* map = getMap();
    printf("\n\n\n");
    printMap(map);
    generateMap(map);
    reset(&map);
    // int x = orientationUpdatePath(3,0,5);  
    // printf("%d\n",x);
    // printf("%d\n",orientationUpdatePath(1,0,1));
}

