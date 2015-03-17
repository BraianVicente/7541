#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La cola está planteada como una cola de punteros genéricos. */
typedef struct nodo_cola{
	void* dato;
	void* siguiente;
} nodo_c;

typedef struct cola_enlazada{	
	void* inicio;
	void* fin;
	} cola_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t* cola_crear()
{
	cola_t* cola = malloc(sizeof(cola_t));
	if (cola == NULL) return NULL;
	cola->inicio = NULL;
	cola->fin = NULL;
	return cola;
}

bool cola_esta_vacia(const cola_t *cola)
{
	if (cola->inicio == NULL) return true;
	return false;
}

bool cola_encolar(cola_t* cola, void* valor)
{
	nodo_c* nodo = malloc (sizeof(nodo_c));
	if (nodo == NULL) return false;
	nodo->dato = valor;
	nodo->siguiente = NULL;
	if (cola->inicio == NULL )
	{
		cola->inicio = nodo;
		cola->fin = cola->inicio;
		return true;
	}
	nodo_c* nodo_fin = cola->fin;
	nodo_fin->siguiente = nodo;
	cola->fin = nodo;
	return true;
}

void* cola_ver_primero(const cola_t *cola)
{
	if ( (cola == NULL) || (cola->inicio == NULL) )  return NULL;
	nodo_c* nodo = cola->inicio;
	void* valor = nodo->dato;
	return  valor;
}

void* cola_desencolar(cola_t *cola)
{
	if ( (cola == NULL) || (cola->inicio == NULL) )  return NULL;
	nodo_c* nodo = cola->inicio;
	void* valor = nodo->dato;
	cola->inicio = nodo->siguiente;
	free(nodo);
	return  valor;
}


void cola_destruir(cola_t *cola, void destruir_dato(void*))
{
	void* dato;
	while ( !(cola_esta_vacia(cola)) )
	{
		dato = cola_desencolar(cola);
		if (destruir_dato != NULL) destruir_dato(dato);
	}
	free(cola);
}
