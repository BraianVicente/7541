#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 ******************************************************************/

typedef struct vector
{
	size_t tam;
	int *datos;
} vector_t;

/*******************************************************************
 *                    PRIMITIVAS DEL VECTOR
 ******************************************************************/

// Crea un vector de tamaño tam
// Post: vector es una vector vacío de tamaño tam
vector_t* vector_crear(size_t tam);

// Destruye el vector
// Pre: el vector fue creado
// Post: se eliminaron todos los elementos del vector
void vector_destruir(vector_t *vector);

// Cambia el tamaño del vector
// Pre: el vector fue creado
// Post: el vector cambió de tamaño a nuevo_tam y devuelve true
// o el vector queda intacto y devuelve false si no se pudo cambiar el tamaño
// a nuevo_tam
bool vector_redimensionar(vector_t *vector, size_t nuevo_tam);

// Almacena en valor el dato guardado en la posición pos del vector
// Pre: el vector fue creado
// Post: se almacenó en valor el dato en la posición pos. Devuelve false si la
// posición es inválida (fuera del rango del vector, que va de 0 a tamaño-1)
bool vector_obtener(vector_t *vector, size_t pos, int *valor);

// Almacena el valor en la posición pos
// Pre: el vector fue creado
// Post: se almacenó el valor en la posición pos. Devuelve false si la posición
// es inválida (fuera del rango del vector, que va de 0 a tamaño-1) y true si
// se guardó el valor con éxito.
bool vector_guardar(vector_t *vector, size_t pos, int valor);

// Devuelve el tamaño del vector
// Pre: el vector fue creado
size_t vector_obtener_tamanio(vector_t *vector);

/*******************************************************************
 *                        IMPLEMENTACION
 ******************************************************************/

// Crea un vector de tamaño tam
// Post: vector es una vector vacío de tamaño tam
vector_t* vector_crear(size_t tam)
{
	vector_t* vector = malloc(sizeof(vector_t));
	if (vector == NULL) return NULL;

	vector->datos = malloc(tam * sizeof(int));
	if (vector->datos == NULL)
	{
	    free(vector);
	    return NULL;
	}
	vector->tam = tam;
	return vector;
}

// Destruye el vector
// Pre: el vector fue creado
// Post: se eliminaron todos los elementos del vector
void vector_destruir(vector_t *vector)
{
	if ( vector->datos!=NULL ) free(vector->datos);
	if ( vector!=NULL) free(vector);
}

// Cambia el tamaño del vector
// Pre: el vector fue creado
// Post: el vector cambió de tamaño a nuevo_tam y devuelve true
// o el vector queda intacto y devuelve false si no se pudo cambiar el tamaño
// a nuevo_tam
bool vector_redimensionar(vector_t *vector, size_t tam_nuevo)
{
	int* datos_nuevo = realloc(vector->datos, tam_nuevo * sizeof(int));
	// Cuando tam_nuevo es 0, es correcto que devuelva NULL
	// En toda otra situación significa que falló el realloc
	if (tam_nuevo > 0 && datos_nuevo == NULL)
	{
	    return false;
	}
	vector->datos = datos_nuevo;
	vector->tam = tam_nuevo;
	return true;
}

// Almacena en valor el dato guardado en la posición pos del vector
// Pre: el vector fue creado
// Post: se almacenó en valor el dato en la posición pos. Devuelve false si la
// posición es inválida (fuera del rango del vector, que va de 0 a tamaño-1)
bool vector_obtener(vector_t *vector, size_t pos, int *valor)
{
	if (vector->datos == NULL || vector->tam == 0) return false;
	if ( (pos>=0) && (((vector->tam)-1)>=pos )) {
		*valor=vector->datos[pos];
		return true;
	}
	return false;
}

// Almacena el valor en la posición pos
// Pre: el vector fue creado
// Post: se almacenó el valor en la posición pos. Devuelve false si la posición
// es inválida (fuera del rango del vector, que va de 0 a tamaño-1) y true si
// se guardó el valor con éxito.
bool vector_guardar(vector_t *vector, size_t pos, int valor)
{
	if ( vector->datos==NULL || (vector->tam == 0) ) return false;
	if ( (pos>=0) && (((vector->tam)-1)>=pos ))	{
		vector->datos[pos]=valor;
		return true;
	} else return false;
}

// Devuelve el tamaño del vector
// Pre: el vector fue creado
size_t vector_obtener_tamanio(vector_t *vector)
{
if ( vector!=NULL )return vector->tam;
	else return 0;
}


/*******************************************************************
 *                        PRUEBAS UNITARIAS
 ******************************************************************/

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
	printf("%s: %s\n", name, result? "OK" : "ERROR");
}

/* Pruebas para un vector de tamanio 0*/
void pruebas_vector_nulo()
{
	printf("INICIO DE PRUEBAS CON VECTOR DE TAMANIO 0\n");

	/* Declaro las variables a utilizar*/
	vector_t* vec = vector_crear(0);

	/* Inicio de pruebas */
	print_test("crear vector con tamanio 0", vec != NULL);
	print_test("obtener tamanio vector es 0", vector_obtener_tamanio(vec) == 0);

	/* Pruebo que guardar en un vector de tamanio 0 devuelve false siempre (no se puede guardar) */
	print_test("guardar en vec[0] es false", !vector_guardar(vec, 0, 5));
	print_test("guardar en vec[1] es false", !vector_guardar(vec, 1, 10));
	print_test("guardar en vec[15] es false", !vector_guardar(vec, 15, 0));

	/* Pruebo que obtener valores de un vector de tamaño 0 devuelve false */
	int valor;
	print_test("obtener vec[0] es false", !vector_obtener(vec, 0, &valor));
	print_test("obtener vec[1] es false", !vector_obtener(vec, 1, &valor));

	/* Destruyo el vector*/
	vector_destruir(vec);
	print_test("el vector fue destruido", true);
}

/* Pruebas de guardar y obtener algunos elementos*/
void pruebas_vector_algunos_elementos()
{
	printf("INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS\n");

	/* Creo un vector de tamanio 5*/
	vector_t* vec2 = vector_crear(5);

	print_test("crear vec2 con tamanio 5", vec2 != NULL);
	print_test("obtener tamanio es 5", vector_obtener_tamanio(vec2) == 5);

	/* Pruebo que guardar en un vector de tamanio 5 funciona para posiciones menores que 5 */
	print_test("guardar 20 en vec2[0] es true", vector_guardar(vec2, 0, 20));
	print_test("guardar 30 en vec2[1] es true", vector_guardar(vec2, 1, 30));
	print_test("guardar 15 en vec2[0] es true", vector_guardar(vec2,0,15));
	print_test("guardar 7 en vec2[4] es true", vector_guardar(vec2, 4, 7));

	/* Pruebo que guardar en un vector de tamanio 5 no funciona para posiciones mayores o iguales que 5 */
	print_test("guardar 35 en vec2[5] es false", !vector_guardar(vec2, 5, 35));
	print_test("guardar 40 en vec2[6] es false", !vector_guardar(vec2, 6, 40));

	/* Pruebo obtener los valores de un vector previamente guardados */
	int valor;
	print_test("se puede obtener vec2[0]", vector_obtener(vec2, 0, &valor));
	print_test("obtener vec2[0] es 15", valor == 15);
	print_test("se puede obtener vec2[1]", vector_obtener(vec2, 1, &valor));
	print_test("obtener vec2[1] es 30", valor == 30);
	print_test("no se puede obtener vec2[5]", !vector_obtener(vec2, 5, &valor));
	print_test("valor no fue modificado", valor == 30);

	/* Destruyo el vector*/
	vector_destruir(vec2);
	print_test("el vector fue destruido", true);
}

/* Pruebas al redimensionar un vector (agrandar y achicar) */
void pruebas_vector_redimension()
{
	printf("INICIO DE PRUEBAS DE REDIMENSION\n");
	/* Creo un vector de tamanio 3*/
	vector_t* vec3 = vector_crear(3);

	/* Pruebo guardar elementos en el vector de tamanio 3*/
	print_test("guardar 5 en vec3[0] es true", vector_guardar(vec3, 0, 5));
	print_test("guardar 10 en vec3[1] es true", vector_guardar(vec3, 1, 10));

	/* Pruebo redimensionar (agrandar) el vector */
	print_test("redimensionar a tamanio 10", vector_redimensionar(vec3, 10));
	print_test("El nuevo tamanio del vector es 10", vector_obtener_tamanio(vec3) == 10);

	/* Pruebo que los elementos guardados antes son correctos*/
	int valor;
	print_test("puedo obtener el valor de vec3[0] luego de redimensionar (agrandar)", vector_obtener(vec3, 0, &valor));
	print_test("el valor contenido en vec3[0] es 5", valor == 5);
	print_test("puedo obtener el valor de vec3[1] luego de redimensionar (agrandar)", vector_obtener(vec3, 1, &valor));
	print_test("el valor contenido en vec3[1] es 10", valor == 10);

	/* Pruebo que se pueda agregar ahora en la posicion 5 */
	print_test("guardar 50 en vec3[5] es true, luego de redimensionar", vector_guardar(vec3, 5, 50));
	print_test("puedo obtener el valor de vec3[5], luego de redimensionar", vector_obtener(vec3, 5, &valor));
	print_test("el valor contenido en vec3[5] es 50", valor == 50);

	/* Pruebo redimensionar (achicar) el vector */
	print_test("redimensionar a tamanio 2", vector_redimensionar(vec3, 2));
	print_test("El nuevo tamanio del vector es 2", vector_obtener_tamanio(vec3) == 2);

	/* Pruebo que los elementos de las primeras posiciones sigan estando*/
	print_test("puedo obtener el valor de vec3[0] luego de redimensionar (achicar)", vector_obtener(vec3, 0, &valor));
	print_test("el valor contenido en vec3[0] es 5", valor == 5);
	print_test("puedo obtener el valor de vec3[1] luego de redimensionar (achicar)", vector_obtener(vec3, 1, &valor));
	print_test("el valor contenido en vec3[1] es 10", valor == 10);

	/* Pruebo que no puedo leer lo que esta en la posicion 5*/
	print_test("no puedo obtener el valor de vec3[5] luego de redimensionar (achicar)", !vector_obtener(vec3, 5, &valor));

	/* Puebo que no puedo guardar en la posicion 5*/
	print_test("no puedo guardar 0 en vec3[5] luego de redimensionar (achicar)", !vector_guardar(vec3, 5, 0));

	/* Destruyo el vector*/
	vector_destruir(vec3);
	print_test("el vector fue destruido", true);
}

/* Pruebas del vector al trabajar con un volumen grande de elementos */
void pruebas_vector_volumen()
{
	printf("INICIO DE PRUEBAS DE VOLUMEN\n");

	/* Defino el tamanio del vector*/
	size_t tam = 10000;

	/* Creo el vector con ese tamanio*/
	vector_t* vec_vol = vector_crear(tam);

	/* Prueba de correcta creacion del vector */
	print_test("crear vec_vol con tamanio grande", vec_vol != NULL);
	print_test("obtener tamanio vec_vol es el indicado", vector_obtener_tamanio(vec_vol) == tam);

	/* Pruebo guardar en todas las posiciones */
	size_t i;
	bool ok = true;
	for (i = 0; i < tam; i++)
	{
		// Si algun elemento no se pudo guardar correctamente, ok sera false
		ok &= vector_guardar(vec_vol, i, i);
	}
	print_test("se pudieron guardar todos los elementos", ok);
	print_test("no se puede guardar un elemento en vec_vol[tam]", !vector_guardar(vec_vol, tam, 10));

	/* Pruebo que lo guardado sea correcto */
	ok = true;
	int valor;
	for (i = 0; i < tam; i++)
	{
		ok &= vector_obtener(vec_vol, i, &valor);
		ok &= (valor == i);
	}
	print_test("se pudieron obtener todos los elementos", ok);
	print_test("no se puede obtener el valor de vec_vol[tam]", !vector_obtener(vec_vol, tam, &valor));

	/* Destruyo el vector*/
	vector_destruir(vec_vol);
	print_test("el vector fue destruido", true);
}

/* Ejecuta todas las pruebas. */
void pruebas_vector()
{
	pruebas_vector_nulo();
	pruebas_vector_algunos_elementos();
	pruebas_vector_redimension();
	pruebas_vector_volumen();
}

/* Programa principal. */
int main(void)
{
	pruebas_vector();
	return 0;
}
