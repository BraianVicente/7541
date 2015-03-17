#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAM_INI 50

/*******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 ******************************************************************/

typedef void (*destruir_dato_t)(void *dato);

typedef struct vector{
	void **datos;
	size_t tam;
	size_t cantidad;
	destruir_dato_t destruir_dato;
} vector_t;

/*******************************************************************
 *                        IMPLEMENTACION
 ******************************************************************/

vector_t* vector_crear(destruir_dato_t destruir_dato){

	vector_t* vector = malloc(sizeof(vector_t));
	if (vector == NULL) return NULL;

	vector->datos = malloc(TAM_INI * sizeof(void*));
	if (vector->datos == NULL)
	{
	    free(vector);
	    return NULL;
	}
	vector->tam = TAM_INI;
	vector->cantidad = 0;
	vector->destruir_dato = destruir_dato;
	return vector;
}

void vector_destruir(vector_t *vector){

	size_t cant = vector->cantidad;
	size_t i = 0;
	if(vector->destruir_dato != NULL){
		while ((cant!= 0) && (i < vector->tam)){
			vector->destruir_dato(vector->datos[i]);
			i++;
			cant--;
		}
	}
	free(vector->datos);
	free(vector);
}

static bool vector_redimensionar(vector_t *vector, size_t tam_nuevo){

	if (tam_nuevo <= 0) return false;

	void* datos_nuevo = realloc(vector->datos, tam_nuevo * sizeof(void*));
	if (datos_nuevo == NULL) return false;

	vector->datos = datos_nuevo;
	vector->tam = tam_nuevo;
	return true;
}

void* vector_obtener(vector_t *vector, size_t pos){
	if ((vector->tam <= pos) || (vector->cantidad <= pos)) return NULL;
	return vector->datos[pos];
}

bool vector_guardar(vector_t *vector, void* valor){

	if (vector->cantidad == vector->tam -1){
		if (!vector_redimensionar(vector, vector->tam * 2)) return false;
	}
	vector->datos[vector->cantidad] = valor;
	vector->cantidad++;
	return true;
}

size_t vector_obtener_tamanio(vector_t *vector){
	return vector->tam;
}

size_t vector_obtener_cantidad(vector_t *vector){
	return vector->cantidad;
}
