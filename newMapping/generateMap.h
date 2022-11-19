#include <string.h>
#include "coordinate.h"

typedef struct printValues
{
    char start;
    char explored;
    char avail;
    char end;
} printValues;

typedef struct printOffsets
{
    int startPositionYOffset;
    int startPositionXOffset;
    int getToNextCellY;
    int getToNextCellX;
    int startPositionY;
    int startPositionX;
    int removeBordersY;
    int removeBordersX;
} printOffsets;

coordinate *getTestMap();

int gridBorderBuilder(int heightOrWidth, int heightOrWidthFlag);

char *gridStringConcat(char *printExplored, int arrayWidth, char *borderStr, char *borderStrToAdd);

char *gridBuilder(char *printExplored, int index, int arrayWidth);

int computeSizeOfMap(coordinate *map, int *arrayHeight, int *arrayWidth, printOffsets *offsetValue);

int addOffsetForGridMap(int startPositionOffset, int startPosition, int offset);

void addAvailPathToGridMap(char **mapToPrint, int tempY, int tempX, printValues *value);

// char **generateFullMap(coordinate *map, int *gridHeight);
// new stuff
void printFullMap(char **map, int gridHeight, char *mapName);

char **buildGridMap(coordinate *map, int *gridHeight, int *carArrHeight, int *carArrWidth, printOffsets *offsetValue);

void generateFullMap(coordinate *map, char **mapToPrint, int gridHeight, printValues *value, printOffsets *offsetValue);

void generateShortestPathMap(coordinate *shortestPathMap, coordinate *originalMap, char **mapToPrint, int gridHeight, printValues *value, printOffsets *offsetValue);

void cleanMap(int carArrHeight, int carArrWidth, char **mapToPrint, printOffsets *offsetValue, int gridHeight);

void getPrintedMap(coordinate *originalMap, coordinate *shortestPathMap);