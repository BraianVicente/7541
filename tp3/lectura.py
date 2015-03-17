from collections import deque
from grafo import *
from comandos import *
import sys
LECTURA = 'r'

# deque incluye una clase 'deque' que es mas eficiente que una lista como cola
# deque.append(elemento) agrega a la derecha
# deque.appendleft(elemento) agrega a la izquierda
# deque.pop(elemento) quita a la derecha
# deque.popleft(elemento) quita a la izquierda
# usar append y pop para pila
# usar append y popleft para cola

def procesar_input():
	return raw_input()

def procesar_entrada(entrada):
	"""DOCUMENTACION PROCESAR_ENTRADA.
	Devuelve una cola con las palabras que esten separadas por espacios.
	Ejemplo:
	> "Hola como andas?"
	cola = ['Hola','como','andas?']
	< cola
	cola.popleft()
	cola = ['como','andas?']
	< 'Hola'
	"""

	lista_entrada = entrada.split()
	salida = deque()
	for v in lista_entrada:
		salida.append(v)
	return salida

def procesar_archivo():
	"""Procesa entrada de archivos de texto.
	En caso de error devuelve None."""
	seguir = True
	cant = 0
	while seguir :
		entrada = raw_input("INGRESE NOMBRE DE ARCHIVO DEL GRAFO: ")
		try:
			archivo = open(entrada,LECTURA)
			seguir = False
		except:
			cant += 1
			print "ERROR DE ARCHIVO."
			if cant == 5 : return None

	return archivo

def cargar_grafo(archivo):
	"""Carga y devuelve un grafo desde un archivo de texto, se debe indicar el
	nombre (en caso de que este en la misma ruta que el programa) o la ruta
	del archivo.
	El formato del archivo debe ser el siguiente:
		N
		0 nombre0
		1 nombre1
		...
		N-1 nombre_N-1
		M
		0 id_x0 id_y0
		1 id_x1 id_y1
		...
		M-1 id_xM-1 id_yM-1

	Siendo N la cantidad de vertices y M la cantidad de aristas.
	Para crear una arista se debe indicar:
		id_xM verice de partida
		id_yM el vertice de llegada.
	"""
	grafo = Grafo()
	if not archivo : return
	vertices = archivo.readline()
	cant = int(vertices)
	tabla_vertices = {}
	while cant > 0 :
		vertices = archivo.readline()
		lista_vertices = vertices.split()
		grafo.vertice_agregar(lista_vertices[1])
		tabla_vertices[lista_vertices[0]] = lista_vertices[1]
		cant = cant - 1
	aristas = archivo.readline()
	cant = int(aristas)
	while cant > 0 :
		aristas = archivo.readline()
		lista_aritas = aristas.split()
		arista_1 = tabla_vertices[lista_aritas[1]]
		arista_2 = tabla_vertices[lista_aritas[2]]
		grafo.arista_agregar(arista_1,arista_2)
		cant = cant - 1
	archivo.close()
	return grafo

def cargar_pruebas():
	"""Procesa entrada de archivos de texto.
	En caso de error devuelve None."""
	seguir = True
	cant = 0
	while seguir :
		entrada = raw_input("INGRESE NOMBRE DEL ARCHIVO DE PRUEBAS: ")
		try:
			archivo = open(entrada,LECTURA)
			seguir = False
		except:
			cant += 1
			print "ERROR DE ARCHIVO."
			if cant == 5 : return None

	return archivo
