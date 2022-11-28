
#include "coordinate.h"
#include "mainBlackBox.h"

void testWithNegXandYSensorArray(int *buff, int count) {
    int testSensorArray[] = {0b001, 0b001, 0b010, 0b101,
                            0b100, 0b001, 0b100, 
                            0b001, 0b001, 0b001, 0b100,
                            0b001, 0b101,
                            0b000,
                            0b001, 0b100, 
                            0b001, 0b001, 0b100,};
                            
    for (int i=0;i<count;i++) {
        buff[i] = testSensorArray[i];
    }
}

coordinate testWithNegXandYStartCoord() {
    coordinate testStart = {0,0,0,0};
    return testStart;
}

coordinate testWithNegXandYEndCoord() {
    coordinate testEnd = {1,0,0,0};
    return testEnd;
}