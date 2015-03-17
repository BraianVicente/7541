#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 ******************************************************************/

typedef struct lista{
	void* inicio;
	void* fin;
	size_t tamanio;
} lista_t;

typedef struct nodo_lista{
	void* dato;
	void* siguiente;

} nodo_l;

typedef struct iterador	{
	void* anterior;
	void* actual;
	size_t tamanio;
}lista_iter_t;


/*******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 ******************************************************************/

lista_t* lista_crear(){
	lista_t* lista = malloc(sizeof(lista_t));
	if (lista == NULL) return NULL;
	lista->inicio = NULL;
	lista->fin  = NULL;
	lista->tamanio = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t* lista){
	if (lista->inicio == NULL) return true;
	return false;
}

bool lista_insertar_primero(lista_t* lista, void* dato){
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

bool lista_insertar_ultimo(lista_t* lista, void *dato){
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

void* lista_borrar_primero(lista_t* lista){
	if (lista->tamanio == 0) return NULL;
	nodo_l* nodo = lista->inicio;
	if (lista->inicio == lista->fin ) lista->fin = NULL;
	lista->inicio = nodo->siguiente;
	lista->tamanio = lista->tamanio - 1;
	void* dato = nodo->dato;
	free(nodo);
	return dato;
}

void* lista_ver_primero(const lista_t* lista){
	if (lista->tamanio == 0) return NULL;
	nodo_l* nodo = lista->inicio;
	return nodo->dato;
}

size_t lista_largo(const lista_t* lista){
	return lista->tamanio;
}

void lista_destruir(lista_t* lista, void destruir_dato(void*)){
	while ( !(lista_esta_vacia(lista)) ){
		void* dato = lista_borrar_primero(lista);
		if ((destruir_dato != NULL)){
			destruir_dato(dato);
		}
	}
	free(lista);
}

/*******************************************************************
 *                PRIMITIVAS DEL ITERADOR
 ******************************************************************/

lista_iter_t* lista_iter_crear(const lista_t* lista){
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if (iter == NULL) return NULL;
	iter->anterior = NULL;
	iter->actual = lista->inicio;
	iter->tamanio = lista->tamanio;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t* iter){
	if (iter->actual == NULL) return false;
	nodo_l* nodo = iter->actual;
	iter->anterior = iter->actual;
	iter->actual = nodo->siguiente;
	return true;
}

void* lista_iter_ver_actual(const lista_iter_t* iter){
	if (iter->actual == NULL) return NULL;
	nodo_l* nodo;
	nodo = iter->actual;
	return nodo->dato;
}

bool lista_iter_al_final(const lista_iter_t* iter){
	if (iter->actual == NULL) return true;
	return false;
}

void lista_iter_destruir(lista_iter_t* iter){
	if (iter != NULL) free(iter);
}

bool lista_insertar(lista_t* lista, lista_iter_t* iter, void* dato){
	if ( (lista_esta_vacia(lista)) || (iter->anterior == NULL) ){
		if (lista_insertar_primero(lista,dato)){
			iter->actual = lista->inicio;
			iter->anterior = NULL;
			iter->tamanio = lista->tamanio;
			return true;
		}
		return false;
	}
	if (iter->actual == NULL) {
		if (lista_insertar_ultimo(lista,dato)){
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

void* lista_borrar(lista_t* lista, lista_iter_t* iter){
	if  (iter->actual == NULL) return NULL;
	if (iter->actual == lista->inicio ){
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

void lista_iterar(lista_t* lista, bool (*visitar)(void* dato, void* extra), void* extra){
	lista_iter_t* iter = lista_iter_crear(lista);
	void* dato = lista_iter_ver_actual(iter);
	while ( (lista_iter_avanzar(iter)) && (visitar(dato,extra)) ){
		dato = lista_iter_ver_actual(iter);
	}
	lista_iter_destruir(iter);
}
