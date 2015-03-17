#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*******************************************************************
*             		ESTRUCTURAS DEL HASH
******************************************************************/

typedef void (*hash_destruir_dato_t)(void *dato);

typedef struct hash hash_t;

typedef struct hash_iter hash_iter_t;


/*******************************************************************
*             DECLARACION DE PRIMITIVAS DEL HASH
******************************************************************/

//Pre: el hash fue creado.
//Post: se devuelve la cantidad de claves validas en la tabla de hash.
size_t hash_cantidad(const hash_t *hash);

//Pre: se creo una funcion de destruccion para los datos a meter en la
//tabla de hash.
//Post: recibo una tabla de hash que tiene en cada posicion 3 campos:
//estado, clave, dato asociado. Si no puedo crearla devuelvo NULL.
hash_t* hash_crear(hash_destruir_dato_t destruir_dato);

//Pre: el hash fue creado.
//Post: elimina los datos validos, con la funcion de destruccion
//que se le paso al crearla y luego libera la memoria de la propia tabla.
void hash_destruir(hash_t *hash);

//Pre: el hash fue creado.
//Post: se aplica la funcion de hash a la clave, se obtiene una posicion
//en la tabla y se busca insertar en un VACIO. Si encuentra la clave
//para no tenerla duplicada se reemplaza el dato destruyendo el dato
//anterior con la funcion de destruccion. Se cambio el estado de VACIO
//a OCUPADO. Devuelvo true si pude guardar.
bool hash_guardar(hash_t *hash, const char *clave, void *dato);

//Pre: el hash fue creado.
//Post: se obtiene la posicion de la clave aplicando la funcion de hash
//y se busca hasta encontrar un lugar VACIO salteando los BORRADOS. Si no
//encuentro la clave a borrar devuelvo NULL. Si la encuentra devuelve el
//dato y reemplaza el estado de la posicion de OCUPADO a BORRADO.
void *hash_borrar(hash_t *hash, const char *clave);

//Pre: el hash fue creado.
//Post: se obtiene el dato o valor asociado a cierta clave sin borrarla,
//ni cambiar su estado. Si no encuentra el dato devuelve NULL.
void *hash_obtener(const hash_t *hash, const char *clave);


//Pre: el hash fue creado.
//Post: devuelve true si encuentra la clave, sino false.
bool hash_pertenece(const hash_t *hash, const char *clave);

/***********************************************************************/

//Pre: el hash fue creado.
//Post: crea una estructura iteradora que apunta al primer elemento valido
//(ocupado) de la tabla. Devuelve NULL si no pudo crearlo.
hash_iter_t *hash_iter_crear(const hash_t *hash);


//Pre: el iter fue creado.
//Post: el iterador avanza sobre la tabla salteando BORRADOS Y VACIOS,
//hasta la proxima posicion valida (ocupada). Devuelve false si el array
//no tiene una proxima posicion ocupada.
bool hash_iter_avanzar(hash_iter_t *iter);

//Pre: el iter fue creado.
//Post: el iterador devuelve la clave sin modificar su estado. Devuelve
//NULL en caso de querer ver actual si estoy al final de los datos validos.
const char *hash_iter_ver_actual(const hash_iter_t *iter);


//Pre: el iter fue creado.
//Post: devuelve true si estoy parado en el ultimo dato valido (ocupado).
bool hash_iter_al_final(const hash_iter_t *iter);


//Pre: el iter fue creado.
//Post: el iterador es destruido.
void hash_iter_destruir(hash_iter_t* iter);




