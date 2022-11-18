#include "coordinate.h"
#include "map.h"
#include "movement.h"
#include "car.h"

int main(){
    coordinate * map = NULL;
    coordinate start = initStartingCoordinate();
    car Car = {start , 0};
    int movement = 1;
    int sensorArray[]= {0b011,0b001,0b001
    };
    for (int i = 0; i < 3; i++){
        
        coordinate* carC = &(Car.carCoordinate);
        int num1 = convertSensorDataToUnexploredPath(sensorArray[i],Car.orientation);
        int num2 = convertSensorDataToAvailPath(sensorArray[i],Car.orientation);
        // Update the sensor coordinate into the car.
        updateCoordinateAvailablePaths(carC, num1+(num2<<4));
        // Find out the next move.
        movement = getNextMove(carC);
        // Update the unexploredPath.
        updateUnexploredPath(carC,movement);
        // Update map.

        if(map != NULL){
            // Car moves Here
            /*
            
            */
            // Updae the XY coordinate.
            updateXYCoordinate(carC,movement);
            map = updateCoordinateToMap(map,*carC);
        }
        else{
            map = updateCoordinateToMap(map,*carC);
        }

        printCoordinate(*carC);
    }
    printf("\n");
    printMap(map);
    free(map);
}