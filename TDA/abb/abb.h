#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stddef.h>


/******************************************************************
*                  DEFINICION TIPOS DE DATOS
******************************************************************/
typedef struct abb_iter abb_iter_t;

typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);

typedef void (*abb_destruir_dato_t) (void *);


/******************************************************************
*                  DEFINICION FUNCIONES ABB
******************************************************************/


// Crea el ABB en caso de que no lo pueda crear devuelve NULL
// Post: devuelve un ABB con su funcion de comparar, destruccion
// y con raiz NULL. En caso de que no pueda crearla devuelve NULL.
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);



bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

void *abb_borrar(abb_t *arbol, const char *clave);

void *abb_obtener(const abb_t *arbol, const char *clave);

bool abb_pertenece(const abb_t *arbol, const char *clave);


// Funcion que permite saber la cantidad de elemtos del arbol.
// Post: devuelve la cantidad de elemento del arbol.
size_t abb_cantidad(abb_t *arbol);

// Pre: el arbol deve existir.
// Post: destruye el arbol.
void abb_destruir(abb_t *arbol);


/******************************************************************
*                       ITERADOR INTERNO
******************************************************************/

// Pre: el arbol existe y se debe mandar una funcion visitar.
// Post: recorre cada uno de los elementos del arbol, segun el
// resultado de la funcion vistar.
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);



/******************************************************************
*                       ITERADOR EXTERNO
******************************************************************/

// Crea el iterador del arbol y lo deja posicionado en el
// nodo actual.
// Pre: el arbol debe existir.
// Post: devuelte el iterador en la posicion actual. En caso de
// que el arbol este vacio, el actual apunta a NULL.
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

// Permite avanzar en el iterador.
// Pre: el iterador debe existir.
// Post: devuelve verdadero en caso de que pueda avanzar
// y falso en caso de que no.
bool abb_iter_in_avanzar(abb_iter_t *iter);

// Devuelve la clave actual del iterador.
// Pre: iterador debe existir.
// Post: devuelve la clave almacenada en la posicion actual
// del iterador. En caso de que este al final, devuelte NULL.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

// Permite saber si el iterador se encuentra al final.
// Pre: el iterador debe existir.
// Post: devuelve verdadero en caso de que este al final,
// falso en caso de que no este al final.
bool abb_iter_in_al_final(const abb_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador debe existir.
void abb_iter_in_destruir(abb_iter_t* iter);


#endif
