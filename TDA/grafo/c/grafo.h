#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>
#include <stddef.h>
#include "../hash/hash.h"

/****************************************************************************/
/*                         ESTRUCTUCAS DEL GRAFO                            */
/****************************************************************************/

typedef struct arista_nodo{
	char* clave ;
	size_t peso ;
}Arista ;

typedef struct nodo_vertice {
	hash_t* tabla_adyacentes;
	void* extra ;
	char* clave ;
	size_t adyacentes_cantidad ;
} Vertice ;

typedef struct grafo_type{
	hash_t* tabla_vertices ;
	size_t cantidad ;
} Grafo ;


Grafo* grafo_crear() ;

bool grafo_esta_vacio(Grafo* grafo) ;

bool vertice_agregar(Grafo* grafo, const char* clave);

void* vertice_borrar(Grafo* grafo, const char* clave) ;

Vertice* vertice_obtener(Grafo* grafo, const char* clave) ;

bool vertice_pertenece(Grafo* grafo,const char* clave) ;

hash_t* vectir_obtener_adyacentes(Grafo* grafo, const char* clave) ;

size_t vertice_adyacentes_cantidad(Grafo* grafo, const char* clave) ;

bool arista_agregar(Grafo* grafo,const char* origen, const char* destino, size_t peso) ;

void* arista_borrar(Grafo* grafo,const char* origen, const char* destino) ;

bool arista_pertenece(Grafo* grafo,const char* origen,const char* destino) ;

void grafo_destruir(Grafo* grafo) ;

#endif // GRAFO_H
