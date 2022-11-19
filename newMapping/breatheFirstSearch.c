#include "breatheFirstSearch.h"
#include "movement.h"

// Return next coordinate.
coordinate* updateMiniMap(coordinate* mainMap, coordinate* pathMap){
    // Get last pos
    int lastPosition = getTotalCoordinatesInMap(pathMap);
    coordinate *pathCoordinate = &(pathMap[lastPosition-1]);
    coordinate *nextCoordinate = (coordinate *) malloc(sizeof(coordinate));
    *nextCoordinate = *pathCoordinate;
    resetUnexploredPath(pathCoordinate);
    int movement = getNextMove(nextCoordinate);
    updateUnexploredPath(nextCoordinate,movement);
    updateXYCoordinate(nextCoordinate ,movement);
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
            int first4Bits = node->data[lastPosition-1].paths & 15;
            // Find out the number of bis
            int numberOf1Bits = findNumberOf1Bits(first4Bits);
            // If not all path explored
            if(numberOf1Bits != 0){
                if(numberOf1Bits > 1){
                    // Make another copy of the map via mallocs
                    coordinate* mapCopy = copyMap(node->data);
                    // Update node data
                    // Add a new node in the linked list
                    insertAtEnd(&head,numberOfPaths, mapCopy);
                    // Increase number of paths
                    numberOfPaths++;
                }
                coordinate* nextCoordinate = updateMiniMap(map,node->data);
            }
        }
        Node* node = search(head,0);
        // isDone = 1;
    }


}