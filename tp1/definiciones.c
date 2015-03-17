#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "lista.h"
#define TAMANIO_INICIAL_BUFFER 2


/*******************************************************************
*             DEFINICION DE LOS TIPOS DE DATOS
******************************************************************/

typedef struct participantes
{
	char* nombre;
	bool tiro_balde;
	bool dono;
	lista_t* donaciones;
} participantes_t;

typedef struct type_datos
{
	char* nombre;
	void* participante;
	bool esta;
} dato_t;

typedef struct nominaciones
{
	char* nombre;
	char* estado;
} nominaciones_t;

/*******************************************************************
*            PRIMITIVAS PARA MANEJAR EL TP1
******************************************************************/

bool participante_no_esta(void* dato, void* participante);

void* participante_buscar(char* participante,lista_t* lista_participantes);

void* participante_agregar(char* participante, lista_t* lista_participantes, lista_iter_t* iter);

void participante_borrar(void* dato);

void donaciones_agregar(participantes_t* participante,size_t dinero);

bool donar(lista_t* lista_participantes,lista_iter_t* iter, char* participante, void* extra);

void donaciones_imprimir(lista_t* donaciones);

void donaciones_destruir(void* dato);

bool nominaciones_imprimir(void* nominaciones, void* extra );

void nominados_participantes_destruir(void* dato);

void* nominados_crear_lista(void* extra);

void* nominar(lista_t* lista_participantes,lista_iter_t* iter, char* participante, lista_t* nominados_participante);

void* tirar_balde(lista_iter_t* iter_nominados,char* participante, void* extra);



/*******************************************************************
*            PRIMITIVAS PARA MANEJAR PARTICIPANTES
******************************************************************/

bool participante_no_esta(void* dato, void* participante)
{
	dato_t* dato_participante;
	dato_participante = participante;
	participantes_t* participante_enlistado;
	participante_enlistado = dato;
	char* nombre = participante_enlistado->nombre;
	char* mi_participante = dato_participante->nombre;
	if ((strcmp(nombre,mi_participante)) == 0)
	{
		dato_participante->esta = true;
		dato_participante->participante = dato;
		return false;
	}
	return true;
}

void* participante_buscar(char* participante,lista_t* lista_participantes)
{
	dato_t* dato_participante = malloc(sizeof(dato_t));
	dato_participante->nombre = participante;
	dato_participante->esta = false;
	dato_participante->participante = NULL;
	lista_iterar(lista_participantes,participante_no_esta,dato_participante);
	void* mi_participante = dato_participante->participante;
	free(dato_participante);
	return mi_participante;
}

void* participante_agregar(char* participante, lista_t* lista_participantes, lista_iter_t* iter)
{
	participantes_t* mi_participante = malloc(sizeof(participantes_t));
	if (mi_participante == NULL) return NULL;

	lista_t* donaciones = lista_crear();

	char* nombre = malloc((1+strlen(participante))*sizeof(char));
	strcpy(nombre,participante);

	mi_participante->nombre = nombre;
	mi_participante->donaciones = donaciones;
	mi_participante->dono = false;
	mi_participante->tiro_balde = false;

	if (lista_iter_al_final(iter)) lista_insertar(lista_participantes,iter,mi_participante);
	else lista_insertar_ultimo(lista_participantes,mi_participante);

	return mi_participante;
}

void participante_borrar(void* dato)
{
	participantes_t* mi_participante = dato;
	lista_destruir(mi_participante->donaciones,free);
	free(mi_participante->nombre);
	free(mi_participante);
}

/*******************************************************************
*                      PRIMITIVAS DONACIONES
******************************************************************/

void donaciones_agregar(participantes_t* participante,size_t dinero)
{
	size_t* dinero_donado = malloc(sizeof(size_t));
	*dinero_donado = dinero;
	participante->dono = true;
	lista_insertar_primero(participante->donaciones,dinero_donado);
}

bool donar(lista_t* lista_participantes,lista_iter_t* iter, char* participante, void* extra)
{
	char* char_dinero = extra;
	char* finstr;
	int dinero;
	dinero = strtol(char_dinero,&finstr,10);

	if (strlen(finstr) > 0  ) return false;
	if (dinero <= 0) return false;

	void* encontrado = participante_buscar(participante,lista_participantes);
	if  (encontrado != NULL)
	{
		donaciones_agregar(encontrado,dinero);
		return true;
	}

	participantes_t* nuevo_participante = participante_agregar(participante,lista_participantes,iter);
	donaciones_agregar(nuevo_participante,dinero);
	return true;
}

void donaciones_imprimir(lista_t* donaciones)
{
	lista_iter_t* iter = lista_iter_crear(donaciones);
	printf("OK [");
	int* dinero;
	int total;
	total = 0 ;
	while(!lista_iter_al_final(iter))
	{
		void* dato = lista_iter_ver_actual(iter);
		dinero = dato;
		total = total + *dinero;
		printf("%i", *dinero);
		lista_iter_avanzar(iter);
		if (!lista_iter_al_final(iter)) printf(",");

	}
	printf("] TOTAL: %i\n",total);
	lista_iter_destruir(iter);
}

void donaciones_destruir(void* dato)
{
	lista_t* donaciones = dato;
	lista_destruir(donaciones,free);
}

/*****************************************************************
 *                  PRIMITIVAS DE NOMINACIONES
 ******************************************************************/

bool nominaciones_imprimir(void* nominaciones, void* extra )
{
	nominaciones_t* nominado = nominaciones;
	printf("%s %s\n",nominado->estado,nominado->nombre);
	return true;
}

void nominados_participantes_destruir(void* dato)
{
	nominaciones_t* nominado = dato;
	free(nominado->nombre);
	free(nominado);
}

// Secciona la cadena de la cual se reciven las nominaciones.
// Post: devuelte una lista con todos los nominados por el participante.
static void crear_nominaciones(lista_t* nominados_participante,char* str_nominados,size_t tam_str)
{
	char* nombre ;
	size_t tam;
	size_t i=0;
	size_t j;
	nominaciones_t* nominado;

	while (i<=tam_str)
	{
		tam = TAMANIO_INICIAL_BUFFER;
		j=0;
		nombre = malloc(sizeof(char)*(tam));

		while (str_nominados[i] != '\0' && str_nominados[i] != ' ' )
		{
			if(j + 1 == tam)
			{ // si llego al tamanio de mi cadena
				tam += tam;  // la forma de modificar tam es arbitraria
				char* aux = realloc(nombre, tam * sizeof(char));
				if(!aux) break;  // si falla realloc, termino aca
				nombre = aux;
			}
			nombre[j] = str_nominados[i];
			j++;
			i++;
		}
		i++;
		nombre[j] = '\0';
		nominado = malloc(sizeof(nominaciones_t));
		nominado->nombre = nombre;
		nominado->estado = NULL;
		lista_insertar_ultimo(nominados_participante,nominado);
	}
}


void* nominados_crear_lista(void* extra)
{
	lista_t* nominados_participante = lista_crear();
	char* str = extra;
	size_t tam_str = strlen(str);

	char str_nominados[tam_str];
	strcpy(str_nominados,str) ;

	crear_nominaciones(nominados_participante,str_nominados,tam_str);

	return nominados_participante;
}
// Agrega los participantes nominados a lista_participantes, solo si no se encuentran en
// ella, sea cualsea la razon.
// Post: los participantes nominados fueron agregados correctamente al sistema
// y asigna el correspondiente estado segun hallan podido ingresar o no al sistema.
static void agregar_nominados(lista_t* lista_participantes,lista_iter_t* iter,lista_t* nominados_participante)
{
	participantes_t* participante_nominado;
	nominaciones_t* dato_nominado;
	lista_iter_t* iter_nominaciones = lista_iter_crear(nominados_participante);

	dato_nominado = lista_iter_ver_actual(iter_nominaciones);
	participante_nominado = participante_buscar(dato_nominado->nombre,lista_participantes);

	while (!lista_iter_al_final(iter_nominaciones))
	{
		if ( participante_nominado == NULL)
		{
			dato_nominado->estado = "OK";
			participante_agregar(dato_nominado->nombre,lista_participantes,iter);
		}
		else
		{
			dato_nominado->estado = "ERROR4";
		}
		if(lista_iter_avanzar(iter_nominaciones))
		{
			dato_nominado = lista_iter_ver_actual(iter_nominaciones);
			if(dato_nominado != NULL) participante_nominado = participante_buscar(dato_nominado->nombre,lista_participantes);
		}

	}
	lista_iter_destruir(iter_nominaciones);

}


void* nominar(lista_t* lista_participantes,lista_iter_t* iter, char* participante, lista_t* nominados_participante)
{
	participantes_t* mi_participante;

	mi_participante = participante_buscar(participante,lista_participantes);
	if (mi_participante == NULL)
	{
		return NULL;
	}
	if (!mi_participante->dono)
 	{
		return NULL;
	}

	agregar_nominados(lista_participantes,iter,nominados_participante);

	return nominados_participante;
}

/*******************************************************************
*                      PRIMITIVAS TIRAR_BALDE
******************************************************************/

void* tirar_balde(lista_iter_t* iter_nominados,char* participante, void* extra)
{
	char* decision;
	decision = extra;
	participantes_t* dato_participante;
	dato_participante = lista_iter_ver_actual(iter_nominados);
	if (dato_participante == NULL) return "ERROR5";
	if ( strcmp(dato_participante->nombre,participante) != 0) return "ERROR5";
	if ( ( strcmp(decision,"no") == 0 ) && (!dato_participante->dono) ) return "ERROR6";
	lista_iter_avanzar(iter_nominados);
	dato_participante->tiro_balde = true;
	return dato_participante->donaciones;
}
