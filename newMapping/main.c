#include "coordinate.h"
#include "map.h"
#include "movement.h"
#include "car.h"
#include "generateMap.h"
#include "breatheFirstSearch.h"



coordinate * senseCoordinateAndAddToMap (coordinate* map, car *Car, int sensedData, coordinate* carC){
    int unexplorePath = convertSensorDataToUnexploredPath(sensedData,Car->orientation);
    int availablePath = convertSensorDataToAvailPath(sensedData,Car->orientation);

    // Update the sensor coordinate into the car.
    updateCoordinatePaths(carC, unexplorePath + (availablePath << 4));
    // Find out the next move.
    if(map== NULL){
        carC->paths &= ~(4 << 4);
    }
    //
    int movement = getNextMove(carC);
    if (movement != Car->orientation)
    {
        Car->orientation = ChangeOrientation(Car->orientation, movement);
    }
    // Update the unexploredPath.
    updateUnexploredPath(carC, Car->orientation);
    // Update map.
    // Car moves Here
    /*

    */
    // Updae the XY coordinate.
    map = updateCoordinateToMap(map, *carC);
    return map;
}
coordinate* exploreMap(coordinate* map, car* Car, int sensedData){
    int loopPosition = -1;
    coordinate* carC = &(Car->carCoordinate);
    if (map != NULL)
    {
        // Temp variable for carC
        coordinate tmp = *carC;
        // If code reach here means it has already reach the location.
        updateXYCoordinate(&tmp, Car->orientation);
        // -1 if not looped
        loopPosition = checkIfAlreadyInMap(map, tmp);
        
        if (loopPosition != -1 )
        {
            printf("LOOPED\n");
            updateLoop(&map[loopPosition], carC);
            // If fully explore return map
            if(isMapFullyExplored(map) == -1){
                printf("MAP FULLY EXPLORED");
                return map;
            }
            coordinate * shortestPath = findShortestPathInMap(map,tmp);
            
            test(shortestPath,Car);
            coordinate *mapCoordinate = (findCoordinateBasedOnXY(map,carC->x,carC->y));
            *carC = *mapCoordinate;
            int movement = getNextMove(carC);
            if (movement != Car->orientation)
            {
                Car->orientation = ChangeOrientation(Car->orientation, movement);
            }
            updateUnexploredPath(carC,Car->orientation);
            *mapCoordinate = *carC;
            reset(&shortestPath);
        }
        else{
            *carC = tmp;
        }

    }

    // If not looped and freshly init, then update data.
    if(map != NULL && loopPosition != -1){

    }
    else{
        map = senseCoordinateAndAddToMap(map,Car, sensedData, carC);
    }
    printCoordinate(*carC);
    return map;
}


int main()
{
    coordinate *map = NULL;
    // init
    coordinate start = initStartingCoordinate();
    car Car = {start, 0};

    int sensorArray[]= {0b111,0b001,0b001,0b010, 0b011, 
                        0b011,0b001,0b010,0b001,0b011,
                        0b001,0b001,0b010,0b001,0b001,
                        0b100,0b000,0b001,0b010,0b001,
                        0b0001,0b001,0b001,0b000};
    // int sensorArray[]= {0b001,0b001,0b001,0};
    for (int i = 0; i < 24; i++){
        map = exploreMap(map,&Car,sensorArray[i]);
    }

    printf("\n\n");
    printf("\n\n");
    printMap(map);
    printf("\n\n");
    coordinate x = {0,0,0,0};    
    coordinate y = {3,2,0,0};
    coordinate *shorttestPath = findShortestPathInMapByStartAndEnd(map ,x,y);
    getPrintedMap(map,shorttestPath);
    free(shorttestPath);
    reset(&map);

}