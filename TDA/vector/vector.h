#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>

typedef void (*destruir_dato_t)(void *dato);

typedef struct vector vector_t;



/*******************************************************************
 *                    PRIMITIVAS DEL VECTOR
 ******************************************************************/

// Crea vector vacio de TAM_INI posiciones. Se debe pasar la funcion
// de destruccion de sus elementos.
// Post: devuelve un vector vacío
vector_t* vector_crear(destruir_dato_t destruir_dato);

// Destruye el vector
// Pre: el vector fue creado
// Post: se eliminaron todos los elementos del vector
void vector_destruir(vector_t *vector);

// Obtiene el dato guardado en la posicion especificada
// Pre: el vector fue creado
// Post: se obtiene el valor de la posicion pedida. Si la misma
// no estaba en el rango de los valores guardados [0..cantidad-1]
// se devuelve NULL. Tambien devuelve NULL si la posicion es mas grande
// que el tamaño del vector.
void* vector_obtener(vector_t *vector, size_t pos);

// Almacena el valor en la posición pos
// Pre: el vector fue creado
// Post: se guarda el valor en la posicion siguiente al guardado
// anterior. Devuelve false solo si al redimensionar no lo logra.
bool vector_guardar(vector_t *vector, void* valor);

// Devuelve el tamaño del vector
// Pre: el vector fue creado
size_t vector_obtener_tamanio(vector_t *vector);

// Devuelve la cantidad de elementos ocupados del vector
// Pre: el vector fue creado
size_t vector_obtener_cantidad(vector_t *vector);

#endif // VECTOR_H
