#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "conjunto.h"

/* Estructura que modela a un conjunto. */
struct conjunto {
    conjunto_dato_t* datos;
    size_t cant;
    size_t tam;
};


/* Crea un conjunto de tamaño tam.
   Devuelve un puntero a NULL en caso de error. */
conjunto_t* conjunto_crear(int tamanio)
{
    if (tamanio <= 0) return NULL;
    conjunto_t* conjunto = malloc(sizeof(conjunto_t));
    conjunto_dato_t* datos = malloc(tamanio*sizeof(conjunto_dato_t));
    if(!datos || !conjunto) {
        free(conjunto);
        free(datos);
        return NULL;
    }
    conjunto->datos = datos;
    conjunto->tam = tamanio;
    conjunto->cant = 0;
    return conjunto;
}

/* Agrega un dato al conjunto. Devuelve false en caso de error. */
bool conjunto_agregar(conjunto_t* conjunto, conjunto_dato_t dato)
{
    if(!conjunto) return false;
    if(conjunto_pertenece(conjunto, dato)) return false;
    if(conjunto->tam == conjunto->cant) return false;
    conjunto->datos[conjunto->cant] = dato;
    conjunto->cant++;
    return true;
}

/* Elimina un dato del conjunto. */
bool conjunto_eliminar(conjunto_t* conjunto, conjunto_dato_t dato)
{
    if(!conjunto) return false;
    for(size_t i = 0; i < conjunto->tam; i++) {
        if(conjunto->datos[i] == dato) {
            conjunto->datos[i] = conjunto->datos[conjunto->cant-1];
            conjunto->cant--;
            return true;
        }
    }
    return false;
}

/* Devuelve verdadero en caso de que el dato pertenezca al conjunto,
   falso en caso contrario. */
bool conjunto_pertenece(conjunto_t* conjunto, conjunto_dato_t dato)
{
    if(!conjunto) return false;
    for(size_t i = 0; i < conjunto->cant; i++) {
        if(conjunto->datos[i] == dato) return true;
    }
    return false;
}

/* Devuelve la unión de dos conjuntos en un conjunto nuevo.
   Devueve NULL en caso de error. */
conjunto_t* conjunto_union(conjunto_t* conjunto1, conjunto_t* conjunto2)
{
    if(!conjunto1 || !conjunto2) return NULL;
    conjunto_t* c_union = conjunto_crear(conjunto1->tam + conjunto2->tam);
    if(!c_union) return NULL;
    for(size_t i = 0; i < conjunto1->tam; i++)
        conjunto_agregar(c_union, conjunto1->datos[i]);
    for(size_t i = 0; i < conjunto2->tam; i++) {
        if(!conjunto_pertenece(conjunto1, conjunto2->datos[i]))
            conjunto_agregar(c_union, conjunto2->datos[i]);
    }
    return c_union;
}

/* Devuelve la intersección de dos conjuntos en un conjunto nuevo.
   Devueve NULL en caso de error. */
conjunto_t* conjunto_interseccion(conjunto_t* conjunto1, conjunto_t* conjunto2)
{
    if(!conjunto1 || !conjunto2) return NULL;
    conjunto_t* c_inter = conjunto_crear(conjunto1->tam);
    if(!c_inter) return NULL;
    for(size_t i = 0; i < conjunto1->tam; i++) {
        if(conjunto_pertenece(conjunto2, conjunto1->datos[i]))
                conjunto_agregar(c_inter, conjunto1->datos[i]);
    }
        return c_inter;
}

/* Destruye el conjunto*/
void conjunto_destruir (conjunto_t* conjunto)
{
    free(conjunto->datos);
    free(conjunto);
}
