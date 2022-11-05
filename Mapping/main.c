#include "map.h"
coordinate * getMap(){
    coordinate* map = NULL;
    int totalLines = getTotalLines();
    int* sensorArray = getSensorArrayFromText();
    for(int i =0; i < totalLines; i++){
        //If at the very beginning.
        if(map == NULL){
            map = updateCoordinateToMap(map, initStartingCoordinate());
            updateCoordinatePaths(map,sensorArray[0]);
            getnextMove(map);
        }
        else{
            //get size of Map
            int lastPosition = getTotalCoordinatesInMap(map);
            //Replicate a coordinate like the previous map
            coordinate c = replicateLastPosition(map);
            // Update current path
            updateCoordinatePaths(&c , sensorArray[i]);
            // Update Orientation
            getnextMove(&c);
            // Update where the current coordinate is
            updateXYCoordinate(&map[lastPosition],&c);
            // Update Unexplored Path for current path
            int pathRemain = updateUnexploredPath(&map[lastPosition]);
            // Check if next coordinate has already been explored
            int isExplored = checkIfAlreadyInMap(map , c);
            //Check if map has been explored, -1 is not loop
            if(isExplored == -1){
                // Unexplored
                //Add current coordinate to map if unexplored
                map = updateCoordinateToMap(map, c);                
            }
            else{
                printCoordinate(map[isExplored]);
                printCoordinate(c);
                printf("Loop\n");
            }
        }
    }
    return map;
}



int main(){
    coordinate * map = getMap();
    printMap(map);
    if(isMapFullyExplored(map) != -1){
        int lastPosition = getTotalCoordinatesInMap(map);
        // printf("\n\n");
        // printCoordinate(map[lastPosition]);
    }
    else{
        printf("Complete");
    }
    
}