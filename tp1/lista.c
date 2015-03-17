#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 ******************************************************************/

/* La cola está planteada como una cola de punteros genéricos. */

typedef struct lista
{
	void* inicio;
	void* fin;
	size_t tamanio;
} lista_t;

typedef struct nodo_lista
{
	void* dato;
	void* siguiente;
	
} nodo_l;

typedef struct iterador	
{
	void* anterior;
	void* actual;
	size_t tamanio;
}lista_iter_t;
	

/*******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 ******************************************************************/

// Crea una lista vacia.
// Post: Se devuelve una lista vacia.
lista_t* lista_crear()
{
	lista_t* lista = malloc(sizeof(lista_t));
	if (lista == NULL) return NULL;
	lista->inicio = NULL;
	lista->fin  = NULL;
	lista->tamanio = 0;
	return lista;
}

// Devuelve verdadero si la lista esta vacia, falsa en caso de que no
// Pre: La lista fue creada.
// Post: Devuelte verdadero en caso de que este vacia, falso en caso
// de que no lo este.
bool lista_esta_vacia(const lista_t* lista)
{
	if (lista->inicio == NULL) return true;
	return false;
}

// Inserta un elemento en la lista, en la primera posicion, en caso de
// que la lista este vacia, se le asigna al ultimo el mismo elemento 
// de la lista.
// Pre: La lista fue creada. La lista no debe estar asociada a
// ningun iterador.
// Post: Devuelte verdadero en caso de que se halla podido insertar
// sin problemas el elemento requerido. Falso en caso contrario.
bool lista_insertar_primero(lista_t* lista, void* dato)
{
	nodo_l* nodo = malloc(sizeof(nodo_l));
	if (nodo == NULL) return false;
	nodo->dato = dato;
	if (lista->inicio == NULL) nodo->siguiente = NULL;
	else nodo->siguiente = lista->inicio;
	if ( (lista->inicio == NULL) && (lista->fin == NULL) ) 	lista->fin = nodo;
	lista->inicio = nodo;
	lista->tamanio= lista->tamanio + 1;
	return true;	
}

// Inserta un elemento en la lista, en la ultima posicion, en caso de
// que la lista este vacia, se le asigna al primero el mismo elemento
// de la lista.
// Pre: La lista fue creada. La lista no debe estar asociada a
// ningun iterador.
// Post: Devuelte verdadero en caso de que se halla podido insertar
// sin problemas el elemento requerido. Falso en caso contrario.
bool lista_insertar_ultimo(lista_t* lista, void *dato)
{
	nodo_l* nodo_fin;
	nodo_l* nodo = malloc(sizeof(nodo_l));
	if (nodo == NULL) return false;
	if (lista->fin != NULL)
	{
		nodo_fin = lista->fin;
		nodo_fin->siguiente = nodo;
	}
	nodo->dato = dato;
	nodo->siguiente = NULL;
	if ( (lista->inicio == NULL) && (lista->fin == NULL) ) 	lista->inicio = nodo;
	lista->fin = nodo;
	lista->tamanio= lista->tamanio + 1;
	return true;
}

// Devuelte el primer elemento de la lista y luego lo borra de la lista.
// Pre: La lista fue creada y no esta vacia. La lista no debe estar
// asociada a ningun iterador.
// Post: Devuelve el dato borrado. En caso  de que la lista este vacia
// devuelte NULL.
void* lista_borrar_primero(lista_t* lista)
{
	if (lista->tamanio == 0) return NULL;
	nodo_l* nodo = lista->inicio;
	if (lista->inicio == lista->fin ) lista->fin = NULL;
	lista->inicio = nodo->siguiente;
	lista->tamanio = lista->tamanio - 1;
	void* dato = nodo->dato;
	free(nodo);
	return dato;
}

// Devuelte el primer elemento de la lista.
// Pre: La lista fue creada.
// Post: Devuelte el elemento de la posicion inicial. En caso de que la
// lista este vacia devuelte NULL.
void* lista_ver_primero(const lista_t* lista)
{
	if (lista->tamanio == 0) return NULL;
	nodo_l* nodo = lista->inicio;
	return nodo->dato;
}

// Devuelte el largo de la lista.
// Pre: La lista fue creada.
// Post: Devuelte el largo de la lista.
size_t lista_largo(const lista_t* lista)
{
	return lista->tamanio;
}

// Destruye todos los elementos de la lista
// Pre: La lista fue creada y no esta vacia. La lista no debe estar
// asociada a ningun iterador.
// Post: se detruyo la lista con todos sus elementos.
void lista_destruir(lista_t* lista, void destruir_dato(void*))
{
	while ( !(lista_esta_vacia(lista)) )
	{
		void* dato = lista_borrar_primero(lista);
		if ((destruir_dato != NULL)) 
		{
			destruir_dato(dato);
		}
	}
	free(lista);
}

/*******************************************************************
 *                PRIMITIVAS DEL ITERADOR
 ******************************************************************/

// Crea un iterador a una lista.
// Pre: La lista existe.
// Post: Devuelte el iterador. En caso de que no se pueda crear
// devuelte NULL.
lista_iter_t* lista_iter_crear(const lista_t* lista)
{
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if (iter == NULL) return NULL;
	iter->anterior = NULL;
	iter->actual = lista->inicio;
	iter->tamanio = lista->tamanio;
	return iter;
}

// Devuelte true si pudo avanzar, false en caso contrario.
// Pre: El iterador fue creado.
// Post: No puede avanzar cuando la posicion actual es NULL y
// devuelve falso. En caso de que no este en NULL devuelve verdadero.
bool lista_iter_avanzar(lista_iter_t* iter)
{
	if (iter->actual == NULL) return false;
	nodo_l* nodo = iter->actual;
	iter->anterior = iter->actual;
	iter->actual = nodo->siguiente;
	return true;	
}

// Devuelte el elemento de la posicion actual en la iteracion.
// Pre: El iterador fue creado.
// Post: En caso de que el iterador este vacio o de que la lista este 
// vacia, devuelte NULL.
void* lista_iter_ver_actual(const lista_iter_t* iter)
{
	if (iter->actual == NULL) return NULL;
	nodo_l* nodo;
	nodo = iter->actual;
	return nodo->dato;	
}

// Devuelte true si el iterador se encuentra al final, false en caso
// contrario.
// Pre: El iterador existe.
// Post: Devuelte verdadero en caso de que se pueda seguir iterando
// falso en caso de que no pueda.
bool lista_iter_al_final(const lista_iter_t* iter)
{
	if (iter->actual == NULL) return true;
	return false;
}

// Destruye el iterador.
// Pre: El iterador existe.
void lista_iter_destruir(lista_iter_t* iter)
{
	if (iter != NULL) free(iter);
}


// Inserta un elemento a la lista en la posicion actual.
// Pre: La lista existe y su iterador.
// Post: Devuelve verdadero en caso de que se inserte correctamente
// el elemento, falso en caso contrario.
bool lista_insertar(lista_t* lista, lista_iter_t* iter, void* dato)
{
	if ( (lista_esta_vacia(lista)) || (iter->anterior == NULL) )
	{
		if (lista_insertar_primero(lista,dato))
		{
			iter->actual = lista->inicio;
			iter->anterior = NULL;
			iter->tamanio = lista->tamanio;
			return true;
		}
		return false;
	}
	if (iter->actual == NULL) 
	{
		if (lista_insertar_ultimo(lista,dato))
		{
			iter->actual = lista->fin;
			iter->tamanio = lista->tamanio;
			return true;
		}
		return false;
	}
	nodo_l* nodo = malloc(sizeof(nodo_l));
	if (nodo == NULL) return false;
	nodo->siguiente = iter->actual;
	nodo->dato = dato;
	nodo_l* aux_nodo = iter->anterior;
	aux_nodo->siguiente = nodo;
	iter->actual = nodo;
	lista->tamanio = lista->tamanio + 1 ;
	iter->tamanio = lista->tamanio;
	return true;	
}

// Borra el elemento actual de la iteracion de la lista.
// Pre: La lista existe
// Post: Devuelte el dato borrado de la lista. En caso de que este 
// en la ultima posicion, borra el ultimo elemento y actualiza
// el fin de la lista. Devuelve NULL en caso de que
// no pueda borrar.
void* lista_borrar(lista_t* lista, lista_iter_t* iter)
{
	if  (iter->actual == NULL) return NULL;
	if (iter->actual == lista->inicio )
	{
		void* dato = lista_borrar_primero(lista);
		iter->actual = lista->inicio;
		return dato;
	}
	nodo_l* nodo_actual = iter->actual;
	nodo_l* nodo_anterior = iter->anterior;
	nodo_anterior->siguiente = nodo_actual->siguiente;
	iter->actual = nodo_actual->siguiente;
	if (nodo_actual->siguiente == NULL) lista->fin = iter->anterior;
	lista->tamanio = lista->tamanio - 1 ;
	iter->tamanio = lista->tamanio;
	void* datos = nodo_actual->dato;
	free(nodo_actual);
	return datos;
}

/*******************************************************************
 *                        ITERADOR INTERNO
 ******************************************************************/

// Primitivas de iterador interno (la función de callback "visitar"
// recibe el dato y un puntero extra, y devuelve true si se debe seguir
// iterando, false en caso contrario).
// Recibe una lista y una funcion con un dato extra, que le permite 
// crear un iterador y realizar lo que la funcion le establezca
// hasta que se termine la lista o que corte por la funcion externa,
// lo que ocurra primero.
// Pre: La lista fue creada, la funcion recibida es una funcion
// booleana. En caso de que no se utilize un dato extra enviar NULL.

void lista_iterar(lista_t* lista, bool (*visitar)(void* dato, void* extra), void* extra)
{
	lista_iter_t* iter = lista_iter_crear(lista);
	void* dato = lista_iter_ver_actual(iter);
	while ( (lista_iter_avanzar(iter)) && (visitar(dato,extra)) )
	{
		dato = lista_iter_ver_actual(iter);
	}
	lista_iter_destruir(iter);
}
