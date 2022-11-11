# ICT2104 Mapping
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

<br>The car is also able to detect loops and a dead end/explored point. If the car reaches a dead end/explored point, it will turn around by turning right twice. If the car reaches a loop, it will print "Loop".





