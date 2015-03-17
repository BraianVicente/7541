from heapq import*
from collections import deque
from grafo import *
from lectura import *
NO_VISITADO = False
VISITADO = True
VALIDO = 0
VACIO = 0
MARCADO = -1
COMUN = 1
NO_ENTERADO = False
ENTERADO = True

class dato_extra(object):
	def __init__(self):
		self.lista = []



def BFS_LISTA_CAMINO_MINIMO(grafo,vert_origen,vert_destino):
	"""Funcion que recorre el grafo en anchira. Sirve para encon-
	trar, si existe, el camino minimo entre 2 vertices.
	Si el camino minimo existe, devuelte una lista inversa(destino->origen)
	sino devuelve None"""
	cola = deque()
	visitados = {}
	padre = {}
	for vertice in grafo.claves() :
		visitados[vertice] = NO_VISITADO
		padre[vertice] = None
	cola.append(vert_origen)
	while len(cola) > 0 :
		actual = cola.popleft()
		visitados[actual.clave] = VISITADO
		for ady in actual.adyacentes.values():
			if visitados[ady.clave] == NO_VISITADO :
				visitados[ady.clave] = VISITADO
				padre[ady.clave] = actual
				cola.append(ady)
		if actual.clave == vert_destino.clave and padre[actual.clave] != None :
			lista = []
			clave = padre[vert_destino.clave]
			while clave != vert_origen :
				lista.insert(0,clave.clave)
				clave = padre[clave.clave]
			return lista
	return None

def BFS_DISTANCIAS(grafo,vert_origen):
	"""Funcion que recorre el grafo en anchira(por niveles). Sirve para encon-
	trar, todos los caminos a distancia 1, 2, etc.
	Devuelve una lista que contiene una estructura que guarda la lista de ver-
	tices que estan a distancia
	sino devuelve None"""
	cola = deque()
	visitados = {}
	tiempo = 0
	distancias = []
	for vertice in grafo.claves() :
		visitados[vertice] = NO_VISITADO
	vert_origen.extra = tiempo
	cola.append(vert_origen)
	while len(cola) > 0 :
		actual = cola.popleft()
		visitados[actual.clave] = VISITADO
		tiempo = actual.extra + 1
		if len(distancias) < tiempo :
			distancias.append(dato_extra())
		for ady in actual.adyacentes.values():
			if visitados[ady.clave] == NO_VISITADO :
				visitados[ady.clave] = VISITADO
				ady.extra = tiempo
				distancias[tiempo-1].lista.append(ady.clave)
				cola.append(ady)
	return distancias

def marcar(total,marcados):
	if ((total/2) + 1 ) == marcados:
		return True
	return False

########################################################################
#                        COMANDOS OBLIGATORIOS                         #
########################################################################


def diametro(grafo):
	"""DOCUMENTACION  DIAMETRO
	Descripcion: Indica el maximo de todos los caminos minimos entre dos
	musicos de toda la red.
	Pre: El grafo deve existir.
	Post: Devuelve la lista de los vertices que forman el camino mas largo de
	todo el grafo. En caso de que el grafo no tenga ninguna arista, devuelve
	una lista vacia.
	"""
	diametro = []
	mayor = []
	distancias = []
	for origen in grafo.valores() :
		distancias = BFS_DISTANCIAS(grafo,origen)
		a = len(distancias)
		b = len(mayor)
		if a > b :
			mayor = distancias
			mayor_vertice = origen
	v = -1
	lista_destino = []
	long_list = len(lista_destino)
	while long_list <= 0 :
		lista_destino = mayor[v].lista
		long_list = len(lista_destino)
		v -= 1
	destino = grafo.vertice_obtener(lista_destino[0])
	lista = BFS_LISTA_CAMINO_MINIMO(grafo,mayor_vertice,destino)
	if lista != None :
		if len(lista) + 2 > len(diametro) :
			lista.insert(0,origen.clave)
			lista.append(destino.clave)
			diametro = lista
	return diametro


def main() :
	grafo = cargar_grafo()
	lista = diametro(grafo)
	print lista

main()
