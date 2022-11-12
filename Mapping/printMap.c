#include "printMap.h"
#include "map.h"
#include "movement.h"
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
    int addedY = 0, addedX = 0;                               // used for checking
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
            // if car is at orientation 3 ( <----- )
            // and y coordinate is at the max value
            // then, the only way to check and add height to this map is if there is an available path on the right side of orientation 3
            // if right path is available, we add one more row to the top of y
            if (map[i].pathAvail & 1 && currentOrientation == 3 && addedY == 0)
            {
                tempMaxOfY++;
                addedY = 1;
            }
            if (map[i].pathAvail & 4 && currentOrientation == 1 && addedY == 0)
            {
                tempMaxOfY++;
                addedY = 1;
            }
        }

        if (map[i].x == maxOfX)
        {
            if (map[i].pathAvail & 4 && currentOrientation == 2 && addedX == 0)
            {
                tempMaxOfX++;
                addedX = 1;
            }
            if (map[i].pathAvail & 1 && currentOrientation == 0 && addedX == 0)
            {
                tempMaxOfX++;
                addedX = 1;
            }
        }
    }
    // reset checking values
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
            // if car is at orientation 3 ( <----- )
            // and y coordinate is at the min value
            // then, the only way to check and add height to this map is if there is an available path on the left side of orientation 3
            // if left path is available, we add one more row to the bottom of y
            if (map[i].pathAvail & 4 && currentOrientation == 3 && addedY == 0)
            {
                tempMinOfY--;
                addedY = 1;
            }
            if (map[i].pathAvail & 1 && currentOrientation == 1 && addedY == 0)
            {
                tempMinOfY--;
                addedY = 1;
            }
        }

        if (map[i].x == minOfX)
        {
            if (map[i].pathAvail & 4 && currentOrientation == 0 && addedX == 0)
            {
                tempMinOfX--;
                addedX = 1;
            }
            if (map[i].pathAvail & 1 && currentOrientation == 2 && addedX == 0)
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

    // add offset because of the borders
    int startPositionXOffset = 2, startPositionYOffset = 1;

    if (startPositionX != 0)
    {
        for (int i = 0; i < startPositionX; i++)
        {
            // add 4 because of the borders, until start position is found
            startPositionXOffset += 4;
        }
    }

    if (startPositionY != 0)
    {
        for (int i = 0; i < startPositionY; i++)
        {
            // add 2 because of the borders, until start position is found
            startPositionYOffset += 2;
        }
    }

    // to build empty map
    int gridHeight = gridBorderBuilder(arrayHeight, 0);
    int gridWidth = gridBorderBuilder(arrayWidth, 1);

    // allocate memory for height of map
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

    for (int i = 0; i < gridHeight; i++)
    {
        // at each row of mapToPrint array, add borders around and inside map
        gridBuilder(mapToPrint[i], i, arrayWidth);
    }

    // just for printing an empty map
    printf("Empty Map\n");
    for (int i = gridHeight - 1; i >= 0; --i)
    {
        printf("%s\n", mapToPrint[i]);
    }
    printf("\n\n");

    // initialise values to add into mapToPrint that was created
    int totalCoordinatesMoved = getTotalCoordinatesInMap(map) + 1;
    int heightCounter = 0;
    int widthCounter = 0;

    int tempY;
    int tempX;
    int tempYPrint0;
    int tempXPrint0;

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
                mapToPrint[tempY][tempX] = ' ';
            }
            else if (map[i].y < map[i - 1].y)
            {
                tempY = tempY - 1; // TODO: use constant variable
                // remove border in between
                mapToPrint[tempY][tempX] = ' ';
            }
            else if (map[i].x > map[i - 1].x)
            {
                tempX = tempX + 2; // TODO: use constant variable
                // remove border in between
                mapToPrint[tempY][tempX] = ' ';
            }
            else if (map[i].x < map[i - 1].x)
            {
                tempX = tempX - 2; // TODO: use constant variable
                // remove border in between
                mapToPrint[tempY][tempX] = ' ';
            }
        }

        // get current coordinate y with offset to fit into mapToPrint that has borders
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

        // get current coordinate y with offset to fit into mapToPrint that has borders
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

        // set value in mapToPrint
        if (i == 0)
            mapToPrint[tempY][tempX] = 's'; // where the car moved
        else
            mapToPrint[tempY][tempX] = '1'; // where the car moved

        // prepare to check for available path from where current coordinate is, based on orientation
        tempYPrint0 = tempY;
        tempXPrint0 = tempX;
        if (map[i].pathAvail & 4)
        {
            // add 0 for left
            if (nextOrientation == 0 || ((nextOrientation == 1 || nextOrientation == 3) && currentOrientation == 0)) // move to function
            {
                tempXPrint0 = tempX - 4;                        // TODO: use constant variable
                mapToPrint[tempYPrint0][tempXPrint0 + 2] = ' '; // constant here is prev line constant / 2
            }
            else if (nextOrientation == 1 || ((nextOrientation == 0 || nextOrientation == 2) && currentOrientation == 1))
            {
                tempYPrint0 = tempY + 2; // TODO: use constant variable
                mapToPrint[tempYPrint0 - 1][tempXPrint0] = ' ';
            }
            else if (nextOrientation == 2 || ((nextOrientation == 1 || nextOrientation == 3) && currentOrientation == 2))
            {
                tempXPrint0 = tempX + 4; // TODO: use constant variable
                mapToPrint[tempYPrint0][tempXPrint0 - 2] = ' ';
            }
            else if (nextOrientation == 3 || ((nextOrientation == 0 || nextOrientation == 2) && currentOrientation == 3))
            {
                tempYPrint0 = tempY - 2; // TODO: use constant variable
                mapToPrint[tempYPrint0 + 1][tempXPrint0] = ' ';
            }

            if (mapToPrint[tempYPrint0][tempXPrint0] != 's' && mapToPrint[tempYPrint0][tempXPrint0] != '1')
            {

                mapToPrint[tempYPrint0][tempXPrint0] = '0';
            }
        }

        if (map[i].pathAvail & 1)
        {
            // add 0 for right
            if (nextOrientation == 0 || ((nextOrientation == 1 || nextOrientation == 3) && currentOrientation == 0))
            {
                tempXPrint0 = tempX + 4; // TODO: use variable
                mapToPrint[tempYPrint0][tempXPrint0 - 2] = ' ';
            }
            else if (nextOrientation == 1 || ((nextOrientation == 0 || nextOrientation == 2) && currentOrientation == 1))
            {
                tempYPrint0 = tempY - 2; // TODO: use variable
                mapToPrint[tempYPrint0 + 1][tempXPrint0] = ' ';
            }
            else if (nextOrientation == 2 || ((nextOrientation == 1 || nextOrientation == 3) && currentOrientation == 2))
            {
                tempXPrint0 = tempX - 4; // TODO: use variable
                mapToPrint[tempYPrint0][tempXPrint0 + 2] = ' ';
            }
            else if (nextOrientation == 3 || ((nextOrientation == 0 || nextOrientation == 2) && currentOrientation == 3))
            {
                tempYPrint0 = tempY + 2; // TODO: use variable
                mapToPrint[tempYPrint0 - 1][tempXPrint0] = ' ';
            }
            if (mapToPrint[tempYPrint0][tempXPrint0] != 's' && mapToPrint[tempYPrint0][tempXPrint0] != '1')
            {

                mapToPrint[tempYPrint0][tempXPrint0] = '0';
            }
        }
    }

    printf("Traversed Map\n");
    for (int i = gridHeight - 1; i >= 0; --i)
    {
        printf("%s\n", mapToPrint[i]);
    }
    printf("\n\n");

    // for (int i=0; i<gridHeight; i++) {
    //     free(stringList[i]);
    // }
    free(mapToPrint);
}