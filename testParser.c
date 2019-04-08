#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jsmn.h"

#define JSON_FILE_PATH "jsons/test.json"
#define BUFFER_SIZE 5000
#define MAX_TOKEN_COUNT 128

void readfile(char* filepath, char* fileContent){
    FILE *f;
    char c;
    int index;
    f = fopen(filepath,"rt");
    while((c = fget(f)) != EOF){
        fileContent[index] = c;
        index++;
   }
    fileContent[index] = '\0';
}
int parseJSON(){
    
}