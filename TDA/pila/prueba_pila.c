#include "pila.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* *****************************************************************
 *                         PRUEBAS PILAS
 * *****************************************************************/

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
	printf("%s: %s\n", name, result? "OK" : "ERROR");
}

int main()
{
	puts("\n\nDECLARO LOS ELEMENTOS A UTILIZAR");
	
	char* elem0={"holamundo"};
	int elem1=1;
	int elem2=2;
	int elem3=3;
	float elem4=6.125;
	double  elem5=1500;
	int elem6=2120;
	char* elem7={"01239"};
	char elem8='8';
	char elem9='o';

	printf("\nELEM0: %s", elem0);
	printf("\nELEM1: %i", elem1);
	printf("\nELEM2: %i", elem2);
	printf("\nELEM3: %i", elem3);
	printf("\nELEM4: %f", elem4);
	printf("\nELEM5: %f", elem5);
	printf("\nELEM6: %i", elem6);
	printf("\nELEM7: %s", elem7);
	printf("\nELEM8: %c", elem8);
	printf("\nELEM9: %c", elem9);
	

	pila_t* mi_pila0,* mi_pila1,* mi_pila2;
	puts("\n\nINICIO DE PRUEBAS MI_PILA0");
	mi_pila0 = pila_crear();
	print_test("MI_PILA0 ESTA VACIA", pila_esta_vacia(mi_pila0) );


	puts("\n\nINICIO DE PRUEBAS APILAR/DESAPILAR MI_PILA0");
	
	print_test("\nAPILAR ELEM0 EN LA PILA", pila_apilar(mi_pila0, elem0) );
	print_test("MI_PILA0 NO ESTA VACIA", !(pila_esta_vacia(mi_pila0)) );
	print_test("TOPE DE MI_PILA0 ES ELEM0", pila_ver_tope(mi_pila0) == elem0);
	print_test("APILAR ELEM1 EN MI_PILA0", pila_apilar(mi_pila0, &elem1) );
	print_test("TOPE DE MI_PILA0 ES ELEM1", pila_ver_tope(mi_pila0) == &elem1 );
	print_test("DESAPILAR ELEM1 EN MI_PILA0", pila_desapilar(mi_pila0) == &elem1 );
	print_test("TOPE DE MI_PILA0 ES ELEM0", pila_ver_tope(mi_pila0) == elem0 );
	print_test("DESAPILAR ELEM0 EN MI_PILA0 ", pila_desapilar(mi_pila0) == elem0 );
	print_test("TOPE DE MI_PILA0 ES NULL", pila_ver_tope(mi_pila0) == NULL);
	print_test("DESAPILAR MI_PILA0 ES NULL", pila_desapilar(mi_pila0) == NULL );
	pila_destruir(mi_pila0);
	puts("SE DESTRUYO MI_PILA0");
	
	mi_pila1 = pila_crear();
	mi_pila2 = pila_crear();
	
	puts("\n\nINICIO DE PRUEBAS EN MI_PILA1 Y MI_PILA2\n\n");
	print_test("MI_PILA1 ESTA VACIA", pila_esta_vacia(mi_pila1) );
	print_test("MI_PILA2 ESTA VACIA", pila_esta_vacia(mi_pila2) );


	puts("\nINICIO DE PRUEBAS APILAR/DESAPILAR MI_PILA1 Y MI_PILA2");
	
	print_test("\nAPILAR ELEM0 EN LA MI_PILA1", pila_apilar(mi_pila1, &elem0) );
	print_test("MI_PILA1 NO ESTA VACIA", !(pila_esta_vacia(mi_pila1)) );
	print_test("TOPE DE MI_PILA1 ES ELEM0", pila_ver_tope(mi_pila1) == &elem0);
	print_test("DESAPILAR ELEM0 EN MI_PILA0 ", pila_desapilar(mi_pila1) == &elem0 );
	print_test("MI_PILA1 ESTA VACIA", pila_esta_vacia(mi_pila1) );
	print_test("DESAPILAR PILA ES NULL", pila_desapilar(mi_pila1) == NULL );
	print_test("APILAR ELEM1 EN MI_PILA1", pila_apilar(mi_pila1, &elem1) );
	print_test("TOPE DE MI_PILA1 ES ELEM1", pila_ver_tope(mi_pila1) == &elem1);
	print_test("APILAR ELEM2 EN MI_PILA2", pila_apilar(mi_pila2, &elem2) );
	print_test("MI_PILA2 NO ESTA VACIA", !(pila_esta_vacia(mi_pila2)) );
	print_test("TOPE DE MI_PILA2 ES ELEM2", pila_ver_tope(mi_pila2) == &elem2);
	
	
	int* var1=pila_ver_tope(mi_pila2);
	int* var2=pila_ver_tope(mi_pila1);
	int elem10= *var1 + *var2 ;
	printf("\nSUMAR TOPE MI_PILA1 Y TOPE MI_PILA2 ES ELEM10: %i\n", elem10);
	print_test("DESAPILAR ELEM1 DE MI_PILA1", pila_desapilar(mi_pila1) == &elem1 );
	print_test("MI_PILA1 ESTA VACIA", pila_esta_vacia(mi_pila1) );
	
	puts("\nELEM10 ES LA SUMA DEL TOPE MI_PILA1 CON EL TOPE DE MI_PILA2");
	print_test("APILANDO ELEM10 EN MI_PILA1", pila_apilar(mi_pila1, &elem10) );
	print_test("APILANDO ELEM0 EN MI_PILA1", pila_apilar(mi_pila1, elem0) );
	print_test("APILANDO ELEM1 EN MI_PILA1", pila_apilar(mi_pila1, &elem1) );
	print_test("APILANDO ELEM2 EN MI_PILA1", pila_apilar(mi_pila1, &elem2) );
	print_test("APILANDO ELEM3 EN MI_PILA1", pila_apilar(mi_pila1, &elem3) );
	print_test("APILANDO ELEM4 EN MI_PILA1", pila_apilar(mi_pila1, &elem4) );
	print_test("APILANDO ELEM5 EN MI_PILA1", pila_apilar(mi_pila1, &elem5) );
	print_test("APILANDO ELEM6 EN MI_PILA1", pila_apilar(mi_pila1, &elem6) );
	print_test("APILANDO ELEM7 EN MI_PILA1", pila_apilar(mi_pila1, elem7) );
	print_test("APILANDO ELEM8 EN MI_PILA1", pila_apilar(mi_pila1, &elem8) );
	print_test("APILANDO ELEM9 EN MI_PILA1", pila_apilar(mi_pila1, &elem9) );

	
	size_t i;
	for (i=0; i<10 ;i++)
	{
		pila_apilar(mi_pila1, elem0);
		pila_apilar(mi_pila1, &elem1);
		pila_apilar(mi_pila1, &elem2);
		pila_apilar(mi_pila1, &elem3);
		pila_apilar(mi_pila1, &elem4);
		pila_apilar(mi_pila1, &elem5);
		pila_apilar(mi_pila1, &elem6);
		pila_apilar(mi_pila1, elem7);
		pila_apilar(mi_pila1, &elem8);
		pila_apilar(mi_pila1, &elem9);
	}
	puts("\n\nSE VUELVE A CREAR MI_PILA0");
	puts("SE PROCEDERA A COPIAR TODO EL CONTENIDO DE MI_PILA1 A MI_PILA0\n");
	mi_pila0 = pila_crear();
	while ( !(pila_esta_vacia(mi_pila1)) )
	{
		pila_apilar(mi_pila0,pila_desapilar(mi_pila1));
		
	}
	
	print_test("\nDESAPILAR MI_PILA0 ES ELEM10", pila_desapilar(mi_pila0) == &elem10 );
	print_test("TOPE DE MI_PILA0 ES AHORA ELEM0", pila_ver_tope(mi_pila0) == elem0);
	
	


	pila_destruir(mi_pila0);
	pila_destruir(mi_pila1);
	pila_destruir(mi_pila2);
	puts("SE DESTRUYERON TODAS LAS PILAS.\n\n");
}
