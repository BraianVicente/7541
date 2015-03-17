#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define VACIO 0
#define BORRADO 1
#define OCUPADO 2
#define TAMANIO_INICIAL 127
#define TAB_INICIO 0
#define HASH_AGRANDAR 1
#define HASH_DISMINUIR 0
#define HASH_ITER_AL_FINAL -1

typedef struct nodo_hash{
	size_t estado;
	void* dato;
	char* clave;
}nodo_hash_t;

typedef void (*hash_destruir_dato_t)(void *dato);

typedef struct hash{
	nodo_hash_t** datos;
	size_t cantidad;
	size_t tamanio;
	size_t borrados;
	hash_destruir_dato_t destruir_dato;
} hash_t;

typedef struct hash_iter{
	const hash_t* hash;
	size_t actual;
	size_t recorrido;
} hash_iter_t;

/*******************************************************************
*             DECLARACION DE FUNCIONES DEL HASH
******************************************************************/

hash_t* hash_redimensionar(hash_t *hash, int redimension);

static size_t fhash(const char *clave, size_t tamanio);

size_t hash_cantidad(const hash_t *hash);

hash_t* hash_crear(hash_destruir_dato_t destruir_dato);

void hash_destruir(hash_t *hash);

bool hash_guardar(hash_t *hash, const char *clave, void *dato);

void *hash_borrar(hash_t *hash, const char *clave);

void *hash_obtener(const hash_t *hash, const char *clave);

bool hash_pertenece(const hash_t *hash, const char *clave);

hash_iter_t *hash_iter_crear(const hash_t *hash);

bool hash_iter_avanzar(hash_iter_t *iter);

const char *hash_iter_ver_actual(const hash_iter_t *iter);

bool hash_iter_al_final(const hash_iter_t *iter);

void hash_iter_destruir(hash_iter_t *iter);

/*******************************************************************
*                     FUNCION DE HASHING
******************************************************************/

static uint32_t rc_crc32(uint32_t crc, const char *buf, size_t len)
{
	static uint32_t table[256];
	static int have_table = 0;
	uint32_t rem;
	uint8_t octet;
	int i, j;
	const char *p, *q;

	/* This check is not thread safe; there is no mutex. */
	if (have_table == 0) {
		/* Calculate CRC table. */
		for (i = 0; i < 256; i++) {
			rem = i;  /* remainder from polynomial division */
			for (j = 0; j < 8; j++) {
				if (rem & 1) {
					rem >>= 1;
					rem ^= 0xedb88320;
				} else
					rem >>= 1;
			}
			table[i] = rem;
		}
		have_table = 1;
	}

	crc = ~crc;
	q = buf + len;
	for (p = buf; p < q; p++) {
		octet = *p;  /* Cast to unsigned octet. */
		crc = (crc >> 8) ^ table[(crc & 0xff) ^ octet];
	}
	return ~crc;
}


static size_t fhash(const char *clave, size_t tamanio){

	size_t hashing = rc_crc32(0, clave, strlen(clave));
	return hashing % tamanio;
}

/*******************************************************************
* 	          IMPLEMENTACION DE PRIMITIVAS DEL HASH
******************************************************************/

size_t hash_cantidad(const hash_t *hash){
	return hash->cantidad;
}

// Devuelve una tabla de hash vacia del tamanio ingresado.
// Pre: se debe ingresar un tamanio mayor a 0.
// Post: devuelve la tabla de hash con sus correspondientes nodos vacios.
static nodo_hash_t** hash_crear_tabla(size_t tamanio){

	nodo_hash_t** aux = malloc((tamanio)*sizeof(nodo_hash_t));
	if (aux != NULL) {

		for(size_t i = 0; i <= tamanio - 1;i++)
		{
			nodo_hash_t* nodo = malloc(sizeof(nodo_hash_t));
			nodo->estado = VACIO;
			nodo->dato = NULL;
			nodo->clave = NULL;
			aux[i] = nodo;
		}
	}

	return aux;
}

hash_t* hash_crear(hash_destruir_dato_t destruir_dato){


	hash_t* hash = malloc(sizeof(hash_t));
	if (hash == NULL) return NULL;

	hash->cantidad = 0;
	hash->borrados = 0;
	hash->tamanio = TAMANIO_INICIAL;
	hash->destruir_dato = destruir_dato;

	nodo_hash_t** aux = hash_crear_tabla(TAMANIO_INICIAL);
	if (aux == NULL){
		free(hash);
		return NULL;
	}
	hash->datos = aux;
	return hash;
}

// Destruye la tabla de hash y todos sus nodos.
// Pre: la tabla de hash debe existir, se debe indicar el tamanio de dicha tabla y
// se debe ingresar la funcion de destruccion de datos que guarda el hash. En caso de
// que no se deseen destruir, indicar NULL.
// Post: la tabla de hash queda vacia.
static void hash_destruir_datos(nodo_hash_t** datos,size_t tamanio, hash_destruir_dato_t destruir_dato ){

	for(size_t i = 0;i <= tamanio - 1;i++){
		if (datos[i]->estado == OCUPADO){
			if (destruir_dato != NULL){
				if (datos[i]->dato != NULL) destruir_dato(datos[i]->dato);
			}
			free(datos[i]->clave);
		}
		free(datos[i]);
	}
}

void hash_destruir(hash_t *hash){
	hash_destruir_datos(hash->datos,hash->tamanio,hash->destruir_dato);
	free(hash->datos);
	free(hash);
}

// Encuentra la posicion que ocupa la clave indicada o en su defecto una posicion vacia.
// Pre: la tabla de hash debe existir, se debe indicar el tamanio de dicha tabla,
// la clave que se desea buscar y ademas se debe indicar una semilla(i) desde donde se
// comienza a buscar.
// Post: la semilla(i) contiene la posicion encontrada(ya sea ocupada o vacia).
static void hash_obtener_posicion(nodo_hash_t** datos, const char *clave,size_t* i ,size_t tamanio){


// Si esta ocupado no busca otra posicion en el hash.
	if ( datos[*i]->estado == OCUPADO ){
		if (strcmp(datos[*i]->clave,clave) == 0) return;
	}

// Recorro hasta encontrar una posicion vacia para guardar.
	while ( datos[*i]->estado != VACIO ){
		*i = *i + 1;
		*i = *i % (tamanio);
		if ( datos[*i]->estado == OCUPADO ){
			if ( strcmp(datos[*i]->clave,clave) == 0 ) return;
		}
	}
// Cuando salgo comparo por el estado.
}

// Crea un duplicado de la clave indicada.
// Pre: la clave debe existir.
// Post: devuelve el puntero a la clave duplicada.
static char* duplicar_clave(const char* clave){
	char* clave_aux = malloc((strlen(clave) + 1)*sizeof(char));
	if (clave_aux == NULL) return NULL;
	strcpy(clave_aux,clave);
	return clave_aux;
}

// Pre: si se quiere agrandar redimensionar debe ser 1, si se quiere achicar,
// redimensionar debe ser 0
// Post: devuelve el hash con el nuevo tamanio. En caso de que no se pueda
// crear devuelve el hash sin modificaciones.
hash_t* hash_redimensionar(hash_t *hash, int redimension){

	size_t tamanio_nuevo;
	if (redimension == HASH_DISMINUIR) tamanio_nuevo = hash->tamanio / 2 ;
	if (redimension == HASH_AGRANDAR) tamanio_nuevo = 2*(hash->tamanio);

	nodo_hash_t** aux = hash_crear_tabla(tamanio_nuevo);
	hash_iter_t* iter = hash_iter_crear(hash);

	const char* char_actual =  hash_iter_ver_actual(iter);

	while (hash_iter_avanzar(iter)){
		size_t i = fhash(char_actual,tamanio_nuevo);
		i = i % tamanio_nuevo;
		hash_obtener_posicion(aux,char_actual,&i,tamanio_nuevo);
		char* char_aux = duplicar_clave(char_actual);
		aux[i]->clave = char_aux;
		aux[i]->dato = hash_obtener(hash,char_aux);
		aux[i]->estado = OCUPADO;

		if (!hash_iter_al_final(iter)){
			char_actual =  hash_iter_ver_actual(iter);
		}
	}
	hash_iter_destruir(iter);
// Es NULL porque no quiero destruir lo que contiene.
	hash_destruir_datos(hash->datos,hash->tamanio,NULL);

	free(hash->datos);

	hash->tamanio = tamanio_nuevo;
	hash->borrados = 0;
	hash->datos = aux;

	return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
	if (clave == NULL) return false;

	if ( ( ((hash->borrados) + (hash->cantidad) ) / hash->tamanio ) > 0.8 ){
		hash = hash_redimensionar(hash,HASH_AGRANDAR);
	}

	size_t i = fhash(clave,hash->tamanio);
	hash_obtener_posicion(hash->datos,clave,&i,hash->tamanio);

// Si el estado es ocupado, entonces tengo que reemplazar el dato.
	if(hash->datos[i]->estado == OCUPADO){
		if (hash->destruir_dato != NULL){
			if (hash->datos[i]->dato != NULL){
				hash->destruir_dato(hash->datos[i]->dato);
			}
		}
		hash->datos[i]->dato = dato;
		return true;
	}
	if (hash->datos[i]->estado == VACIO){
		char* clave_aux = duplicar_clave(clave);
		hash->datos[i]->clave = clave_aux;
		hash->cantidad++;
		hash->datos[i]->dato = dato;
		hash->datos[i]->estado = OCUPADO;

		return true;
	}
// Si el estado no es OCUPADO ni VACIO entonces no puedo guardar.
	return false;
}

void *hash_borrar(hash_t *hash, const char *clave){

	if( hash->tamanio  > TAMANIO_INICIAL*2  && (hash->borrados) > hash->tamanio/2){
		if ( ( ( (hash->borrados) + (hash->cantidad) )/ hash->tamanio ) < 0.1 ){

			hash = hash_redimensionar(hash,HASH_DISMINUIR);
		}
	}

	size_t i = fhash(clave,hash->tamanio);
	hash_obtener_posicion(hash->datos,clave,&i,hash->tamanio);
	if (hash->datos[i]->estado != OCUPADO) return NULL;
	void* aux = hash->datos[i]->dato;
	free(hash->datos[i]->clave);

	hash->datos[i]->dato = NULL;
	hash->datos[i]->clave = NULL;
	hash->datos[i]->estado = BORRADO;
	hash->borrados++;
	hash->cantidad--;

	return aux;
}

void *hash_obtener(const hash_t *hash, const char *clave){
	size_t i = fhash(clave,hash->tamanio);
	hash_obtener_posicion(hash->datos,clave,&i,hash->tamanio);
	if (hash->datos[i]->estado != OCUPADO) return NULL;
	return hash->datos[i]->dato;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
	if ( hash_obtener(hash,clave) != NULL ) return true;
	return false;
}

/*******************************************************************
* 	        IMPLEMENTACION DE PRIMITIVAS DEL HASH_ITER
******************************************************************/

// Busca desde una posicion dada el siguiente ocupado
// si no lo encuentra, es decir llega al final de la tabla
// devuelve HASH_ITER_AL_FINAL.
static size_t buscar_sig_pos_ocupada(const hash_t* hash, size_t inicio){

	while ( inicio <= hash->tamanio - 1 ){
		if ( hash->datos[inicio]->estado != OCUPADO ) inicio++;
		else break;
	}
	if (inicio == hash->tamanio) return HASH_ITER_AL_FINAL; // llegue al final de la tabla
	return inicio;
}

hash_iter_t *hash_iter_crear(const hash_t *hash){

	hash_iter_t* iter = malloc(sizeof(hash_iter_t));
	if (iter == NULL) return NULL;
	iter->hash = hash;
	iter->actual = buscar_sig_pos_ocupada(hash,TAB_INICIO);
	iter->recorrido = hash->cantidad;
	return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){

	if (hash_iter_al_final(iter)) return false;
	if ( (iter->hash->tamanio) == (iter->actual) ) return false;// estoy en el final de la tabla
	iter->actual = buscar_sig_pos_ocupada( iter->hash,iter->actual + 1 );
	iter->recorrido--;
	return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){

	if ( hash_iter_al_final(iter) )return NULL;
	if ( iter->actual == HASH_ITER_AL_FINAL ) return NULL;
	return iter->hash->datos[iter->actual]->clave;
}

bool hash_iter_al_final(const hash_iter_t *iter){

	if (iter->recorrido == 0) return true;
	return false;
}

void hash_iter_destruir(hash_iter_t *iter){
	free(iter);
}
