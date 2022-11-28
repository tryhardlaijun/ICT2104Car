# ICT2104 Mapping
### Video Link
https://youtu.be/hH59fNtPMeE
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
Our program makes use of breadth first search in order to detect the shortest path given a starting and ending coordinate. For each level, it explores all the possible nodes at the present depth before proceeding on to the next depth. It does this by creating a linked list to contain the possible paths, starting at the initial coordinate and creating a visited array, and then marking that coordinate as visited. It then checks if there is multiple open paths for that coordinate using the "paths" variable of the coordinate. For each possible path, it creates a new node in the linked list. In each node, the following coordinates that the car visits will be added on until it reaches the end point or if a coordinate has been visited before in another node. Thus, each node contains it's own mini map and the node with the shortest amount of coordinates will be the shortest path. The program will return the shortest path as an array of visited coordinates just like the original map.

<br>
Here, we can see that the car has went to [1,3] and has detected that there are three different paths. It stores each path that it took in a different map.
<br>
<img width="500" alt="image" src="https://user-images.githubusercontent.com/49942089/204198413-8f1ce3b4-8e3c-41ce-a4f5-9e35f91e78a9.png">
<br>
Once it has traversed all the nodes at the first depth, it continues on to the nodes at the second depth and prints the path again.
<br>
<img width="500" alt="image" src="https://user-images.githubusercontent.com/49942089/204199664-316236d4-d61e-4acf-acbc-30969e031183.png">
<br>
Lastly, it traverses the nodes at the third depth and proceeds to print the shortest path to the next junction.
<br>
<img width="500" alt="image" src="https://user-images.githubusercontent.com/49942089/204199376-ff1e259b-b622-4aab-8722-bd1773684abc.png">
<br>
At the end of the program, the map of the shortest path will be displayed.
<br>
<img width="200" alt="image" src="https://user-images.githubusercontent.com/49942089/204197605-f31e54c5-7ef4-439a-9b3b-313a278783f3.png">


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
<img width="300" alt="image" src="https://user-images.githubusercontent.com/49942089/204200388-9b9530d6-837b-49f0-983d-29641dfbbe1e.png">

We assume the orientation of the car is forward for wherever the car is placed down at. Thus, we can read this example from **'s'**. Afterwards, move up and continue through the path of all the **'1'**. 

In this example too, the car goes one round and comes back to the initial position of **'s'** while displaying the available path that the car did not explore. 



