#include "map.h"
#include <stdbool.h>

coordinate startingCoordinate = {0, 0, 0, 0, 3, 1};
coordinate endingCoordinate = {0, 1, 0, 0, 0, 1};

int main()
{   
    coordinate *fastestPath = NULL; //create array for fastest path
    coordinate *map = NULL;
    coordinate *junctions = NULL; //create array for fastest path
    coordinate *unexploredCoordinates = NULL;
    //int totalLines = getTotalLines();
    int *sensorArray = getSensorArrayFromText();
    int finalSteps = 0; //variable to count the number of shortest steps
    int index = 0;

    for (int i = 0;; i++)
    {
        // printf("I is %d",i);
        //  If at the very beginning.
        if (map == NULL)
        {
            map = updateCoordinateToMap(map, startingCoordinate);
            updateCoordinatePaths(map, sensorArray[0]);
        }
        else
        {                
            int steps1;
            // get size of Map
            int lastPosition = getTotalCoordinatesInMap(map);
            // Replicate a coordinate like the previous map
            coordinate c = replicateLastPosition(map);
            // Update current path
            int junction = updateCoordinatePaths(&c, sensorArray[i]);
            if (junction == 1){
                 junctions[index++] = c;


            //     for (int i = 1;; i++) //infinite for loop to count how many dots are there in the array (minus first one)
            //     {
            //         steps1++; //add steps
            //         if (map[i].isLast == 1)//check if ending point
            //         {
            //             break; //end the loop
            //         }
            //     }

            }

            // Update Orientation
            int location = getnextMove(&c, endingCoordinate); 




            //printf("Location: %d\n", location); ger
            // Update where the current coordinate is
            updateXYCoordinate(&map[lastPosition], &c);
            // Update Unexplored Path for current path
            int pathRemain = updateUnexploredPath(&map[lastPosition]);
            // Check if next coordinate has already been explored
            int isExplored = checkIfAlreadyInMap(map, c);
            // Check if map has been explored
            if (isExplored == -1)
            {
                // Unexplored
                // Add current coordinate to map if unexplored
                map = updateCoordinateToMap(map, c);
            }
            else
            { // Explored
                // Check if in unexploredArray
                int getUnexploredPosition = checkIfAlreadyInMap(unexploredCoordinates, c);
                if (getUnexploredPosition != -1)
                {
                    unexploredCoordinates[getUnexploredPosition] = c;
                }
            }
            if (pathRemain != 0)
            {
                unexploredCoordinates = updateCoordinateToMap(unexploredCoordinates, map[lastPosition]);
            }
            //location is reverse, means that the car will not go forward anymore
            if (location == -2)
            {
                int steps = -1; //dont want to count initial starting point
                if (fastestPath == NULL)
                {
                    fastestPath = map; //initialize the fastest path first if it is empty
                    printf("Fastest path initialised\n\n");
                }
                // int steps = sizeof(map)/sizeof(map[0]);
                // printf("total step is %d\t", steps);
                for (int i = 1;; i++) //infinite for loop to count how many dots are there in the array (minus first one)
                {
                    steps++; //add steps
                    if (map[i].isLast == 1)//check if ending point
                    {
                        break; //end the loop
                    }
                }
                if (finalSteps == 0)
                {
                    finalSteps = steps; //set final steps 
                    printf("Final steps is %d", finalSteps);
                    printf("\nFinal steps updated\n\n");
                }
                if (steps == 0) //should be called if both directions explored
                {
                    printf("Shortest Path found!!!\n");
                    printf("Shortest Path is %d steps", finalSteps);
                    break;
                }
                else if (steps < finalSteps)
                {
                    finalSteps = steps;
                    fastestPath = map;
                    printf("Final steps is %d\n", finalSteps);
                    printf("Final steps has changed\n\n");
                }
                else
                {
                    printf("Final steps is %d\n", finalSteps);
                    printf("Final steps no change\n\n");
                }

                printf("\nThe current fastest path:\n");
                printMap(fastestPath);
                map = NULL;            
                break;
            }
        }
    }
    // printMap(map);
    // printMap(unexploredCoordinates);
    // printCoordinate(map[1]);
}

// we have no actual map, how to set the boundary of where the car is supposed to go
// each dot has information on where it can go next?
// once it reaches a point, and sees that it can go two different locatoins
// have 2 diff list of where it can go, then calculate shortest path
// how does path avail work
// if path unexplored is 3 how does it take the &2

// if path avail is 3 and 6,
// duplicate list that you have been to and then go to both possible directoins
//

// is the path that you have been to stored?

//does it remember where it has been?
//if it is forced to go forward instead of right
