#ifndef COMANDOS_H
#define COMANDOS_H

#include <stdbool.h>
#include <stddef.h>

#include "cola.h"
#include "lista.h"

/* DEFINICION DE ESTRUCTURA INTERNA DE DATOS, NECESARIA PARA LA 
 * IMPLEMENTACION DE LOS COMANDOS*/

typedef struct my_twitter twitter_t;

/* DEFINICION DE LAS FUNCIONES DESTRUCTURAS NECESARIAS, Y QUE EL USUARIO
 * DEBE UTILIZAR PARA LIBERAR LA MEMORIA*/
 
void my_twitter_destruir(twitter_t* my_twitter);

/* FUNCION DE CREACION DE LAS ESTRUCTURAS DE MY_TWITTER */

twitter_t* my_twitter_crear();

/* IMPLEMENTACION DE LOS COMANDOS NECESARIOS PARA EL SISTEMA*/

// Permite ingresar al sistema un nuevo mensaje (twit) y este queda 
// registrado bajo un ID unico.
/* Pre: se debe haber creado la estructura my_twitter y tener
 * la entrada representada en una cola.
 * Post: En caso de que no se ingrese un usuario (@alguien) o que 
 * solo se ingrese el comando, devuelve ERROR_COMANDO_INVALIDO. Sino
 * devulve OK ID del twit y quedan registrados en el sistema ademas
 * del usuario que twitea, los usuarios y hashtags nombrados para 
 * buscarlos luego en el mismo.*/

void usuario_twittear(twitter_t* my_twitter, cola_t* twit_palabras);

// Aumentar la popularidad del twitt indicado por el ID ingresado.
// Pre: Debe existir la estructura interna que representa a los twits.
// Post: En caso de que no exista el twitt, devolvera por pantalla 
// ERROR_TWIT_ID_INVALIDO. Si el comando es invalido
// (ya sea por falla numerica o de parametros) devolvera 
// ERROR_COMANDO_INVALIDO y si no imprimira OK ID_del_twitt
void usuario_favorito(twitter_t* my_twitter, cola_t* cola_entrada);

// Imprime los resultados de la busqueda segun el orden indicado 
// (cronologico o popular)
// Pre: se debe haber creado la estructura my_twitter y tener
// la entrada representada en una cola.
// Post: En caso de que falle devuelve ERROR_COMANDO_INVALIDO, sino 
// devuelve por pantalla la cantidad de twitt's referidos al hashtag o 
// usuario y luego estos listados, segun el orden indicado.
void usuario_buscar(twitter_t* my_twitter, cola_t* cola_entrada);

#endif //COMANDOS_H
