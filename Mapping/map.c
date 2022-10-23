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

coordinate* replicateLastPosition(coordinate* map){
    //Get size of the map 
    int lastPosition = getTotalCoordinatesInMap(map);
    return &map[lastPosition];
}



int main(){
    coordinate* map = NULL;
    if(map == NULL){
        map = malloc(sizeof(coordinate));
        *map = initStartingCoordinate();
    }
    map = updateCoordinateToMap(map, makeCoordinate(1,4,2,3,2,1));
    map = updateCoordinateToMap(map, makeCoordinate(2,3,2,3,2,1));
    map = updateCoordinateToMap(map, makeCoordinate(3,2,2,4,2,1));
    map = updateCoordinateToMap(map, makeCoordinate(4,1,3,7,2,1));
    coordinate* last = replicateLastPosition(map);
    last->x = 11110;
    nextMove(last);
    nextMove(last);
    nextMove(last);
    printMap(map);
}