#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "home/champaine/7541/TDA/pila/pila.h"


#define IGUALES 0


/******************************************************************
*                  DEFINICION TIPOS DE DATOS
******************************************************************/

typedef int (*abb_comparar_clave_t) (const char *, const char *);

typedef void (*abb_destruir_dato_t) (void *);


typedef struct abb_iter{
	pila_t *pila_iter;
}abb_iter_t;

typedef struct nodo_abb{
	char *clave;
	void *dato;
	struct nodo_abb* izq;
	struct nodo_abb* der;
}nodo_abb_t;

typedef struct abb{
	nodo_abb_t *raiz;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
	size_t cantidad;
} abb_t;

/*******************************************************************
*             DECLARACION DE FUNCIONES DEL ABB
******************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

void *abb_borrar(abb_t *arbol, const char *clave);

void *abb_obtener(const abb_t *arbol, const char *clave);

bool abb_pertenece(const abb_t *arbol, const char *clave);

size_t abb_cantidad(abb_t *arbol);

void abb_destruir(abb_t *arbol);

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

bool abb_iter_in_avanzar(abb_iter_t *iter);

const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

bool abb_iter_in_al_final(const abb_iter_t *iter);

void abb_iter_in_destruir(abb_iter_t* iter);

static void *borrar_nodo(nodo_abb_t *actual, nodo_abb_t *anterior, abb_t *arbol);



/******************************************************************
*                  IMPLEMENTACION DE FUNCIONES ABB
******************************************************************/


// Crea el ABB en caso de que no lo pueda crear devuelve NULL
// Pre: se deben pasar las funciones cmp destruir_dato. Necesariamente
// la funcion cmp no puede ser NULL.
// Post: devuelve un ABB con su funcion de comparar, destruccion
// y con raiz NULL. En caso de que no pueda crearla devuelve NULL.
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* arbol = malloc(sizeof(abb_t)) ;
	if(!arbol) return NULL;
	arbol->raiz = NULL;
	arbol->cantidad = 0;
	arbol->cmp = cmp;
	arbol->destruir_dato = destruir_dato;
	return arbol;
}


//Funcion auxiliar para la creacion de nodos

static nodo_abb_t* nodo_crear(){

	nodo_abb_t* nodo = malloc(sizeof(nodo_abb_t));
	if (nodo == NULL)
		return NULL;
	nodo->clave = NULL;
	nodo->dato = NULL;
	nodo->izq = NULL;
	nodo->der = NULL;
	return nodo;
}


static nodo_abb_t* buscar_nodo(nodo_abb_t* raiz, const char* clave, const abb_t* arbol){

	if (raiz == NULL) return NULL;

	if (arbol->cmp(raiz->clave,clave) == IGUALES){
		return raiz; // CASO BASE
	}

	if ((raiz->der == NULL) && (raiz->izq == NULL)){
		return NULL; // NO ESTA
	}

	if (arbol->cmp(raiz->clave,clave) > IGUALES){
		raiz = raiz->izq;
		return buscar_nodo(raiz,clave,arbol);
	}

	raiz = raiz->der;
	return buscar_nodo(raiz,clave,arbol);

}

// La idea de la funcion es buscar el nodo en donde tenga que insertar
// sea a derecha o izquierda el nodo que me pasan como dato
// devuelvo un puntero para insertarlo alli.
// Uso const por que NO debo modificarlo solo buscar.
static bool buscar_ubicacion_nodo(nodo_abb_t* raiz,nodo_abb_t* nodo, const char *clave,  abb_t* arbol){

	if (arbol->raiz == NULL ) {
		arbol->raiz = nodo;
		arbol->cantidad++;
		return true;
	}


	if (arbol->cmp(raiz->clave,clave) == IGUALES){
		if (arbol->destruir_dato != NULL) arbol->destruir_dato(raiz->dato);
		raiz->dato = nodo->dato;
		free(nodo->clave);
		free(nodo);
		return true;
	}

	if (arbol->cmp(raiz->clave,clave) > IGUALES){
		if (raiz->izq == NULL ){
			raiz->izq = nodo;
			arbol->cantidad++;
			return true;
		}
		return buscar_ubicacion_nodo(raiz->izq,nodo,clave,arbol);
	}
	if (raiz->der == NULL){
		raiz->der = nodo;
		arbol->cantidad++;
		return true;
	}
	return buscar_ubicacion_nodo(raiz->der,nodo,clave,arbol);

	return false;
}


bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

	if (arbol == NULL) return false;

	nodo_abb_t* nodo = nodo_crear();
	if (nodo == NULL) return false;

	char* clave_aux = malloc((strlen(clave) + 1)*sizeof(char));
	if (clave_aux == NULL) return false;
	strcpy(clave_aux,clave);

	nodo->clave = clave_aux;
	nodo->dato = dato;
// Hice que busque la posicion para guardarlo al final. Agrega la cantidad.
	return buscar_ubicacion_nodo(arbol->raiz,nodo,clave,arbol);

}

// Funcion auxiliar para buscar el nodo a borrar.
// Pre: se deve mandar como actual el nodo a partir del cual se quiere buscar
// y en anterior, el anterior a este. En caso de que el actual sea la raiz
// anterior debe ser un nodo_abb_t* anterior == NULL.
// Post: el dato mandado en actual pasa a ser el que se quiere borrar y
// el anterior es el que apunta al actual.
static void *abb_buscar_borrar(nodo_abb_t *actual, nodo_abb_t *anterior, abb_t *arbol, const char *clave){
	// Caso Borde: esta vacio.
	if (actual == NULL) return NULL;
	// Caso Base.
	// Devuelvo el actual sin cambios.
	if (actual->clave == NULL) return NULL;
	if (arbol->cmp(actual->clave,clave) == IGUALES) return borrar_nodo(actual,anterior,arbol);


// Se supone que si la funcion cmp devuelve algo mayor a 0 es
// porque el segundo operando es mayor.
	if (arbol->cmp(actual->clave,clave) > IGUALES) return abb_buscar_borrar(actual->izq,actual,arbol,clave);
	else return abb_buscar_borrar(actual->der,actual,arbol,clave);
}

// Funcion que borra el caso de que un nodo sea hoja sin hijos.
// Post: devuelte el dato del nodo
static void *borrar_caso_1(nodo_abb_t *actual, nodo_abb_t *anterior, abb_t *arbol){

	void *dato = actual->dato;

	if (anterior == NULL) arbol->raiz = NULL;
	else{
		if (anterior->izq == actual) anterior->izq = NULL;
		if (anterior->der == actual) anterior->der = NULL;
	}
	arbol->cantidad--;
	free(actual->clave);
	free(actual);
	return dato;
}

// Funcion que borra en el caso de que el nodo sea una hoja con 1 solo hijo.
// Post: devuelte el dato del nodo
static void *borrar_caso_2(nodo_abb_t *actual, nodo_abb_t *anterior, abb_t *arbol){


	void *dato = actual->dato;
	if (anterior == NULL){
		if (actual->izq != NULL) arbol->raiz = actual->izq;
		if (actual->der != NULL) arbol->raiz = actual->der;
	}
	else{
		if (anterior->izq == actual){
			if (actual->izq != NULL) anterior->izq = actual->izq;
			if (actual->der != NULL) anterior->izq = actual->der;
		}

		if (anterior->der == actual){
			if (actual->izq != NULL) anterior->der = actual->izq;
			if (actual->der != NULL) anterior->der = actual->der;
		}
	}
	arbol->cantidad--;
	free(actual->clave);
	free(actual);
	return dato;
}


// Funcion que busca el minimo valor a partir de una hoja.
// Post: devuelte el dato del nodo
static void *buscar_reemplazante(nodo_abb_t* actual){

	if (actual->izq != NULL) return buscar_reemplazante(actual->izq);
	return actual;
}

// Funcion que borra en el caso de que el nodo tenga 2 hijos.
// Post: devuelte el dato del nodo
 void* borrar_caso_3(nodo_abb_t *actual, nodo_abb_t *anterior, abb_t *arbol){

	void* dato = actual->dato;
	nodo_abb_t* reemplazante = actual->der;
	reemplazante = buscar_reemplazante(reemplazante);

	char* clave_aux = malloc((strlen(reemplazante->clave) + 1)*sizeof(char));
	if (clave_aux == NULL)
	{
		free(reemplazante);
		return NULL;
	}
	strcpy(clave_aux,reemplazante->clave);

	void* dato_aux = abb_borrar(arbol,clave_aux);

	free(actual->clave);
	actual->clave = clave_aux;
	actual->dato = dato_aux;
	return dato;
}

// Funcion que elije que tipo de caso es (sin hijo, 1 hijo, 2 hijos)
// Post: devuelte el dato del nodo
static void *borrar_nodo(nodo_abb_t *actual, nodo_abb_t *anterior, abb_t *arbol){

	if ( (actual->izq == NULL) && (actual->der == NULL) ){
		return borrar_caso_1(actual,anterior,arbol);
	}
	if ( (actual->izq != NULL) && (actual->der != NULL) ){
		return borrar_caso_3(actual,anterior,arbol);
	}
	return borrar_caso_2(actual,anterior,arbol);

}

// Borra el nodo correspondiente a la clave ingresada.
// Post: devuelte el dato del nodo.
void *abb_borrar(abb_t *arbol, const char *clave){
	if (arbol == NULL) return NULL;
	nodo_abb_t *anterior = NULL;
	nodo_abb_t *actual = arbol->raiz;
// Caso borde de que este vacio.
	if (actual == NULL) return NULL;
	return 	abb_buscar_borrar(actual,anterior,arbol,clave);

}

void *abb_obtener(const abb_t *arbol, const char *clave){

	if (arbol->raiz == NULL) return NULL;
	nodo_abb_t* raiz = arbol->raiz;
	nodo_abb_t* aux = buscar_nodo(raiz,clave,arbol);
	if (aux == NULL) return NULL;

	return aux->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){

	if (arbol->raiz == NULL) return NULL;
	nodo_abb_t* raiz = arbol->raiz;
	nodo_abb_t* aux = buscar_nodo(raiz,clave,arbol);
	if (aux == NULL) return false;
	return true;
}

// Funcion que permite saber la cantidad de elemtos del arbol.
// Post: devuelve la cantidad de elemento del arbol.
size_t abb_cantidad(abb_t *arbol){
	return arbol->cantidad;
}

// Caso base, el nodo es una hoja(rama sin hijos)
// En caso de que el "hijo" sea "hoja", destruyo la "hoja".
static void destruir_nodo(nodo_abb_t* nodo_abb, void destruir_dato(void *)){

	if (nodo_abb->izq != NULL){
		destruir_nodo(nodo_abb->izq, destruir_dato);
	}
	if (nodo_abb->der != NULL) {
		destruir_nodo(nodo_abb->der, destruir_dato);
	}
	if (destruir_dato != NULL) destruir_dato(nodo_abb->dato);
	free(nodo_abb->clave);
	free(nodo_abb);
}

// Destruye el arbol previamente creado.
// Pre: el arbol deve existir.
// Post: destruye el arbol y todos sus elementos.
void abb_destruir(abb_t *arbol){
	if (arbol->raiz != NULL) destruir_nodo(arbol->raiz,arbol->destruir_dato);
	free(arbol);
}

/******************************************************************
*                     ITERADOR INTERNO
******************************************************************/

// Pre: el nodo exista.
// Post: recorre el arbol inorder, desde la hoja que se le paso
// siempre que la funcion visitar devuelva verdadero. En caso de
// que visitar sea falso termina el recorrido.
static bool nodo_abb_in_order(nodo_abb_t *nodo_abb, bool visitar(const char *, void *, void *), void *extra){

	// Si el hijo izq no es NULL lo visita.
	// Si la visita del hijo izq es falsa termina.
	if (nodo_abb->izq != NULL)
		return (nodo_abb_in_order(nodo_abb->izq,visitar,extra));

	// Visita el nodo actual.
	// Si la visita es falsa termina.
	if (!visitar(nodo_abb->clave,nodo_abb->dato,extra)) return false;

	// Si el hijo der no es NULL lo visita.
	// Si la visita del hijo der es falsa termina.
	if (nodo_abb->der != NULL)
		return nodo_abb_in_order(nodo_abb->der,visitar,extra);
	// Si paso por todo devuelte ok y sigue la recursividad
	// en caso de que deba seguir.
	return true;
}

// Pre: el arbol existe y se debe mandar una funcion visitar.
// Post: recorre cada uno de los elementos del arbol, segun el
// resultado de la funcion vistar.
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
	// Me parece demasiado sencillo algo debo estar obviando.
	if (visitar == NULL) return;
	if (arbol->raiz != NULL) nodo_abb_in_order(arbol->raiz,visitar,extra);
}

/******************************************************************
*                       ITERADOR EXTERNO
******************************************************************/

// Avanza lo mas hacia la izquierda posible del padre.
// Pre: la pila del iterador debe existir.
// Post: deja en el tope de la pila el elemento mas al a izq.
static pila_t* avanzar_izq(pila_t* pila_iter,nodo_abb_t* nodo_abb){
	if (nodo_abb != NULL){
		pila_apilar(pila_iter,nodo_abb);
		return avanzar_izq(pila_iter,nodo_abb->izq);
	}
	return pila_iter;
}

// Crea el iterador del arbol y lo deja posicionado en el
// nodo actual.
// Pre: el arbol debe existir.
// Post: devuelte el iterador en la posicion actual. En caso de
// que el arbol este vacio, el actual apunta a NULL.
abb_iter_t *abb_iter_in_crear(const abb_t *arbol){

	abb_iter_t *iter = malloc(sizeof(abb_iter_t));
	if (!iter) return NULL;
	pila_t *pila = pila_crear();
	if (!pila){
		free(iter);
		return NULL;
	}
	iter->pila_iter = pila;

	if (arbol->raiz != NULL) iter->pila_iter = avanzar_izq(iter->pila_iter,arbol->raiz);

	return iter;
}

// Permite avanzar en el iterador.
// Pre: el iterador debe existir.
// Post: devuelve verdadero en caso de que pueda avanzar
// y falso en caso de que no.
bool abb_iter_in_avanzar(abb_iter_t *iter){
	if (abb_iter_in_al_final(iter))	return false;
	nodo_abb_t *desapilado = pila_desapilar(iter->pila_iter);

	if ( (desapilado->der != NULL) ){
		pila_apilar(iter->pila_iter,desapilado->der);
		nodo_abb_t* aux = desapilado->der;
		if (aux->izq != NULL) iter->pila_iter = avanzar_izq(iter->pila_iter,aux->izq);
	}
	return true;
}

// Devuelve la clave actual del iterador.
// Pre: iterador debe existir.
// Post: devuelve la clave almacenada en la posicion actual
// del iterador. En caso de que este al final, devuelte NULL.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter){

	if (abb_iter_in_al_final(iter)) return NULL;
	nodo_abb_t *tope = pila_ver_tope(iter->pila_iter);
	return tope->clave;

}

// Permite saber si el iterador se encuentra al final.
// Pre: el iterador debe existir.
// Post: devuelve verdadero en caso de que este al final,
// falso en caso de que no este al final.
bool abb_iter_in_al_final(const abb_iter_t *iter){
	if (pila_esta_vacia(iter->pila_iter)) return true;
	return false;
}

// Destruye el iterador.
// Pre: el iterador debe existir.
void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila_iter);
	free(iter);

}

