#pragma once 

#include <string.h>
#include "movement.h"

int gridBorderBuilder(int heightOrWidth, int heightOrWidthFlag);

char *gridStringConcat(char *printExplored, int arrayWidth, char *borderStr, char *borderStrToAdd, int strLen);

char *gridBuilder(char *printExplored, int index, int arrayWidth);

int computeSizeOfMap(coordinate *map, int *arrayHeight, int *arrayWidth, int *startPositionY, int *startPositionX);

void generateMap(coordinate *map);

