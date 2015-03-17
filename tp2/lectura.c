#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cola.h"

#define TAMANIO_INICIAL_BUFFER 10
#define FIN_LINEA '\n'
#define FIN_STRING '\0'


char* leer_linea(){
        char c; 
        size_t tam = TAMANIO_INICIAL_BUFFER; 
        int i;

        char* buffer = malloc(sizeof(char)*(tam));
        if (!buffer) return NULL;

        for(i = 0; (c = getchar()) != FIN_LINEA && c != EOF; i++){ //leo hasta el enter o fin de archivo

                if(i + 1 == tam){ // si llego al tamanio de mi cadena
                        tam += tam;  // la forma de modificar tam es arbitraria
                        char* aux = realloc(buffer, tam * sizeof(char));
                        if(!aux) break;  // si falla realloc, termino aca
                        buffer = aux;
                }

                buffer[i] = c;
        }
        buffer[i] = FIN_STRING; // es necesario cerrar el string
        return buffer;
}

cola_t* dividir_linea(char* linea){

	cola_t* cola = cola_crear();
	char* buffer = malloc ((strlen(linea) + 1) * sizeof(char));
	size_t i, index;
	for (i = 0, index = 0; i <= strlen(linea); i++){
		if (linea[i] != ' '){
        buffer[index] = linea[i];
        index++;
		} else {
        buffer[index] = '\0';
        index = 0;
        cola_encolar(cola, buffer);
        buffer = malloc((strlen(linea) + 1) * sizeof(char));
		}
	}
	free(linea);//ya encole las palabras pidiendo memoria para c/u
	cola_encolar(cola,buffer);
	return cola;
}
