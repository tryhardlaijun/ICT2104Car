#include <string.h>
#include "coordinate.h"

coordinate *getTestMap();

int gridBorderBuilder(int heightOrWidth, int heightOrWidthFlag);

char *gridStringConcat(char *printExplored, int arrayWidth, char *borderStr, char *borderStrToAdd);

char *gridBuilder(char *printExplored, int index, int arrayWidth);

int computeSizeOfMap(coordinate *map, int *arrayHeight, int *arrayWidth, int *startPositionY, int *startPositionX);

int addOffsetForGridMap(int startPositionOffset, int startPosition, int offset);

void addAvailPathToGridMap(char **mapToPrint, int tempY, int tempX, char printAvail, char printStart, char printExplored);

void generateMap(coordinate *map);
