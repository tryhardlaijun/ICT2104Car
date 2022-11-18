#include "coordinate.h"

enum movement{YPlus, XPlus, YMinus, XMinus};
enum turns{FORWARD, RIGHT, REVERSE, LEFT};

int updateUnexploredPath(coordinate* c, int bitPosition){
    if(bitPosition < 0 && bitPosition > 4)
        return -1;
    c->paths &= ~(1 << bitPosition);
    return c->paths;
}



int updateXYCoordinate(coordinate* currentCoordinate, int movedDirection){
    // update coordinate by checking if the vehicle turned in the previous
    switch (movedDirection)
    {
        //Increment Y coordinate relative to the previous
        case YPlus:
            currentCoordinate->y = (currentCoordinate->y) + 1;
            break;
        //Increment x coordinate relative to the previous
        case XPlus:
            currentCoordinate->x = (currentCoordinate->x) + 1;
            break;
        //Decrement Y coordinate relative to the previous
        case YMinus:
            currentCoordinate->y = currentCoordinate->y - 1;
            break;
        //Decrement X coordinate relative to the previous
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
    if(c->paths & (1<< FORWARD)){
        printf("Move Forward\n");
        return FORWARD;
    }
    //remove all bits but the 1st bit. (Check If right is open)
    else if(c->paths & (1 << RIGHT)){
        printf("Move Right\n");
        return RIGHT;
    }
    //remove all bits but the 3rd bit. (Check If left is open)
    else if(c->paths & (1 << LEFT)){
        printf("MOVE Left\n");
        return LEFT;
    }
    // It is a dead end all bits are 0.
    else if(c->paths & (1 << REVERSE)){
        printf("Reverse\n");
        //Car would turn around by turning right twice
        return REVERSE;
    }
    else{
        // DONT MOVE.
        printf("Don't Move\n");
        return -1;
    }
}
