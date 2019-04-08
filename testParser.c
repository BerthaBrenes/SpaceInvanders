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
int parseJSON(char *filepath,void callback(char *, char*)){
    char JSON_STRING[BUFFER_SIZE];
    
    char value[1024];
    char key[1024];
    readfile(filepath,JSON_STRING);
    
    int i,r;
    jsmn_parser p;
    jsmntok_t t[MAX_TOKEN_COUNT];
    jsmn_init(&p);

    r= jsmn_parse(&p, JSON_STRING, strlen(JSMN_STRING),t,sizeof(t)/(sizeof(t[0])));
    if(r < 0){
        printf("Error al parsear el JSON\n");
        return 1;
    }
      if (r < 1 || t[0].type != JSMN_OBJECT) {
       printf("Se espera un objeto\n");
       return 1;
    }
    for (i = 1; i < r; i++){
        jsmntok_t json_value = t[i+1];
        jsmntok_t json_key = t[i];
        int string_length = json_value.end - json_value.start;
        int key_length = json_key.end - json_key.start;
        int idx;

        for (idx = 0; idx < string_length; idx++){
           value[idx] = JSON_STRING[json_value.start + idx ];
       }

       for (idx = 0; idx < key_length; idx++){
           key[idx] = JSON_STRING[json_key.start + idx];
        }
        value[string_length] = '\0';
        key[key_length] = '\0';
        callback(key,value);
        i++;
    }
    return 0;
}
void mycallback(char *key, char* value){
    print("%s : %s\n", key, value);
}

int main()
{
    parseJSON(JSON_FILE_PATH, mycallback);
    return 0;
}