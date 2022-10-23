#pragma once 

#include "movement.h"
#include "file.h"
#include "coordinate.h"

enum movement;
enum turns;


int updateUnexploredPath(coordinate* c);

int turnNextOrientationLeft(int orientation);

int turnNextOrientationRight(int orientation);

int getAbsoluteMovement(int coordinateOrientation , int nextMove);

int updateXYCoordinate(coordinate* ,coordinate* );

int getnextMove(coordinate* c);

