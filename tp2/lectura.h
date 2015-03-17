#ifndef LECTURA_H
#define LECTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cola.h"

// Funcion auxiliar para ingreso de texto por teclado
// Pre: -
// Post: Devuelve un puntero a una porcion de memoria con el texto indicado.
// En caso de fallar, devuelve NULL
// Recordar: La memoria es reservada dentro de la funcion, el usuario deberia
// de liberarla.
char* leer_linea();

// FUNCION PARA DIVIDIR LA ENTRADA EN PALABRAS Y COLOCARLAS EN UNA COLA
// Pre: debo tener la entrada del usuario leida en un char*
// Post: devuelvo una cola con las palabras de la entrada.
cola_t* dividir_linea(char* linea);

#endif //LECTURA_H
