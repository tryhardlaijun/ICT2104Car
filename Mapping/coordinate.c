#include "coordinate.h"

// Declare all variable as 0 but isLast is 1;
coordinate initStartingCoordinate(){
    coordinate startingCoordinate = {0,0,0,0,0,1};
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
    printf("x is %d\ty is %d\tpathAvail is %d\tpathUnexplored is %d\tNext orientation is %d\tisLast is %d\t\n"
    ,c.x,c.y,c.pathAvail,
    c.pathUnexplored,c.nextOrientation,c.isLast);
}
// input the path into a coordinates unexplored and availalbe path.
void updateCoordinatePaths(coordinate* c , int path){
    c->pathUnexplored = path;
    c->pathAvail = path;
}