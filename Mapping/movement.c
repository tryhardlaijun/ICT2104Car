#include "movement.h"
#include "file.h"
#include "coordinate.h"

enum movement{YPlus, XPlus, YMinus, XMinus};

int nextMove(coordinate* c){
    //remove all bits but the 2nd bit. (Check If front is open)
    if(c->pathUnexplored & 2){
        printf("Move Forward\n");
        c->pathUnexplored &= ~2;
    }
    //remove all bits but the 1st bit. (Check If right is open)
    else if(c->pathUnexplored & 1){
        printf("Move Right\n");
        c->pathUnexplored &= ~1;
    }
    //remove all bits but the 3rd bit. (Check If left is open)
    else if(c->pathUnexplored & 4){
        printf("Move Left\n");
        c->pathUnexplored &= ~4;
    }
    // It is a dead end all bits are 0.
    else{
        printf("Explored Or Dead End\n");
        c->pathUnexplored = -1;
    }
    printf("%d \n", c->pathUnexplored);
    return c->pathUnexplored;
}


// int main(){ 
//     int* sensorArray = getSensorArrayFromText();
//     int max = getTotalLines();
//     for(int i = 0; i < max; i++){
//         nextMove(sensorArray[i]);
//     }
//     printf("Total size is %d", max);
// }

