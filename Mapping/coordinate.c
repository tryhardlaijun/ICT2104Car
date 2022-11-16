#include "coordinate.h"

// Declare all variable as 0 but isLast is 1;
coordinate initStartingCoordinate(){
    coordinate startingCoordinate = {0,0,0,0,0,0,1,1};
    return startingCoordinate;
}

// Declare all variable to their respective fields
coordinate makeCoordinate(int x , int y, int pathAvail, int pathUnexplored, int nextOrientation, int isLast){
    // Declare all variable as 0 but isLast is 1;
    coordinate startingCoordinate = {x,y,pathAvail,pathUnexplored,nextOrientation,isLast};
    return startingCoordinate;
}

// Print out Coordinate data
void printCoordinate(coordinate c){
    printf("x is %d\ty is %d\tpathAvail is %d\tpathUnexplored is %d\tNext orientation is %d\tSelf Orientation is %d\tisLast is %d\tIsReversible is %d\t\n"
    ,c.x,c.y,c.pathAvail,
    c.pathUnexplored,c.nextOrientation,c.selfOrientation,c.isLast,c.isReversible);
}
// input the path into a coordinates unexplored and availalbe path.
void updateCoordinatePaths(coordinate* c , int path){
    c->pathUnexplored = path;
    c->pathAvail = path;
}

int checkIfCoordinateMatch(coordinate a, coordinate b){
    return (a.x == b.x && a.y == b.y);
}

// First var is src, second is dest
void replicateCoordinate(coordinate* src , coordinate* dest){
    dest -> isLast = src -> isLast;
    dest -> nextOrientation = src -> nextOrientation;
    dest -> pathAvail = src -> pathAvail;
    dest -> pathUnexplored = src -> pathUnexplored;
    dest -> selfOrientation = src -> selfOrientation;
    dest -> x = src -> x;
    dest -> y = src -> y;
}