// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include "coordinate.h"
// #define MAX 5

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