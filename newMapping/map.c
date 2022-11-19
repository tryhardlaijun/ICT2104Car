#include "map.h"

coordinate* updateCoordinateToMap(coordinate* map, coordinate c){
    int lastPosition = 0;
    //map[lastPosition] -> Last explored
    if(map == NULL){
        lastPosition = 0;
    }
    else
        lastPosition = getTotalCoordinatesInMap(map);
    //+1 -> Starting from 0 then +1 again -> extra space for new coordinate
    //Realloc would copy all the current data into a new space with extra space
    //then free the previous memory used, 
    //unless the current address is being used.
    coordinate* temp = realloc(map,sizeof(coordinate)*(lastPosition+1));
    // NULL means computer not enough space to reallocate
    if(temp == NULL){
        free(map);
        return NULL;
    }
    else{
        map = temp;
    }
    if(lastPosition >= 1){
        //Ensure previous Explored Coordinate is no longer labelled last
        map[lastPosition-1].isLast = 0;
    }
    //Update new coordinate to newly create space
    map[lastPosition] = c;
    //Ensure last memory isLast bit is 1
    map[lastPosition].isLast = 1;

    return map;
}

//Find last explore coordinate by looking coordinate with isLast bit = 1
int getTotalCoordinatesInMap(coordinate* map){
    if(map == NULL){
        printf("Map Not Init Yet.");
        return -1;
    }
    //Assume max amount of coordinate is 1000
    for(int i = 0; i < MAX; i++){
        //If last bit is true then return number
        if(map[i].isLast == 1){
            return i+1;
        }
    }
    printf("EXCEED Size 1000 \n");
    //Return -1 signal error.
    return -1;
}

//Return -1 is fully clear , >0 if not a cleared and -2 if over 100 coordinates.
int isMapFullyExplored(coordinate* map){
    //Assume max amount of coordinate is 1000
    for(int i = 0; i < MAX; i++){
        //If last bit is true then return number
        if ((map[i].paths & 15) != 0){
            return i;
        }
        else if(map[i].isLast == 1){
            return -1;
        }
    }
    printf("EXCEED Size 100 \n");
    //Return -1 signal error.
    return -2;
}

// Return Coordinate of the map. Return NULL if not in map.
coordinate* findCoordinateBasedOnXY(coordinate * map ,int x , int y){
    int lastPosition = getTotalCoordinatesInMap(map);
    for (int i = 0; i < lastPosition; i++){
        if(map[i].x == x && map[i].y == y)
            return &map[i];
    }
    return NULL;
}

//Print all coordinate info from the map
void printMap(coordinate* map){
    if (map == NULL)
        return;
    int count = getTotalCoordinatesInMap(map);
    for(int i = 0; i < count; i++){
       printCoordinate(map[i]);
    }
}

//Return a copy of the coordinate at the end of the map
coordinate replicateLastPosition(coordinate* map){
    //Get size of the map 
    int lastPosition = getTotalCoordinatesInMap(map);
    return map[lastPosition-1];
}

// Check if coordinate is already in map
int checkIfAlreadyInMap(coordinate* map , coordinate c){
    if(map == NULL){
        return -1;
    }
    int totalCoordinate = getTotalCoordinatesInMap(map);
    //Check if loop
    for(int i = 0; i < totalCoordinate; i++){
        if(c.x == map[i].x && c.y == map[i].y){
            return i;
        }
    }
    return -1;
}


int getOrientationFromTwoCoordinate(coordinate* mapCoordinate , coordinate* prevCoordinate){
    int xDifference = prevCoordinate->x -  mapCoordinate->x;
    int yDifference = prevCoordinate->y -  mapCoordinate->y;
    if(xDifference == 1 && yDifference == 0){
        return 1;
    }
    else if (xDifference == -1 && yDifference == 0){
        return 3;
    }
    else if (xDifference == 0 && yDifference == 1){
        return 0;
    }
    else if (xDifference == 0 && yDifference == -1){
        return 2;
    }
}
//Check if loop is in pathUnexplored. Return 1 for successfully uopdate, 0 for nothing updated.
int updateLoop(coordinate* mapCoordinate , coordinate* prevCoordinate){
    int inverseBit = getOrientationFromTwoCoordinate(mapCoordinate,prevCoordinate);
    mapCoordinate->paths &= ~(1 << inverseBit);
    return 1;
}

// Make copy of map.
coordinate* copyMap(coordinate* src){
    int lastPosition = getTotalCoordinatesInMap(src);
    coordinate* des = malloc(sizeof(coordinate)*(lastPosition+1));
    for(int i = 0; i < lastPosition; i++){
        des[i] = src[i];
    }
    return des;
}

//Free all map memory.
 void reset(coordinate** myPointer) {
     if (myPointer) {
         free(*myPointer);
         *myPointer = NULL;
     }
 }
