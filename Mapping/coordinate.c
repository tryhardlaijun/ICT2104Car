#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

typedef struct coordinate
{
    unsigned int x;
    unsigned int y;
     // 3 bit datatype
    unsigned int pathAvail : 3;
    // 3 bit datatype
    unsigned int pathUnexplored : 3;
    unsigned int orientation : 2;
    unsigned int isLast : 1;
}coordinate;

int main(){
    
}
