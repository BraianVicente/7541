#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

void imprimir_super(lista_t *super)
{
	lista_iter_t *iter = lista_iter_crear(super);
	int i = 1;
	
	while (!lista_iter_al_final(iter))
	{
		char *elemento = lista_iter_ver_actual(iter);
		printf("%d. %s\n", i, (char *)elemento);
		lista_iter_avanzar(iter);
		i++;
	}
	lista_iter_destruir(iter);
}

int main()
{
	lista_t *super = lista_crear();
	
	lista_insertar_ultimo(super, "leche");
	lista_insertar_ultimo(super, "huevos");
	lista_insertar_ultimo(super, "pan");
	lista_insertar_ultimo(super, "mermelada");

	imprimir_super(super);

	lista_destruir(super, NULL);
}
