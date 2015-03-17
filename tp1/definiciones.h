#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lista.h"

/*******************************************************************
*               DEFINICION DE LOS TIPOS DE DATOS
******************************************************************/

typedef struct participantes {
	char* nombre;
	bool tiro_balde;
	bool dono;
	lista_t* donaciones;
} participantes_t;

typedef struct type_datos dato_t;

typedef struct nominaciones nominaciones_t;

/*******************************************************************
*            PRIMITIVAS PARA MANEJAR EL TP1
******************************************************************/

#ifndef DEFINICIONES_H
#define DEFINICIONES_H

/*******************************************************************
*            PRIMITIVAS PARA MANEJAR PARTICIPANTES
******************************************************************/



// Permite saber si el nombre del dato, corresponde al nombre del participante.
// Pre: dato no es NULL y participante corresponde a un char*
// Post: devuelte verdadero si coincide, falso en caso contrario.
bool participante_no_esta(void* dato, void* participante);

// Busca un participante en la lista.
// Pre: debe existir la lista.
// Post: devuelve en caso de que se encuentre la posicion de memoria
// donde se encuentra el participante. En caso de no encontrarse NULL.
void* participante_buscar(char* participante,lista_t* lista_participantes);

// Recive el nombre de un participante y lo agrega a lista de participantes.
// Pre: El participante no debe estar en la lista. La lista existe.
// Post: devuelve NULL en caso de que falle, sino devuelte el participante.
void* participante_agregar(char* participante, lista_t* lista_participantes, lista_iter_t* iter);

// Destruye el participante.
void participante_borrar(void* dato);

/*******************************************************************
*                      PRIMITIVAS DONACIONES
******************************************************************/

// Agrega una donacion a un participante, recive la estructura y el dinero.
// Pre: El participante debe existir.
// NOTA: Se usa size_t porque es un valor positivo siempre.
void donaciones_agregar(participantes_t* participante,size_t dinero);

// Procesa el pedido de donacion de los participantes.
// Pre: la lista debe existir. 
// Post: devuelve falso en caso de que la cantidad ingresada es invalida,
// ya sea por ser menor a 0 o ser un caracter no numerico.
bool donar(lista_t* lista_participantes,lista_iter_t* iter, char* participante, void* extra);

// Imprime las donaciones realizadas por lo participantes.
void donaciones_imprimir(lista_t* donaciones);

// Destruye las donaciones realizadas por los participantes.
void donaciones_destruir(void* dato);

/*****************************************************************
 *                  PRIMITIVAS DE NOMINACIONES
 ******************************************************************/

// Imprime la lista de los participantes nominados y su correspondiente estado
// segun halla sido correcta o no su nominacion.
bool nominaciones_imprimir(void* nominaciones, void* extra );

// Destruye los participantes a ser nominados.
void nominados_participantes_destruir(void* dato);

// Crea la lista de participantes a nominar.
// Post: devuelte una lista en la cual estan todos los participantes
// enlistados en el orden correspondiente.
void* nominados_crear_lista(void* extra);

// Agrega los participantes a nominar solo si no estan en la lista.
// Post: devuelve la lista de los participantes, con su correspondiente
// estado segun hallan podido ser nominados o no. En caso de que el participante
// que pretende nominar no este en la lista o no halla donado devuelte NULL.
void* nominar(lista_t* lista_participantes,lista_iter_t* iter, char* participante, lista_t* nominados_participante);

/*******************************************************************
*                      PRIMITIVAS TIRAR_BALDE
******************************************************************/

// Toma la decicion de tirar el balde.
// Post: en caso de que el participante que pretende tirarse el balde no es el proximo
// en el orden de aparicion, devuelve ERROR5, y si el participante decide no tirarse el
// balde, pero no dono dinero devuelte ERROR6, si no se produce ningun erro devuelve
// la lista de las donaciones realizadas.
void* tirar_balde(lista_iter_t* iter_nominados,char* participante, void* extra);


#endif // DEFINICIONES_H
