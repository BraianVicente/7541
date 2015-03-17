#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

#define VERDADERO true
#define FALSO false

/****************************************************************************/
/*                         FUNCIONES AUXILIARES                             */
/****************************************************************************/

// Crea un duplicado de la clave indicada.
// Pre: la clave debe existir.
// Post: devuelve el puntero a la clave duplicada.
char* duplicar_clave(const char* clave){
	char* clave_aux = malloc((strlen(clave) + 1)*sizeof(char));
	if (clave_aux == NULL) return NULL;
	strcpy(clave_aux,clave);
	return clave_aux;
}


/****************************************************************************/
/*                         DESTRUCTORES DE DATOS                            */
/****************************************************************************/


static void vertice_destruir(void* dato){
	Vertice* vertice = (Vertice*) dato ;
	hash_destruir(vertice->tabla_adyacentes) ;
	free(vertice->clave) ;
	free(vertice->extra) ;
	free(vertice) ;
}

static void arista_destruir(void* dato) {
	Arista* arista = (Arista*) dato ;
	free(arista->clave);
	free(arista);
}

void grafo_destruir(Grafo* grafo) {
	hash_destruir(grafo->tabla_vertices);
	free(grafo) ;
}

/****************************************************************************/
/*                         PRIMITIVAS DEL GRAFO                             */
/****************************************************************************/

Grafo* grafo_crear(){
	Grafo* grafo = malloc( sizeof(Grafo) ) ;
	hash_t* tabla_vertices = hash_crear(vertice_destruir);
	if (!tabla_vertices) return NULL ;
	grafo->tabla_vertices = tabla_vertices ;
	grafo->cantidad = 0 ;
	return grafo ;
}

bool grafo_esta_vacio(Grafo* grafo){
	if (hash_cantidad(grafo->tabla_vertices) > 0) {
		return VERDADERO;
	} else {
		return FALSO;
	}
}

static Vertice* vertice_crear(const char* clave){
	char* clave_nueva = duplicar_clave(clave) ;
	Vertice* vertice = malloc(sizeof(Vertice)) ;
	if (! vertice) return NULL ;
	hash_t* tabla_adyacentes = hash_crear(arista_destruir) ;
	if (! tabla_adyacentes) return NULL ;
	vertice->tabla_adyacentes = tabla_adyacentes ;
	vertice->clave = clave_nueva ;
	vertice->extra = NULL ;
	vertice->adyacentes_cantidad = 0 ;
	return vertice;
}

bool vertice_agregar(Grafo* grafo, const char* clave){
	if (! hash_pertenece(grafo->tabla_vertices,clave) ) {
		Vertice* vertice = vertice_crear(clave);
		if (hash_guardar(grafo->tabla_vertices,clave,vertice) ){
			grafo->cantidad ++ ;
			return VERDADERO ;
		} else {
			return FALSO;
		}
	}
	return FALSO ;
}

Vertice* vertice_obtener(Grafo* grafo, const char* clave) {
	if ( vertice_pertenece(grafo,clave) ){
		return hash_obtener(grafo->tabla_vertices,clave) ;
	}
	return NULL ;
}

void* vertice_borrar(Grafo* grafo, const char* clave) {
	if (vertice_pertenece(grafo,clave)) {
		Vertice* vertice = (Vertice*) hash_borrar(grafo->tabla_vertices,clave) ;
		grafo->cantidad-- ;
		return vertice ;
		}

	return NULL ;
}

bool vertice_pertenece(Grafo* grafo,const char* clave) {
	return hash_pertenece(grafo->tabla_vertices,clave) ;
}

hash_t* vectir_obtener_adyacentes(Grafo* grafo, const char* clave){
	if (vertice_pertenece(grafo,clave)) {
		Vertice* vertice = vertice_obtener(grafo,clave) ;
		return vertice->tabla_adyacentes ;
	}
	return NULL ;
}

size_t vertice_adyacentes_cantidad(Grafo* grafo, const char* clave){
	Vertice* vertice = vertice_obtener(grafo,clave) ;
	return hash_cantidad(vertice->tabla_adyacentes) ;
}

static Arista* arista_crear(const char* clave, size_t peso){
	Arista* arista = malloc(sizeof(Arista));
	if ( !arista ) return NULL ;
	arista->clave = duplicar_clave(clave); ;
	arista->peso = peso ;
	return arista ;
}

bool arista_agregar(Grafo* grafo,const char* origen, const char* destino, size_t peso) {
	if (vertice_pertenece(grafo,origen) && vertice_pertenece(grafo,destino)){
		Vertice* vertice = vertice_obtener(grafo,origen);
		Arista* arista = arista_crear(destino,peso) ;
		if (hash_guardar(vertice->tabla_adyacentes,origen,arista)){
			vertice->adyacentes_cantidad++ ;
			return VERDADERO ;
		}
	}
	return FALSO ;
}

void* arista_borrar(Grafo* grafo,const char* origen, const char* destino){
	if (vertice_pertenece(grafo,origen) && vertice_pertenece(grafo,destino)){
		Vertice* vertice = vertice_obtener(grafo,origen);
		if (arista_pertenece(grafo,origen,destino)){
			Arista* arista = (Arista*)hash_borrar(vertice->tabla_adyacentes,destino) ;
			return arista ;
		}
	}
	return NULL ;
}

bool arista_pertenece(Grafo* grafo,const char* origen,const char* destino){
	if (vertice_pertenece(grafo,origen) && vertice_pertenece(grafo,destino)){
		Vertice* vertice = vertice_obtener(grafo,origen) ;
		return hash_pertenece(vertice->tabla_adyacentes,destino) ;
	}
	return FALSO ;
}
