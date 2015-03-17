#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "conjunto.h"

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
    printf("%s: %s\n", name, result? "OK" : "ERROR");
}

bool prueba_instanciar_conjunto()
{
    conjunto_t* conjunto = conjunto_crear(-2);
    if (!conjunto) return true; // if (conjunto == NULL)
    conjunto_destruir(conjunto);
    return false;
}

bool prueba_instanciar_conjunto2()
{
    conjunto_t* conjunto = conjunto_crear(0);
    if (!conjunto) return true;
    conjunto_destruir(conjunto);
    return false;
}

bool prueba_instanciar_conjunto3()
{
	conjunto_t* conjunto = conjunto_crear(3);
	if (!conjunto) return false;
	conjunto_destruir(conjunto);
	return true;
}

/*bool prueba_instanciar_conjunto3()
{
    conjunto_t* conjunto = conjunto_crear(3);
    if (conjunto) return true;
    return false;
}*/

bool prueba_pertenece_a_vacio()
{
	conjunto_t* conjunto = conjunto_crear(2);
	bool resultado = ! conjunto_pertenece(conjunto,3);
    conjunto_destruir(conjunto);
    return resultado;
}

/* Ejecuta todas las pruebas. */
void pruebas_conjunto()
{
    print_test("Prueba instanciar conjunto negativo",prueba_instanciar_conjunto());
    print_test("Prueba instanciar conjunto nulo",prueba_instanciar_conjunto2());
    print_test("Prueba instanciar conjunto valido",prueba_instanciar_conjunto3());
    print_test("Prueba pertenece a conjunto vacio",prueba_pertenece_a_vacio());
}

/* Programa principal. */
int main(void)
{
    pruebas_conjunto();
    return 0;
}
