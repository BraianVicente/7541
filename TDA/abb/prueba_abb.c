#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "abb.h"


/* ******************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
	printf("%s: %s\n", name, result? "OK" : "ERROR");
}

/* Funcion auxliar para comparar strings reescrita para
 * que no rompa si alguno es NULL*/

int cmp_str(const char* s1, const char* s2){

	if ((s1 == NULL) && (s2 == NULL)) return 0;
	else if ((s1 != NULL) && (s2 == NULL)) return -1;
	else if ((s1 == NULL) && (s2 != NULL)) return 1;

	return strcmp(s1,s2);
}

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

void prueba_crear_abb_vacio()
{
	puts("\nINICIO DE PRUEBA_CREAR_ABB_VACIO");
	abb_t* arbol = abb_crear(NULL,NULL);

	print_test("Prueba abb crear abb vacio", arbol != NULL);
	print_test("Prueba abb la cantidad de elementos es 0", (abb_cantidad(arbol) == 0));
	print_test("Prueba abb obtener clave A, es NULL, no existe", abb_obtener(arbol, "A") == NULL);
	print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(arbol, "A"));
	print_test("Prueba abb borrar clave A, es NULL, no existe", abb_borrar(arbol, "A") == NULL);

	abb_destruir(arbol);
}

void prueba_iterar_abb_vacio()
{
	puts("\nINICIO DE PRUEBA_ITERAR_ABB_VACIO");
	abb_t* arbol = abb_crear(NULL,NULL);
	abb_iter_t* iter = abb_iter_in_crear(arbol);
	print_test("Prueba abb iter crear iterador abb vacio", iter != NULL);
	print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
	print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
	print_test("Prueba abb iter ver actual es NULL", abb_iter_in_ver_actual(iter) == NULL);

	abb_iter_in_destruir(iter);
	abb_destruir(arbol);
}

void prueba_obtener_pertenece(){
	puts("\nINICIO DE PRUEBA_OBTENER_PERTENECE");
	abb_t* arbol = abb_crear(cmp_str,NULL);

	char *clave1 = "perro", *valor1 = "guau";
	char *clave2 = "gato", *valor2 = "miau";
	char *clave3 = "vaca", *valor3 = "mu";

	print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1));
	print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2));
	print_test("Prueba abb insertar clave3", abb_guardar(arbol, clave3, valor3));
	print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(arbol) == 3);

	print_test("Prueba abb pertenece clave1, es true", abb_obtener(arbol, clave1) == valor1);
	print_test("Prueba abb pertenece clave2, es true", abb_obtener(arbol, clave2) == valor2);
	print_test("Prueba abb pertenece clave3, es true", abb_obtener(arbol, clave3) == valor3);

	abb_destruir(arbol);

}

void prueba_abb_insertar()
{
	puts("\nINICIO DE PRUEBA_ABB_INSERTAR");
	abb_t* arbol = abb_crear(cmp_str,NULL);

	char *clave1 = "perro", *valor1 = "guau";
	char *clave2 = "gato", *valor2 = "miau";
	char *clave3 = "vaca", *valor3 = "mu";

	/* Inserta 1 valor y luego lo borra */
	print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1));
	print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
	print_test("Prueba abb obtener clave1 es valor1", abb_obtener(arbol, clave1) == valor1);
	print_test("Prueba abb obtener clave1 es valor1", abb_obtener(arbol, clave1) == valor1);
	print_test("Prueba abb pertenece clave1, es true", abb_pertenece(arbol, clave1));
	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(arbol, clave1) == valor1);
	print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

	/* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
	print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2));
	print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
	print_test("Prueba abb obtener clave2 es valor2", abb_obtener(arbol, clave2) == valor2);
	print_test("Prueba abb obtener clave2 es valor2", abb_obtener(arbol, clave2) == valor2);
	print_test("Prueba abb pertenece clave2, es true", abb_pertenece(arbol, clave2));

	print_test("Prueba abb insertar clave3", abb_guardar(arbol, clave3, valor3));
	print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);
	print_test("Prueba abb obtener clave3 es valor3", abb_obtener(arbol, clave3) == valor3);
	print_test("Prueba abb obtener clave3 es valor3", abb_obtener(arbol, clave3) == valor3);
	print_test("Prueba abb pertenece clave3, es true", abb_pertenece(arbol, clave3));

	abb_destruir(arbol);
}

void prueba_abb_reemplazar()
{
	puts("\nINICIO DE PRUEBA_ABB_REEMPLAZAR");
	abb_t* arbol = abb_crear(cmp_str,NULL);

	char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
	char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

	/* Inserta 2 valores y luego los reemplaza */
	print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1a));
	print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(arbol, clave1) == valor1a);
	print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(arbol, clave1) == valor1a);
	print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2a));
	print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(arbol, clave2) == valor2a);
	print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(arbol, clave2) == valor2a);
	print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

	print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(arbol, clave1, valor1b));
	print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);
	print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);
	print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(arbol, clave2, valor2b));
	print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);
	print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);
	print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

	abb_destruir(arbol);
}

void prueba_abb_reemplazar_con_destruir()
{
	puts("\nINICIO DE PRUEBA_ABB_REEMPLAZAR_CON_DESTRUIR");
	abb_t* arbol = abb_crear(cmp_str,free);

	char *clave1 = "perro", *valor1a, *valor1b;
	char *clave2 = "gato", *valor2a, *valor2b;

	/* Pide memoria para 4 valores */
	valor1a = malloc(10 * sizeof(char));
	valor1b = malloc(10 * sizeof(char));
	valor2a = malloc(10 * sizeof(char));
	valor2b = malloc(10 * sizeof(char));

	/* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
	print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1a));
	print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(arbol, clave1) == valor1a);
	print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2a));
	print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(arbol, clave2) == valor2a);
	print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);


	print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(arbol, clave1, valor1b));
	print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);
	print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(arbol, clave2, valor2b));
	print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);

	print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

	/* Se destruye el abb (se debe liberar lo que quedó dentro) */
	abb_destruir(arbol);
}

void prueba_abb_borrar()
{
	puts("\nINICIO DE PRUEBA_ABB_BORRAR");
	abb_t* arbol = abb_crear(cmp_str,NULL);

	char *clave1 = "perro", *valor1 = "guau";
	char *clave2 = "gato", *valor2 = "miau";
	char *clave3 = "vaca", *valor3 = "mu";

	/* Inserta 3 valores y luego los borra */
	print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1));
	print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2));
	print_test("Prueba abb insertar clave3", abb_guardar(arbol, clave3, valor3));

	/* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
	print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(arbol, clave3));
	print_test("Prueba abb borrar clave3, es valor3", abb_borrar(arbol, clave3) == valor3);

	print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(arbol, clave3));
	print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(arbol, clave3));
	print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(arbol, clave3));
	print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

	print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(arbol, clave1));
	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(arbol, clave1) == valor1);
	print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(arbol, clave3));
	print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(arbol, clave1));
	print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(arbol, clave1));
	print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);

	print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(arbol, clave2));
	print_test("Prueba abb borrar clave2, es valor2", abb_borrar(arbol, clave2) == valor2);
	print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(arbol, clave3));
	print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(arbol, clave2));
	print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(arbol, clave2));
	print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

	abb_destruir(arbol);
}

void prueba_abb_clave_vacia()
{
	puts("\nINICIO DE PRUEBA_ABB_CLAVE_VACIA");
	abb_t* arbol = abb_crear(cmp_str,NULL);

	char *clave = "", *valor = "";

	print_test("Prueba abb insertar clave vacia", abb_guardar(arbol, clave, valor));
	print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
	print_test("Prueba abb obtener clave vacia es valor", abb_obtener(arbol, clave) == valor);
	print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(arbol, clave));
	print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(arbol, clave) == valor);
	print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

	abb_destruir(arbol);
}

void prueba_abb_valor_null()
{
	puts("\nINICIO DE PRUEBA_ABB_VALOR_NULL");

	abb_t* arbol = abb_crear(cmp_str,NULL);

	char *clave = "", *valor = NULL;

	/* Inserta 1 valor y luego lo borra */
	print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(arbol, clave, valor));
	print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
	print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(arbol, clave) == valor);
	print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(arbol, clave));
	print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(arbol, clave) == valor);
	print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

	abb_destruir(arbol);
}

void prueba_abb_volumen(size_t largo, bool debug)
{
	puts("\nINICIO PRUEBA_ABB_VOLUMEN");
	abb_t* arbol = abb_crear(cmp_str,NULL);

	const size_t largo_clave = 10;

	char letras[27] = "abcdefghijklmnopqrstuvwxyz";
	char** claves = malloc(sizeof(char*) * largo);

	int* valores[largo];
	int val;
	/* Inserta 'largo' parejas en el arbol */
	bool ok = true;

	size_t i;
	for( i = 0; i < largo ; i++){
		valores[i] = malloc(sizeof(int));
		val = rand () % largo;
		*valores[i] = val; // para que quede dentro del largo
		char* str = malloc(sizeof(char) * largo_clave);
		size_t j;
		for(j = 0; j < largo_clave - 1; j++){
			str[j] = letras[(rand()+9) % 26];
		}
		str[j] = '\0';
		claves[i] = str;
		ok = abb_guardar(arbol, claves[i], valores[i]);
		if (!ok) break;

	}

	if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
	if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(arbol) == largo);

	/* Verifica que devuelva los valores correctos */
	for ( i = 0; i < largo; i++) {
		ok = abb_pertenece(arbol, claves[i]);
		if (!ok) break;
		ok = abb_obtener(arbol, claves[i]) == valores[i];
		if (!ok) break;
	}

	if (debug) print_test("Prueba abb pertenece y obtener muchos elementos", ok);
	if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(arbol) == largo);
// HAY UN ERROR PORQUE REEMPLAZA CLAVES
	/* Verifica que borre y devuelva los valores correctos */
	ok = true;
	for ( i = 0; i < largo ; i++) {
		ok = abb_borrar(arbol, claves[i]) == valores[i];
		if (!ok) break;
	}

	if (debug) print_test("Prueba abb borrar muchos elementos", ok);
	if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);
	size_t num = abb_cantidad(arbol);
	int nuenum = num;
	printf("CANTIDAD ELEMENTOS %i\n",nuenum);

	/* Destruye el abb y crea uno nuevo que sí libera */
	abb_destruir(arbol);

	for( i = 0; i < largo ; i++) free(claves[i] );
	for( i = 0; i < largo ; i++) free(valores[i] );
	free(claves);

	/* Destruye el abb - debería liberar los enteros */

}

int buscar(const char* clave, char* claves[], size_t largo)
{
	for (size_t i = 0; i < largo; i++) {
		if (strcmp(clave, claves[i]) == 0) return i;
	}
	return -1;
}

void prueba_abb_iterar()
{
	puts("\nINICIO DE PRUEBA_ABB_ITERAR");
	abb_t* arbol = abb_crear(cmp_str,NULL);

	char *claves[] = {"perro", "gato", "vaca"};
	char *valores[] = {"guau", "miau", "mu"};

	/* Inserta 3 valores */
	print_test("Prueba abb insertar clave1", abb_guardar(arbol, claves[0], valores[0]));
	print_test("Prueba abb insertar clave2", abb_guardar(arbol, claves[1], valores[1]));
	print_test("Prueba abb insertar clave3", abb_guardar(arbol, claves[2], valores[2]));

	// Prueba de iteración sobre las claves almacenadas.
	abb_iter_t* iter = abb_iter_in_crear(arbol);
	const char *clave;
	int indice;

	print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

	/* Primer valor */
	clave = abb_iter_in_ver_actual(iter);
	indice = buscar(clave, claves, sizeof(claves) / sizeof(char));
	print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
	print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
	print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
	print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

	/* Segundo valor */
	clave = abb_iter_in_ver_actual(iter);
	indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
	print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
	print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
	print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
	print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

	/* Tercer valor */
	clave = abb_iter_in_ver_actual(iter);
	indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
	print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
	print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
	/* Se anula esta prueba por diferencias de criterios */
	abb_iter_in_avanzar(iter);
	print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

	/* Vuelve a tratar de avanzar, por las dudas */
	print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
	print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
	print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

	abb_iter_in_destruir(iter);
	abb_destruir(arbol);
}

void prueba_abb_iterar_volumen(size_t largo)
{
	puts("\nINICIO DE PRUEBA_ABB_ITERAR_VOLUMEN");
	abb_t* arbol = abb_crear(cmp_str,NULL);

	const size_t largo_clave = 10;

	char letras[27] = "abcdefghijklmnopqrstuvwxyz";
	char** claves = malloc(sizeof(char*) * largo);

	int* valores[largo];
	int val;
	/* Inserta 'largo' parejas en el arbol */
	bool ok = true;
	srand(time(NULL));

	int i;
	for( i = 0; i < largo ; i++){
		valores[i] = malloc(sizeof(int));
		val = rand () % largo;
		*valores[i] = val; // para que quede dentro del largo
		char* str = malloc(sizeof(char) * largo_clave);
		size_t j;
		for(j = 0; j < largo_clave - 1; j++){
			str[j] = letras[rand() % 26];
		}
		str[j] = '\0';
		claves[i] = str;
		ok = abb_guardar(arbol, claves[i], valores[i]);
		if (!ok) break;

	}


//	printf("CANTIDAD ELEMENTOS %i\n",abb_cantidad(arbol));

	// Prueba de iteración sobre las claves almacenadas.
	abb_iter_t* iter = abb_iter_in_crear(arbol);
	print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

	ok = true;
	const char *clave;
	int *valor;

	for (i = 0; i < largo; i++) {
		if ( abb_iter_in_al_final(iter) ) {
			ok = false;
			break;
		}
		clave = abb_iter_in_ver_actual(iter);
		if ( clave == NULL ) {
			ok = false;
			break;
		}
		valor = abb_obtener(arbol, clave);
		if ( valor == NULL ) {
			ok = false;
			break;
		}
		*valor = largo;
		abb_iter_in_avanzar(iter);
	}
	print_test("Prueba abb iteración en volumen", ok);
	print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == largo);
	if (i != largo) printf("Largo recorrido: %d\n", i);
	print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

	ok = true;
	for (i = 0; i < largo; i++) {
		if ( *valores[i] != largo ) {
			ok = false;
			break;
		}
	}
	print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

	for( i = 0; i < largo ; i++) free(claves[i] );
	for( i = 0; i < largo ; i++) free(valores[i] );
	free(claves);

	abb_iter_in_destruir(iter);
	abb_destruir(arbol);
}

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

/* Programa principal. */
int main(int argc, char** argv)
{

	if (argc < 2) {
		/* Ejecuta todas las pruebas unitarias. */
		prueba_crear_abb_vacio();
		prueba_iterar_abb_vacio();
		prueba_abb_insertar();
		prueba_obtener_pertenece();
		prueba_abb_reemplazar();
		prueba_abb_reemplazar_con_destruir();
		prueba_abb_borrar();
		prueba_abb_volumen(5000, true);
		prueba_abb_iterar();
		prueba_abb_iterar_volumen(5000);
	} else {
		size_t largo = atoi(argv[1]);
		prueba_abb_volumen(largo, false);
	}
	return 0;
}
