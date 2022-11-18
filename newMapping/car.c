#include "car.h"

int turnNextOrientationRight(int nextOrientation){
    // If Vehicle facing Left from origin, then reset to 0 to indicate it is back to origin
    if(nextOrientation == 3){
        nextOrientation = 0;
    }
    // Increment
    else{
        nextOrientation += 1;
    }
    return nextOrientation;
}

int turnNextOrientationLeft(int nextOrientation){
    //If Vehicle is at origin already, then update to 3 to signal it is facing LEFT
    if(nextOrientation == 0){
        nextOrientation = 3;
    }
    // Decrement
    else{
        nextOrientation -= 1;
    }
    return nextOrientation;
}



int convertSensorDataToUnexploredPath(int num, int orientation){
    // Shift 3rd bit to 4th.
    num |= (num & 4) << 1;
    // Change bit to 3rd bit to 0.
    num &= ~4;
    // Bit shift until the orientation hits 0.
    if(orientation >= 0 && orientation < 4){
        while(orientation != 0){
            if(num & 1){
                num -= 1;
                num = num >> 1;
                num += 8;
            }
            else{
                num = num >> 1;
            }
            orientation = turnNextOrientationRight(orientation);
        }
    }
    return num;
    
}
int convertSensorDataToAvailPath(int num, int orientation){
    // Shift 3rd bit to 4th.
    num |= (num & 4) << 1;
    // Change bit to 3rd bit to 1.
    num |= 4;
    if(orientation >= 0 && orientation < 4){
        while(orientation != 0){
            if(num & 1){
                num -= 1;
                num = num >> 1;
                num += 8;
            }
            else{
                num = num >> 1;
            }
            orientation = turnNextOrientationRight(orientation);
        }
    }
    return num;
    
}
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


int ChangeOrientation(int orientCar, int orientMovement){
        while(orientCar != orientMovement){
            if(orientCar == 3 && orientMovement == 0){
                orientCar = turnNextOrientationRight(orientCar);
                printf("The vehicle has to turn right.\n");
            }
            else if(orientCar == 0 && orientMovement == 3){
                orientCar = turnNextOrientationLeft(orientCar);
                printf("The vehicle has to turn Left.\n");
            }
            else if(orientCar > orientMovement){
                orientCar = turnNextOrientationLeft(orientCar);
                printf("The vehicle has to turn Left.\n");
            }
            else{
                orientCar = turnNextOrientationRight(orientCar);
                printf("The vehicle has to turn right.\n");
            }
        }
        return orientMovement;
}

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



// int main(){
 
// }