#pragma once 

#include "movement.h"
#include "file.h"
#include "coordinate.h"

enum movement;
enum turns;


int updatePreviousCoordinate(coordinate* c);

int turnOrientationRight(int orientation);

int turnOrientationLeft(int orientation);

int getAbsoluteMovement(int coordinateOrientation , int nextMove);

int updateXYCoordinate(coordinate* c);

int getnextMove(coordinate* c);

