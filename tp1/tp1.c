#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "definiciones.h"
#include "lista.h"
#include "lectura.h"

#define TAMANIO_INICIAL_BUFFER 2
#define DONAR "donar"
#define NOMINAR "nominar"
#define TIRAR_BALDE "tirar_balde"

/*******************************************************************
*            TRABAJO PRACTICO ICE BUCKET CHALLANGE
******************************************************************/
// Se definio esta estructura para guardar los datos que contiene
// la entrada por teclado.
typedef struct salida{
	char* nombre;
	char* comando;
	char* extra;
}salida_t;

static char* seccionar_comandos(char* entrada, char* dato, size_t* actual)
{
	size_t tam = TAMANIO_INICIAL_BUFFER;
	size_t j = 0;
	dato = malloc(sizeof(char)*(tam));
	if (!dato) return NULL;
	while (entrada[*actual] != ' ')
	{
		if(j + 1 == tam)
		{ // si llego al tamanio de mi cadena
			tam += tam;  // la forma de modificar tam es arbitraria
			char* aux = realloc(dato, tam * sizeof(char));
			if(!aux) break;  // si falla realloc, termino aca
			dato = aux;
		}
		dato[j] = entrada[*actual];
		j++;
		*actual = *actual + 1;
	}
// Agrego fin de linea
	dato[j] = '\0';
	*actual = *actual + 1;

	return dato;

}

static char* seccionar_extra(char* entrada,char* dato,size_t* actual)
{
	size_t tam = TAMANIO_INICIAL_BUFFER;
	size_t j = 0;
	dato = malloc(sizeof(char)*(tam));
	if (!dato) return NULL;

	while (entrada[*actual] != '\0')
	{
		if(j + 1 == tam)
		{ // si llego al tamanio de mi cadena
			tam += tam;  // la forma de modificar tam es arbitraria
			char* aux = realloc(dato, tam * sizeof(char));
			if(!aux) break;  // si falla realloc, termino aca
			dato = aux;
		}
		dato[j] = entrada[*actual];
		j++;
		*actual = *actual + 1;
		}
// Agrego fin de linea
	dato[j] = '\0';

	return dato;

}
// Secciona la cadena, devuelve el nombre de participante, el comando
// elegido y un dato extra que luego es procesado segun el comando.
void* seccionar_cadena(char* entrada)
{

	salida_t* salida = malloc(sizeof(salida_t));
	if (!salida) return NULL;

	size_t i=0;
	salida->nombre = seccionar_comandos(entrada,salida->nombre,&i);
	if (!salida->nombre)
	{
		free(salida);
		return NULL;
	}

	salida->comando = seccionar_comandos(entrada,salida->comando,&i);
	if (!salida->comando)
	{
		free(salida->nombre);
		free(salida);
		return NULL;
	}

	salida->extra = seccionar_extra(entrada,salida->extra,&i);
	if (!salida->extra)
	{
		free(salida->nombre);
		free(salida->comando);
		free(salida);
		return NULL;
	}

	return salida;
}


static void comando_donar(lista_t* lista_participantes,lista_iter_t* iter, char* nombre, char* extra)
{
		bool resultado = donar(lista_participantes,iter,nombre,extra);
		if (resultado) printf("OK\n");
		else printf("ERROR1\n");
}

static void comando_nominar(lista_t* lista_participantes,lista_iter_t* iter,char* nombre,char* extra)
{
		lista_t* nominados_participante = nominados_crear_lista(extra);

		if (nominar(lista_participantes,iter,nombre,nominados_participante) == NULL )
		{
			participantes_t* mi_participante = participante_buscar(nombre,lista_participantes);
			if (mi_participante == NULL) printf("ERROR2\n");
			else if (!mi_participante->dono) printf("ERROR3\n");
		}
		else lista_iterar(nominados_participante,nominaciones_imprimir,NULL);

		lista_destruir(nominados_participante,nominados_participantes_destruir);
}

static void comando_tirar_balde(lista_t* lista_participantes,lista_iter_t* iter,char* nombre,char* extra)
{
		void* resultado = tirar_balde(iter,nombre,extra);
		if ( (strcmp (resultado,"ERROR5") == 0 )|| (strcmp (resultado,"ERROR6") == 0 ) )
		{
			char* res = resultado;
			printf("%s\n", res);
		}
		else
		{
		lista_t* resul_t;
		resul_t = resultado;
		donaciones_imprimir(resul_t);
		}
}

// Redirecciona a la operacion correspondiente, segun el comando
// recibido, imprime los resultados de las operaciones.
// OK: el participante realizo la donacion correctamente.
// OK nominado: el participante nominado se agrego correctamente al sistema.
// OK [DONACIONES*] TOTAL: N** : se muestra si la operacion de tirar_balde fue
// exitosa.
// *DONACIONES: lista inversa de las donaciones realizadas.
// **N: total de las donaciones realizadas.
// ERROR1: el valor ingresado es incorrecto. Ya sea porque no corresponde
// a un valor posivo, o si es un ingresa un dato no numerico.
// ERROR2: el participante que pretende nominar no esta en el sistema.
// ERROR3: el participante que pretende nominar esta en el sistema pero no
// realizo donaciones.
// ERROR4 nominado: el nominado ya esta en el sistema.
// ERROR5: el participante que pretende tirarse el balde no es el proximo
// en el orden de aparicion.
// ERROR6: el participante decide no tirarse el balde, pero no dono dinero.
void tomar_decicion(lista_t* lista_participantes, lista_iter_t* iter, salida_t* salida)
{
	if (strcmp(salida->comando,DONAR) == 0)
		comando_donar(lista_participantes,iter,salida->nombre,salida->extra);

	if (strcmp(salida->comando,NOMINAR) == 0)
		comando_nominar(lista_participantes,iter,salida->nombre,salida->extra);

	if (strcmp(salida->comando,TIRAR_BALDE) == 0 )
		comando_tirar_balde(lista_participantes,iter,salida->nombre,salida->extra);
}

int main()
{
	lista_t* lista_participantes = lista_crear();
	lista_iter_t* iter =  lista_iter_crear(lista_participantes);
	char* entrada = leer_linea();
	salida_t* salida;
	bool cont = true;
	if ( (strlen(entrada) == 0 )  ) cont = false;
	while (cont)
	{
		salida = seccionar_cadena(entrada);
		tomar_decicion(lista_participantes,iter,salida);
		free(salida->nombre);
		free(salida->comando);
		free(salida->extra);
		free(salida);
		free(entrada);
		entrada = leer_linea();
	if ( (strlen(entrada) == 0 )  ) cont = false;
	}
	free(entrada);
	lista_iter_destruir(iter);
	lista_destruir(lista_participantes,participante_borrar);
}
