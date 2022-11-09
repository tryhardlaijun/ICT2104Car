#include "map.h"
#include "movement.h"
#include <string.h>

coordinate* updateCoordinateToMap(coordinate* map, coordinate c){
    int lastPosition = 0;
    //map[lastPosition] -> Last explored
    if(map == NULL){
        lastPosition = -1;
    }
    else
    lastPosition = getTotalCoordinatesInMap(map);
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
    if(lastPosition >= 0){
        //Ensure previous Explored Coordinate is no longer labelled last
        map[lastPosition].isLast = 0;
    }
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
int isMapFullyExplored(coordinate* map){
    //Assume max amount of coordinate is 1000
    for(int i = 0; i < MAX; i++){
        //If last bit is true then return number
        if (map[i].pathUnexplored != 0){
            return i;
        }
        else if(map[i].isLast == 1){
            return 0;
        }
    }
    printf("EXCEED Size 1000 \n");
    //Return -1 signal error.
    return -1;
}

coordinate getPreviousCoordinate(coordinate c){
    if(c.y == 0 && c.x == 0){
        printf("Starting Point");
        return c;
    }
    coordinate previousCoordinate = c;
    c.nextOrientation = c.selfOrientation;
    // Turn left twice to turn around.
    c.nextOrientation = turnNextOrientationLeft(c.nextOrientation);
    c.nextOrientation = turnNextOrientationLeft(c.nextOrientation);
    updateXYCoordinate(&c,&previousCoordinate);
    return previousCoordinate;
}

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
    int count = getTotalCoordinatesInMap(map);
    for(int i = 0; i < count+1; i++){
       printCoordinate(map[i]);
    }
}


// //Return a copy of the coordinate at the end of the map
// coordinate replicateLastPosition(coordinate* map){
//     //Get size of the map 
//     int lastPosition = getTotalCoordinatesInMap(map);
//     return map[lastPosition];
// }

// >= 0 Looped, -1 not in loop
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
    //No need to reverse.
    return -1;
}


void replicateCoordinate(coordinate* src , coordinate* dest){
    src -> isLast = dest -> isLast;
    src -> nextOrientation = dest -> nextOrientation;
    src -> pathAvail = dest -> pathAvail;
    src -> pathUnexplored = dest -> pathUnexplored;
    src -> selfOrientation = dest -> selfOrientation;
    src -> x = dest -> x;
    src -> y = dest -> y;
}

int checkIfCoordinateMatch(coordinate a, coordinate b){
    return (a.x == b.x && a.y == b.y);
}

//Check if loop is in pathUnexplored.
int updateLoop(coordinate* mapCoordinate , coordinate* previousCoordinate){
    coordinate c = *mapCoordinate;
    //Initiate Count
    int count = 0;
    // Bits that will be low during each interaction
    int unexploredTemp = 0;
    while(c.pathUnexplored > 0){
        getNextMove(&c);
        updateUnexploredPath(&c);
        updateXYCoordinate(&c,&c);
        if(checkIfCoordinateMatch(c, *previousCoordinate)){
            
            mapCoordinate->pathUnexplored = c.pathUnexplored;
            return 1;
        }
        else{
            unexploredTemp = c.pathUnexplored;
            c = *mapCoordinate;
            c.pathUnexplored = unexploredTemp;
        }
        count++;
        
    }
    return 0;
}