#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX 64
/*Se trata de una pila que contiene datos de tipo void*
 *(punteros genéricos).  La pila en sí está definida en el .c. 
 */

typedef struct  _pila {
    void** datos;
    size_t tamanio;
    size_t cantidad;
} pila_t;


/******************************************************************
 *                    PRIMITIVAS  A IMPLEMENTAR
 ******************************************************************/
// La constante determina a cuanto se va a redimensionar
// el la memoria que contiene los datos de la pila

// Crea una pila.
// Post: devuelve una nueva pila vacía.
pila_t* pila_crear()
{
	pila_t* pila = malloc( sizeof(pila_t) );
	if (pila == NULL) return NULL;
	pila->datos = malloc( sizeof(void*) );
	if (pila->datos == NULL) return NULL;
	pila->tamanio = 0;
	pila->cantidad = 0;
	return pila;
}

// Destruye la pila.
// Pre: la pila fue creada.
// Post: se eliminaron todos los elementos de la pila.
void pila_destruir(pila_t *pila)
{
	free(pila->datos);
	free(pila);	
}

// Devuelve verdadero o falso, según si la pila tiene o no elementos apilados.
// Pre: la pila fue creada.
bool pila_esta_vacia(const pila_t *pila)
{
	if ( pila->tamanio == 0 ) return true;
	if ( pila->cantidad == 0 ) return true;	
	return false;
}

// Redimensiola la pila segun tamanio_nuevo, devuelve true si
// se redimensiono correctamente y false si no se pudo
// Pre: la pila fue creada
// Post: devuelve la pila sin cambios si no se puede redimensionar
static bool pila_redimensionar(pila_t *pila, int tamanio_nuevo)
{
	void** new_dato = realloc (pila->datos, ( ((pila->tamanio) + tamanio_nuevo)  *  sizeof(void*))  );
	if ( new_dato != NULL ) 
	{
		pila->datos = new_dato;
		pila->tamanio = (pila->tamanio) + tamanio_nuevo  ;
		return true;
	}
	free(new_dato);
	return false;
	
}

// Agrega un nuevo elemento a la pila. Devuelve falso en caso de error.
// Pre: la pila fue creada.
// Post: se agregó un nuevo elemento a la pila, valor es el nuevo tope.

bool pila_apilar(pila_t *pila, void *valor)
{
	if ( pila->datos == NULL ) 
	{
			return false;
	}
	if ( pila_esta_vacia(pila) || ( ( (pila->tamanio) - (pila->cantidad )  ) == 0 ) )
	{
		if ( !(pila_redimensionar (pila, MAX)) ) return false;
	}
	pila->datos[pila->cantidad] = valor;
	pila->cantidad = pila->cantidad + 1 ;
	return true;

}

// Obtiene el valor del tope de la pila. Si la pila tiene elementos,
// se devuelve el valor del tope. Si está vacía devuelve NULL.
// Pre: la pila fue creada.
// Post: se devolvió el valor del tope de la pila, cuando la pila no está
// vacía, NULL en caso contrario.
void* pila_ver_tope(const pila_t *pila)
{
	if (pila->cantidad <= 0 ) return NULL;
	return pila->datos[(pila->cantidad - 1)];		
}

// Saca el elemento tope de la pila. Si la pila tiene elementos, se quita el
// tope de la pila, y se devuelve ese valor. Si la pila está vacía, devuelve 
// NULL.
// Pre: la pila fue creada.
// Post: si la pila no estaba vacía, se devuelve el valor del tope anterior 
// y la pila contiene un elemento menos.
void* pila_desapilar(pila_t *pila)
{
	if ( pila->datos == NULL || pila->cantidad == 0 ) return NULL;
	void* valor = pila->datos[pila->cantidad - 1] ;
	pila->cantidad= (pila->cantidad) - 1;
	if ( ( (pila->tamanio) - (pila->cantidad) ) >= (MAX + (MAX/2)) )
		pila_redimensionar(pila,(-MAX));
	return valor;	

}
