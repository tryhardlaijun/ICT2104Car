#include "file.h"
char const* const fileName = "sensedData.txt";

int binaryToNumber(char* binaryString){
    int total = 0;
    //Whiel not NULL pointer && not \n"
    while (*binaryString && *binaryString != '\n')
    {
        // total *2 to shift bits to the right
        total *= 2;
        //Check add extra 1 bit to string if char is '1'
        if (*binaryString == '1') 
            total += 1;
        //Got to the next char
        binaryString++;
    }
    return total;
}
int readFile(int* sensorArray){
    //read any text file from currect directory
    FILE* file = fopen(fileName, "r"); 
    //Check if file exist
    if(!file){
        printf("\n Unable to open : %s ", fileName);
        return -1;
    }
    // Max buffer 500 char per line
    char line[500];
    // Set counter for array.
    int count = 0;
    // While fgets doesnt return NULL -> Not end of file and counter < MAX;
    while (fgets(line, sizeof(line), file) && count < MAX) {
        //Result = decimal number form of binary string
        int result = binaryToNumber(line);
        //Add to sensor array
        sensorArray[count] = result;
        sensorArray[count+1] = -1;
        count++;
    }
    // Close the file
    fclose(file);
    return 0;
}
int getTotalLines(){
    //read any text file from currect directory
    FILE* file = fopen(fileName, "r"); 
    //Check if file exist
    if(!file){
        printf("\n Unable to open : %s ", fileName);
        return -1;
    }
    // Max buffer 500 char per line
    char line[500];
    // Set counter for array.
    int count = 0;
    // While fgets doesnt return NULL -> Not end of file and counter < MAX;
    while (fgets(line, sizeof(line), file) && count < MAX) {
        count++;
    }
    // Close the file
    fclose(file);
    return count;
}

int* getSensorArrayFromText(){
    //sensorArray to max MAX int size;
    int *sensorArray = (int*) calloc(MAX, sizeof(int));
    readFile(sensorArray);
    return sensorArray;
}

// int main(){
//     int *sensorArray = getSensorArrayFromText();
//     for(int i = 0; i < MAX; i++){
//         if(sensorArray[i] == -1)
//             break;
//         printf("%d \n", sensorArray[i]);
//     }
//     free(sensorArray);
// }


