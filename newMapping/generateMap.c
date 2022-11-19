#include <stdio.h>
#include "coordinate.h"
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
    int gridHeightBorder = 3; // initialise to 3
    int gridWidthBorder = 5;

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
};

char *gridStringConcat(char *printExplored, int arrayWidth, char *borderStr, char *borderStrToAdd, int strLen)
{
    if (arrayWidth == 1)
        return strcpy(printExplored, borderStr);
    strcpy(printExplored, borderStr);
    for (int i = 0; i < arrayWidth; i++)
    {
        strcat(printExplored, borderStrToAdd);
    }
    return printExplored;
}

char *gridBuilder(char *printExplored, int index, int arrayWidth)
{
    int strLen = 7;
    char *borderStrOuter = "+", *borderStrOuterToAdd = " - +";
    char *borderStrInner = "|", *borderStrInnerToAdd = "   |";

    if (index % 2 == 0)
        return gridStringConcat(printExplored, arrayWidth, borderStrOuter, borderStrOuterToAdd, strLen);
    return gridStringConcat(printExplored, arrayWidth, borderStrInner, borderStrInnerToAdd, strLen);
};

int computeSizeOfMap(coordinate *map, int *arrayHeight, int *arrayWidth, int *startPositionY, int *startPositionX)
{
    int maxOfY = 0, minOfY = 0;
    int maxOfX = 0, minOfX = 0;
    int checkAvailMaxY = 0, checkAvailMinY = 0;
    int checkAvailMaxX = 0, checkAvailMinX = 0;

    int totalCoordinates = getTotalCoordinatesInMap(map);

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
    *startPositionY = (minOfY * -1);
    *startPositionX = (minOfX * -1);

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

void addAvailPathToGridMap(char **mapToPrint, int tempY, int tempX, char printAvail, char printStart, char printExplored)
{
    // if coordinate in grid map already has start or explored values, don't overwrite the data
    if (mapToPrint[tempY][tempX] != printStart && mapToPrint[tempY][tempX] != printExplored)
        mapToPrint[tempY][tempX] = printAvail;
}

void generateMap(coordinate *map)
{
    // zaf - can change printExplored = '1' and printAvail to '0'
    //     - comment c15-c20 or edit coordinates of getTestMap() to test for this
    char printStart = 's', printExplored = ' ', printAvail = ' ';

    // initialise values and compute size of map
    int carArrHeight = 0, carArrWidth = 0, startPositionY = 0, startPositionX = 0;
    computeSizeOfMap(map, &carArrHeight, &carArrWidth, &startPositionY, &startPositionX);

    // printf("\nsize of map = arrayheight: %d, arraywidth: %d, startPosY: %d, startPosX:%d\n", carArrHeight, carArrWidth, startPositionY, startPositionX);

    // calculate offset because of borders
    int startPositionYOffset = 1, startPositionXOffset = 2;
    int getToNextCellY = 2, getToNextCellX = 4;
    int removeBordersY = getToNextCellY / 2, removeBordersX = getToNextCellX / 2;

    // if car does not start at the original position, e.g. [0,0], we add more offsets
    // add 2 to offset Y because e.g.   + - +   the position of 's' to next cell 'e', jumps by getToNextCellY = 2
    //                                  | e |
    //                                  + - +
    //                                  | s |
    //                                  + - +
    startPositionYOffset = addOffsetForGridMap(startPositionYOffset, startPositionY, getToNextCellY);
    // add 4 to offset X because e.g.   + - + - +   the position of 's' to next cell 'e', jumps by getToNextCellX = 4
    //                                  | s | e |
    //                                  + - + - +
    startPositionXOffset = addOffsetForGridMap(startPositionXOffset, startPositionX, getToNextCellX);

    // build empty map first, 0 will trigger if condition for height, 1 will trigger else condition for width
    int gridHeight = gridBorderBuilder(carArrHeight, 0);
    int gridWidth = gridBorderBuilder(carArrWidth, 1);

    // printf("\ngridHeight = %d, gridWidth = %d\n", gridHeight, gridWidth);

    // allocate memory for height of grid map
    char **mapToPrint = (char **)malloc(gridHeight * sizeof(char *));
    if (mapToPrint == NULL)
    {
        printf("die\n");
        exit(0);
    }
    for (int i = 0; i < gridHeight; i++)
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
    for (int i = 0; i < gridHeight; i++)
    {
        gridBuilder(mapToPrint[i], i, carArrWidth);
    }

    // just for printing an empty map
    // printf("Empty Map\n");
    // for (int i = gridHeight - 1; i >= 0; --i)
    // {
    //     printf("%s\n", mapToPrint[i]);
    // }
    // printf("\n\n");

    // initialise values to add into mapToPrint that was created
    int totalCoordinatesMoved = getTotalCoordinatesInMap(map);
    int heightCounter = 0, widthCounter = 0, tempY = 0, tempX = 0;

    for (int i = 0; i < totalCoordinatesMoved; i++)
    {
        int availPaths = map[i].paths >> 4;
        if (i == 0)
        {
            tempY = startPositionYOffset;
            tempX = startPositionXOffset;
            // where the car starts
            mapToPrint[tempY][tempX] = printStart;
        }
        else
        {
            // 2 and 4 same reason as explained when adding offset  to startPositionOffset
            tempY = (getToNextCellY * map[i].y) + startPositionYOffset;
            tempX = (getToNextCellX * map[i].x) + startPositionXOffset;
            // where the car moved
            if (mapToPrint[tempY][tempX] != printStart && mapToPrint[tempY][tempX] != printExplored)
                mapToPrint[tempY][tempX] = printExplored;
        }

        // check available paths and open up border
        // check up is avail
        if (availPaths & 1)
        {
            mapToPrint[tempY + removeBordersY][tempX] = ' ';
            addAvailPathToGridMap(mapToPrint, tempY + getToNextCellY, tempX, printAvail, printStart, printExplored);
        }
        // check down is avail
        if (availPaths & 4)
        {
            mapToPrint[tempY - removeBordersY][tempX] = ' ';
            addAvailPathToGridMap(mapToPrint, tempY - getToNextCellY, tempX, printAvail, printStart, printExplored);
        }
        // check right is avail
        if (availPaths & 2)
        {
            mapToPrint[tempY][tempX + removeBordersX] = ' ';
            addAvailPathToGridMap(mapToPrint, tempY, tempX + getToNextCellX, printAvail, printStart, printExplored);
        }
        // check left is avail
        if (availPaths & 8)
        {
            mapToPrint[tempY][tempX - removeBordersX] = ' ';
            addAvailPathToGridMap(mapToPrint, tempY, tempX - getToNextCellX, printAvail, printStart, printExplored);
        }
    }

    printf("Traversed Map\n");
    for (int i = gridHeight - 1; i >= 0; --i)
    {
        printf("%s\n", mapToPrint[i]);
    }
    printf("\n\n");

    for (int i = 0; i < gridHeight; i++)
    {
        free(mapToPrint[i]);
    }
    free(mapToPrint);
}
