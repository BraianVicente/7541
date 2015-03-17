#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

/*******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 ******************************************************************/

typedef struct lista lista_t;
typedef struct iterador	lista_iter_t;

/*******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 ******************************************************************/

// Crea una lista vacia.
// Post: Se devuelve una lista vacia.
lista_t *lista_crear();

// Devuelve verdadero si la lista esta vacia, falsa en caso de que no
// Pre: La lista fue creada.
// Post: Devuelte verdadero en caso de que este vacia, falso en caso
// de que no lo este.
bool lista_esta_vacia(const lista_t *lista);

// Inserta un elemento en la lista, en la primera posicion, en caso de
// que la lista este vacia, se le asigna al ultimo el mismo elemento 
// de la lista.
// Pre: La lista fue creada. La lista no debe estar asociada a
// ningun iterador.
// Post: Devuelte verdadero en caso de que se halla podido insertar
// sin problemas el elemento requerido. Falso en caso contrario.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Inserta un elemento en la lista, en la ultima posicion, en caso de
// que la lista este vacia, se le asigna al primero el mismo elemento
// de la lista.
// Pre: La lista fue creada. La lista no debe estar asociada a
// ningun iterador.
// Post: Devuelte verdadero en caso de que se halla podido insertar
// sin problemas el elemento requerido. Falso en caso contrario.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Devuelte el primer elemento de la lista y luego lo borra de la lista.
// Pre: La lista fue creada y no esta vacia. La lista no debe estar
// asociada a ningun iterador.
// Post: Devuelve el dato borrado. En caso  de que la lista este vacia
// devuelte NULL.
void *lista_borrar_primero(lista_t *lista);

// Devuelte el primer elemento de la lista.
// Pre: La lista fue creada.
// Post: Devuelte el elemento de la posicion inicial. En caso de que la
// lista este vacia devuelte NULL.
void *lista_ver_primero(const lista_t *lista);

// Devuelte el largo de la lista.
// Pre: La lista fue creada.
// Post: Devuelte el largo de la lista.
size_t lista_largo(const lista_t *lista);

// Destruye todos los elementos de la lista
// Pre: La lista fue creada y no esta vacia. La lista no debe estar
// asociada a ningun iterador.
// Post: se detruyo la lista con todos sus elementos.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

/*******************************************************************
 *                PRIMITIVAS DEL ITERADOR
 ******************************************************************/

// Crea un iterador a una lista.
// Pre: La lista existe.
// Post: Devuelte el iterador. En caso de que no se pueda crear
// devuelte NULL.
lista_iter_t *lista_iter_crear(const lista_t *lista);

// Devuelte true si pudo avanzar, false en caso contrario.
// Pre: El iterador fue creado.
// Post: No puede avanzar cuando la posicion actual es NULL y
// devuelve falso. En caso de que no este en NULL devuelve verdadero.
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelte el elemento de la posicion actual en la iteracion.
// Pre: El iterador fue creado.
// Post: En caso de que el iterador este vacio o de que la lista este 
// vacia, devuelte NULL.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelte true si el iterador se encuentra al final, false en caso
// contrario.
// Pre: El iterador existe.
// Post: Devuelte verdadero en caso de que se pueda seguir iterando
// falso en caso de que no pueda.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: El iterador existe.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un elemento a la lista en la posicion actual.
// Pre: La lista existe y su iterador.
// Post: Devuelve verdadero en caso de que se inserte correctamente
// el elemento, falso en caso contrario.
bool lista_insertar(lista_t *lista, lista_iter_t *iter, void *dato);

// Borra el elemento actual de la iteracion de la lista.
// Pre: La lista existe
// Post: Devuelte el dato borrado de la lista. En caso de que este 
// en la ultima posicion, borra el ultimo elemento y actualiza
// el fin de la lista. Devuelve NULL en caso de que
// no pueda borrar.
void *lista_borrar(lista_t *lista, lista_iter_t *iter);

/*******************************************************************
 *                        ITERADOR INTERNO
 ******************************************************************/

// Recibe una lista y una funcion con un dato extra, que le permite 
// crear un iterador y realizar lo que la funcion le establezca
// hasta que se termine la lista o que corte por la funcion externa,
// lo que ocurra primero.
// Pre: La lista fue creada, la funcion recibida es una funcion
// booleana. En caso de que no se utilize un dato extra enviar NULL.
void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra);

#endif // LISTA_H
