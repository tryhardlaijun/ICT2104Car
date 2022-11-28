#include "car.h"

// Simualate turn left and update orienation
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
// Simualate turn left and update orienation
int turnNextOrientationLeft(int nextOrientation){
    //If Vehicle is at origin already, then update to 3 to signal it is facing WEST
    if(nextOrientation == 0){
        nextOrientation = 3;
    }
    // Decrement
    else{
        nextOrientation -= 1;
    }
    return nextOrientation;
}
//Change sensed Data into Absolute data.
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
//Change sensed Data into Absolute data.
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
//update Car orientation. Insert Motor Code here
int ChangeOrientation(int orientCar, int orientMovement){
    
    if(orientMovement >= 0 && orientMovement <= 4){         
         while(orientCar != orientMovement){
            if(orientCar == 3 && orientMovement == 0){
                orientCar = turnNextOrientationRight(orientCar);
                printf("Motor Turn right.\n");
            }
            else if(orientCar == 0 && orientMovement == 3){
                orientCar = turnNextOrientationLeft(orientCar);
                printf("Motor Turn Left.\n");
            }
            else if(orientCar > orientMovement){
                orientCar = turnNextOrientationLeft(orientCar);
                printf("Motor Turn Left.\n");
            }
            else{
                orientCar = turnNextOrientationRight(orientCar);
                printf("Motor Turn right.\n");
            }
        }   
       
    }
    else{
        printf("DEAD END\n");
    }
    return orientMovement;
}

void modifyOrientation(car* Car){
    int movement = getNextMove(&(Car->carCoordinate));
    if (movement != Car->orientation)
    {
        Car->orientation = ChangeOrientation(Car->orientation, movement);
    }
}
//
void moveCarAccordingToPath(coordinate* path, car * Car){
    int lastPosition = getTotalCoordinatesInMap(path);
    for(int i = 0; i < lastPosition; i++){
        // The orientation the car has to be to move.
        int orientation = getOrientationFromTwoAdjacentCoordinate(&(Car->carCoordinate),&(path[i]));
        if(!checkIfCoordinateMatch(path[i],Car->carCoordinate)){
            
            Car->orientation = ChangeOrientation(Car->orientation, orientation);
            // MOTOR MOVEEE!!!
            Car->carCoordinate.x = path[i].x;
            Car->carCoordinate.y = path[i].y;
            motorMove(orientation);
        }
    }

}


// int main(){
 
// }