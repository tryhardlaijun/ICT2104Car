#include "car.h"

void testTurning(){
    ChangeOrientation(1,3);
    printf("\n");
    ChangeOrientation(0,3);
    printf("\n");
    ChangeOrientation(3,0);
    printf("\n");
    ChangeOrientation(1,2);
    printf("\n");
    ChangeOrientation(1,3);
    printf("\n");
    ChangeOrientation(3,2);
    printf("\n");
}
//
void testDataConversion(){
    //3
    int x = convertSensorDataToUnexploredPath(6,0);
    printf("%d\n", x);
    //6
    x = convertSensorDataToUnexploredPath(6,1);
    printf("%d\n", x);
    //12
    x = convertSensorDataToUnexploredPath(6,2);
    printf("%d\n", x);
    //9
    x = convertSensorDataToUnexploredPath(6,3);
    printf("%d\n", x);

    //7
    x = convertSensorDataToAvailPath(6,0);
    printf("%d\n", x);
    //14
    x = convertSensorDataToAvailPath(6,1);
    printf("%d\n", x);
    //13
    x = convertSensorDataToAvailPath(6,2);
    printf("%d\n", x);
    //11
    x = convertSensorDataToAvailPath(3,3);
    printf("%d\n", x);
    
    
    // //15
    // x = convertSensorDataToAbsouluteBits(7,2);
    // printf("%d\n", x);
    // //5
    // x = convertSensorDataToAbsouluteBits(1,2);
    // printf("%d\n", x);
    // //2
    // x = convertSensorDataToAbsouluteBits(2,2);
    // printf("%d\n", x);
    // x = convertSensorDataToAbsouluteBits(3,3);
    // printf("%d\n", x);
    // x = convertSensorDataToAbsouluteBits(5,3);
    // printf("%d\n", x);
    // x = convertSensorDataToAbsouluteBits(6,4);
    // printf("%d\n", x);
}
