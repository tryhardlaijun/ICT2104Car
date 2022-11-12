#include "map.h"

void blackBoxUpdateLoop(){
    coordinate loopCoordinate = {0,0,7,7,0,0,1};
    coordinate currentCoordinate = {1,0,0,0,0,0,1};
    
    if(updateLoop(&loopCoordinate,&currentCoordinate)){
        printf("PASS");
    }
    else{
        printf("Fail");
    }
}

void blackBoxgetPreviousCoordinate(){
    coordinate testC = {1,0,7,7,0,3,1};
    coordinate currentCoordinate = {2,0,0,0,0,0,1};
    testC = getPreviousCoordinate(testC);
    if(checkIfCoordinateMatch(testC,currentCoordinate)){
        printf("PASS");
    }
    else{
        printf("Fail");
    }
}

