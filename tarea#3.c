#include <stdio.h>
#include <stdlib.h>
// Tarea #3 del paradigma de programacion imperativo
// Estudiante Bertha Brenes Brenes

//Ejercicio 2.1
void millas(){
    for(int i=0; i <10; i++){
        printf("El valor de %d km en milas es: %f \n", i+1,(i+1)*0.621371);
    }
}

//Ejercicio 2.2
void farenheit(int celsius){
    printf("%d",(celsius*(9/5))+32);
    farenheit(20);
}

//Ejercicio 2.3
int contarDigitos(int n){
    if(n == 0){
        return 1;
    }else{
        return (1 + contarDigitos(n-1));
    }
}

//Ejercicio 2.4
int contarDigPare(int n){
 if(n == 1){
     return 0;
 }else
 {
    if(n%2 ==0){
        return (1 + contarDigPare(n/10));
    }else{
        return (0 + contarDigPare(n/10));
    }
 }
}

//Ejercicio 2.5 & 2.6
int  strcmp(char *s, char *p){
    while((*s != '\0') && (*p != '\0')){
        p++;
        s++;
    }
    if((*s == '\0') &&(*p != '\0')){
        printf("son iguales");
        return 0;
    }
    else if((*s == '\0')){
        printf("p es mayor");
        return 1;
    }
    else{
        printf("s es mayor");
        return 2;
    }
}

//Ejercicio 2.7
void strcat(char * dest, char *src){
    sprintf(dest, "%s%s", dest, src);
    printf("La nueva palabra es: %s\n", dest);
}

//Ejercicio 2.8
void leerDocumento(char archivo){
    char ch, list;
    FILE *fp;
 
   fp = fopen(archivo, "r"); // read mode
 
   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
    while((ch = fgetc(fp)) != EOF){
        list = ch;
    }
    printf("%c", list);
 
   fclose(fp);
}
int main(){
    return 0;
}