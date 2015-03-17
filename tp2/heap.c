#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM_INI 31
#define MAX 0
#define VACIO 0

/*
 * Implementación de un TAD cola de prioridad, usando un max-heap.
 *
 * Notar que al ser un max-heap el elemento mas grande será el de mejor
 * prioridad. Si se desea un min-heap, alcanza con invertir la función de
 * comparación.
 */

/* Prototipo de función de comparación que se le pasa como parámetro a las
 * diversas funciones del heap.
 * Debe recibir dos punteros del tipo de dato utilizado en el heap, y
 * debe devolver:
 *   menor a 0  si  a < b
 *       0      si  a == b
 *   mayor a 0  si  a > b
 */
typedef int (*cmp_func_t) (const void *a, const void *b);

/* Tipo utilizado para el heap. */
typedef struct heap{
	void** datos;
	size_t cantidad;
	size_t tamanio;
	cmp_func_t cmp;
} heap_t;

/* Función de heapsort genérica. Esta función ordena mediante heap_sort
 * un arreglo de punteros opacos, para lo cual requiere que se
 * le pase una función de comparación. Modifica el arreglo "in-place".
 * Notar que esta función NO es formalmente parte del TAD Heap.
 */

static void swap(void** x, void** y){
	void* aux = *x;
	*x = *y;
	*y = aux;
}

static bool heap_redimensionar(heap_t* heap, size_t tam_nuevo){
	void* datos_nuevo = realloc(heap->datos, tam_nuevo * sizeof(void*));
	if ( datos_nuevo == NULL) return false;
	heap->datos = datos_nuevo;
	heap->tamanio = tam_nuevo;
	return true;
}

// Hace upheap desde la posicion indicada, hasta el inicio del heap.
// Pre: el heap debe existir, el heap no debe estar vacio, la posicion indicada
static void upheap(void* elementos[], int padre, cmp_func_t cmp,int posicion){
	if ( (padre < 0) ) return;
	if (cmp(elementos[padre],elementos[posicion]) < 0 ){
		swap(&elementos[padre],&elementos[posicion]);
		posicion = padre ;
		padre = (posicion - 1 ) / 2 ;
		upheap(elementos,padre,cmp,posicion);
	}
}

static void heap_insertar_ultimo(heap_t* heap, void* elem){
	heap->datos[heap->cantidad] = elem;
	int posicion = heap->cantidad ;
	int padre = (posicion - 1 ) / 2 ;
	upheap(heap->datos,padre,heap->cmp,posicion);
}

static void downheap(void* elementos[], size_t cant, cmp_func_t cmp,size_t i){
	if ( (cant - 1) == i ) return;
// Caso borde estamos en la ultima posicion del heap.
	size_t hijo1 = 0;
	if ( ( (2 * i) + 1) <= (cant - 1) ) hijo1 = (2 * i) + 1;
	if ( (hijo1 == 0) || (elementos[hijo1] == NULL) ) return;
// Caso base de la recursion, el hijo1 es NULL.
	size_t hijo2 = 0;
	if ( ( (2 * i) + 2) <= (cant - 1) ) hijo2 = (2 * i) + 2;
	size_t hijo_mayor;
	if ( (hijo2 == 0) || (elementos[hijo2] == NULL) ) hijo_mayor = hijo1;
	else{
		if ( cmp(elementos[hijo1],elementos[hijo2]) < 0 ) hijo_mayor = hijo2;
		else hijo_mayor = hijo1;
	}
	if ( (cmp(elementos[hijo_mayor],elementos[i])) > 0 ){
		swap(&elementos[hijo_mayor],&elementos[i]);
		downheap(elementos,cant,cmp,hijo_mayor);
	}
}

// Hace un heap.
void heapify(void *elementos[], size_t cant, cmp_func_t cmp){
	for (int i = (cant/2) - 1; i >= 0; i--){
		downheap(elementos,cant,cmp,i);
	}
}

void heap_sort_orden(void *elementos[], size_t cant, cmp_func_t cmp){
	cant--;
	if (cant <= 0 ) return;
	swap(&elementos[0],&elementos[cant]);
	downheap(elementos,cant,cmp,0);
	heap_sort_orden(elementos,cant,cmp);

}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){

	heapify(elementos,cant,cmp);
	heap_sort_orden(elementos,cant,cmp);
}


/* Crea un heap. Recibe como único parámetro la función de comparación a
 * utilizar. Devuelve un puntero al heap, el cual debe ser destruido con
 * heap_destruir().
 */
heap_t *heap_crear(cmp_func_t cmp){

	heap_t* heap = malloc(sizeof(heap_t));
	if (heap == NULL) return NULL;
	heap->datos = calloc(TAM_INI,sizeof(void*));

	if (heap->datos == NULL){
		free(heap);
		return NULL;
	}
	heap->cantidad = VACIO;
	heap->tamanio = TAM_INI;
	heap->cmp = cmp;
	return heap;
}

/* Elimina el heap, llamando a la función dada para cada elemento del mismo.
 * El puntero a la función puede ser NULL, en cuyo caso no se llamará.
 * Post: se llamó a la función indicada con cada elemento del heap. El heap
 * dejó de ser válido. */
void heap_destruir(heap_t *heap, void destruir_elemento(void *)){

	if (destruir_elemento != NULL){
		for (int i = 0; ((i < heap->cantidad) && heap->datos[i]!=NULL); i++)
			destruir_elemento(heap->datos[i]);
	}
	free(heap->datos);
	free(heap);
}

/* Devuelve la cantidad de elementos que hay en el heap. */
size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad;
}

/* Devuelve true si la cantidad de elementos que hay en el heap es 0, false en
 * caso contrario. */
bool heap_esta_vacio(const heap_t *heap){

	if (heap->cantidad == 0) return true;
	return false;
}

/* Agrega un elemento al heap. El elemento no puede ser NULL.
 * Devuelve true si fue una operación exitosa, o false en caso de error.
 * Pre: el heap fue creado.
 * Post: se agregó un nuevo elemento al heap.
 */
bool heap_encolar(heap_t *heap, void *elem){
	if (elem == NULL) return false;

	if (heap->cantidad == heap->tamanio - 1) {
		if ( !heap_redimensionar(heap,heap->tamanio * 4) ) return false;
	}
	heap_insertar_ultimo(heap,elem);
	heap->cantidad++;
	return true;
}

/* Devuelve el elemento con máxima prioridad. Si el heap esta vacío, devuelve
 * NULL.
 * Pre: el heap fue creado.
 */
void* heap_ver_max(const heap_t *heap){

	if(heap->cantidad == VACIO) return NULL;
	return heap->datos[MAX];

}

/* Elimina el elemento con máxima prioridad, y lo devuelve.
 * Si el heap esta vacío, devuelve NULL.
 * Pre: el heap fue creado.
 * Post: el elemento desencolado ya no se encuentra en el heap.
 */

void *heap_desencolar(heap_t *heap){

	if (heap->tamanio > TAM_INI) {
		if ( (heap->cantidad * 4) == heap->tamanio - 1 )
			heap_redimensionar(heap,heap->tamanio / 2);
	}

	if (heap->cantidad  == VACIO) return NULL;
	void* maximo = heap->datos[MAX];

	heap->datos[MAX] = heap->datos[heap->cantidad - 1];
	heap->datos[heap->cantidad - 1] = NULL;
	downheap(heap->datos,heap->cantidad,heap->cmp,MAX);
	heap->cantidad--;

	return maximo;
}

