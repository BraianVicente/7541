#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

/******************************************************************
 *                         PRUEBAS LISTA
 ******************************************************************/

// Hacer pruebas para comparar 2 listas elemento a elemento.
// Terminar pruebas de volumen.
// Terminar de verificar casos borde.
// Caso borde.
// 1 Crear iter si la lista esta vacia.
// 2 Avanzar iter si la lista esta vacia.
// 3 Avanzar iter si la lista esta al final.
// 4 lista_iterar si la lista esta vacia.
// 5 borrar_actual si la lista esta vacia.
// 6 borrar primero si la lista esta vacia.
// 7 lista_iter_al_final si la lista esta vacia.
// 8 lista_iter_al_final si la lista esta al final.
// 9 lista_iter_destruir si la lista esta vacia.
void pruebas_volumen()
{
	puts("\n\nINICIANDO PRUEBAS VOLUMEN LISTA");
	
	
	lista_t* lista = lista_crear();
	
	int elem0 = 10;
	int elem1 = -10;
	int elem2 = 0;
	int elem3 = 1510;
	int elem4 = -12310;
	int elem5 = 110;


	size_t i ;
	for(i=0;i<=1000;i++)
	{
		lista_insertar_primero(lista,&elem0);
		lista_insertar_primero(lista,&elem1);
		lista_insertar_primero(lista,&elem2);
		lista_insertar_primero(lista,&elem3);
		lista_insertar_primero(lista,&elem4);
		lista_insertar_primero(lista,&elem5);
		
	}	
	
	
	lista_destruir(lista,NULL);
	
	puts("\n\nTERMINADAS PRUEBAS VOLUMEN LISTA");
	
}

void imprimir_dato(void* dato)
{
	dato_t* cad;
	cad = dato;
	
	char* datos = cad->datos;
	char* valor = cad->valor;
	printf("\nDATO ALMACENADO %s\n", datos);
	printf("VALOR DEL DATO ALMANCENADO %s\n\n", valor);
}

void pruebas_lista()
{
// Se probo el ingreso de datos y el correcto funcionamiento del 
// ingreso de datos.
	puts("\n\nINICIANDO PRUEBAS PARA LISTA");
	
	
	lista_t* lista = lista_crear();
	print_test("NO SE PUEDE VER NINGUN ELEMENTO", !lista_ver_primero(lista) );
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

	print_test("\nINTESTAR PRIMERO DATO_0",lista_insertar_primero(lista,dato_0) );
	print_test("INTESTAR ULTIMO DATO_1",lista_insertar_ultimo(lista,dato_1) );
	print_test("BORRAR DATO_0",lista_borrar_primero(lista) == dato_0 );
	print_test("BORRAR DATO_1",lista_borrar_primero(lista) == dato_1 );
	print_test("NO SE PUEDE VER NINGUN ELEMENTO", !lista_ver_primero(lista) );
	
	print_test("\nINTESTAR ULTIMO DATO_1",lista_insertar_ultimo(lista,dato_1) );
	print_test("INTESTAR PRIMERO DATO_0",lista_insertar_primero(lista,dato_0) );
	print_test("INTESTAR PRIMERO DATO_2",lista_insertar_primero(lista,dato_2) );
	print_test("INTESTAR ULTIMO: DATO_3",lista_insertar_ultimo(lista,dato_3) );
	print_test("TAMANIO ES 4: ", lista_largo(lista) == 4);
	
	print_test("\nBORRAR DATO_2",lista_borrar_primero(lista) == dato_2 );
	free(dato_2);
	print_test("BORRAR DATO_0",lista_borrar_primero(lista) == dato_0 );
	free(dato_0);
	print_test("EL PRIMERO ES DATO_1",lista_ver_primero(lista) == dato_1);
	print_test("TAMANIO ES 2: ", lista_largo(lista) == 2);
	
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("\nSE CREO EL ITERADOR", iter != NULL);
	print_test("INSERTAR: DATO_4",lista_insertar(lista,iter,dato_4) );
	print_test("AVANZAR EN EL ITERADOR",lista_iter_avanzar(iter) );
	print_test("EL PRIMERO ES DATO_4", lista_ver_primero(lista) == dato_4);
	print_test("EL ACTUAL ES DATO_1", lista_iter_ver_actual(iter) == dato_1);

// SE ITERA HASTA EL FINAL DE LA LISTA PARA LUEGO AGREGAR AL FINAL
// CON EL LISTA_INSETAR();
	while (!lista_iter_al_final(iter))  lista_iter_avanzar(iter);
	
// SE CORROVORA QUE EL LA POSICION ACTUAL SEA NULL
// Y SE PROCEDE A AGREGAR AL FINAL
	print_test("\nNO SE PUEDE BORRAR ACTUAL",lista_borrar(lista,iter) == NULL);
	print_test("INSERTAR: DATO_5",lista_insertar(lista,iter,dato_5) );
	print_test("EL ACTUAL ES DATO_5", lista_iter_ver_actual(iter) == dato_5);
	print_test("INSERTAR: DATO_6",lista_insertar(lista,iter,dato_6) );
	puts("SE PROCEDERA A ITERAR HASTA EL FINAL DE LA LISTA");
	while (!lista_iter_al_final(iter))  lista_iter_avanzar(iter);
	
	print_test("\nSE PUDO BORRAR ES NULL", lista_borrar(lista,iter) == NULL );
	print_test("INSERTAR: DATO_7",lista_insertar(lista,iter,dato_7) );
	print_test("INSERTAR: DATO_8",lista_insertar(lista,iter,dato_8) );
	print_test("EL ACTUAL ES DATO_8", lista_iter_ver_actual(iter) == dato_8);
	print_test("BORRAR ACTUAL ES DATO_8",lista_borrar(lista,iter) == dato_8);
	free(dato_8);
	print_test("TAMANIO ES 6 ", lista_largo(lista) == 6);

	lista_iter_destruir(iter);
	puts("\nSE DESTRUYE EL ITERADOR Y SE VUELVE A CREAR OTRO");
	
	iter = lista_iter_crear(lista);
	puts("SE VERIFICA QUE EL PRIMER ELEMENTO SEA EL INSERTADO POSTERIORMENTE");
	print_test("EL ACTUAL ES DATO_4", lista_iter_ver_actual(iter) == dato_4);
	size_t i;
	for(i=0;i<(lista_largo(lista)-1);i++)
	{
		lista_iter_avanzar(iter);
	}
	puts("SE AVANZA HASTA EL ULTIMO ELEMENTO DEL ITERADOR");
	puts("SE VERIFICA QUE EL ULTIMO ELEMENTO SEA EL INSERTADO POSTERIORMENTE");
	print_test("EL ACTUAL ES DATO_7", lista_iter_ver_actual(iter) == dato_7);
	lista_iter_destruir(iter);
	lista_destruir(lista,free);	
	puts("\n\nSE DESTRUYO LA LISTA");
	puts("SE TERMINARON LAS PRUEBAS CON DATO");
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

bool imprimir_datos_alumnos(void* alum, void* extra)
{
	alumno_t* alumno = alum;
	printf("\n\nNOMBRE: %s\n", alumno->nombre );
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
	return true;
}

void prueba_alumno_iter_interno()
{
	puts("\n\nINICIANDO PRUEBAS PARA ALUMNO\n");

	lista_t* lista = lista_crear();
	lista_esta_vacia(lista);
	print_test("NO SE PUEDE VER NINGUN ELEMENTO", !lista_ver_primero(lista) );
	
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
	print_test("SE INSERTO ULTIMO ALUM_0",lista_insertar_ultimo(lista,alum_0));
	
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
	print_test("SE INSERTO ULTIMO ALUM_1",lista_insertar_ultimo(lista,alum_1));
	
	lista_iterar(lista,imprimir_datos_alumnos,NULL);
	
	lista_destruir(lista,destruir_alumno);
	
	puts("\n\nSE DESTRUYO LA LISTA");
	puts("SE TERMINARON LAS PRUEBAS CON ALUMNO\n\n");
}

int main()
{
	
	pruebas_lista();
	prueba_alumno_iter_interno();
	pruebas_volumen();
}
