// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include "coordinate.h"
// #define MAX 5
// coordinate startingCoordinate = {0, 0, 0, 0, 0, 1};
// coordinate endingCoordinate = {4, 0, 0, 0, 0, 1};

// // x,y,pathAvail,pathUnexplored,nextOrientation,isLast
//     coordinate a0 = {0, 0, 0, 0, 0, 1};
//     coordinate a1 = {0, 1, 0, 0, 0, 1};
//     coordinate a2 = {0, 2, 0, 0, 0, 1};
//     coordinate a3 = {0, 3, 0, 0, 0, 1};
//     coordinate a4 = {0, 4, 0, 0, 0, 1};

//     coordinate b0 = {1, 0, 0, 0, 0, 1};
//     coordinate b1 = {1, 1, 0, 0, 0, 1};
//     coordinate b2 = {1, 2, 0, 0, 0, 1};
//     coordinate b3 = {1, 3, 0, 0, 0, 1};
//     coordinate b4 = {1, 4, 0, 0, 0, 1};

//     coordinate c0 = {2, 0, 0, 0, 0, 1};
//     coordinate c1 = {2, 1, 0, 0, 0, 1};
//     coordinate c2 = {2, 2, 0, 0, 0, 1};
//     coordinate c3 = {2, 3, 0, 0, 0, 1};
//     coordinate c4 = {2, 4, 0, 0, 0, 1};

//     coordinate d0 = {3, 0, 0, 0, 0, 1};
//     coordinate d1 = {3, 1, 0, 0, 0, 1};
//     coordinate d2 = {3, 2, 0, 0, 0, 1};
//     coordinate d3 = {3, 3, 0, 0, 0, 1};
//     coordinate d4 = {3, 4, 0, 0, 0, 1};
// struct Vertex {
//     unsigned int label;
//     bool visited;
// };

// //stack variables

// int stack[MAX]; 
// int top = -1; 

// //graph variables

// //array of vertices
// struct Vertex* lstVertices[MAX];

// //adjacency matrix
// int adjMatrix[MAX][MAX];

// //vertex count
// int vertexCount = 0;

// //stack functions

// void push(int item) { 
//    stack[++top] = item; 
// } 

// int pop() { 
//    return stack[top--]; 
// } 

// int peek() {
//    return stack[top];
// }

// bool isStackEmpty() {
//    return top == -1;
// }

// //graph functions

// //add vertex to the vertex list
// void addVertex(int label) {
//    struct Vertex* vertex = (struct Vertex*) malloc(sizeof(struct Vertex));
//    vertex->label = (char) label;
//    vertex->visited = false;     
//    lstVertices[vertexCount++] = vertex;
// }

// //add edge to edge array
// void addEdge(int start,int end) {
//    adjMatrix[start][end] = 1;
//    adjMatrix[end][start] = 1;
// }

// //display the vertex
// void displayVertex(int vertexIndex) {
//    printf("%i ",lstVertices[vertexIndex]->label);
// }       

// //get the adjacent unvisited vertex
// int getAdjUnvisitedVertex(int vertexIndex) {
//    int i;

//    for(i = 0; i < vertexCount; i++) {
//       if(adjMatrix[vertexIndex][i] == 1 && lstVertices[i]->visited == false) {
//          return i;
//       }
//    }

//    return -1;
// }

// void depthFirstSearch() {
//    int i;

//    //mark first node as visited
//    lstVertices[0]->visited = true;

//    //display the vertex
//    displayVertex(0);   

//    //push vertex index in stack
//    push(0);

//    while(!isStackEmpty()) {
//       //get the unvisited vertex of vertex which is at top of the stack
//       int unvisitedVertex = getAdjUnvisitedVertex(peek());

//       //no adjacent vertex found
//       if(unvisitedVertex == -1) {
//          pop();
//       } else {
//          lstVertices[unvisitedVertex]->visited = true;
//          displayVertex(unvisitedVertex);
//          push(unvisitedVertex);
//       }
//    }

//    //stack is empty, search is complete, reset the visited flag        
//    for(i = 0;i < vertexCount;i++) {
//       lstVertices[i]->visited = false;
//    }        
// }

// int main() {
//    int i, j;

//    for(i = 0; i < MAX; i++)    // set adjacency {
//       for(j = 0; j < MAX; j++){ // matrix to 0
//          adjMatrix[i][j] = 0;
//    }

//    addVertex('a0');   // 0
//    addVertex('a1');   // 1
//    addVertex('a2');   // 2
//    addVertex('a3');   // 3
//    addVertex('a4');   // 4

//    addEdge(0, 1);    // S - A
//    addEdge(0, 2);    // S - B
//    addEdge(0, 3);    // S - C
//    addEdge(1, 4);    // A - D
//    addEdge(2, 4);    // B - D
//    addEdge(3, 4);    // C - D

//    printf("Depth First Search: ");
//    depthFirstSearch(); 

//    return 0;   
// }