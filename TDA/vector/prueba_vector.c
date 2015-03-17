#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "vector.h"
#define TAMANIO_CLAVES 10

/*******************************************************************
 *                        PRUEBAS UNITARIAS
 ******************************************************************/

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
	printf("%s: %s\n", name, result? "OK" : "ERROR");
}

/* Funcion auxiliar para crear claves aleatorias. */
char** crear_claves(size_t largo,const size_t largo_clave){

	char letras[27] = "abcdefghijklmnopqrstuvwxyz";
	char** claves = malloc(sizeof(char*) * largo);

	size_t i;
	srand(time(NULL));
	for( i = 0; i < largo ; i++){
		char* str = malloc(sizeof(char) * largo_clave);
		size_t j;
		for(j = 0; j < largo_clave - 1; j++){
			str[j] = letras[(rand() + 1) % 26];
		}
		str[j] = '\0';
		claves[i] = str;
	}
	return claves;
}

void pruebas_vector_invalidos(){

	puts("\nINICIANDO PRUEBAS GUARDAR OBTENER");
	vector_t* vector = vector_crear(NULL);

	print_test("EL VECTOR ESTA VACIO",vector_obtener_cantidad(vector) == 0);
	print_test("OBTENER 1 ELEMENTO ES NULL",vector_obtener(vector,0) == NULL);
	print_test("EL VECTOR SIGUE VACIO",vector_obtener_cantidad(vector) == 0);

	print_test("GUARDAR ELEMENTO NULL", vector_guardar(vector,NULL));
	print_test("EL VECTOR NO ESTA VACIO",vector_obtener_cantidad(vector) != 0);

	vector_destruir(vector);
	print_test("EL VECTOR FUE DESTRUIDO", true);

}

void pruebas_vector_guardar_obtener()
{
	printf("\n\nINICIO DE PRUEBAS GUARDAR Y OBTENER\n");

	vector_t* vector = vector_crear(NULL);

	int vec[5] = {10,5,100,-125,0};
	printf("vec = [%i, %i, %i, %i, %i] \n", vec[0],vec[1],vec[2],vec[3],vec[4]);

	print_test("GUARDAR UN VALOR EN VEC2[0]", vector_guardar(vector,&vec[0]));
	print_test("GUARDAR UN VALOR EN VEC2[1]", vector_guardar(vector,&vec[1]));
	print_test("GUARDAR UN VALOR EN VEC2[2]", vector_guardar(vector,&vec[2]));
	print_test("GUARDAR UN VALOR EN VEC2[3]", vector_guardar(vector,&vec[3]));
	print_test("GUARDAR UN VALOR EN VEC2[4]", vector_guardar(vector,&vec[4]));


	/* Pruebo obtener los valores de un vector previamente guardados */
	print_test("VEC2[0] CONTIENE VEC[0]", *(int*)vector_obtener(vector,0) == vec[0]);
	print_test("VEC2[1] CONTIENE VEC[1]", *(int*)vector_obtener(vector,1) == vec[1]);
	print_test("VEC2[2] CONTIENE VEC[2]", *(int*)vector_obtener(vector,2) == vec[2]);
	print_test("VEC2[3] CONTIENE VEC[3]", *(int*)vector_obtener(vector,3) == vec[3]);
	print_test("VEC2[4] CONTIENE VEC[4]", *(int*)vector_obtener(vector,4) == vec[4]);

	/* Destruyo el vector*/
	vector_destruir(vector);
	print_test("EL VECTOR FUE DESTRUIDO", true);
}

/* Pruebas del vector al trabajar con un volumen grande de elementos */
void pruebas_vector_volumen(size_t volumen)
{
	printf("\n\nINICIO DE PRUEBAS DE VOLUMEN\n");
	vector_t* vector = vector_crear(free);

	char** claves = crear_claves(volumen,TAMANIO_CLAVES);

	bool ok = true;
	for (size_t i = 0; i < volumen; i++)
	{
		ok = vector_guardar(vector,claves[i]);
		if (!ok) break;
	}
	print_test("PRUEBA GUARDAR VECTOR EN VOLUMEN", ok);
	print_test("LA CANTIDAD DE ELEMENTOS ES CORRECTA",vector_obtener_cantidad(vector) == volumen);
	print_test("SE GUARDARON TODOS LOS ELEMENTOS", ok);

	ok = true;
	for (size_t i = 0; i < volumen; i++)
	{
		ok = ( (char*)vector_obtener(vector,i) == claves[i] );
		if (!ok) break;
	}
	print_test("SE PUDIERON OBTENER TODOS LOS ELEMENTOS", ok);
	vector_destruir(vector);
	free(claves);
	print_test("EL VECTOR FUE DESTRUIDO", true);
}

/* Ejecuta todas las pruebas. */
void pruebas_vector()
{
	pruebas_vector_invalidos();
	pruebas_vector_guardar_obtener();
	pruebas_vector_volumen(10000);
}

/* Programa principal. */
int main(void)
{
	pruebas_vector();
	return 0;
}
