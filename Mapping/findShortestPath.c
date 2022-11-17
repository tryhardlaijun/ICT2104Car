#include "map.h"
#include "LinkedListPaths.h"
#include "coordinate.h"


int bitShift4Left(int num){
    if(num & 8){
        num -= 8;
        num = num << 1;
        num += 1;
    }
    else{
        num = num << 1;
    }
    return num;
}
int bitShift4Right(int num){
    if(num & 1){
        num -= 1;
        num = num >> 1;
        num += 8;
    }
    else{
        num = num >> 1;
    }
    return num;
}
// Update the orientation according to the origin Orientation and origin paths.
int orientationUpdatePath(int orientOrigin, int orientCompare, int origin, int isRevisible){
    origin = origin << 1;
    origin+= isRevisible;
    // Turn left if origin is bigger
    while(orientOrigin != orientCompare)
    if(orientOrigin == 3 && orientCompare == 0){
        orientOrigin = turnNextOrientationLeft(orientOrigin);
        origin = bitShift4Right(origin);
    }
    else if(orientOrigin == 0 && orientCompare == 3){
        orientOrigin = turnNextOrientationRight(orientOrigin);
        origin = bitShift4Left(origin);
    }
    else if(orientOrigin > orientCompare){
        orientOrigin = turnNextOrientationLeft(orientOrigin);
        origin = bitShift4Right(origin);
    }
    else{
        orientOrigin = turnNextOrientationRight(orientOrigin);
        origin = bitShift4Left(origin);
    }
    origin -= isRevisible;
    origin = origin >> 1;
    return origin;
}
int readShortestPath(int orientOrigin, int orientCompare){
    // Turn left if origin is bigger
    if(orientOrigin == 3 && orientCompare == 0){
        orientOrigin = turnNextOrientationLeft(orientOrigin);
        printf("Turn Left\n");
    }
    else if(orientOrigin == 0 && orientCompare == 3){
        orientOrigin = turnNextOrientationRight(orientOrigin);
        printf("Turn Right\n");
    }
    else if(orientOrigin > orientCompare){
        orientOrigin = turnNextOrientationLeft(orientOrigin);
        printf("Turn Left\n");
    }
    else{
        orientOrigin = turnNextOrientationRight(orientOrigin);
        printf("Turn Right\n");
    }
    return orientOrigin;
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
    updateXYCoordinate(nextCoordinate);
    // Update Explored Path
    updateUnexploredPath(currCoordinate);
    
    *nextCoordinate = *(findCoordinateBasedOnXY(mainMap, nextCoordinate->x,nextCoordinate->y));
    // if(x == NULL){
    //     free(nextCoordinate);
    //     return NULL;
    // }
    nextCoordinate->pathAvail = orientationUpdatePath(nextCoordinate->selfOrientation,currCoordinate->nextOrientation,
    nextCoordinate->pathAvail, nextCoordinate->isReversible);

    // nextCoordinate->pathUnexplored = orientationUpdatePath(nextCoordinate->selfOrientation,currCoordinate->nextOrientation,
    // nextCoordinate->pathUnexplored, nextCoordinate->isReversible);

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


coordinate* findShortestPathInMap(coordinate* map , coordinate start){
    // Setup linked List
    Node *head = NULL;
    // Setup number of paths
    int numberOfPaths = 1;
    // setup starting points
    coordinate * c =(coordinate *) malloc(sizeof(coordinate));
    // Set up shortPath 
    coordinate* shortestPath = NULL;
    //Input coordinate sync with map
    *c = *(findCoordinateBasedOnXY(map, start.x,start.y));
    // Set isLast bit.
    c->isLast = 1;
    c->pathUnexplored = c->pathAvail;
    insertAtEnd(&head,0, c);
    // If not starting path, then add the reversed path of the bot into it.
    if(head->data[0].isReversible){
        // Take the nextious bits
        coordinate * previous = malloc(sizeof(coordinate));
        replicateCoordinate(c,previous);
        previous->selfOrientation = turnNextOrientationRight(previous->selfOrientation);
        previous->selfOrientation = turnNextOrientationRight(previous->selfOrientation);
        previous->pathAvail = 2;
        previous->pathUnexplored = previous->pathAvail;
        // *previous = *(findCoordinateBasedOnXY(map, previous->x,previous->y));
        // previous->isLast = 1;
        insertAtEnd(&head,numberOfPaths, previous);
        printLinkedlist(head);
        numberOfPaths++;

    }
    else{
        printf("Not Reverisble\n");
    }
    int isDone = 1;
    //Loop until it finds an path with available p
    while(isDone){
        // Move forward for every path avail.
        for(int i = 0; i < numberOfPaths; i++){
            // Find the first node.
            Node* node = search(head,i);
            // Get last position of the map
            int lastPosition = getTotalCoordinatesInMap(node->data);
            // Find out the number of bis
            int numberOf1Bits = findNumberOf1Bits(node->data[lastPosition-1].pathUnexplored);
            // If not all path explored
            if(numberOf1Bits != 0){
                // Update lastCoordinate in the node's Map with the main map and give out nextCoordinate.
                coordinate* nextCoordinate = updateMiniMap(map,node->data);
                if(nextCoordinate == NULL){
                    return NULL;
                }
                // Check if the number of bits exceeds 1.
                if(numberOf1Bits > 1){
                    // Make another copy of the map via mallocs
                    coordinate* mapCopy = copyMap(node->data);
                    // Add a new node in the linked list
                    insertAtEnd(&head,numberOfPaths, mapCopy);
                    // Increase number of paths
                    numberOfPaths++;
                }
                // If reached a coordinate which is not 0 -> Found unexplored Coordinate.
                if(nextCoordinate->pathUnexplored != 0){
                    printf("DONE\n");
                    // Ensure While Loop is completes
                    isDone = 0;
                    // Setup temp var to free malloc-ed coordinate
                    coordinate tmp = *nextCoordinate;
                    //Change unexplored path according to explored.
                    tmp.pathUnexplored = orientationUpdatePath(tmp.selfOrientation,
                    tmp.nextOrientation,tmp.pathUnexplored,0);
                    // Add coordinate into map.
                    // getNextMove(&tmp);
                    node->data = updateCoordinateToMap(node->data, tmp);

                    // Copy into shortestPath.
                    shortestPath = copyMap(node->data);
                    // Free coordinate.
                    free(nextCoordinate);
                    break;
                }
                // If all paths of coordinate explored, reset its path available.
                nextCoordinate->pathUnexplored = nextCoordinate->pathAvail;
                // Setup temp var to free malloc-ed coordinate
                coordinate tmp = *nextCoordinate;
                // Add coordinate into map.
                node->data = updateCoordinateToMap(node->data, tmp);
                // Free coordinate.
                free(nextCoordinate);
                
            }
        }
        // Free all memory in linked list.
        printLinkedlist(head);
    }
    freeList(head);
    printf("\n\n\n\n\n");
    printMap(shortestPath);
    return shortestPath;
}
