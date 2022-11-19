#include <string.h>
#include "coordinate.h"

typedef struct printValues
{
    char start;
    char explored;
    char avail;
    char end;
} printValues;

coordinate *getTestMap();

int gridBorderBuilder(int heightOrWidth, int heightOrWidthFlag);

char *gridStringConcat(char *printExplored, int arrayWidth, char *borderStr, char *borderStrToAdd);

char *gridBuilder(char *printExplored, int index, int arrayWidth);

int computeSizeOfMap(coordinate *map, int *arrayHeight, int *arrayWidth, int *startPositionY, int *startPositionX);

int addOffsetForGridMap(int startPositionOffset, int startPosition, int offset);

void addAvailPathToGridMap(char **mapToPrint, int tempY, int tempX, printValues *value);

// char **generateFullMap(coordinate *map, int *gridHeight);
// new stuff
void printFullMap(char **map, int gridHeight);

char **buildGridMap(coordinate *map, int *gridHeight, int *startPositionY, int *startPositionX);

void generateFullMap(coordinate *map, char **mapToPrint, int gridHeight, printValues *value, int startPositionY, int startPositionX);
