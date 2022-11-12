#include "findShortestPath.h"


int countAmountOfRightTurns(int origin , int compare){
    int count = 0;
    while(origin != compare){
        origin = turnNextOrientationRight(origin);
        count++;
    }
    return count;
}

int changePathsByOrientationRight(int num){
    if(num & 4){
        num -= 4;
        num = num << 1;
        num += 1;
    }
    else{
        num = num << 1;
    }
    return num;
}

int orientationUpdatePath(int orientOrigin, int orientCompare, int origin){
    if (origin == 7)
        return 7;
    int x = countAmountOfRightTurns(orientOrigin, orientCompare);
    if(x > 0){
        // Reset bit from start for count
        origin &= ~(1 << (3 - x));
    }
    for(int i = 0; i < x-1; i++){
        origin = changePathsByOrientationRight(origin);
    }
    if(x > 0){
    // Set origin, original bit
        origin |= (1 << (x-1));
    }
    return origin;
}


coordinate* updateMiniMap(coordinate* mainMap, coordinate* pathMap){
    // Get last pos
    int lastPosition = getTotalCoordinatesInMap(pathMap);
    coordinate *currCoordinate = &(pathMap[lastPosition-1]);
    // create space for next coordinate
    coordinate* nextCoordinate =  malloc(sizeof(coordinate)); 
    *nextCoordinate = *currCoordinate;
    // Find out next move and change orientation
    getNextMove(currCoordinate);
    //Update Orientaition
    nextCoordinate->selfOrientation = currCoordinate->nextOrientation;
    // Update Coordinate5
    updateXYCoordinate(currCoordinate,nextCoordinate);
    // Update Explored Path
    updateUnexploredPath(currCoordinate);
    *nextCoordinate = *(findCoordinateBasedOnXY(mainMap, nextCoordinate->x,nextCoordinate->y));
    nextCoordinate->pathAvail = orientationUpdatePath(nextCoordinate->selfOrientation,currCoordinate->nextOrientation, nextCoordinate->pathAvail);
    nextCoordinate->selfOrientation = currCoordinate->nextOrientation;
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


coordinate* findShortestPath(coordinate* map){
    // Setup linked List
    Node *head = NULL;
    // Setup number of paths
    int numberOfPaths = 1;
    coordinate * c =(coordinate *) malloc(sizeof(coordinate));
    coordinate start = map[0];
    start.isLast = 1;
    coordinate* shortestPath = NULL;
    *c = start;
    c->pathUnexplored = c->pathAvail;
    insertAtEnd(&head,0, c);
    if(head->data[0].x == 0 && head->data[0].y == 0){
        // printf("Starting Point\n");
    }
    else{
        insertAtEnd(&head,numberOfPaths, c);
        numberOfPaths++;
    }
    int isDone = 1;
    while(isDone){
        for(int i = 0; i < numberOfPaths; i++){
            Node* node = search(head,i);

            int lastPosition = getTotalCoordinatesInMap(node->data);
            int numberOf1Bits = findNumberOf1Bits(node->data[lastPosition-1].pathUnexplored);
            if(numberOf1Bits != 0){
                coordinate* nextCoordinate = updateMiniMap(map,node->data);
                // if(nextCoordinate == NULL){

                // }
                if(numberOf1Bits > 1){
                    coordinate* mapCopy = copyMap(node->data);
                    insertAtEnd(&head,numberOfPaths, mapCopy);
                    numberOfPaths++;
                }
                if(nextCoordinate->pathUnexplored != 0){
                    printf("DONE\n");
                    isDone = 0;
                    coordinate tmp = *nextCoordinate;
                    updateCoordinateToMap(node->data, tmp);
                    shortestPath = copyMap(node->data);
                    free(nextCoordinate);
                    break;
                }
                nextCoordinate->pathUnexplored = nextCoordinate->pathAvail;
                coordinate tmp = *nextCoordinate;
                updateCoordinateToMap(node->data, tmp);
                free(nextCoordinate);
                
            }
        }
        printLinkedlist(head);
    }
    freeList(head);
    printf("\n\n\n\n\n");
    printMap(shortestPath);
    return shortestPath;
}

