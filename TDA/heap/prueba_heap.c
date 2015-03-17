#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "heap.h"
#define VOLUMEN 50000
#define TAM 10

/* ******************************************************************
 *                      ESTRUCTURAS AUXILIARES
 * *****************************************************************/

typedef struct twitts_favoritos{
	char* twitt;
	int cant;
}fav_t;

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

int cmp_str(const void* a, const void* b){
	const char* s1 = (char*)a;
	const char* s2 = (char*)b;
	if ((s1 == NULL) && (s2 == NULL)) return 0;
	else if ((s1 != NULL) && (s2 == NULL)) return 1;
	else if ((s1 == NULL) && (s2 != NULL)) return -1;

	return strcmp(s1,s2);
}


int cmp_int(const void* a, const void* b){
	int ent1 = *(int*)a;
	int ent2 = *(int*)b;
	if (ent1 < ent2) return 1;
	if (ent1 > ent2) return -1;
	return 0;
}

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

void prueba_heap_vacio(){

	puts("\n\nINICIO PRUEBA_HEAP_VACIO");
	heap_t* heap = heap_crear(NULL);

	print_test("\nEL HEAP SE CREO CORRECTAMENTE", heap!=NULL);
	print_test("LA CANTIDAD DEL HEAP VACIO ES 0", heap_cantidad(heap) == 0);
	print_test("EL HEAP ESTA VACIO", heap_esta_vacio(heap) );
	print_test("DESENCOLAR UN HEAP VACIO ES NULL", heap_desencolar(heap) == NULL);
	print_test("VER EL MAXIMO DE UN HEAP VACIO ES NULL", heap_ver_max(heap) == NULL);

	heap_destruir(heap,NULL);
}

void prueba_heap_algunos_elementos(){

	puts("\n\nINICIO PRUEBA_HEAP_ALGUNOS_ELEMENTOS");

	heap_t* heap = heap_crear(cmp_str);

	char* valor1 = "ABEL";
	char* valor2 = "BARBOSA";
	char* valor3 = "Aaron";

	print_test("\nENCOLAR VALOR 1", heap_encolar(heap,valor1));
	print_test("ENCOLAR VALOR 2", heap_encolar(heap,valor2));
	print_test("ENCOLAR VALOR 3", heap_encolar(heap,valor3));
	print_test("EL HEAP NO ESTA VACIO", !heap_esta_vacio(heap));
	print_test("LA CANTIDAD DEL HEAP ES 3", heap_cantidad(heap)==3);

	print_test("\nDESENCOLAR DEBE DAR EL VALOR 2 COMO MAX", heap_desencolar(heap) == valor2);
	print_test("LA CANTIDAD DEL HEAP ES 2", heap_cantidad(heap) == 2);
	print_test("DESENCOLAR DEBE DAR EL VALOR 1 COMO MAX", heap_desencolar(heap) == valor3);
	print_test("LA CANTIDAD DEL HEAP ES 1", heap_cantidad(heap) == 1);
	print_test("DESENCOLAR DEBE DAR EL VALOR 3 COMO MAX", heap_desencolar(heap)==valor1);
	print_test("LA CANTIDAD DEL HEAP ES 0", heap_cantidad(heap) == 0);
	print_test("EL HEAP ESTA VACIO", heap_esta_vacio(heap));

	heap_destruir(heap,NULL);
}

void prueba_heap_destruir_algunos_elementos(){

	puts("\n\nINICIO PRUEBA_HEAP_DESTRUIR_ALGUNOS_ELEMENTOS");

	heap_t* heap = heap_crear(cmp_str);

	char* valor1 = "RUIZ";
	char* valor2 = "AMARGO";
	char* valor3 = "AMOR";

	print_test("\nENCOLAR AMOR", heap_encolar(heap,valor3));
	print_test("ENCOLAR RUIZ", heap_encolar(heap,valor1));
	print_test("ENCOLAR AMARGO", heap_encolar(heap,valor2));

	print_test("\nDESENCOLAR ES RUIZ", (char*)heap_desencolar(heap) == valor1 );
	print_test("DESENCOLAR ES AMOR", (char*)heap_desencolar(heap) == valor3 );
	print_test("DESENCOLAR ES AMARGO", (char*)heap_desencolar(heap) == valor2 );

	print_test("\nEL HEAP ESTA VACIO", heap_esta_vacio(heap));
	print_test("LA CANTIDAD DEL HEAP ES 0", heap_cantidad(heap) == 0);

	heap_destruir(heap,NULL);
}

void prueba_heap_enteros(){

	puts("\n\nINICIO PRUEBA_HEAP_ENTEROS");
	heap_t* heap = heap_crear(cmp_str);

	int enteros[5] = {5, 8, 5, 2, 0};
	int* valor1 = &enteros[0];
	int* valor2 = &enteros[1];
	int* valor3 = &enteros[2];
	int* valor4 = &enteros[3];
	int* valor5 = &enteros[4];

	print_test("\nENCOLAR VALOR 1", heap_encolar(heap,valor1));
	print_test("ENCOLAR VALOR 2", heap_encolar(heap,valor2));
	print_test("ENCOLAR VALOR 3", heap_encolar(heap,valor3));
	print_test("ENCOLAR VALOR 4", heap_encolar(heap,valor4));
	print_test("ENCOLAR VALOR 5", heap_encolar(heap,valor5));
	print_test("EL HEAP NO ESTA VACIO", !heap_esta_vacio(heap));
	print_test("LA CANTIDAD DEL HEAP ES 5", heap_cantidad(heap)==5);

	print_test("\nDESENCOLAR DEBE DAR EL VALOR 8 COMO MAX", heap_desencolar(heap)==valor2);
	print_test("DESENCOLAR DEBE DAR EL VALOR 5 COMO MAX", heap_desencolar(heap)==valor1);
	print_test("DESENCOLAR DEBE DAR EL VALOR 5 COMO MAX", heap_desencolar(heap)==valor3);
	print_test("DESENCOLAR DEBE DAR EL VALOR 2 COMO MAX", heap_desencolar(heap)==valor4);
	print_test("DESENCOLAR DEBE DAR EL VALOR 0 COMO MAX", heap_desencolar(heap)==valor5);
	print_test("LA CANTIDAD DEL HEAP ES 0", heap_cantidad(heap)==0);
	print_test("EL HEAP ESTA VACIO", heap_esta_vacio(heap));

	heap_destruir(heap,free);
}

int cmp_fav(const void* a, const void* b){
	const fav_t* fav_a = a;
	const fav_t* fav_b = b;
	if (fav_a->cant < fav_b->cant) return 1;
	if (fav_a->cant > fav_b->cant) return -1;
	return 0;
}

void imprimir_favoritos(void *elementos[], int cant){
	for(int i = 0; i < cant ;i++){
		fav_t* fav_a = elementos[i];
		printf("%s, TIENE %i FAVS\n",fav_a->twitt,fav_a->cant);
	}
}

void prueba_heapsort_estructuras(){


	puts("\n\nINICIANDO PRUEBAS CON ESTRUCTURAS");
	char* twitt_01 = "@USER prueba01 #hagstag";
	char* twitt_02 = "@USER prueba02 #hagstag";
	char* twitt_03 = "@USER prueba03 #hagstag";
	char* twitt_04 = "@USER prueba04 #hagstag";
	char* twitt_05 = "@USER prueba05 #hagstag";
	char* twitt_06 = "@USER prueba06 #hagstag";

	fav_t* fav1 = malloc(sizeof(fav_t));
	fav1->twitt = twitt_01 ;
	fav1->cant = 5;
	printf("TWITT_01: %s TIENE %i FAVS\n",twitt_01,fav1->cant);

	fav_t* fav2 = malloc(sizeof(fav_t));
	fav2->twitt = twitt_02 ;
	fav2->cant = 9;
	printf("TWITT_02: %s TIENE %i FAVS\n",twitt_02,fav2->cant);

	fav_t* fav3 = malloc(sizeof(fav_t));
	fav3->twitt = twitt_03 ;
	fav3->cant = 1;
	printf("TWITT_03: %s TIENE %i FAVS\n",twitt_03,fav3->cant);

	fav_t* fav4 = malloc(sizeof(fav_t));
	fav4->twitt = twitt_04 ;
	fav4->cant = 0;
	printf("TWITT_04: %s TIENE %i FAVS\n",twitt_04,fav4->cant);

	fav_t* fav5 = malloc(sizeof(fav_t));
	fav5->twitt = twitt_05 ;
	fav5->cant = 3;
	printf("TWITT_05: %s TIENE %i FAVS\n",twitt_05,fav5->cant);

	fav_t* fav6 = malloc(sizeof(fav_t));
	fav6->twitt = twitt_06 ;
	fav6->cant = 2;
	printf("TWITT_06: %s TIENE %i FAVS\n",twitt_06,fav6->cant);

	void* elementos[6];
	void* elementos2[6];
	elementos[0] = fav1;
	elementos[1] = fav2;
	elementos[2] = fav3;
	elementos[3] = fav4;
	elementos[4] = fav5;
	elementos[5] = fav6;

	elementos2[0] = fav2;
	elementos2[1] = fav1;
	elementos2[2] = fav5;
	elementos2[3] = fav6;
	elementos2[4] = fav3;
	elementos2[5] = fav4;

	heap_sort(elementos,6,cmp_fav);

	bool ok = true;
	for (int i = 0; i < 6; i++){
		if ( cmp_fav(elementos[i],elementos2[i]) != 0 ){
		ok = false;
		break;
		}
	}
	print_test("SE ORDENO EL FAVORITOS", ok);
	puts("SE IMPRIMIRA LOS 3 TWITT'S CON MAS FAVORITOS");
	imprimir_favoritos(elementos,3);
	free(fav1);
	free(fav2);
	free(fav3);
	free(fav4);
	free(fav5);
	free(fav6);

}

void pruebas_heap_destruir_dinamica(){

	puts("\n\nINICIO PRUEBA_DESTRUCCION_DINAMICA");
	heap_t* heap = heap_crear(cmp_int);

	int* valor1 = malloc(sizeof(int));
	int* valor2 = malloc(sizeof(int));
	int* valor3 = malloc(sizeof(int));
	int* valor4 = malloc(sizeof(int));

	*valor1 = 8;
	*valor2 = 5;
	*valor3 = 5;
	*valor4 = 2;

	print_test("\nENCOLAR VALOR 1", heap_encolar(heap,valor1));
	print_test("ENCOLAR VALOR 2", heap_encolar(heap,valor2));
	print_test("ENCOLAR VALOR 3", heap_encolar(heap,valor3));
	print_test("ENCOLAR VALOR 4", heap_encolar(heap,valor4));
	print_test("EL HEAP NO ESTA VACIO", !heap_esta_vacio(heap));
	print_test("LA CANTIDAD DEL HEAP ES 4", heap_cantidad(heap)==4);

	heap_destruir(heap,free);
}

void prueba_heap_redimensionar(int volumen){

	puts("\n\nINICIO PRUEBA_VOLUMEN");

	heap_t* heap = heap_crear(cmp_int);
	int enteros[volumen];
	int aux;
	for (size_t i = 0; i < volumen ; i++){
		aux = rand() % (VOLUMEN-1);
		enteros[i] = aux;
	}
	bool ok = true;
	for (size_t i = 0; i < volumen ; i++){
		ok = heap_encolar(heap,&enteros[i]);
//		printf("POSICION	 %i	VALOR	%i	 TOPE	%i\n",i,enteros[i],*(int*)heap_ver_max(heap));
		if (!ok){
			break;
		}
//		printf("POSICION	 %i	VALOR	%i	 TOPE	%i\n",i,enteros[i],heap_ver_max(heap));
	}

//	printf("\nVER CANTIDAD %i\n",heap_cantidad(heap));
	printf("ENCOLAR %i ELEMENTOS",volumen);
	print_test("", ok);
	print_test("NO ESTA VACIO", !heap_esta_vacio(heap));

	printf("EL HEAP TIENE %i ELEMENTOS",volumen);
	print_test("", VOLUMEN == heap_cantidad(heap));
	for (size_t i = 0; i <= volumen ; i++) {
//		printf(" DESENCOLADO: %i\n",heap_desencolar(heap));
		heap_desencolar(heap);
	}

	printf("DESENCOLAR LOS ELEMENTOS\n");
	print_test("ESTA VACIO", heap_esta_vacio(heap));
	print_test("EL HEAP TIENE 0 ELEMENTOS", 0 == heap_cantidad(heap));

	heap_destruir(heap,NULL);
}

/* 	Ejecucion de todas las pruebas unitarias*/

void pruebas_heap(){

	prueba_heap_vacio();
	prueba_heap_algunos_elementos();
	prueba_heap_destruir_algunos_elementos();
	prueba_heap_enteros();
	prueba_heapsort_estructuras();
	pruebas_heap_destruir_dinamica();
	prueba_heap_redimensionar(VOLUMEN);
}

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main()
{
	pruebas_heap();
	return 0;
}
