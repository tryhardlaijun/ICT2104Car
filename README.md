# ICT2104 Mapping
# Process of Program
<br>At the start of the program, it checks if the map is initialized. If not, initialize it. It uses the sensorArray data to determine the possible paths for the car and updates the available and unnexplored paths of the car. Next, the car moves and it updates the unexplored path. This process repeats until the program detects that the map has been fully explored. 

# Current Capabilities
The system reads a sensorArray list consisting of the possible paths that it can take. The possible paths are stored with 4 bits.
<br> If there are multiple possible paths, the car will prioritise going front first, followed by right, left, down.
<br> The sensorArray values are absolute, meaning there is no orientation for the car.

<br>Once the program runs, for each step taken, there will be 2 different kinds of output. Firstly, the direction moved would be printed as “Move Upward”, “Move Right”, and “Move Left”. Secondly, at each coordinate, there would be information about the coordinate and the car printed.

<br>Each coordinate stores the following information:
<br>X and Y values.
<br>paths: A 8-bit value which combines two different information:
<br>pathAvail: A 4-bit value determines the possible directions the car can go on the map. The bit order is as follows, Left, Back, Right, Up.
<br>pathUnexplored: Similar to pathAvail, but once the possible path is taken, the bit is removed.
<br>isLast: A 1-bit value which indicates whether the coordinate is the last visited one.

### Examples of Output:
<img width="500" alt="image" src="https://user-images.githubusercontent.com/49942089/201339360-8df05cff-acb4-492e-ac8b-e1fc568205f6.png">

<br>The car is also able to detect loops and a dead end/explored point. If the car reaches a dead end/explored point, it will turn around by turning right twice. If the car reaches a loop, it will print "Loop". In the example output above, before the printing of "Loop", we grabbed where this looped coordinate is, together with the coordinate of where it came from.

From here onwards, we will find the shortest path to the next available path that has not been explored by the car.

# Breadth First Search
Our program makes use of breadth first search in order to detect the shortest path.  It does this by creating a linked list, starting at the first point and initializing a visited array, and then marking that node as visited. It then checks if there is multiple open paths for that node using the "paths" variable of the coordinate. It then checks if the coordinate is in the map. If it is not in the map, the coordinate will be added into the map as well as the visited array. If it is in the map, it resets the bits so that the program thinks it is a dead end and does not add the coordinate to the visited array. If there is multiple paths, it will explore each path and store each of them into a list. For each level, it explores all the possible nodes at the present depth and prints the map before proceeding on to the next depth.

<br>
Here, we can see that the car has went to [1,3] and has detected that there are three different paths. It stores each path that it took in a different map.
<br>
<img width="500" alt="image" src="https://user-images.githubusercontent.com/49942089/202858143-955fc6ed-cf63-4f8c-acce-3b58f62a832d.png">
<br>
Once it has traversed all the nodes at the first depth, it continues on to the nodes at the second depth and prints the path again.
<br>
<img width="500" alt="image" src="https://user-images.githubusercontent.com/49942089/202858187-41d6ed5a-5bcf-498d-b87a-533c07251fab.png">
<br>
Lastly, it traverses the nodes at the third depth and proceeds to print the shortest path to the next junction.
<br>
<img width="500" alt="image" src="https://user-images.githubusercontent.com/49942089/202858350-9577d32c-fe59-469f-ac9a-fa87acdeaed0.png">
<br>


<br>
<img width="292" alt="image" src="https://user-images.githubusercontent.com/49942089/202843081-588881b8-39d7-4966-b3ea-650a308de301.png">


# Printing of the map
We first start off by computing the size of the map, as this will be printed in a 2D array. By computing the size of the map, we can account for the borders that will be printed, as well as the initial starting position of the car.

The size of the map is computed based on the maximum of X and Y coordinates. This computation will also account for if there are available paths at this maximum values.

Next, we allocate memory and build out an empty map. The reason an empty map is built without initialising the explored coordinates first is to account for the offset of the starting position of the car.

### Example of empty map:
![emptyMap](https://user-images.githubusercontent.com/90232507/201453598-48a2b192-1b0c-4d6d-972a-f0a78236c96d.png)


Afterwards, we fill in the map with the coordinates taken from the previous section with an additional offset and add it into the map. 

The map prints **'s'** for the first coordinate, and subsequently prints **'1'** for where it explores. Where there is an available path, the map prints **'0'**. The map also removes the borders in between for where the car moves or where an available path is found.

Lastly, the completed map is printed, and deallocates memory.

### Example of completed map:
![TraversedMap](https://user-images.githubusercontent.com/90232507/201453705-07f0a732-b3ce-42ca-bf49-7ae5239790e7.png)

We assume the orientation of the car is forward for wherever the car is placed down at. Thus, we can read this example from **'s'**. Afterwards, move up and continue through the path of all the **'1'**. 

In this example too, the car goes one round and comes back to the initial position of **'s'** while displaying the available path that the car did not explore. 



