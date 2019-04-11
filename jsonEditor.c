#include<stdio.h>
#include<json-c/json.h>


int main(int argc, char **argv) {
	
	FILE *fp;
	char buffer[1024];
	fp = fopen("datos.json","r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);
	printf("JSON Inicial: %sn", buffer);
	crearJson();
   	
}
void crearJson(){
	FILE *fp;

    fp = fopen("datos.json", "w+");
	json_object * jobj = json_object_new_object();

    /*Creating a json string*/
    json_object *jstring = json_object_new_string("Trasnferencia de datos");

    json_object *DatoA = json_object_new_int(0);
    json_object *DatoB = json_object_new_int(1);
    json_object *DatoC = json_object_new_int(2);



    /*Form the json object*/
    /*Each of these is like a key value pair*/
    json_object_object_add(jobj,"NombreFile", jstring);
    json_object_object_add(jobj,"Dato1", DatoA);
    json_object_object_add(jobj,"Dato2", DatoB);
    json_object_object_add(jobj,"Dato3", DatoC);

    /*Now printing the json object*/
    printf ("Nuevo Json File: %sn",json_object_to_json_string(jobj));
    fputs(json_object_to_json_string(jobj), fp);
    fclose(fp);
}

void ingresarDatos(int primerDato, int segundoDato, int tercerDato){
	FILE *fp;

    fp = fopen("datos.json", "w+");
	json_object * jobj = json_object_new_object();

    /*Creating a json string*/
    json_object *jstring = json_object_new_string("Trasnferencia de datos");

    json_object *Dato1 = json_object_new_int(primerDato);
    json_object *Dato2 = json_object_new_int(segundoDato);
    json_object *Dato3 = json_object_new_int(tercerDato);



    /*Form the json object*/
    /*Each of these is like a key value pair*/
    json_object_object_add(jobj,"NombreFile", jstring);
    json_object_object_add(jobj,"Dato1", Dato1);
    json_object_object_add(jobj,"Dato1", Dato2);
    json_object_object_add(jobj,"Dato1", Dato3);

    /*Now printing the json object*/
    printf ("Nuevo Json File: %sn",json_object_to_json_string(jobj));
    fputs(json_object_to_json_string(jobj), fp);
    fclose(fp);
}
