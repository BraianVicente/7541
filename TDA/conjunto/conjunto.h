#ifndef CONJUNTO_T
#define CONJUNTO_T
typedef int conjunto_dato_t;

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct conjunto conjunto_t;

/* Crea un conjunto de tamaño tam.
   Devuelve un puntero a NULL en caso de error. */
conjunto_t* conjunto_crear(int tamanio);

/* Agrega un dato al conjunto. Devuelve false en caso de error. */
bool conjunto_agregar(conjunto_t* conjunto, conjunto_dato_t dato);

/* Elimina un dato del conjunto. */
bool conjunto_eliminar(conjunto_t* conjunto, conjunto_dato_t dato);

/* Devuelve verdadero en caso de que el dato pertenezca al conjunto,
   falso en caso contrario. */
bool conjunto_pertenece(conjunto_t* conjunto, conjunto_dato_t dato);

/* Devuelve la unión de dos conjuntos en un conjunto nuevo.
   Devueve NULL en caso de error. */
conjunto_t* conjunto_union(conjunto_t* conjunto1, conjunto_t* conjunto2);

/* Devuelve la intersección de dos conjuntos en un conjunto nuevo.
   Devueve NULL en caso de error. */
conjunto_t* conjunto_interseccion(conjunto_t* conjunto1, conjunto_t* conjunto2);

/* Destruye el conjunto*/
void conjunto_destruir (conjunto_t* conjunto);

#endif