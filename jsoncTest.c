#include<stdio.h>
#include<json-c/json.h>


int main(int argc, char **argv) {
	FILE *fp;
	char buffer[1024];
	struct json_object *parsed_json, *parser_jugador;
	struct json_object *jugador;
	struct json_object *age;
	struct json_object *friends;
	struct json_object *friend;
    struct json_object *calamar;
    struct json_object *cangrejo;
    struct json_object *pulpo;
    struct json_object *enemigos;
    struct json_object *platillo;
    struct json_object *misil;
    struct json_object *balas;
    struct json_object *escudo;
	size_t n_friends;
	size_t i;	

	fp = fopen("test.json","r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(parsed_json, "jugador",&jugador);
    json_object_object_get_ex(parsed_json, "calamar",&calamar);
    json_object_object_get_ex(parsed_json, "cangrejo",&cangrejo);
    json_object_object_get_ex(parsed_json, "pulpo",&pulpo);
    json_object_object_get_ex(parsed_json, "enemigos",&enemigos);
    json_object_object_get_ex(parsed_json, "platillo",&platillo);
    json_object_object_get_ex(parsed_json, "misil",&misil);
    json_object_object_get_ex(parsed_json, "balas",&balas);
    json_object_object_get_ex(parsed_json, "escudo",&escudo);
	
	// json_object_object_get_ex(parsed_json, "value", &age);
	// json_object_object_get_ex(parsed_json, "menuitem", &friends);

	printf("jugador: %s\n", json_object_get_object(jugador));
	printf("Value: %d\n", json_object_get_int(age));

	// n_friends = json_object_array_length(friends);
	// printf("Found %lu menuitem\n",n_friends);

	// for(i=0;i<n_friends;i++) {
	// 	friend = json_object_array_get_idx(friends, i);
	// 	printf("%lu. %s\n",i+1,json_object_get_string(friend));
	// }	
}