#include "map.h"
#include "test.h"
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
int countAmountOfRightTurns(int origin , int compare){
    int count = 0;
    while(origin != compare){
        origin = turnNextOrientationRight(origin);
        count++;
    }
    return count;
}

coordinate updateMiniMap(coordinate* mainMap, coordinate* pathMap){
    // Get last pos
    int lastPosition = getTotalCoordinatesInMap(pathMap);
    // create space for next coordinate
    coordinate nextCoordinate = (pathMap[lastPosition-1]);
    // Find out next move and change orientation
    getNextMove(&pathMap[lastPosition-1]);
    // Update Coordinate
    updateXYCoordinate(&pathMap[lastPosition-1],&nextCoordinate);
    // Update Explored Path
    updateUnexploredPath(&pathMap[lastPosition-1]);
    nextCoordinate = *(findCoordinateBasedOnXY(mainMap, nextCoordinate.x,nextCoordinate.y));
    nextCoordinate.pathUnexplored = nextCoordinate.pathAvail;
    return nextCoordinate;
}
int findNumberOf1Bits(int num){
    int count = 0;
    while(num != 0){
        if(num & 1){
            count++;
        }
        num = num >> 1;

    }
    return count;
}


void test(coordinate* map){
        Node *head = NULL;
    int count = 1;
    coordinate * c =(coordinate *) malloc(sizeof(coordinate));
    coordinate start = map[0];
    start.isLast = 1;
    *c = start;
    c->pathUnexplored = c->pathAvail;
    insertAtEnd(&head,0, c);
    if(head->data[0].x == 0 && head->data[0].y == 0){
        // printf("Starting Point\n");
    }
    else{
        insertAtEnd(&head,count, c);
        count++;
    }

    while(1){
        for(int i = 0; i < count; i++){
            Node* node = search(head,i);

            int lastPosition = getTotalCoordinatesInMap(node->data);
            int numberOf1Bits = findNumberOf1Bits(node->data[lastPosition-1].pathUnexplored);
            if(numberOf1Bits != 0){
                coordinate nextCoordinate = updateMiniMap(map,node->data);
                if(numberOf1Bits > 1){
                    coordinate* mapCopy = copyMap(node->data);
                    insertAtEnd(&head,count, mapCopy);
                    count++;
                }
                updateCoordinateToMap(node->data,nextCoordinate);
                
            }
 
  
        }
        printLinkedlist(head);
    }

    freeList(head);
}
int main(){
    coordinate * map = getMap();
    test(map);

}

//     printMap(map);
//     if(isMapFullyExplored(map) != -1){
//         int lastPosition = getTotalCoordinatesInMap(map);
//         // coordinate z = getPreviousCoordinate();
//         // printf("\n\n");
//         // printCoordinate(map[lastPosition]);
//     }
//     else{
//         printf("Complete");
//     }
// }