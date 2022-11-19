#include "movement.h"



int updateUnexploredPath(coordinate* c, int bitPosition){
    if(bitPosition < 0 && bitPosition > 4)
        return -1;
    c->paths &= ~(1 << bitPosition);
    return c->paths;
}



int updateXYCoordinate(coordinate* currentCoordinate, int movedDirection){
    // update coordinate by checking if the vehicle turned in the previous
    printf("CAR MOVE\n");
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

//Return direction. 0 = Forwred, 1 = Right, 2 = SOUTH , 3 = LEfT
int getNextMove(coordinate* c){
    int value = 0;
    //remove all bits but the 2nd bit. (Check If front is open)
    if(c->paths & (1<< NORTH)){
        
        value = NORTH;
    }
    //remove all bits but the 1st bit. (Check If right is open)
    else if(c->paths & (1 << EAST)){
        
        value = EAST;
    }
    //remove all bits but the 3rd bit. (Check If left is open)
    else if(c->paths & (1 << WEST)){
        
        value = WEST;
    }
    // It is a dead end all bits are 0.
    else if(c->paths & (1 << SOUTH)){
        
        //Car would turn around by turning right twice
        value = SOUTH;
    }
    else{
        // DONT MOVE.
        value = -1;
    }
    motorMove(value);
    return value;
}

void motorMove(int input){
    switch(input){
        case NORTH:
            printf("Move NORTH\n");
            break;
        case EAST:
            printf("Move EAST\n");
            break;
        case WEST:
            printf("MOVE WEST\n");
            break;
        case SOUTH:
            printf("MOVE SOUTH\n");
            break;
        default:
            printf("Don't Move\n");
            break;

    }
}