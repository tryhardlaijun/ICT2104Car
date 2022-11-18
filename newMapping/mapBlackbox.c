#include "map.h"
coordinate* blackBoxUpdateToMap(){
    coordinate * map = NULL;
    coordinate c = initStartingCoordinate();
    map = updateCoordinateToMap(map,c);
    map = updateCoordinateToMap(map,c);
    map = updateCoordinateToMap(map,c);
    map = updateCoordinateToMap(map,c);
    map = updateCoordinateToMap(map,c);
    map = updateCoordinateToMap(map,c);
    printf("%d \n" , getTotalCoordinatesInMap(map));
    printMap(map);
    return map;
}

void blackBoxForFullyExplored(){
    coordinate* map = blackBoxUpdateToMap();
    // -1
    printf("%d\n", isMapFullyExplored(map));
    // -1
    map[2].paths |= (1<< 4);
    printf("%d\n", isMapFullyExplored(map));
    // 2
    map[3].paths |= 2;
    printf("%d\n", isMapFullyExplored(map));
}

void testFindCoordinateBasedOnXY(coordinate *test){
    if(test == NULL){
        printf("NULL \n");
    }
    else{
        printCoordinate(*test);
    }
}
void blackBoxTestFindXYCoordinate(){
        coordinate* map = blackBoxUpdateToMap();
    coordinate *test = findCoordinateBasedOnXY(map,1,1);
    // NULL
    testFindCoordinateBasedOnXY(test);
    //3
    map[3].x = 1;
    test = findCoordinateBasedOnXY(map,1,0);
    testFindCoordinateBasedOnXY(test);
    //4
    map[4].y = 1;
    map[4].x = 1;
    test = findCoordinateBasedOnXY(map,1,1);
    testFindCoordinateBasedOnXY(test);
    reset(&map);

}
// int main(){
// }

