#include<stdio.h>
#include<stdlib.h>
#include "coordinate.h"
#define MAX 1000

coordinate* addCoordinateToMap(coordinate* Map, coordinate c){
    //Map[lastPosition] -> Last explored
    int lastPosition = findLastExplored(Map);
    //+1 -> Starting from 0 then +1 again -> extra space for new coordinate
    //Realloc would copy all the current data into a new space with extra space
    //then free the previous memory used, 
    //unless the current address is being used.
    coordinate* temp = realloc(Map,sizeof(coordinate)*(lastPosition+1+1));
    // NULL means computer not enough space to reallocate
    if(temp == NULL){
        free(Map);
        return NULL;
    }
    else{
        Map = temp;
    }
    //Ensure previous Explored Coordinate is no longer labelled last
    Map[lastPosition].isLast = 0;
    //Update new coordinate to newly create space
    Map[lastPosition+1] = c;
    //Ensure last memory isLast bit is 1
    Map[lastPosition+1].isLast = 1;
    
    return Map;
}

//Find last explore coordinate by looking coordinate with isLast bit = 1
int findLastExplored(coordinate* Map){
    //Assume max amount of coordinate is 1000
    for(int i = 0; i < MAX; i++){
        //If last bit is true then return number
        if(Map[i].isLast == 1){
            return i;
        }
    }
    printf("EXCEED Size 1000 \n");
    //Return -1 signal error.
    return -1;
}
int main(){
    coordinate* Map = NULL;
    if(Map == NULL){
        Map = malloc(sizeof(coordinate));
        *Map = initStartingCoordinate();
    }
    Map = addCoordinateToMap()
    printf("%d\n",findLastExplored(Map));

}