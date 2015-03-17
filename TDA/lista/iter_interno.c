#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

bool imprimir_elemento(void *dato, void *extra)
{
	// extra contiene la dirección de la variable 'cuenta'
	int *cuenta = (int*)extra;
	printf("%d. %s\n", *cuenta, (char *)dato);
	(*cuenta)++;
	
	return true; // seguir iterando
}

int main()
{
	lista_t *super = lista_crear();
	
	lista_insertar_ultimo(super, "leche");
	lista_insertar_ultimo(super, "huevos");
	lista_insertar_ultimo(super, "pan");
	lista_insertar_ultimo(super, "mermelada");

	int cuenta = 0;
	lista_iterar(super, imprimir_elemento, &cuenta);
	printf("Tengo que comprar %d cosas\n", cuenta);
	
	lista_destruir(super, NULL);
}
