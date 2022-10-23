#include "map.h"
#include "movement.h"
coordinate* updateCoordinateToMap(coordinate* map, coordinate c){
    //map[lastPosition] -> Last explored
    int lastPosition = getTotalCoordinatesInMap(map);
    //+1 -> Starting from 0 then +1 again -> extra space for new coordinate
    //Realloc would copy all the current data into a new space with extra space
    //then free the previous memory used, 
    //unless the current address is being used.
    coordinate* temp = realloc(map,sizeof(coordinate)*(lastPosition+1+1));
    // NULL means computer not enough space to reallocate
    if(temp == NULL){
        free(map);
        return NULL;
    }
    else{
        map = temp;
    }
    //Ensure previous Explored Coordinate is no longer labelled last
    map[lastPosition].isLast = 0;
    //Update new coordinate to newly create space
    map[lastPosition+1] = c;
    //Ensure last memory isLast bit is 1
    map[lastPosition+1].isLast = 1;

    return map;
}

//Find last explore coordinate by looking coordinate with isLast bit = 1
int getTotalCoordinatesInMap(coordinate* map){
    //Assume max amount of coordinate is 1000
    for(int i = 0; i < MAX; i++){
        //If last bit is true then return number
        if(map[i].isLast == 1){
            return i;
        }
    }
    printf("EXCEED Size 1000 \n");
    //Return -1 signal error.
    return -1;
}

void printMap(coordinate* map){
    int count = getTotalCoordinatesInMap(map);
    for(int i = 0; i < count+1; i++){
       printCoordinate(map[i]);
    }
}

coordinate replicateLastPosition(coordinate* map){
    //Get size of the map 
    int lastPosition = getTotalCoordinatesInMap(map);
    return map[lastPosition];
}

int checkIfLoop(coordinate* map , coordinate c){
    int totalCoordinate = getTotalCoordinatesInMap(map);
    for(int i = 0; i < totalCoordinate; i++){
        if(c.x == map[i].x && c.y == map[i].y){
            return i;
        }
    }
    return -1;
}


int main(){
    coordinate* map = NULL;
    int * extraPlaceArray = NULL;
    int totalLines = getTotalLines();
    int* sensorArray = getSensorArrayFromText();
    for(int i =0; i < totalLines; i++){
        //If at the very beginning.
        if(map == NULL){
            map = malloc(sizeof(coordinate));
            *map = initStartingCoordinate();
            updateCoordinatePaths(map,sensorArray[0]);
            getnextMove(map);
        }
        else{
            //Replicate a coordinate like the previous map
            coordinate c = replicateLastPosition(map);
            // Update current path
            updateCoordinatePaths(&c , sensorArray[i]);
            // Update Orientation
            getnextMove(&c);
            // Update where the current coordinate is
            updateXYCoordinate(&map[i-1],&c);
            // Update Unexplored Path for current path
            int pathRemain = updateUnexploredPath(&map[i-1]);
            //Add current coordinate to map
            map = updateCoordinateToMap(map, c);
            // Check if next coordinate cause a loop or is coordinate deadend.
            if(checkIfLoop(map,c) != -1 ||  !c.pathUnexplored){
                printf("THERE IS LOOP HERE OR DEADEND (REVERSE)\n");
                // INSERT NAOMI'S CODE
            }
            

        }
    }
    printMap(map);

}