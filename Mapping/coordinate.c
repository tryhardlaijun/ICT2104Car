#include "coordinate.h"

// Declare all variable as 0 but isLast is 1;
coordinate initStartingCoordinate(){
    coordinate startingCoordinate = {0,0,0,0,1,1};
    return startingCoordinate;
}

coordinate initEndingCoordinate(){
    coordinate endingCoordinate = {0,1,0,0,0,1};
    return endingCoordinate;
}

// Declare all variable to their respective fields
coordinate makeCoordinate(int x , int y, int pathAvail, int pathUnexplored, int nextOrientation, int isLast){
    // Declare all variable as 0 but isLast is 1;
    coordinate startingCoordinate = {x,y,pathAvail,pathUnexplored,nextOrientation,isLast};
    return startingCoordinate;
}

coordinate makeEndCoordinate(int x , int y, int pathAvail, int pathUnexplored, int nextOrientation, int isLast){
    // Declare all variable as 0 but isLast is 1;
    coordinate endingCoordinate = {x,y,pathAvail,pathUnexplored,nextOrientation,isLast};
    return endingCoordinate;
}


// Print out Coordinate data
void printCoordinate(coordinate c, int i){
    printf("%d, x is %d\ty is %d\tpathAvail is %d\tpathUnexplored is %d\tNext orientation is %d\tisLast is %d\t\n"
    ,i, c.x,c.y,c.pathAvail,
    c.pathUnexplored,c.nextOrientation,c.isLast);
}
// input the path into a coordinates unexplored and availalbe path.
int updateCoordinatePaths(coordinate* c , int path){
    c->pathUnexplored = path;
    c->pathAvail = path;
    if (c->pathUnexplored == 3) //
    {
        //printf("\nCan turn right here    ");
        return 1;
    }
    else{
        return 0;
    }
    
    //printf("\tpathUnexplored is %d\t\n" ,c->pathUnexplored);
}



