#include "cola.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


/********************************************************
*                 PRUEBAS PARA COLA
********************************************************/

typedef struct type_alumno
{
	char* nombre;
	char* apellido;
	char* nacimiento;
	int anio_ingreso;
	void** materias_aprobadas;
	size_t cantidad_materias;
}alumno_t;

typedef struct type_datos
{
	void* datos;
	void* valor;
} dato_t;

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
	printf("%s: %s\n", name, result? "OK" : "ERROR");
}

void pruebas_vacio()
{
	puts("INICIANDO PRUEBAS COLA VACIA.");

	cola_t* cola = cola_crear();

	print_test("COLA ESTA VACIA",cola_esta_vacia(cola));
	print_test("COLA VER PRIMERO ES NULL",cola_ver_primero(cola) == NULL);
	print_test("COLA DESENCOLAR ES  NULL",cola_desencolar(cola) == NULL);
	cola_destruir(cola,NULL);

	puts("SE DESTRUYO LA COLA");
	puts("SE TERMINARON LAS PRUEBAS VACIO.\n\n");
}

void pruebas_volumen(int volumen)
{
	puts("INICIANDO PRUEBAS EN VOLUMEN.");
	printf("EL VOLUMEN ES DE %i ELEMENTOS\n", volumen);
	cola_t* cola = cola_crear();
	bool ok;

	int* vec = malloc(sizeof(int) * volumen);
	for(size_t i = 0; i < volumen; i++) vec[i] = i;

	ok = true;
	for (size_t i = 0; i < volumen; i++)
	{
		ok = cola_encolar(cola,&vec[i]);
		if (!ok) break;
	}
	print_test("PRUEBA ENCOLAR EN VOLUMEN", ok);

	print_test("TOPE COLA ES 0", *(int*)cola_ver_primero(cola) == vec[0]);

	ok = true;
	for (size_t i = 0; i < volumen; i++)
	{
		ok = ( *(int*)cola_desencolar(cola) == vec[i]);
		if (!ok) break;
	}
	print_test("PRUEBA DESENCOLAR EN VOLUMEN", ok);
	print_test("COLA ESTA VACIA",cola_esta_vacia(cola));
	print_test("COLA VER PRIMERO ES NULL",cola_ver_primero(cola) == NULL);
	print_test("COLA DESENCOLAR ES  NULL",cola_desencolar(cola) == NULL);

	cola_destruir(cola,NULL);
	free(vec);

	puts("SE DESTRUYO LA COLA");
	puts("SE TERMINARON LAS PRUEBAS EN VOLUMEN.\n\n");
}

void prueba_datos()
{
	puts("INICIANDO PRUEBAS PARA DATO.");

	cola_t* cola = cola_crear();

	dato_t* dato_0 = malloc(sizeof(dato_t));
	dato_0->datos = "dato_0";
	dato_0->valor = "valor_dato_0";
	dato_t* dato_1 = malloc(sizeof(dato_t));
	dato_1->datos = "dato_1";
	dato_1->valor = "valor_dato_1";
	dato_t* dato_2 = malloc(sizeof(dato_t));
	dato_2->datos = "dato_2";
	dato_2->valor = "valor_dato_2";
	dato_t* dato_3 = malloc(sizeof(dato_t));
	dato_3->datos = "dato_3";
	dato_3->valor = "valor_dato_3";
	dato_t* dato_4 = malloc(sizeof(dato_t));
	dato_4->datos = "dato_4";
	dato_4->valor = "valor_dato_4";
	dato_t* dato_5 = malloc(sizeof(dato_t));
	dato_5->datos = "dato_5";
	dato_5->valor = "valor_dato_5";
	dato_t* dato_6 = malloc(sizeof(dato_t));
	dato_6->datos = "dato_6";
	dato_6->valor = "valor_dato_6";
	dato_t* dato_7 = malloc(sizeof(dato_t));
	dato_7->datos = "datos";
	dato_7->valor = "valor_dato_7";
	dato_t* dato_8 = malloc(sizeof(dato_t));
	dato_8->datos = "dato_8";
	dato_8->valor = "valor_dato_8";

	print_test("ENCOLANDO DATO_0",cola_encolar(cola,dato_0) );
	print_test("ENCOLANDO DATO_1",cola_encolar(cola,dato_1) );
	print_test("ENCOLANDO DATO_2",cola_encolar(cola,dato_2) );
	print_test("ENCOLANDO DATO_3",cola_encolar(cola,dato_3) );
	print_test("ENCOLANDO DATO_4",cola_encolar(cola,dato_4) );
	print_test("ENCOLANDO DATO_5",cola_encolar(cola,dato_5) );
	print_test("ENCOLANDO DATO_6",cola_encolar(cola,dato_6) );
	print_test("ENCOLANDO DATO_7",cola_encolar(cola,dato_7) );
	print_test("ENCOLANDO DATO_8",cola_encolar(cola,dato_8) );

	print_test("COLA NO ESTA VACIA",!cola_esta_vacia(cola));
	puts("SE PROCEDE A DESTRUIR LA COLA");
	cola_destruir(cola,free);

	puts("SE DESTRUYEROS LOS DATOS DESENCOLADOS");
	puts("SE DESTRUYO LA COLA");
	puts("SE TERMINARON LAS PRUEBAS CON DATO.\n\n");

}

void destruir_alumno(void* alumno)
{
	alumno_t* alum = alumno;
	size_t i;
	size_t tam = alum->cantidad_materias;
	dato_t* mat;
	for(i=0;i<=(tam-1);i++)
	{
		mat = alum->materias_aprobadas[i] ;
		free(mat);
	}
	free(alum->materias_aprobadas);
	free(alum);
}

void imprimir_datos_alumnos(void* alum)
{
	alumno_t* alumno = alum;
	printf("NOMBRE: %s\n", alumno->nombre );
	printf("APELLIDO: %s\n", alumno->apellido );
	printf("FECHA DE NACIMIENTO: %s\n", alumno->nacimiento );
	printf("ANIO INGRESO: %i\n", alumno->anio_ingreso );
	size_t i;
	size_t tam = alumno->cantidad_materias;
	dato_t* mat;
	for(i=0;i<=(tam-1);i++)
	{
		mat = alumno->materias_aprobadas[i];
		char* materia = mat->datos;
		char* nota = mat->valor;
		printf("MATERIA: %s ",materia);
		printf("NOTA: %s\n",nota);
	}
}

void prueba_alumno()
{
	puts("INICIANDO PRUEBAS PARA ALUMNO");

	cola_t* cola = cola_crear();

	alumno_t* alum_0 = malloc(sizeof(alumno_t));
	alum_0->nombre = "Braian";
	alum_0->apellido = "Vicente";
	alum_0->nacimiento = "19931229";
	alum_0->anio_ingreso = 2014;
	dato_t* alum_0_aprobada_0 = malloc(sizeof(dato_t));
	alum_0_aprobada_0->datos= "Algoritmos y Programacion I";
	alum_0_aprobada_0->valor="4";
	dato_t* alum_0_aprobada_1 = malloc(sizeof(dato_t));
	alum_0_aprobada_1->datos= "Analisis Matematico II";
	alum_0_aprobada_1->valor="4";
	void** mat_alum_0=malloc(2*sizeof(dato_t));
	alum_0->cantidad_materias = 2 ;
	mat_alum_0[0] = alum_0_aprobada_0;
	mat_alum_0[1] = alum_0_aprobada_1;
	alum_0->materias_aprobadas = mat_alum_0;
	print_test("SE ENCOLO ALUM_0",cola_encolar(cola,alum_0));

	alumno_t* alum_1 = malloc(sizeof(alumno_t));
	alum_1->nombre = "Pepe";
	alum_1->apellido = "Garcia";
	alum_1->nacimiento = "19920815";
	alum_1->anio_ingreso = 2013;
	dato_t* alum_1_aprobada_0 = malloc(sizeof(dato_t));
	alum_1_aprobada_0->datos= "Algoritmos y Programacion I";
	alum_1_aprobada_0->valor="4";
	dato_t* alum_1_aprobada_1 = malloc(sizeof(dato_t));
	alum_1_aprobada_1->datos= "Algebra II";
	alum_1_aprobada_1->valor="4";
	dato_t* alum_1_aprobada_2 = malloc(sizeof(dato_t));
	alum_1_aprobada_2->datos= "Analisis Matematico II";
	alum_1_aprobada_2->valor="5";
	void** mat_alum_1=malloc(3*sizeof(dato_t));
	alum_1->cantidad_materias = 3 ;
	mat_alum_1[0] = alum_1_aprobada_0;
	mat_alum_1[1] = alum_1_aprobada_1;
	mat_alum_1[2] = alum_1_aprobada_2;
	alum_1->materias_aprobadas = mat_alum_1;
	print_test("SE ENCOLO ALUM_1",cola_encolar(cola,alum_1));


	puts("\nA CONTINUACION SE IMPRIMIRAN LOS DATOS DEL TOPE ALUMO, QUE TENDRIA QUE SER ALUM_0");
	imprimir_datos_alumnos(cola_desencolar(cola));
	destruir_alumno(alum_0);

	puts("\n\nA CONTINUACION SE IMPRIMIRAN LOS DATOS DEL TOPE ALUMO, QUE TENDRIA QUE SER ALUM_1");
	imprimir_datos_alumnos(cola_desencolar(cola));
	destruir_alumno(alum_1);

	print_test("\nCOLA ESTA VACIA",cola_esta_vacia(cola));
	print_test("COLA VER PRIMERO ES NULL",cola_ver_primero(cola) == NULL);
	print_test("COLA DESENCOLAR ES  NULL",cola_desencolar(cola) == NULL);
	cola_destruir(cola,destruir_alumno);



	puts("SE DESTRUYERON LOS DATOS DESENCOLADOS");
	puts("SE DESTRUYO LA COLA");
	puts("SE TERMINARON LAS PRUEBAS CON ALUMNO\n\n");
}

void pruebas_dato_comun()
{
	puts("INICIANDO PRUEBAS DATOS COMUNES.");

	cola_t* cola = cola_crear();

	char elem0 = 'a';
	int elem1 = 1;
	int elem2 = 2;
	int elem3 = 3;
	float elem4 = 6.125;
	double  elem5 = 1500;
	int elem6 = 2120;
	char elem7 = 'O';
	char elem8 = 'K';

	printf("\nTIPO CHAR ELEM0: %c ", elem0);
	printf("\nTIPO INT ELEM1: %i ", elem1);
	printf("\nTIPO INT ELEM2: %i ", elem2);
	printf("\nTIPO INT ELEM3: %i ", elem3);
	printf("\nTIPO FLOAT ELEM4: %f ", elem4);
	printf("\nTIPO DOUBLE ELEM5: %f ", elem5);
	printf("\nTIPO INT ELEM6: %i ", elem6);
	printf("\nTIPO CHAR ELEM7: %c ", elem7);
	printf("\nTIPO CHAR ELEM8: %c \n\n", elem8);

	print_test("ENCOLAR ELEM0", cola_encolar(cola,&elem0) );
	print_test("ENCOLAR ELEM1", cola_encolar(cola,&elem1) );
	print_test("COLA VER PRIMERO ES ELEM0",*(char*)cola_ver_primero(cola) == elem0);
	print_test("COLA DESENCOLAR ES ELEM0",*(char*)cola_desencolar(cola) == elem0);
	print_test("COLA VER PRIMERO ES ELEM1",*(int*)cola_ver_primero(cola) == elem1);
	print_test("COLA DESENCOLAR PRIMERO ES ELEM1",*(int*)cola_desencolar(cola) == elem1);
	print_test("COLA ESTA VACIA",cola_esta_vacia(cola));
	print_test("COLA VER PRIMERO ES NULL",cola_ver_primero(cola) == NULL);
	print_test("COLA DESENCOLAR ES NULL",cola_desencolar(cola) == NULL);
	print_test("COLA ESTA VACIA",cola_esta_vacia(cola));

	print_test("\nENCOLAR ELEM2", cola_encolar(cola,&elem2) );
	print_test("COLA NO ESTA VACIA",!cola_esta_vacia(cola));
	print_test("ENCOLAR ELEM3", cola_encolar(cola,&elem3) );
	int suma = *(int*)cola_desencolar(cola) + *(int*)cola_desencolar(cola);
	print_test("SUMAR DESENCOLADOS", suma == elem2+elem3 );
	printf("EL RESULTADO DE LA SUMA ES %i\n",suma);

	print_test("\nENCOLAR ELEM4", cola_encolar(cola,&elem4) );
	print_test("ENCOLAR ELEM5", cola_encolar(cola,&elem5) );
	print_test("ENCOLAR ELEM6", cola_encolar(cola,&elem6) );
	print_test("COLA DESENCOLAR ES ELEM4",*(float*)cola_desencolar(cola) == elem4);
	print_test("COLA DESENCOLAR ES ELEM5",*(double*)cola_desencolar(cola) == elem5);
	print_test("COLA DESENCOLAR ES ELEM6",*(int*)cola_desencolar(cola) == elem6);

	print_test("\nENCOLAR ELEM7", cola_encolar(cola,&elem7) );
	print_test("ENCOLAR ELEM8", cola_encolar(cola,&elem8) );
	char str[3] = {*(char*)cola_desencolar(cola),*(char*)cola_desencolar(cola),'\0'};
	printf("RESULTADO DE CONCATENAR ELEM7 CON ELEM8: %s\n",str);
	print_test("COLA VER PRIMERO ES NULL",cola_ver_primero(cola) == NULL);
	print_test("COLA DESENCOLAR ES NULL",cola_desencolar(cola) == NULL);
	print_test("COLA ESTA VACIA",cola_esta_vacia(cola));

	cola_destruir(cola,NULL);
	puts("SE DESTRUYO LA COLA");
	puts("SE TERMINARON LAS PRUEBAS DE DATOS COMUNES.\n\n");

}
int main()
{
	pruebas_vacio();
	pruebas_dato_comun();
	pruebas_volumen(2000);
	prueba_datos();
	prueba_alumno();
}
