#include <stdio.h>
#include <stdbool.h>

/* ******************************************************************
 *                     FUNCIONES A COMPLETAR 
 * *****************************************************************/

/* La funcion swap intercambia dos valores enteros. */
void swap (int *x, int *y) {
	int aux=*x;
	*x=*y;
	*y=aux;
}

/* La funcion maximo busca el mayor elemento del 
 * arreglo y devuelve su posicion. Si el vector es
 * de largo 0, devuelve -1. */
int maximo(int vector[], int n) {
	if (n>0){
		int i,max=0;
		for (i=0; i<n; i++){
			if (vector[i] > vector[max]) max=i;
			}
		return max;
		} else return -1;
	}

/* La función comparar recibe dos vectores y dos largos, y devuelve -1 si
 	el primer vector es menor que el segundo, 0 si son iguales y 1 si el
 * segundo es menor. Un vector es menor a otro cuando al compararlos
 * elemento a elemento, el primer elemento en el que difieren no existe 
 * o es menor.*/
int comparar(int vector1[], int n1, int vector2[], int n2) {
	int i=0,val=0;
	while ( (i<=n1-1) && (i<n2-1) && (val==0) ) {
		if (vector1[i]==vector2[i]) {
			val=0;
			i++;
		}
	}

	if ( (n1==0) && (n2>0) ) val=-1;
	if ( (n1>0) && (n2==0) ) val=1;
	if ( (i<=n1-1) && (i>n2-1) && (val==0) ) val=1;
	else val=-1;
	return val;
}

/* La funcion seleccion ordena un arreglo recibido, mediante
 * el algoritmo de seleccion. */
void seleccion(int vector[], int n) {
	int i;
	if (n>0){
		for (i=n-1;i>0;i--){
			if (vector[maximo(vector,i)] > vector[i]) swap(&vector[i],&vector[maximo(vector,i)]);
		}
	}
}

/* ******************************************************************
 *                        PRUEBAS UNITARIAS 
 * *****************************************************************/

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result) {
	printf("%s: %s\n", name, result? "OK" : "ERROR");
}


/* Prueba que la funcion swap se ejecute correctamente. */
void prueba_swap() {
	int a = 5, b = 6;
	swap(&a,&b);
	print_test("Prueba swap 1", (a==6 && b==5));

	a = 10, b = -10;
	swap(&a,&b);
	print_test("Prueba swap 2", (a==-10 && b==10));
}

#define VACIO NULL
#define NVACIO 0

/* Prueba que la funcion maximo se ejecute correctamente. */
void prueba_maximo() {
	/* Declaro los vectores a utilizar. */
	int unico[] = { 8 };
	int vector1[] = { 1, 2, 3, 4, 5 };
	int vector2[] = { -1000, -1500, -2000, -3000 };
	int vector3[] = { 8, -10, 27, 3, -50 };
	/* Declaro los largos de los vectores */
	int nunico = 1;
	int nvector1 = 5;
	int nvector2 = 4;
	int nvector3 = 5;

	print_test("Prueba maximo vacio", maximo(VACIO, NVACIO) == -1);
	print_test("Prueba maximo unico", maximo(unico, nunico) == 0);
	print_test("Prueba maximo vector1", maximo(vector1, nvector1) == 4);
	print_test("Prueba maximo vector2", maximo(vector2, nvector2) == 0);
	print_test("Prueba maximo vector3", maximo(vector3, nvector3) == 2);
}

/* Prueba que la funcion comparar se ejecute correctamente. */
void prueba_comparar() {
	/* Declaro los vectores a utilizar. */
	int unico[] = { 5 };
	int vec1[] = { 1, 2, 3, 4, 5 };
	int vec2[] = { 1, 2, 5 };
	int vec3[] = { 5, 8, 9 };
	/* Declaro los largos de los vectores */
	int nunico = 1;
	int nvec1 = 5;
	int nvec2 = 3;
	int nvec3 = 3;

	print_test("Prueba comparar vacio, unico", 
	comparar(VACIO, NVACIO, unico, nunico) == -1);
	print_test("Prueba comparar unico, vec3", 
	comparar(unico, nunico, vec3, nvec3) == -1);
	print_test("Prueba comparar vec1, vec1", 
	comparar(vec1, nvec1, vec1, nvec1) == 0);
	print_test("Prueba comparar vec2, vec1", 
	comparar(vec2, nvec2, vec1, nvec1) == 1);
	print_test("Prueba comparar vec3, vec2", 
	comparar(vec3, nvec3, vec2, nvec2) == 1);
}

/* Prueba de la funcion seleccion. */
void prueba_seleccion() {
	/* Declaro los vectores a utilizar. */
	int unico[] = {8}, unico_ord[] = {8};
	int vec1[] = {3, 5, 4, 2, 1}, vec1_ord[] = {1, 2, 3, 4, 5};
	int vec2[] = {4, 8, 15, 16, 23, 42}, vec2_ord[] = {4, 8, 15, 16, 23, 42};
	int vec3[] = {-38, -46, -65, -78}, vec3_ord[] = {-78, -65, -46, -38};

	/* Declaro los largos de los veces */
	int nunico = 1;
	int nvec1 = 5;
	int nvec2 = 6;
	int nvec3 = 4;

	/* Prueba que la funcion seleccion se ejecute correctamente. */
	seleccion(VACIO, NVACIO);
	print_test("Prueba seleccion vacio", 
	comparar(VACIO, NVACIO, VACIO, NVACIO) == 0);

	seleccion(unico, nunico);
	print_test("Prueba seleccion unico", 
	comparar(unico, nunico, unico_ord, nunico) == 0);

	seleccion(vec1, nvec1);
	print_test("Prueba seleccion vec1", 
	comparar(vec1, nvec1, vec1_ord, nvec1) == 0);

	seleccion(vec2, nvec2);
	print_test("Prueba seleccion vec2", 
	comparar(vec2, nvec2, vec2_ord, nvec2) == 0);

	
	seleccion(vec3, nvec3);
	print_test("Prueba seleccion vec3", 
	comparar(vec3, nvec3, vec3_ord, nvec3) == 0);
}

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

/* Programa principal. */
int main(void) {
	/* Ejecutar todas las pruebas unitarias. */
	prueba_swap();
	prueba_maximo();
	prueba_comparar();
	prueba_seleccion();

	return 0;
}

