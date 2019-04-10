#include<stdio.h>
#include<json-c/json.h>

void print_json_value(json_object *jobj){
	printf("Printer json");
	enum json_type type;
	printf("type: ",type);
	type = json_object_get_type(jobj);
	switch (type) {
		case json_type_boolean:
			printf("json_type_booleann");
			printf("value: %sn", json_object_get_boolean(jobj)? "true": "false");
			break;
		case json_type_double: 
			printf("json_type_doublen");
			printf("value: %lfn", json_object_get_double(jobj));
			break;
		case json_type_int: 
			printf("json_type_intn");
			printf("value: %dn", json_object_get_int(jobj));
			break;
		case json_type_string: 
			printf("json_type_stringn");
			printf("value: %sn", json_object_get_string(jobj));
			break;
	}

}
/*Parsea un json object*/
void json_parse(json_object * jobj) {
	printf("enntre al parser de Objectos");
  enum json_type type;
  json_object_object_foreach(jobj, key, val) { 
    printf("type: ",type);
    type = json_object_get_type(val);
    switch (type) {
      case json_type_boolean:
	  	printf("boolean");	   
      case json_type_double: 
		  printf("double");
      case json_type_int:
	  	printf("int"); 
      case json_type_string: 
	  	printf("String");
	  	print_json_value(val);
		break; 
      case json_type_object: 
	  	printf("json_type_objectn");
		jobj = json_object_object_get(jobj, key);
		json_parse(jobj); 
		break;
      case json_type_array: 
	  	printf("type: json_type_array, ");
		json_parse_array(jobj, key);
		break;
    }
  }
}
/*Parsear un json array*/
void json_parse_array( json_object *jobj, char *key) {
  void json_parse(json_object * jobj); /*Forward Declaration*/
  enum json_type type;

  json_object *jarray = jobj; /*Simply get the array*/
  if(key) {
    jarray = json_object_object_get(jobj, key); /*Getting the array if it is a key value pair*/
  }

  int arraylen = json_object_array_length(jarray); /*Getting the length of the array*/
  printf("Array Length: %dn",arraylen);
  int i;
  json_object * jvalue;

  for (i=0; i< arraylen; i++){
    jvalue = json_object_array_get_idx(jarray, i); /*Getting the array element at position i*/
    type = json_object_get_type(jvalue);
    if (type == json_type_array) {
      json_parse_array(jvalue, NULL);
    }
    else if (type != json_type_object) {
      printf("value[%d]: ",i);
      print_json_value(jvalue);
    }
    else {
      json_parse(jvalue);
    }
  }
}
int main(int argc, char **argv) {
	
	FILE *fp;
	char buffer[1024];
	struct json_object *name;
	struct json_object *valueX;
	struct json_object *valueY;
	struct json_object *vidas;
	struct json_object *vivo;
	struct json_object *jobj;

	fp = fopen("test.json","r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);
	printf("JSON string: %sn", buffer);
	
  	jobj = json_tokener_parse(buffer);
	  	
	json_object_object_get_ex(jobj, "posxJuga", &valueX);
	json_object_object_get_ex(jobj, "posyJuga", &valueY);
	json_object_object_get_ex(jobj, "vidasJuga", &vidas);
	json_object_object_get_ex(jobj, "vivoJuga", &vivo);
	printf("PosX de Jugador: %s\n", json_object_get_int(valueX));
	printf("PosY de Jugador: %d\n", json_object_get_int(valueY));
	printf("Vidas de Jugador: %d\n", json_object_get_int(vidas));
	printf("Vivo de Jugador: %s\n", json_object_get_boolean(vivo)? "true": "false");
	// json_jugadores_parser(jobj);
	// json_calamar_parser(jobj);
	// json_cangrejo_parser(jobj);
	// json_pulpo_parser(jobj);
	//json_parse(jobj);
   	
}
void json_jugadores_parser(json_object *jobj){
	struct json_object *name;
	struct json_object *valueX;
	struct json_object *valueY;
	struct json_object *vidas;
	struct json_object *vivo;
	json_object_object_get_ex(jobj, "jugador", &name);
	json_object *objeto = json_object_get_object(name);
	json_object_object_get_ex(objeto, "posx", &valueX);
	json_object_object_get_ex(objeto, "posy", &valueY);
	json_object_object_get_ex(objeto, "vidas", &vidas);
	json_object_object_get_ex(objeto, "vivo", &vivo);
	printf("PosX de Jugador: %s\n", name);
	printf("PosY de Jugador: %d\n", json_object_get_int(valueY));
	printf("Vidas de Jugador: %d\n", json_object_get_int(vidas));
	printf("Vivo de Jugador: %s\n", json_object_get_boolean(vivo)? "true": "false");
}
void json_calamar_parser(json_object *jobj){
	struct json_object *name;
	struct json_object *valueX;
	struct json_object *valueY;
	struct json_object *puntos;
	struct json_object *vivo;
	json_object_object_get_ex(jobj, "calamar", &name);
	json_object *objeto = json_object_get_object(name);
	json_object_object_get_ex(objeto, "posx", &valueX);
	json_object_object_get_ex(objeto, "posy", &valueY);
	json_object_object_get_ex(objeto, "puntos", &puntos);
	json_object_object_get_ex(objeto, "vivo", &vivo);
	printf("PosX de Cangrejo: %d\n", json_object_get_int(valueX));
	printf("PosY de Cangrejo: %d\n", json_object_get_int(valueY));
	printf("Vidas de Cangrejo: %d\n", json_object_get_int(puntos));
	printf("Vivo de Cangrejo: %s\n", json_object_get_boolean(vivo)? "true": "false");
}
void json_cangrejo_parser(json_object *jobj){
	struct json_object *name;
	struct json_object *valueX;
	struct json_object *valueY;
	struct json_object *puntos;
	struct json_object *vivo;
	json_object_object_get_ex(jobj, "cangrejo", &name);
	json_object *objeto = json_object_get_object(name);
	json_object_object_get_ex(objeto, "posx", &valueX);
	json_object_object_get_ex(objeto, "posy", &valueY);
	json_object_object_get_ex(objeto, "puntos", &puntos);
	json_object_object_get_ex(objeto, "vivo", &vivo);
	printf("PosX de Calamar: %d\n", json_object_get_int(valueX));
	printf("PosY de Calamar: %d\n", json_object_get_int(valueY));
	printf("Vidas de Calamar: %d\n", json_object_get_int(puntos));
	printf("Vivo de Calamar: %s\n", json_object_get_boolean(vivo)? "true": "false");
}
void json_pulpo_parser(json_object *jobj){
	struct json_object *name;
	struct json_object *valueX;
	struct json_object *valueY;
	struct json_object *puntos;
	struct json_object *vivo;
	json_object_object_get_ex(jobj, "pulpo", &name);
	json_object *objeto = json_object_get_object(name);
	json_object_object_get_ex(objeto, "posx", &valueX);
	json_object_object_get_ex(objeto, "posy", &valueY);
	json_object_object_get_ex(objeto, "puntos", &puntos);
	json_object_object_get_ex(objeto, "vivo", &vivo);
	printf("PosX de Pulpo: %d\n", json_object_get_int(valueX));
	printf("PosY de Pulpo: %d\n", json_object_get_int(valueY));
	printf("Vidas de Pulpo: %d\n", json_object_get_int(puntos));
	printf("Vivo de Pulpo: %s\n", json_object_get_boolean(vivo)? "true": "false");
}