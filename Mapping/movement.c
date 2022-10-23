#include "movement.h"
#include "file.h"
#include "coordinate.h"

int main(){ 
    int* ptr = getNumOfLines();
    int count = 0;
    while(ptr[count] != 0 && count < 25 ){
        printf("%d\n", ptr[count]);
        nextMove();
        count++;
    }
}


int nextMove(CoordinateInfo coordinate){
    //remove all bits but the 2nd bit. (Check If front is open)
    if(coordinate.leftPath & 2){
        printf("Move Forward\n");
        coordinate.leftPath &= ~2;
    }
    //remove all bits but the 1st bit. (Check If right is open)
    else if(coordinate.leftPath & 1){
        printf("Move Right\n");
        coordinate.leftPath &= ~1;
    }
    //remove all bits but the 3rd bit. (Check If left is open)
    else if(coordinate.leftPath & 4){
        printf("Move Left\n");
        coordinate.leftPath &= ~4;
    }

    else{
        printf("Explored Or Dead End\n");
    }
}

