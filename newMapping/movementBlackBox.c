#include "movement.h"

void blackBoxUpdateUnexplored(){
    coordinate c = {0,0,((3 << 4) + 3),1};
    // 3
    updateUnexploredPath(&c,6);
    printCoordinate(c);
    // 3
    updateUnexploredPath(&c,2);
    printCoordinate(c);
    // 2
    updateUnexploredPath(&c,0);
    printCoordinate(c);
    //0
    updateUnexploredPath(&c,1);
    printCoordinate(c);
}

void blackBoxTestForTurning(){
        int x = 0;
    x = turnNextOrientationRight(x);
    printf("%d\n",x);
    x = turnNextOrientationRight(x);
    printf("%d\n",x);
    x = turnNextOrientationRight(x);
    printf("%d\n",x);
    x = turnNextOrientationRight(x);
    printf("%d\n",x);
    x = turnNextOrientationRight(x);
    printf("%d END Right\n",x);
    // Left
    x = 0;
    printf("%d\n",x);
    x = turnNextOrientationLeft(x);
    printf("%d\n",x);
    x = turnNextOrientationLeft(x);
    printf("%d\n",x);
    x = turnNextOrientationLeft(x);
    printf("%d\n",x);
    x = turnNextOrientationLeft(x);
    printf("%d\n",x);
    x = turnNextOrientationLeft(x);
    printf("%d END WEST\n",x);
}
void testUpdateCoordinate(){
    coordinate c = {0,0,((3 << 4) + 3),1};
    printCoordinate(c);
    updateXYCoordinate(&c,0);
    printCoordinate(c);
    updateXYCoordinate(&c,1);
    printCoordinate(c);
    updateXYCoordinate(&c,2);
    printCoordinate(c);
    updateXYCoordinate(&c,3);
    printCoordinate(c);
    updateXYCoordinate(&c,0);
    printCoordinate(c);
}

void blackBoxFunctionalityTest(coordinate c){
    int movement = getNextMove(&c);
    updateUnexploredPath(&c,movement);
    updateXYCoordinate(&c,movement);
    printf("%d\n", movement);
    printCoordinate(c);
     movement = getNextMove(&c);
    updateUnexploredPath(&c,movement);
    updateXYCoordinate(&c,movement);
    printf("%d\n", movement); 
    printCoordinate(c);
     movement = getNextMove(&c);
    updateUnexploredPath(&c,movement);
    updateXYCoordinate(&c,movement);
    printf("%d\n", movement);
    printCoordinate(c);
     movement = getNextMove(&c);
    updateUnexploredPath(&c,movement);
    updateXYCoordinate(&c,movement);
    printf("%d\n", movement);
    printCoordinate(c);
}

// int main(){
//     coordinate c = {0,0,((14 << 4)+ 14),1};
//     blackBoxFunctionalityTest(c);
// }