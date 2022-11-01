#include "map.h"

#include<string.h>

int main(){
    //zaf
    // Map will be printed based on this 2d array -> array[maxOfPositiveY-maxOfNegativeY][maxOfPositiveX-maxOfNegativeX] 
    int maxOfPositiveX = 0;  // 1 because it is the minimum
    int maxOfPositiveY = 0; // 1 because it is the minimum
    int maxOfNegativeX = 0; // 0 because it may never be negative
    int maxOfNegativeY = 0;

    coordinate* map = NULL;
    coordinate* unexploredCoordinates = NULL;
    int totalLines = getTotalLines();
    int* sensorArray = getSensorArrayFromText();
    for(int i =0; i < totalLines; i++){
        //If at the very beginning.
        if(map == NULL){
            map = updateCoordinateToMap(map, initStartingCoordinate());
            updateCoordinatePaths(map,sensorArray[0]);
            getnextMove(map);
        }
        else{
            //get size of Map
            int lastPosition = getTotalCoordinatesInMap(map);
            //Replicate a coordinate like the previous map
            coordinate c = replicateLastPosition(map);
            // Update current path
            updateCoordinatePaths(&c , sensorArray[i]);
            // Update Orientation
            getnextMove(&c);
            // Update where the current coordinate is
            updateXYCoordinate(&map[lastPosition],&c, &maxOfPositiveX,&maxOfNegativeX, &maxOfPositiveY, &maxOfNegativeY);
            // Update Unexplored Path for current path // zaf: previous
            int pathRemain = updateUnexploredPath(&map[lastPosition]);
            // Check if next coordinate has already been explored
            int isExplored = checkIfAlreadyInMap(map , c);
            //Check if map has been explored
            if(isExplored == -1){
                // Unexplored
                //Naomi's Code to go to the unexplored spot
                //Add current coordinate to map if unexplored
                map = updateCoordinateToMap(map, c);
            }
            else{ //Explored
                //Check if in unexploredArray
                int getUnexploredPosition = checkIfAlreadyInMap(unexploredCoordinates,c);
                if(getUnexploredPosition != -1){
                    unexploredCoordinates[getUnexploredPosition] = c;
                }
                
            }
            if(pathRemain != 0){ // zaf: previous coordinate?
                unexploredCoordinates = updateCoordinateToMap(unexploredCoordinates, map[lastPosition]);
            }

        }
    }

    int arrayHeight = (maxOfPositiveY+1) - maxOfNegativeY; // +1 cause it started from 0
    int arrayWidth = (maxOfPositiveX+1) - maxOfNegativeX;
    char** printExplored;
    printExplored = (char **)calloc(arrayHeight, sizeof(char*)); // could be char*

    for (int i = 0; i < arrayHeight; i++) {
        printExplored[i] = (char *)(calloc)(arrayWidth*2, sizeof(char));
        int k;
        for (k=0; k < arrayWidth; k++) {
            strcat(printExplored[i], "  ");
            if (k==arrayWidth-1) { // TODO: is this needed?
            strcat(printExplored[i], "\0");
            }
        }
    }

    printMap(map);
    printf("\n");

    int lastPosition = getTotalCoordinatesInMap(map);
    int j;
    int k;
    int startPositionY = 0;
    int startPositionX = 0;
    if (maxOfNegativeY < 0) {
        // offset starting coordinate y of car
        // startPositionY = (maxOfPositiveY) + maxOfNegativeY; // if y ever goes negative, car won't start from y coordinate 0.
        startPositionY = (arrayHeight-1) - maxOfPositiveY;
    }
    if (maxOfNegativeX < 0) {
        // offset starting coordinate x of car
        startPositionX = (arrayWidth-1) + maxOfNegativeX; // if x ever goes negative, car won't start from x coordinate 0.
    }
    for (int i=0; i<lastPosition+1; i++){
        j = map[i].y;
        k = map[i].x;
        int tempY = startPositionY + map[i].y; // get starting coordinate y of car
        int tempX = (startPositionX + map[i].x)*2; // get starting coordinate x of car

        if (i == 0) {
            printExplored[tempY][tempX] = 's';
        } 
        else if (i == lastPosition) {
            printExplored[tempY][tempX] = 'x';
        }
        else {
            printExplored[tempY][tempX] = '.';
        }
        
    }

    for (int i=arrayHeight-1; i >= 0; --i) {
        char *oo = printExplored[i];
        printf(oo);
        printf("\n");

    }

    

    // idk if it's the right way to free it
    // for (int i = 0; i < arrayHeight; i++)
    //     free(printExplored[i]);
    // free(printExplored);

    printf("\n");
    printMap(unexploredCoordinates);

}