#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lista.h"
#include "cola.h"
#include "hash.h"
#include "heap.h"
#include "vector.h"
#include "comandos.h"
#include "lectura.h"

#define LARGO_TWITTEAR 9
#define LARGO_ERRONEO 150
#define ERROR_TWIT_DEMASIADO_LARGO LARGO_ERRONEO + LARGO_TWITTEAR
#define TWITTEAR "twittear"
#define FAVORITO "favorito"
#define	BUSCAR "buscar"

// Pre: funcion que recibe la entrada de usuario previamente leida,
// y la estructura auxiliar creada.
// Post: se invoca a la funcion de comando particular pasandoles la
// estructura, y una cola con las palabras que habia en la entrada,
// restandole la primera que se espera sea el comando. Si la primer
// palabra no es un comando, se devuelve el error correspondiente.

void procesar_entrada(char* linea, twitter_t* my_twitter){

	/*Comienzo descomponiendo la entrada */
	cola_t* cola_linea = dividir_linea(linea);

	/*Despues del primer desencolamiento, el resto son parametros*/
	char* comando = cola_desencolar(cola_linea);

	/* Segun sea el comando llamo a la funcion de comando particular*/
	if (strcmp(comando,TWITTEAR) == 0){
		usuario_twittear(my_twitter,cola_linea);
		free(comando);
		return;
	}
	else if(strcmp(comando,FAVORITO) == 0){
			usuario_favorito(my_twitter,cola_linea);
			free(comando);
			return;
		}
		else if (strcmp(comando,BUSCAR) == 0){
				usuario_buscar(my_twitter,cola_linea);
				free(comando);
				return;
			}
	//si no entra en ningun comando entonces no habia comando, es error
	free(comando);
	cola_destruir(cola_linea,free);
	printf("ERROR_COMANDO_INVALIDO\n");
	return;
}

/***********************************************************************
 *                  SISTEMA TWITTER_150_CARACTERES
 * ********************************************************************/

/* La funcion tiene tres tareas como sistema:
 * CREAR LAS ESTRUCTURAS GENERALES PARA QUE EL SISTEMA FUNCIONE SOBRE
 * ELLAS. LEER LA ENTRADA DEL USUARIO, PROCESARLA Y EFECTUAR EL LLAMADO
 * A LOS COMANDOS.
 * LIBERAR LA MEMORIA DE LAS ESTRUCTURAS GENERALES CREADAS.*/
 // Nota: en caso de que la entrada sea mayor al rango de 0 a 150
 // caracteres se devolvera error y se pedira un nuevo ingreso.

void sistema_twitter(){

	/*Creacion de las estructuras de datos a utilizar*/
	twitter_t* my_twitter = my_twitter_crear();

	/*Ciclo de entrada y salida a cargo del procesar*/
	char* entrada = leer_linea();
	while(!feof(stdin)){
		if (!(strlen(entrada) > ERROR_TWIT_DEMASIADO_LARGO)){
		procesar_entrada(entrada, my_twitter);
		entrada = leer_linea();
		}
		else{
			printf("ERROR_TWIT_DEMASIADO_LARGO\n");
			free(entrada);
			entrada = leer_linea();
		}
	} /*Cuando termina el ciclo de entrada libero
		toda la memoria de las estructuras*/

	my_twitter_destruir(my_twitter);
	free(entrada);
}

int main(){
	sistema_twitter();
	return 0;
}
