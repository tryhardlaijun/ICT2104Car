#include "movement.h"
#include "file.h"
#include "coordinate.h"

enum movement{YPlus, XPlus, YMinus, XMinus};
enum turns{FORWARD = 0 , RIGHT = 1 , LEFT = -1};

int updatePreviousCoordinate(coordinate* c){
    //remove all bits but the 2nd bit. (Check If front is open)
    if(c->pathUnexplored & 2){
        printf("Move Forward\n");
        //Remove second bit from pathUnexplored
        c->pathUnexplored &= ~2;
    }
    //remove all bits but the 1st bit. (Check If right is open)
    else if(c->pathUnexplored & 1){
        printf("Turn Right\n");
        c->orientation = turnOrientationRight(c->orientation);
        //Remove first bit from pathUnexplored
        c->pathUnexplored &= ~1;
    }
    //remove all bits but the 3rd bit. (Check If left is open)
    else if(c->pathUnexplored & 4){
        printf("Turn Left\n");
        c->orientation = turnOrientationLeft(c->orientation);
        //Remove third bit from pathUnexplored
        c->pathUnexplored &= ~4;
    }
    // It is a dead end all bits are 0.
    else{
        printf("Explored Or Dead End\n");
    }
    printf("%d \n", c->pathUnexplored);
    return c->pathUnexplored;
}

int turnOrientationRight(int orientation){
    // If Vehicle facing Left from origin, then reset to 0 to indicate it is back to origin
    if(orientation == 3){
        orientation = 0;
    }
    // Increment
    else{
        orientation += 1;
    }
    return orientation;
}

int turnOrientationLeft(int orientation){
    //If Vehicle is at origin already, then update to 3 to signal it is facing LEFT
    if(orientation == 0){
        orientation = 3;
    }
    // Decrement
    else{
        orientation -= 1;
    }
    return orientation;
}
int getAbsoluteMovement(int coordinateOrientation , int nextMove){
    //Turning Left
    if(nextMove == -1){
        return turnOrientationLeft(coordinateOrientation);
    }
    //Turn right
    else if(nextMove == 1){
        return turnOrientationRight(coordinateOrientation);
    }
    else if (nextMove == 0)
        return coordinateOrientation;
    else
        return -1;
}
int updateXYCoordinate(coordinate* c){
    //Orientation (Facing which direction from the origin)
    int coordinateOrientation = c->orientation;
    // Get direction the car is turned. 1 = right 0=forward -1=Left
    int nextMove = getnextMove(c);
    //Orientation
    int absouluteMovement = getAbsoluteMovement(coordinateOrientation,nextMove);
    switch (absouluteMovement)
    {
        case YPlus:
        c->y += 1;
        break;
        case XPlus:
        c->x += 1;
        break;
        case YMinus:
        c->y -= 1;
        break;
        case XMinus:
        c->x -= 1;
        break;
        default:
            return -1;
        return 1;
    }
}
int getnextMove(coordinate* c){
    //remove all bits but the 2nd bit. (Check If front is open)
    if(c->pathUnexplored & 2){
        printf("Move Forward\n");
        return FORWARD;
    }
    //remove all bits but the 1st bit. (Check If right is open)
    else if(c->pathUnexplored & 1){
        printf("Turn Right\n");
        return RIGHT;
    }
    //remove all bits but the 3rd bit. (Check If left is open)
    else if(c->pathUnexplored & 4){
        printf("Turn Left\n");
        return LEFT;
    }
    // It is a dead end all bits are 0.
    else{
        printf("Explored Or Dead End\n");
        return -2;
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

