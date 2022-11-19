#include "breatheFirstSearch.h"
#include "movement.h"

// Return next coordinate.
coordinate* updateMiniMap(coordinate* mainMap, coordinate* pathMap){
    // Get last pos
    int lastPosition = getTotalCoordinatesInMap(pathMap);
    coordinate *pathCoordinate = &(pathMap[lastPosition-1]);
    coordinate *nextCoordinate = (coordinate *) malloc(sizeof(coordinate));
    // resetUnexploredPath(pathCoordinate);
    int movement = getNextMove(pathCoordinate);
    updateUnexploredPath(pathCoordinate,movement);
    // Transfer into in to next Coordinate
    *nextCoordinate = *pathCoordinate;
    updateXYCoordinate(nextCoordinate ,movement);
    coordinate* tmp = (findCoordinateBasedOnXY(mainMap, nextCoordinate->x,nextCoordinate->y));
    if(tmp == NULL){
        free(nextCoordinate);
        return NULL;
    }
    *nextCoordinate = *tmp;
    availToExploredPath(nextCoordinate);
    updateLoop(nextCoordinate,pathCoordinate);
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

coordinate* createNewPathToLinkedList(Node* node, Node* head, int *numberOfPaths){
    // Make another copy of the map via mallocs
    coordinate* mapCopy = copyMap(node->data);
    // Add a new node in the linked list
    insertAtEnd(&head,*numberOfPaths, mapCopy);
    // Increase number of paths
    (*numberOfPaths)+=1;
}
coordinate* findShortestPathInMap(coordinate* map , coordinate start){
    if(isMapFullyExplored(map) < 0){
        printf("Map fully explored\n");
        return NULL;
    }
    // Setup linked List
    Node *head = NULL;
    // Setup number of paths
    int numberOfPaths = 1;
    // setup starting points
    coordinate * c =(coordinate *) malloc(sizeof(coordinate));
    // Set up shortPath 
    coordinate* shortestPath = NULL;
    // Set up visited Coordinates
    coordinate* visted = NULL;
    //Input coordinate sync with map
    *c = *(findCoordinateBasedOnXY(map, start.x,start.y));
    // Set isLast bit.
    c->isLast = 1;
    // Reset Avail.
    availToExploredPath(c);
    // insert head into linked list.
    insertAtEnd(&head,0, c);
    int isDone = 1;
    while(isDone){
        for(int i = 0; i < numberOfPaths; i++){
            Node* node = search(head,i);
            // Get last position of the map
            int lastPosition = getTotalCoordinatesInMap(node->data);
            // Get last Array Coordinate
            coordinate lastCoordinate = node->data[lastPosition-1];
            int first4Bits = lastCoordinate.paths & 15;
            // Find out the number of bis
            int numberOf1Bits = findNumberOf1Bits(first4Bits);
            // If not all path explored
            if(numberOf1Bits != 0){
                coordinate* nextCoordinate = updateMiniMap(map,node->data);
                // Means there is more than 1 open path for that node.
                if(numberOf1Bits > 1){
                    createNewPathToLinkedList(node,head,&numberOfPaths);
                }
                // Next coordinate is not found in the main map.
                if(nextCoordinate != NULL){
                    // Setup temp var to free malloc-ed coordinate
                    coordinate tmp = *nextCoordinate;
                    // Check if visited
                    int checkIfVisited = checkIfAlreadyInMap(visted, tmp);
                    // If not visited then update inot maps
                    if(checkIfVisited == -1){
                        // Add coordinate into map.
                        node->data = updateCoordinateToMap(node->data, tmp);
                        // Add node into visted.
                        visted = updateCoordinateToMap(visted, tmp);
                    }
                    //else reset bits in last position so that the program would think that it is a deadend.
                    else{
                        resetUnexploredPath(&(node->data[lastPosition-1]));
                    }
                    // Free coordinate.
                    free(nextCoordinate);
                }
                else{
                    shortestPath = copyMap(node->data);
                    isDone = 0;
                    free(nextCoordinate);
                    break;
                }
            }
        }

        printf("\n\n");
        printLinkedlist(head);



    }
    printf("Visted\n\n");
    printMap(visted);
    printf("Shortest \n");
    printMap(shortestPath);
    reset(&visted);
    freeList(head);
    return shortestPath;
}