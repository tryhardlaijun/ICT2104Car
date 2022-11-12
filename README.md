# ICT2104 Mapping
# Process of Program
<br>At the start of the program, it checks if the map is initialized. If not, initialize it. Next, it finds out where the car currently is on the map. It checks the next available path and then moves. It then checks if the next coordinate has been explored. This process repeats until the program detects that the map has been fully explored. 

# Current Capabilities
The system reads a .txt file consisting of the possible paths that it can take. The possible paths are stored with 3 bits.
<br>First bit 1 - Moving left is possible
<br>Second bit 1 - Moving forward is possible
<br>Third bit 1 - Moving right is possible.
<br> If there are multiple possible paths, the car will prioritise going front first, followed by right then left.

<br>Once the program runs, for each step taken, there will be 2 different kinds of output. Firstly, the direction moved would be printed as “Move Forward”, “Turn Right”, and “Turn Left”. Secondly, at each coordinate, there would be information about the coordinate and the car printed.

<br>Each coordinate stores the following information:
<br>X and Y values.
<br>pathAvail: A 3-bit value which reads the .txt file and determines the possible paths relative to where the car is facing.
<br>pathUnexplored: Similar to pathAvail, but once the possible path is taken, the bit is removed.
<br>nextOrientation: A 2-bit value storing the orientation of the car after its next move, relative to where the car was previously. 
<br>selfOrientation: A 2-bit value storing the car’s current orientation.
<br>isLast: A 1-bit value which indicates whether the coordinate is the last visited one.

<br>Examples of Output:
<br><img width="500" alt="image" src="https://user-images.githubusercontent.com/49942089/201339360-8df05cff-acb4-492e-ac8b-e1fc568205f6.png">

<br>The car is also able to detect loops and a dead end/explored point. If the car reaches a dead end/explored point, it will turn around by turning right twice. If the car reaches a loop, it will print "Loop". In the example output above, before the printing of "Loop", we grabbed where this looped coordinate is, together with the coordinate of where it came from.

From here onwards, we will find the shortest path to the next available path that has not been explored by the car.

# Printing of the map
We first start off by computing the size of the map, as this will be printed in a 2D array. By computing the size of the map, we can account for the borders that will be printed, as well as the initial starting position of the car.
<br>The size of the map is computed based on the maximum of X and Y coordinates. This computation will also account for if there are available paths at this maximum values.

<br>Next, we allocate memory and build out an empty map. The reason an empty map is built without initialising the explored coordinates first is to account for the offset of the starting position of the car.
<br>

<br>Example of empty map
<br> {Put image here!}

<br>Afterwards, we fill in the map with the coordinates taken from the previous section with an additional offset and add it into the map. 
<br>The map prints **'s'** for the first coordinate, and subsequently prints **'1'** for where it explores. Where there is an available path, the map prints **'0'**. The map also removes the borders in between for where the car moves or where an available path is found.
<br>Lastly, the completed map is printed, and deallocates memory.

<br>Example of completed map
<br> {Put image here!}



