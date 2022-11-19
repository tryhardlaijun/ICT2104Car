#include "coordinate.h"

// Declare all variable as 0 but isLast is 1;
coordinate initStartingCoordinate(){
    coordinate startingCoordinate = {0,0,0,1};
    return startingCoordinate;
}

// Declare all variable to their respective fields
coordinate makeCoordinate(int x , int y, int paths, int isLast){
    // Declare all variable as 0 but isLast is 1;
    coordinate startingCoordinate = {x,y,paths,isLast};
    return startingCoordinate;
}

// Print out Coordinate data
void printCoordinate(coordinate c){
    printf("x is %d\ty is %d\tpaths availabe is %d\t path unexplored is %d\tisLast bit is %d\n"
    ,c.x,c.y,((c.paths & ~15) >> 4),(c.paths & 15),c.isLast);
}
// input the path into a coordinates unexplored and availalbe path.
// Front is 1st bit , Right is 2nd , Back is 3rd, Lef is 4th.
void updateCoordinateUnexploredPaths(coordinate* c , int path){
    if(path <= 15){
        //Clear first 4 bits
        c ->paths &= ~15;
        //Set bits according to path.
        c->paths |= path;
    }

}
void updateCoordinatePaths(coordinate* c , int paths){
    c -> paths = paths;
}
int checkIfCoordinateMatch(coordinate a, coordinate b){
    return (a.x == b.x && a.y == b.y);
}

// First var is src, second is dest
void replicateCoordinate(coordinate* src , coordinate* dest){
    dest -> x = src -> x;
    dest -> y = src -> y;
    dest -> isLast = src -> isLast;
    dest -> paths = src -> paths;
}

void availToExploredPath(coordinate*c){
    c->paths &= 240;
    c->paths |= ((c->paths & 240) >> 4);
}

void resetUnexploredPath(coordinate*c){
    c->paths &= ~15;
}


// int main(){
//     coordinate c ={0,0,192,1};
//     availToExploredPath(&c);
//     printCoordinate(c);
// }