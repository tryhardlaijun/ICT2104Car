#include <stdio.h>
#include "coordinate.h"
#include "map.h"
#include "generateMap.h"

coordinate *getTestMap()
{
    coordinate c1 = {0, 0, 0b00110011, 0};
    coordinate c2 = {0, 1, 0b01010101, 0};
    coordinate c3 = {0, 2, 0b01010101, 0};
    coordinate c4 = {0, 3, 0b01100110, 0};
    coordinate c5 = {1, 3, 0b11101110, 0};
    coordinate c6 = {2, 3, 0b11101110, 0};
    coordinate c7 = {3, 3, 0b10101010, 0};
    coordinate c8 = {4, 3, 0b11001100, 0};
    coordinate c9 = {4, 2, 0b01010101, 0};
    coordinate c10 = {4, 1, 0b11011101, 0};
    coordinate c11 = {4, 0, 0b10011001, 0};
    coordinate c12 = {3, 0, 0b10101010, 0};
    coordinate c13 = {2, 0, 0b10101010, 0};
    coordinate c14 = {1, 0, 0b10101010, 0};
    // jump to [1,2] after loop found and shortest path calculated
    coordinate c15 = {1, 2, 0b01010101, 0};
    coordinate c16 = {1, 1, 0b00110011, 0};
    coordinate c17 = {2, 1, 0b10101010, 0};
    coordinate c18 = {3, 1, 0b10101010, 0};
    // jump to [2,2] after loop found and shortest path calculated
    coordinate c19 = {2, 2, 0b00110011, 0};
    coordinate c20 = {3, 2, 0b10001000, 1};
    // end

    coordinate *map = NULL;
    coordinate c = initStartingCoordinate();
    map = updateCoordinateToMap(map, c);
    map = updateCoordinateToMap(map, c1);
    map = updateCoordinateToMap(map, c2);
    map = updateCoordinateToMap(map, c3);
    map = updateCoordinateToMap(map, c4);
    map = updateCoordinateToMap(map, c5);
    map = updateCoordinateToMap(map, c6);
    map = updateCoordinateToMap(map, c7);
    map = updateCoordinateToMap(map, c8);
    map = updateCoordinateToMap(map, c9);
    map = updateCoordinateToMap(map, c10);
    map = updateCoordinateToMap(map, c11);
    map = updateCoordinateToMap(map, c12);
    map = updateCoordinateToMap(map, c13);
    map = updateCoordinateToMap(map, c14);
    // jump to [1,2] after loop found and shortest path calculated
    map = updateCoordinateToMap(map, c15);
    map = updateCoordinateToMap(map, c16);
    map = updateCoordinateToMap(map, c17);
    map = updateCoordinateToMap(map, c18);
    // jump to [2,2] after loop found and shortest path calculated
    map = updateCoordinateToMap(map, c19);
    map = updateCoordinateToMap(map, c20);

    return map;
}

int gridBorderBuilder(int heightOrWidth, int heightOrWidthFlag)
{
    int gridHeightBorder = 3; // initialise to 3 based on border we want to build + - + - +
    int gridWidthBorder = 5;  //                                                  |   |   |
                              //                                                  + - + - +
    if (heightOrWidthFlag == 0)
    {
        // height
        if (heightOrWidth == 1)
            return gridHeightBorder;
        else
            return gridHeightBorder + (2 * (heightOrWidth - 1));
    }

    if (heightOrWidthFlag == 1)
    {
        // width
        if (heightOrWidth == 1)
            return gridWidthBorder;
        else
            return (4 * heightOrWidth) + 1;
    }
}

char *gridStringConcat(char *printExplored, int arrayWidth, char *borderStr, char *borderStrToAdd)
{
    // if (arrayWidth == 1)
    //     return strcpy(printExplored, borderStr);
    strcpy(printExplored, borderStr);
    for (int i = 0; i < arrayWidth; i++)
    {
        strcat(printExplored, borderStrToAdd);
    }
    return printExplored;
}

char *gridBuilder(char *printExplored, int index, int arrayWidth)
{
    char *borderStrOuter = "+", *borderStrOuterToAdd = " - +"; // intialise to be added to array of strings, which is our grid map.
    char *borderStrInner = "|", *borderStrInnerToAdd = "   |";

    if (index % 2 == 0)
        return gridStringConcat(printExplored, arrayWidth, borderStrOuter, borderStrOuterToAdd);
    return gridStringConcat(printExplored, arrayWidth, borderStrInner, borderStrInnerToAdd);
};

int computeSizeOfMap(coordinate *map, int *arrayHeight, int *arrayWidth, printOffsets *offsetValue)
{
    int maxOfY = 0, minOfY = 0;
    int maxOfX = 0, minOfX = 0;
    int checkAvailMaxY = 0, checkAvailMinY = 0;
    int checkAvailMaxX = 0, checkAvailMinX = 0;

    int totalCoordinates = getTotalCoordinatesInMap(map);
    // int totalCoordinates = 20;

    for (int i = 0; i < totalCoordinates; i++)
    {

        // get max and min coordinate values
        if (map[i].y > maxOfY)
            maxOfY = map[i].y;
        else if (map[i].y < minOfY)
            minOfY = map[i].y;
        if (map[i].x > maxOfX)
            maxOfX = map[i].x;
        else if (map[i].x < minOfX)
            minOfX = map[i].x;
    }

    // +1 to max of each coordinate in case there's an available path that adds to the map, and the car missed/skipped it.
    // used for testing. if shortest path is always found to the next avail path, we don't need this as the car would have definitely travel to the max coordinate.
    // zaf - comment c15-c20 or edit coordinates of getTestMap() to test for this
    for (int i = 0; i < totalCoordinates; i++)
    {
        int availPaths = map[i].paths >> 4;
        // check for, if at max coordinate y, there is an available path up,
        if (map[i].y == maxOfY && (availPaths & 1) && checkAvailMaxY == 0)
        {
            maxOfY++;
            checkAvailMaxY = 1;
        }
        // check for if at min coordinate y, there is an available path down
        else if (map[i].y == minOfY && (availPaths & 4) && checkAvailMinY == 0)
        {
            minOfY--;
            checkAvailMinY = 1;
        }

        // check for if at max coordinate x, there is an available path right
        if (map[i].x == maxOfX && (availPaths & 2) && checkAvailMaxX == 0)
        {
            maxOfX++;
            checkAvailMaxY = 1;
        }
        // check for if at min coordinate x, there is an available path left
        else if (map[i].x == minOfX && (availPaths & 8) && checkAvailMinX == 0)
        {
            minOfX--;
            checkAvailMinY = 1;
        }
    }

    // max(positive num) - min(negative num) = positive num
    *arrayHeight = 1 + (maxOfY - minOfY);
    *arrayWidth = 1 + (maxOfX - minOfX);
    // to get car starting position in the map, *-1 to get positive num
    offsetValue->startPositionY = (minOfY * -1);
    offsetValue->startPositionX = (minOfX * -1);

    return 0;
}

int addOffsetForGridMap(int startPositionOffset, int startPosition, int offset)
{
    // add offset if car does not start at position 0 / fromZero
    int fromZero = 0;
    if (startPosition != fromZero)
    {
        for (int i = 0; i < startPosition; i++)
        {
            startPositionOffset += offset;
        }
    }
    return startPositionOffset;
}

void addAvailPathToGridMap(char **mapToPrint, int tempY, int tempX, printValues *value)
{
    // if coordinate in grid map already has start or explored values, don't overwrite the data
    if (mapToPrint[tempY][tempX] != value->start && mapToPrint[tempY][tempX] != value->explored)
        mapToPrint[tempY][tempX] = value->avail;
}

char **buildGridMap(coordinate *map, int *gridHeight, int *carArrHeight, int *carArrWidth, printOffsets *offsetValue)
{
    // calculate the size of map with all it's borders and initial starting positions
    computeSizeOfMap(map, carArrHeight, carArrWidth, offsetValue);

    // build empty map first, 0 will trigger if condition for height, 1 will trigger else condition for width
    // grid height will be used to free the fullMap from main.c
    *gridHeight = gridBorderBuilder(*carArrHeight, 0);
    int gridWidth = gridBorderBuilder(*carArrWidth, 1);

    // printf("\ngridHeight = %d, gridWidth = %d\n", gridHeight, gridWidth);

    // allocate memory for height of grid map
    char **mapToPrint = (char **)malloc(*gridHeight * sizeof(char *));
    if (mapToPrint == NULL)
    {
        printf("die\n");
        exit(0);
    }
    for (int i = 0; i < *gridHeight; i++)
    {
        // allocate memory for width of map
        mapToPrint[i] = (char *)malloc(gridWidth + 1);
        if (mapToPrint[i] == NULL)
        {
            printf("die\n");
            exit(0);
        }
    }

    // at each row of mapToPrint, add borders around and inside the map to represent cells
    for (int i = 0; i < *gridHeight; i++)
    {
        gridBuilder(mapToPrint[i], i, *carArrWidth);
    }

    printFullMap(mapToPrint, *gridHeight, "Empty Map, showing size of map, before borders are removed");

    return mapToPrint;
}

void generateFullMap(coordinate *map, char **mapToPrint, int gridHeight, printValues *value, printOffsets *offsetValue)
{
    // if car does not start at the original position, e.g. [0,0], we add more offsets
    // add 2 to offset Y because e.g.   + - +   the position of 's' to next cell 'e', jumps by getToNextCellY = 2
    //                                  | e |
    //                                  + - +
    //                                  | s |
    //                                  + - +
    offsetValue->startPositionYOffset = addOffsetForGridMap(offsetValue->startPositionYOffset, offsetValue->startPositionY, offsetValue->getToNextCellY);
    // add 4 to offset X because e.g.   + - + - +   the position of 's' to next cell 'e', jumps by getToNextCellX = 4
    //                                  | s | e |
    //                                  + - + - +
    offsetValue->startPositionXOffset = addOffsetForGridMap(offsetValue->startPositionXOffset, offsetValue->startPositionX, offsetValue->getToNextCellX);

    // initialise values to add into mapToPrint that was created
    int totalCoordinatesMoved = getTotalCoordinatesInMap(map);
    int heightCounter = 0, widthCounter = 0, tempY = 0, tempX = 0;

    for (int i = 0; i < totalCoordinatesMoved; i++)
    {
        int availPaths = map[i].paths >> 4;
        if (i == 0)
        {
            tempY = offsetValue->startPositionYOffset;
            tempX = offsetValue->startPositionXOffset;
            // where the car starts
            mapToPrint[tempY][tempX] = value->start;
        }
        else
        {
            // 2 and 4 same reason as explained when adding offset  to startPositionOffset
            tempY = (offsetValue->getToNextCellY * map[i].y) + offsetValue->startPositionYOffset;
            tempX = (offsetValue->getToNextCellX * map[i].x) + offsetValue->startPositionXOffset;
            // where the car moved
            if (mapToPrint[tempY][tempX] != value->start && mapToPrint[tempY][tempX] != value->explored)
                mapToPrint[tempY][tempX] = value->explored;
        }

        // if last coordinate, then print e
        if (i == totalCoordinatesMoved - 1)
            mapToPrint[tempY][tempX] = value->end;

        // check available paths and open up border
        // check up is avail
        if (availPaths & 1)
        {
            mapToPrint[tempY + offsetValue->removeBordersY][tempX] = ' ';
            addAvailPathToGridMap(mapToPrint, tempY + offsetValue->getToNextCellY, tempX, value);
        }
        // check down is avail
        if (availPaths & 4)
        {
            mapToPrint[tempY - offsetValue->removeBordersY][tempX] = ' ';
            addAvailPathToGridMap(mapToPrint, tempY - offsetValue->getToNextCellY, tempX, value);
        }
        // check right is avail
        if (availPaths & 2)
        {
            mapToPrint[tempY][tempX + offsetValue->removeBordersX] = ' ';
            addAvailPathToGridMap(mapToPrint, tempY, tempX + offsetValue->getToNextCellX, value);
        }
        // check left is avail
        if (availPaths & 8)
        {
            mapToPrint[tempY][tempX - offsetValue->removeBordersX] = ' ';
            addAvailPathToGridMap(mapToPrint, tempY, tempX - offsetValue->getToNextCellX, value);
        }
    }

    printFullMap(mapToPrint, gridHeight, "Normal Map");
}

void cleanMap(int carArrHeight, int carArrWidth, char **mapToPrint, printOffsets *offsetValue, int gridHeight)
{
    int tempY = 0, tempX = 0;
    // clean map first to reset values from generateFullMap() or generateShortestPathMap()
    for (int i = 0; i < carArrHeight; i++)
    {
        for (int k = 0; k < carArrWidth; k++)
        {
            // the reason removeBordersY and removeBordersX is used is that it is static and is always 1 and 2,
            // which is the original offset of the border incase startPosition is changed
            tempY = (offsetValue->getToNextCellY * i) + offsetValue->removeBordersY;
            tempX = (offsetValue->getToNextCellX * k) + offsetValue->removeBordersX;
            // remove any visited coordinate
            mapToPrint[tempY][tempX] = ' ';
        }
    }

    printFullMap(mapToPrint, gridHeight, "Clean map before showing shortest path");
}

void printFullMap(char **map, int gridHeight, char *mapName)
{
    printf("\n%s\n", mapName);
    for (int i = gridHeight - 1; i >= 0; --i)
    {
        printf("%s\n", map[i]);
    }
    printf("\n\n");
}

void generateShortestPathMap(coordinate *shortestPathMap, coordinate *originalMap, char **mapToPrint, int gridHeight, printValues *value, printOffsets *offsetValue)
{
    int tempY = 0, tempX = 0;
    // start positions should be the first item in shortest path as [0] is where the car stops to analyse shortest path
    int startPositionY = shortestPathMap[0].y, startPositionX = shortestPathMap[0].x;
    // we can get this from offsetValue struct
    // int startPositionYOffset = addOffsetForGridMap(offsetValue->startPositionYOffset, startPositionY, offsetValue->getToNextCellY);
    // int startPositionXOffset = addOffsetForGridMap(offsetValue->startPositionXOffset, startPositionX, offsetValue->getToNextCellX);

    int shortestCoordinatesMoved = getTotalCoordinatesInMap(shortestPathMap);

    for (int i = 0; i < shortestCoordinatesMoved; i++)
    {
        if (i == 0)
        {
            mapToPrint[offsetValue->startPositionYOffset][offsetValue->startPositionXOffset] = value->start;
            continue;
        }
        // 2 and 4 same reason as explained when adding offset  to startPositionOffset
        tempY = (offsetValue->getToNextCellY * shortestPathMap[i].y) + offsetValue->startPositionYOffset;
        tempX = (offsetValue->getToNextCellX * shortestPathMap[i].x) + offsetValue->startPositionXOffset;
        // where the car moved
        if (mapToPrint[tempY][tempX] != value->start && mapToPrint[tempY][tempX] != value->explored)
            mapToPrint[tempY][tempX] = value->explored;

        // if last coordinate, then print e
        if (i == shortestCoordinatesMoved - 1)
            mapToPrint[tempY][tempX] = value->end;
    }

    printFullMap(mapToPrint, gridHeight, "Shortest Path Map");
}

void getPrintedMap(coordinate *originalMap, coordinate *shortestPathMap)
{
    // initialise variables that gets passed around
    int gridHeight = 0, carArrHeight = 0, carArrWidth = 0;
    // added into struct as the same variables gets repeated alot
    // if car starts from [0,0], we have to add in the offsets because of the borders that we have, in this case, [0,0] becomes [2,1]
    //                                                                           + - + - +
    printOffsets initialisePrintingOffsets = {1, 2, 2, 4, 0, 0, 1, 2}; //        |   |   |
    // change this to to see what gets printed into the map values.              + - + - +
    printValues initialMapValues = {'s', '1', ' ', 'e'};
    printValues shortestPathValues = {'s', '1', ' ', 'e'};

    // build the map, and retrieve data for the variables
    char **gridMap = buildGridMap(originalMap, &gridHeight, &carArrHeight, &carArrWidth, &initialisePrintingOffsets);
    // get full map with borders removed
    generateFullMap(originalMap, gridMap, gridHeight, &initialMapValues, &initialisePrintingOffsets);
    // clean gridMap before printing shortest path map
    // could be in a loop if there are multiple shortest paths called.
    cleanMap(carArrHeight, carArrWidth, gridMap, &initialisePrintingOffsets, gridHeight);
    // update gridMap to shortestPath map
    generateShortestPathMap(shortestPathMap, originalMap, gridMap, gridHeight, &shortestPathValues, &initialisePrintingOffsets);

    for (int i = 0; i < gridHeight; i++)
    {
        free(gridMap[i]);
    }
    free(gridMap);
}