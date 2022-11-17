#include "movement.h"
#include "file.h"
#include "coordinate.h"

enum movement
{
    YPlus,
    XPlus,
    YMinus,
    XMinus
};
enum turns
{
    FORWARD = 0,
    RIGHT = 1,
    LEFT = -1,
    REVERSE = -2
};

int updateUnexploredPath(coordinate *c)
{
    // reset the 2nd bit (Check If front is open)
    if (c->pathUnexplored & 2)
    {
        // Remove second bit from pathUnexplored
        c->pathUnexplored &= ~2;
    }
    // reset the 1st bit. (Check If right is open)
    else if (c->pathUnexplored & 1)
    {
        // Remove first bit from pathUnexplored
        c->pathUnexplored &= ~1;
    }
    // reset the 3rd bit. (Check If left is open)
    else if (c->pathUnexplored & 4)
    {
        // Remove third bit from pathUnexplored
        c->pathUnexplored &= ~4;
    }
    // It is a dead end all bits are 0.
    else
    {
        ;
    }
    return c->pathUnexplored;
}

int turnNextOrientationRight(int nextOrientation)
{
    // If Vehicle facing Left from origin, then reset to 0 to indicate it is back to origin
    if (nextOrientation == 3)
    {
        nextOrientation = 0;
    }
    // Increment
    else
    {
        nextOrientation += 1;
    }
    return nextOrientation;
}

int turnNextOrientationLeft(int nextOrientation)
{
    // If Vehicle is at origin already, then update to 3 to signal it is facing LEFT
    if (nextOrientation == 0)
    {
        nextOrientation = 3;
    }
    // Decrement
    else
    {
        nextOrientation -= 1;
    }
    return nextOrientation;
}

//To Delete
// //get movement according to original direction where the car is facing. 
// // 0 = Y+ || 1 = X+ || 2 = Y- || 3 = X-
// int getAbsoluteMovement(int coordinateOrientation , int nextMove){
//     //Previous Coordinate Turned Right.
//     if(nextMove == -1){
//         return turnNextOrientationLeft(coordinateOrientation);
//     }
//     //Previous Coordinate Turned Left.
//     else if(nextMove == 1){
//         return turnNextOrientationRight(coordinateOrientation);
//     }
//     // Previous Coordinate did not turn
//     else if (nextMove == 0)
//         return coordinateOrientation;
//     else
//         return -1;
// }




int updateXYCoordinate(coordinate* currentCoordinate){
    // update coordinate by checking if the vehicle turned in the previous
    switch (currentCoordinate->selfOrientation)
    {
    // Increment Y coordinate relative to the previous
    case YPlus:
        currentCoordinate->y = (currentCoordinate->y) + 1;
        break;
    // Increment x coordinate relative to the previous
    case XPlus:
        currentCoordinate->x = (currentCoordinate->x) + 1;
        break;
    // Decrement Y coordinate relative to the previous
    case YMinus:
        currentCoordinate->y = currentCoordinate->y - 1;
        break;
    // Decrement X coordinate relative to the previous
    case XMinus:
        currentCoordinate->x = currentCoordinate->x - 1;
        break;
    default:
        return -1;
    }
    return 1;
}

//Return direction.
int getNextMove(coordinate* c){
    //remove all bits but the 2nd bit. (Check If front is open)
    if(c->pathUnexplored & 2){
        c->nextOrientation = (c->selfOrientation);
        printf("Move Forward\n");
        return FORWARD;
    }
    // remove all bits but the 1st bit. (Check If right is open)
    else if (c->pathUnexplored & 1)
    {
        printf("Turn Right\n");
        // Update Orientation for the next coordinate
        c->nextOrientation = turnNextOrientationRight(c->selfOrientation);
        return RIGHT;
    }
    // remove all bits but the 3rd bit. (Check If left is open)
    else if (c->pathUnexplored & 4)
    {
        printf("Turn Left\n");
        // Update Orientation for the next coordinate
        c->nextOrientation = turnNextOrientationLeft(c->selfOrientation);
        return LEFT;
    }
    // It is a dead end all bits are 0.
    else
    {
        printf("Explored Or Dead End\n");
        // Car would turn around by turning right twice
        // zaf - shouldn't the orientation update like this
        c->selfOrientation = turnNextOrientationRight(c->selfOrientation);
        c->selfOrientation = turnNextOrientationRight(c->selfOrientation);
        c->nextOrientation = c->selfOrientation;
        // c->nextOrientation = turnNextOrientationRight(c->selfOrientation);
        // c->nextOrientation = turnNextOrientationRight(c->selfOrientation);
        return REVERSE;
    }
}

// int main(){
//     int* sensorArray = getSensorArrayFromText();
//     int max = getTotalLines();
//     for(int i = 0; i < max; i++){
//         nextMove(sensorArray[i]);
//     }
//     printf("Total size is %d", max);
// }
