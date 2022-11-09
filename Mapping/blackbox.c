#include "map.h"

void blackBoxUpdateLoop(){
    coordinate loopCoordinate = {0,0,7,7,0,0,1};
    coordinate previousCoordinate = {1,0,0,0,0,0,1};
    
    if(updateLoop(&loopCoordinate,&previousCoordinate)){
        printf("PASS");
    }
    else{
        printf("Fail");
    }
}

void blackBoxGetPreviousCoordinate(){
    coordinate testC = {1,0,7,7,0,3,1};
    coordinate previousCoordinate = {2,0,0,0,0,0,1};
    testC = getPreviousCoordinate(testC);
    if(checkIfCoordinateMatch(testC,previousCoordinate)){
        printf("PASS");
    }
    else{
        printf("Fail");
    }
}

