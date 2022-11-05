#include "map.h"


int main(){
    coordinate* map = NULL;
    coordinate* unexploredCoordinates = NULL;
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
            //Check if map has been explored
            if(isExplored == -1){
                // Unexplored
                //Naomi's Code to go to the unexplored spot
                //Add current coordinate to map if unexplored
                map = updateCoordinateToMap(map, c);                
            }
        }
    }
    printMap(map);
    printMap(unexploredCoordinates);

}