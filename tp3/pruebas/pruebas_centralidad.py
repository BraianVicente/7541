from grafo import *
from lectura import *
from random import choice
from collections import deque
from heapq import*
NO_VISITADO = False
VISITADO = True

def centralidad(grafo,cantidad):
	print
	ok = False
	caminos	= {}
	heap = []
	for origen in grafo.valores() :
		for destino in grafo.valores() :
			lista = BFS_LISTA_CAMINO_MINIMO(grafo,origen,destino)
			if lista != None :
				for v in lista :
					if not caminos.has_key(v) :
						caminos[v] = 0
					caminos[v] = caminos[v] + 1

	for v in caminos.keys() :
		tupla = (-caminos[v],v)
		heappush(heap,tupla)
	for v in range(cantidad) :
		tupla =  heappop(heap)
		print tupla[1]
	return

def diametro():
	print
	grafo = cargar_grafo()
	diametro = []
	for origen in grafo.valores() :
		for destino in grafo.valores() :
			lista = BFS_LISTA_CAMINO_MINIMO(grafo,origen,destino)
			if lista != None :
				if len(lista) + 2 >= len(diametro) :
					lista.insert(0,destino.clave)
					lista.append(origen.clave)
					diametro = lista

	for v in diametro :
		print v

	return

def camino():
	print
	grafo = cargar_grafo()
	for origen in grafo.valores():
		for destino in grafo.valores():

			lista = BFS_LISTA_CAMINO_MINIMO(grafo,origen,destino)
			if lista or grafo.adyacencia(origen.clave,destino.clave) :

				lista.insert(0,origen.clave)
				lista.append(destino.clave)
				print lista
	print

def distancias():
	"""SIRVE PARA PRUEBAS EN VOLUMEN DE TODO EL GRAFO"""
	grafo = cargar_grafo()
	for origen in grafo.valores() :
		print
		print "distancias", origen.clave
		distancias = BFS_DISTANCIAS(grafo,origen)
		for v in range(len(distancias) - 1) :
			lista = distancias[v].lista
			tiempo = len(lista)
			if len(lista) > 0:
				cadena = ""
				for vert in lista:
					cadena += vert
					cadena += ' '

			print tiempo, cadena



def main():
	#diametro()
	camino()
	distancias()

main()
