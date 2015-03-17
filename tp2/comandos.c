#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"
#include "vector.h"
#include "cola.h"
#include "heap.h"
#include "lista.h"

#define OK 0
#define ERROR_COMANDO_INVALIDO 1
#define ERROR_TWIT_ID_INVALIDO 2
#define LARGO 151

#define DECIMAL 10
#define	HASHTAG "#"
#define	USUARIO "@"
#define ESPACIO " "
#define CRONOLOGICO "cronologico"
#define POPULAR "popular"

/***********************************************************************
 * 							ESTRUCTURA AUXILIAR
 * ********************************************************************/

typedef struct nodo_twit{
	unsigned int id;
	char* twit;
	unsigned int favoritos;
} nodo_twit_t;

typedef struct my_twitter{
	hash_t* tabla_usuarios_hashtags;
	vector_t* vector_twitts;
} twitter_t;

/***********************************************************************
 * 							FUNCIONES AUXILIARES
 * ********************************************************************/

// Post: devuelve un nodo con el id pasado por parametro, inicializado
void* nodo_twit_crear(size_t id){

	nodo_twit_t* nodo = malloc (sizeof(nodo_twit_t));
	if (nodo == NULL) return NULL;

	nodo->id = id;
	nodo->twit = NULL;
	nodo->favoritos = 0;

	return nodo;
}

// Funcion de destruccion de la las listas que contienen los punteros
// a los nodos de twits.
void destruir_datos_tabla(void* lista_a_twits){
	lista_t* aux = (lista_t*) lista_a_twits;
	lista_destruir(aux,NULL);
}

// Funcion de destruccion de los nodos del vector de twits
void destruir_twits(void* nodo){
	nodo_twit_t* aux = (nodo_twit_t*) nodo;
	free(aux->twit);
	free(nodo);
}

void my_twitter_destruir(twitter_t* my_twitter){

	hash_destruir(my_twitter->tabla_usuarios_hashtags);
	vector_destruir(my_twitter->vector_twitts);
	free(my_twitter);
}


twitter_t* my_twitter_crear(){

	hash_t* tab = hash_crear(destruir_datos_tabla);
	vector_t* vec = vector_crear(destruir_twits);

	twitter_t* my_twitter = malloc(sizeof(twitter_t));
	my_twitter->tabla_usuarios_hashtags = tab;
	my_twitter->vector_twitts = vec;

	return my_twitter;
}

/* Funcion auxiliar de impresion, que recibe un entero segun sea el
 * estado en el que quedo un comando luego de ejecutarse, e imprime por
 * pantalla el mismo*/
void imprimir_resultado(int estado){

	switch (estado){
		case OK:
			printf("OK");
			break;
		case ERROR_COMANDO_INVALIDO:
			printf("ERROR_COMANDO_INVALIDO\n");
			break;
		case ERROR_TWIT_ID_INVALIDO :
			printf("ERROR_TWIT_ID_INVALIDO\n");
			break;
	}
}

// Recibo una palabra que deberia ser el hashtag, si no lo es devuelvo
// false. Busca el # en el string.

bool encontrar_caracter(char* linea, char* car){
	char* p;
	p = strstr(linea, car);

	if (p != NULL) return true;
	return false;
}

bool validar_hashtag(char* linea){
	return encontrar_caracter(linea, HASHTAG);
}

//Recibo una palabra que deberia ser el usuario, si no lo es devuelvo
//false. Busca el @ en el string.
bool validar_usuario(char* linea){
	return encontrar_caracter(linea, USUARIO) ;
}

/***********************************************************************************
 *                         FUNCIONES DE USUARIO_TWITTEAR
 * *********************************************************************************/

// Funcion que agrega al hash el # o el @ y ademas, agrega la referencia
// a el nodo del twit en la lista asociada.
void usuario_hashtag_ini(hash_t* tab, nodo_twit_t* nodo, char* msj, char* pal){

	lista_t* ids = (lista_t*) hash_obtener(tab, pal);
	nodo_twit_t* aux = nodo;

	if (ids == NULL){
		ids = lista_crear();
		lista_insertar_primero(ids,aux);
		hash_guardar(tab, pal, ids);
		return;
	}

	lista_insertar_primero(ids,aux);
	return;
}

// Funcion que almacena el mensaje en el nodo del twit, previamente
// analizando todas las palabras del mensaje y agregando al hash
// las palabras que inicien con @ y #
void analizar_mensaje(hash_t* tabla, cola_t* linea, nodo_twit_t* nodo){

	char* msj = calloc(LARGO,sizeof(char));
	while(!cola_esta_vacia(linea)){
		char* pal = cola_desencolar(linea);

		if ((validar_usuario(pal)) || (validar_hashtag(pal))){
			usuario_hashtag_ini(tabla, nodo, msj, pal);
		}
		strcat(msj,ESPACIO);
		strcat (msj,pal);
		free(pal);
	}
	nodo->twit = msj;
	cola_destruir(linea,NULL);
}

void usuario_twittear(twitter_t* my_twitter, cola_t* twit_palabras){

	void* usuario = cola_ver_primero(twit_palabras);
	if ((cola_esta_vacia(twit_palabras)) || (!validar_usuario(usuario))){
		imprimir_resultado(ERROR_COMANDO_INVALIDO);
		cola_destruir(twit_palabras, free);
		return;
	}

	nodo_twit_t* nodo = nodo_twit_crear(vector_obtener_cantidad(my_twitter->vector_twitts));
	analizar_mensaje(my_twitter->tabla_usuarios_hashtags, twit_palabras, nodo);

	vector_guardar(my_twitter->vector_twitts, nodo);
	imprimir_resultado(OK);
// Corregir para que devuelta el numero del ID para que lo imprima fuera de comandos.
	printf(" %i\n", nodo->id);
}

/***********************************************************************************
 *                         FUNCIONES DE USUARIO_FAVORITOS
 * *********************************************************************************/

void usuario_favorito(twitter_t* my_twitter, cola_t* cola_entrada){

	char* char_twitt_id = cola_desencolar(cola_entrada);
	char* aux;
	int int_twitt_id = strtol(char_twitt_id,&aux,DECIMAL);

	if (strlen(aux) > 0) {
		imprimir_resultado(ERROR_COMANDO_INVALIDO);
		free(char_twitt_id);
		cola_destruir(cola_entrada,free);
		return;
	}

	if ((int_twitt_id < 0) || (int_twitt_id >= vector_obtener_cantidad(my_twitter->vector_twitts))){
		if (int_twitt_id < 0) imprimir_resultado(ERROR_COMANDO_INVALIDO);
		if (int_twitt_id >= vector_obtener_cantidad(my_twitter->vector_twitts))
			imprimir_resultado(ERROR_TWIT_ID_INVALIDO);
		free(char_twitt_id);
		cola_destruir(cola_entrada,free);
		return;
	}
	nodo_twit_t* twitt = (nodo_twit_t*)vector_obtener(my_twitter->vector_twitts,int_twitt_id);
	twitt->favoritos++;
	imprimir_resultado(OK);
	printf(" %i\n",int_twitt_id);

	free(char_twitt_id);
	cola_destruir(cola_entrada,free);
	return;
}

/***********************************************************************************
 *                         FUNCIONES DE USUARIO_BUSCAR
 * *********************************************************************************/

// Funcion de comparacion para el heap, compara segun la cantidad de favoritos de
// cada twitt.
// Post: en caso de que el a > b devuelte 1, si a < b devuelve -1 y si son iguales 0.
static int cmp_fav(const void* a, const void* b){
	const nodo_twit_t* fav_a = a;
	const nodo_twit_t* fav_b = b;
	if (fav_a->favoritos > fav_b->favoritos) return 1;
	if (fav_a->favoritos < fav_b->favoritos) return -1;
	return 0;
}

// Funcion visitar para el iterador interno de la lista. Va insertando en un heap
// los datos de la lista.
// Pre: La lista y el heap fueron creados.
// Post: encola el elemento en el heap y devuelve el resultado de dicha operacion(encolar).
static bool crear_heap_iterar(void* dato, void* extra){
	heap_t* heap = extra;
	return 	heap_encolar(heap,dato);
}

// Imprime el resultado de la busqueda segun la popularidad del twitt.
// Pre: la lista de twitt's relacionados con ese hashtag o usuario existe.
// Post: En caso de fallar devuelve por pantalla ERROR_COMANDO_INVALIDO, sino imprime
// la cantidad de resultados encontrados, y luego la lista de ellos en orden de popularidad.
static void orden_pupularidad(lista_t* lista, char* cantidad){

	char* aux = NULL;
	int mostrar_cantidad = strtol(cantidad,&aux,DECIMAL);
	if (strlen(aux) > 0) {
		imprimir_resultado(ERROR_COMANDO_INVALIDO);
		return;
	}

	heap_t* heap = heap_crear(cmp_fav);
	lista_iterar(lista,crear_heap_iterar,heap);

	if ((mostrar_cantidad == 0 ) || mostrar_cantidad > (int)lista_largo(lista))
		mostrar_cantidad = (int)lista_largo(lista);

	imprimir_resultado(OK);
	printf(" %i\n", mostrar_cantidad);
	for(int i = 0; i < mostrar_cantidad;i++){
		if (heap_esta_vacio(heap)) break;
		nodo_twit_t* nodo_twit = (nodo_twit_t*)heap_desencolar(heap);
		printf("%i %s \n",nodo_twit->id,nodo_twit->twit);
	}

	heap_destruir(heap,NULL);
}

// Funcion visitar para ir mostrando en pantalla los twitts asociado al hashtag o usuario
// existente.
// Pre: el usuario o haghstag debe existir.
static bool iterador_cronologico(void* dato, void* extra){
	nodo_twit_t* nodo_twit = (nodo_twit_t*)dato;
	int* cantidad = (int*)extra;

	printf("%i %s \n",nodo_twit->id,nodo_twit->twit);
	*cantidad = * cantidad - 1 ;
	if (*cantidad > 0 ) return true;
	return false;
}

// Imprime el resultado de la busqueda segun el orden cronologico del twitt.
// Pre: la lista de twitt's relacionados con ese hashtag o usuario existe.
// Post: devuelve por patalla la cantidad de resultados encontrados y luego los twitt's
// asociados al hashtag o usuario en orden cronologico.
static void orden_cronologico(lista_t* lista, char* cantidad){

	char* aux= NULL;
	int mostrar_cantidad = strtol(cantidad,&aux,DECIMAL);

	if ((mostrar_cantidad == 0 ) || mostrar_cantidad > (int)lista_largo(lista)  ){
		mostrar_cantidad = (int)lista_largo(lista);
	}
	imprimir_resultado(OK);

	printf(" %i\n", mostrar_cantidad);
	lista_iterar(lista,iterador_cronologico,&mostrar_cantidad);
}

void usuario_buscar(twitter_t* my_twitter, cola_t* cola_entrada){

	char* clave =  (char*)cola_desencolar(cola_entrada);
	if ( !validar_usuario(clave) && !validar_hashtag(clave) ) {
		imprimir_resultado(ERROR_COMANDO_INVALIDO);
		free(clave);
		cola_destruir(cola_entrada,free);
		return;
	}

	char* criterio = (char*)cola_desencolar(cola_entrada);
	char* cantidad = (char*)cola_desencolar(cola_entrada);
	if(!( (cantidad == NULL) || (criterio == NULL) ) ) {
		if (hash_pertenece(my_twitter->tabla_usuarios_hashtags,clave) ){

			lista_t* lista = (lista_t*) hash_obtener(my_twitter->tabla_usuarios_hashtags,clave) ;

			if (strcmp(criterio,CRONOLOGICO)== 0){
				orden_cronologico(lista,cantidad);
			} else {
				if (strcmp(criterio,POPULAR) == 0 ){
					orden_pupularidad(lista,cantidad);
				}else imprimir_resultado(ERROR_COMANDO_INVALIDO);
			}
		} else puts("OK 0");
	} else imprimir_resultado(ERROR_COMANDO_INVALIDO);

	free(cantidad);
	free(criterio);
	free(clave);
	cola_destruir(cola_entrada,free);
}
