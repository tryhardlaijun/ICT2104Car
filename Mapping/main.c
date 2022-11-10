#include "map.h"

#include <string.h>

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
    // this function will compute the max size of the map by finding the maximum and minimum values of x and y
    int maxOfX = 1, minOfX = 0, tempMaxOfX = 0, tempMinOfX = 0;
    int maxOfY = 1, minOfY = 0, tempMaxOfY = 0, tempMinOfY = 0;
    int addedY = 0, addedX = 0;
    int toAddIntoRight = 0, toAddIntoLeft = 0;
    int totalCoordinates = getTotalCoordinatesInMap(map) + 1; // + 1 so that last coordinate is included in for loop

    for (int k = 0; k < totalCoordinates; k++)
    {
        // get max and min values
        if (map[k].y > maxOfY)
            maxOfY = map[k].y;
        else if (map[k].y < minOfY)
            minOfY = map[k].y;
        if (map[k].x > maxOfX)
            maxOfX = map[k].x;
        else if (map[k].x < minOfX)
            minOfX = map[k].x;
    }

    // set temp values
    tempMaxOfX = maxOfX;
    tempMaxOfY = maxOfY;
    tempMinOfX = minOfX;
    tempMinOfY = minOfY;
    for (int i = 0; i < totalCoordinates; i++)
    {
        int nextOrientation = map[i].nextOrientation;        // nextOrientation
        int currentOrientation = map[i - 1].nextOrientation; // currentOrientation
        if (i == 0)
        {
            currentOrientation = 0; // wherever the car is placed down, it should be at orientation 0
        }
        if (map[i].y == maxOfY)
        {
            toAddIntoRight = 0;
            toAddIntoLeft = 0;
            if (nextOrientation != currentOrientation)
            {
                addedY = 0;
            }
            if (currentOrientation == 1)
            {
                // if car is at orientation 1 ( ----> )
                // and y coordinate is at the max value
                // then, the only way to check and add height to this map is if there is an available path on the left side of orientation 1
                // if left path is available, we add one more row to the top of y
                toAddIntoLeft = 1;
            }
            if (currentOrientation == 3)
            {
                toAddIntoRight = 1;
            }

            if (map[i].pathAvail & 1 && toAddIntoRight && addedY == 0)
            {
                tempMaxOfY++;
                addedY = 1;
            }
            if (map[i].pathAvail & 4 && toAddIntoLeft && addedY == 0)
            {
                tempMaxOfY++;
                addedY = 1;
            }
        }

        if (map[i].x == maxOfX)
        {
            toAddIntoRight = 0;
            toAddIntoLeft = 0;

            if (nextOrientation != currentOrientation)
            {
                addedX = 0;
            }
            if (currentOrientation == 0)
            {
                toAddIntoRight = 1; // in this orientation, should add X only if there's a pathAvail right
            }
            if (currentOrientation == 2)
            {
                toAddIntoLeft = 1; // in this orientation, should add X only if there's a pathAvail left
            }

            if (map[i].pathAvail & 4 && toAddIntoLeft && addedX == 0)
            {
                tempMaxOfX++;
                addedX = 1;
            }
            if (map[i].pathAvail & 1 && toAddIntoRight && addedX == 0)
            {
                tempMaxOfX++;
                addedX = 1;
            }
        }
    }

    addedY = 0;
    addedX = 0;
    for (int i = 0; i < totalCoordinates; i++)
    {
        int nextOrientation = map[i].nextOrientation;
        int currentOrientation = map[i - 1].nextOrientation;
        if (i == 0)
        {
            currentOrientation = 0;
        }
        if (map[i].y == minOfY)
        {
            toAddIntoRight = 0;
            toAddIntoLeft = 0;
            if (nextOrientation != currentOrientation)
            {
                addedY = 0;
            }
            if (currentOrientation == 1)
            {
                toAddIntoRight = 1;
            }
            if (currentOrientation == 3)
            {
                toAddIntoLeft = 1;
            }

            if (map[i].pathAvail & 4 && toAddIntoLeft && addedY == 0)
            {
                tempMinOfY--;
                addedY = 1;
            }
            if (map[i].pathAvail & 1 && toAddIntoRight && addedY == 0)
            {
                tempMinOfY--;
                addedY = 1;
            }
        }

        if (map[i].x == minOfX)
        {
            toAddIntoRight = 0;
            toAddIntoLeft = 0;
            if (nextOrientation != currentOrientation)
            {
                addedX = 0;
            }
            if (currentOrientation == 0)
            { // if next orientation is 1 when y = minY
                toAddIntoLeft = 1;
            }
            if (currentOrientation == 2)
            { // if next orientation is 1 when y = minY
                toAddIntoRight = 1;
            }

            if (map[i].pathAvail & 4 && toAddIntoLeft && addedX == 0 && map[i].x - 1 < tempMinOfX)
            {
                tempMinOfX--;
                addedX = 1;
            }
            if (map[i].pathAvail & 1 && toAddIntoRight && addedX == 0 && map[i].x - 1 < tempMinOfX)
            {
                tempMinOfX--;
                addedX = 1;
            }
        }
    }

    *arrayHeight = 1 + (tempMaxOfY - tempMinOfY);
    *arrayWidth = 1 + (tempMaxOfX - tempMinOfX);
    *startPositionY = tempMinOfY * -1;
    *startPositionX = tempMinOfX * -1;

    return 0;
}

void generateMap(coordinate *map)
{
    int arrayHeight = 0, arrayWidth = 0, startPositionY = 0, startPositionX = 0;
    computeSizeOfMap(map, &arrayHeight, &arrayWidth, &startPositionY, &startPositionX);

    int startPositionXOffset = 2, startPositionYOffset = 1;

    if (startPositionX != 0)
    {
        for (int i = 0; i < startPositionX; i++)
        {
            startPositionXOffset += 4;
        }
    }

    if (startPositionY != 0)
    {
        for (int i = 0; i < startPositionY; i++)
        {
            startPositionYOffset += 2;
        }
    }

    int gridHeight = gridBorderBuilder(arrayHeight, 0);
    int gridWidth = gridBorderBuilder(arrayWidth, 1);

    char **stringList = (char **)malloc(gridHeight * sizeof(char *));
    if (stringList == NULL)
    {
        printf("die\n");
        exit(0);
    }
    for (int i = 0; i < gridHeight; i++)
    {
        stringList[i] = (char *)malloc(gridWidth + 1);
        if (stringList[i] == NULL)
        {
            printf("die\n");
            exit(0);
        }
    }

    for (int i = 0; i < gridHeight; i++)
    {
        char *oo = stringList[i];
        gridBuilder(stringList[i], i, arrayWidth);
        int yu = 9;
    }

    printf("Empty Map\n");
    for (int i = gridHeight - 1; i >= 0; --i)
    {
        printf("%s\n", stringList[i]);
    }
    printf("\n\n");

    int totalCoordinatesMoved = getTotalCoordinatesInMap(map) + 1;
    int heightCounter = 0;
    int widthCounter = 0;

    int tempY;
    int tempX;
    int tempYPrint0;
    int tempXPrint0;
    // TODO: plus 1 for now cause last sensedData is a loop and not recorded in map Yet.
    for (int i = 0; i < totalCoordinatesMoved; i++)
    {
        int nextOrientation = map[i].nextOrientation;
        int currentOrientation = map[i - 1].nextOrientation;
        // get previous tempX and tempY if not 0
        if (i != 0)
        {
            if (map[i].y > map[i - 1].y)
            {
                tempY = tempY + 1; // TODO: use constant variable
                // remove border in between
                stringList[tempY][tempX] = ' ';
            }
            else if (map[i].y < map[i - 1].y)
            {
                tempY = tempY - 1; // TODO: use constant variable
                // remove border in between
                stringList[tempY][tempX] = ' ';
            }
            else if (map[i].x > map[i - 1].x)
            {
                tempX = tempX + 2; // TODO: use constant variable
                // remove border in between
                stringList[tempY][tempX] = ' ';
            }
            else if (map[i].x < map[i - 1].x)
            {
                tempX = tempX - 2; // TODO: use constant variable
                // remove border in between
                stringList[tempY][tempX] = ' ';
            }
        }

        tempY = 0;
        if (i == 0)
            tempY = startPositionYOffset;
        else
        {
            if (map[i].y > map[i - 1].y)
                heightCounter += 2;
            else if (map[i].y < map[i - 1].y)
                heightCounter -= 2;
            tempY = startPositionYOffset + heightCounter;
        }

        tempX = 0;
        if (i == 0)
            tempX = startPositionXOffset;
        else
        {
            if (map[i].x > map[i - 1].x)
            {
                widthCounter += 4;
            }
            else if (map[i].x < map[i - 1].x)
                widthCounter -= 4;
            tempX = startPositionXOffset + widthCounter;
        }
        if (i == 0)
            stringList[tempY][tempX] = 's'; // where the car moved
        else
            stringList[tempY][tempX] = '1'; // where the car moved

        tempYPrint0 = tempY;
        tempXPrint0 = tempX;
        if (map[i].pathAvail & 4)
        {
            // add 0 for left
            if (nextOrientation == 0 || ((nextOrientation == 1 || nextOrientation == 3) && currentOrientation == 0)) // move to function
            {
                tempXPrint0 = tempX - 4;                        // TODO: use constant variable
                stringList[tempYPrint0][tempXPrint0 + 2] = ' '; // constant here is prev line constant / 2
            }
            else if (nextOrientation == 1 || ((nextOrientation == 0 || nextOrientation == 2) && currentOrientation == 1))
            {
                tempYPrint0 = tempY + 2; // TODO: use constant variable
                stringList[tempYPrint0 - 1][tempXPrint0] = ' ';
            }
            else if (nextOrientation == 2 || ((nextOrientation == 1 || nextOrientation == 3) && currentOrientation == 2))
            {
                tempXPrint0 = tempX + 4; // TODO: use constant variable
                stringList[tempYPrint0][tempXPrint0 - 2] = ' ';
            }
            else if (nextOrientation == 3 || ((nextOrientation == 0 || nextOrientation == 2) && currentOrientation == 3))
            {
                tempYPrint0 = tempY - 2; // TODO: use constant variable
                stringList[tempYPrint0 + 1][tempXPrint0] = ' ';
            }

            if (stringList[tempYPrint0][tempXPrint0] != 's' && stringList[tempYPrint0][tempXPrint0] != '1')
            {

                stringList[tempYPrint0][tempXPrint0] = '0';
            }
        }

        if (map[i].pathAvail & 1)
        {
            // add 0 for right
            if (nextOrientation == 0 || ((nextOrientation == 1 || nextOrientation == 3) && currentOrientation == 0))
            {
                tempXPrint0 = tempX + 4; // TODO: use variable
                stringList[tempYPrint0][tempXPrint0 - 2] = ' ';
            }
            else if (nextOrientation == 1 || ((nextOrientation == 0 || nextOrientation == 2) && currentOrientation == 1))
            {
                tempYPrint0 = tempY - 2; // TODO: use variable
                stringList[tempYPrint0 + 1][tempXPrint0] = ' ';
            }
            else if (nextOrientation == 2 || ((nextOrientation == 1 || nextOrientation == 3) && currentOrientation == 2))
            {
                tempXPrint0 = tempX - 4; // TODO: use variable
                stringList[tempYPrint0][tempXPrint0 + 2] = ' ';
            }
            else if (nextOrientation == 3 || ((nextOrientation == 0 || nextOrientation == 2) && currentOrientation == 3))
            {
                tempYPrint0 = tempY + 2; // TODO: use variable
                stringList[tempYPrint0 - 1][tempXPrint0] = ' ';
            }
            if (stringList[tempYPrint0][tempXPrint0] != 's' && stringList[tempYPrint0][tempXPrint0] != '1')
            {

                stringList[tempYPrint0][tempXPrint0] = '0';
            }
        }
    }

    printf("Traversed Map\n");
    for (int i = gridHeight - 1; i >= 0; --i)
    {
        printf("%s\n", stringList[i]);
    }
    printf("\n\n");

    // for (int i=0; i<gridHeight; i++) {
    //     free(stringList[i]);
    // }
    free(stringList);
}

int main()
{
    coordinate *map = NULL;
    coordinate *unexploredCoordinates = NULL;
    int totalLines = getTotalLines();
    int *sensorArray = getSensorArrayFromText();
    for (int i = 0; i < totalLines; i++)
    {
        // If at the very beginning.
        if (map == NULL)
        {
            map = updateCoordinateToMap(map, initStartingCoordinate());
            updateCoordinatePaths(map, sensorArray[0]);
            getnextMove(map);
        }
        else
        {
            // get size of Map
            int lastPosition = getTotalCoordinatesInMap(map);
            // Replicate a coordinate like the previous map
            coordinate c = replicateLastPosition(map);
            // Update current path
            updateCoordinatePaths(&c, sensorArray[i]);
            // Update Orientation
            getnextMove(&c);
            // Update where the current coordinate is
            updateXYCoordinate(&map[lastPosition], &c);
            // Update Unexplored Path for current path // zaf: previous
            int pathRemain = updateUnexploredPath(&map[lastPosition]);
            // Check if next coordinate has already been explored
            int isExplored = checkIfAlreadyInMap(map, c);
            // Check if map has been explored
            if (isExplored == -1)
            {
                // Unexplored
                // Naomi's Code to go to the unexplored spot
                // Add current coordinate to map if unexplored
                map = updateCoordinateToMap(map, c);
            }
            else
            { // Explored
                // Check if in unexploredArray
                int getUnexploredPosition = checkIfAlreadyInMap(unexploredCoordinates, c);
                if (getUnexploredPosition != -1)
                {
                    unexploredCoordinates[getUnexploredPosition] = c;
                }
            }
            if (pathRemain != 0)
            { // zaf: previous coordinate?
                unexploredCoordinates = updateCoordinateToMap(unexploredCoordinates, map[lastPosition]);
            }
        }
    }

    printf("\n");
    printMap(map);
    printf("\n");
    printMap(unexploredCoordinates);
    printf("\n");

    generateMap(map);
}