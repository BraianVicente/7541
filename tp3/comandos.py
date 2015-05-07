#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  sin título.py
#  
#  Copyright 2015 champaine <champaine@champaine>
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  
#  
from heapq import*
from collections import deque
from grafo import *

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
def recomendar(grafo,cola,musico,cant):

	"""DOCUMENTACION RECOMENDAR
	Descripcion:
	Pre: recibo un grafo G precargado y una cola de palabras QP con
	primer parametro nombre del musico y segundo cantidad a recomendar
	Post: devuelvo lista de mensajes a mostrar
	"""
	tabla_recomendaciones = {}

	amigos_musico = grafo.vertice_obtener_adyacentes(musico)
	for amigo in amigos_musico:
		recomendaciones = grafo.vertice_obtener_adyacentes(amigo)
		for recomendado in recomendaciones:
			if recomendado != musico and not amigos_musico.has_key(recomendado):
				if not tabla_recomendaciones.has_key(recomendado):
					tabla_recomendaciones[recomendado] = 0
				tabla_recomendaciones[recomendado] += COMUN

	heap_recomendacion = []
	for i in tabla_recomendaciones.keys():
		cont = tabla_recomendaciones[i]
		tupla = (-cont,i)
		heappush(heap_recomendacion,tupla)

	mensaje = []
	while len(heap_recomendacion) > 0 and cant > 0 :
		tupla = heappop(heap_recomendacion)
		mensaje.append(tupla[1])
		cant -= 1

	return mensaje

def difundir(grafo,cola):
	"""Funcion que recorre el grafo por anchura. Sirve para hallar los verti-
	ces a los cuales les llegaria cierta informacion, si ciertos participantes
	la difunden.
	Pre: El grafo debe existir ya la cola no debe estar vacia. Se recibe
	una cola como parametro, que contenga las claves de los vertices que di-
	funden la informacion.
	Post: Devuele una lista con los vertices a quienes les llega la informacion.
	Si no le llega la informacion a ninguno, devuelve una lista vacia.
	En caso de que alguno de los vertices no pertenezca al grafo devuelve None
	"""

	visitados = {}
	enterados = {}
	originales = {}
	for vertice in grafo.valores() :
		visitados[vertice.clave] = NO_VISITADO
		enterados[vertice.clave] = NO_ENTERADO
		vertice.extra = 0

	cola_Enterados = deque()
	while len(cola) > 0 :
		clave_vertice = cola.popleft()
		if not grafo.vertice_pertenece(clave_vertice) : return None
		cola_Enterados.append(clave_vertice)
		originales[clave_vertice] = None

	while len(cola_Enterados) > 0 :
		clave_actual = cola_Enterados.popleft()
		actual = grafo.vertice_obtener(clave_actual)

		enterados[actual.clave] = ENTERADO

		for ady in actual.adyacentes.values():
			if enterados[ady.clave] == NO_ENTERADO :
				ady.extra += 1
				if marcar (len(ady.adyacentes),ady.extra) :
					cola_Enterados.append(ady.clave)
					enterados[ady.clave] = ENTERADO
	lista_clave = []
	for clave in enterados.keys():
		if enterados[clave] and not originales.has_key(clave):
			lista_clave.append(clave)

	return lista_clave

def centralidad(grafo,cantidad):
	"""DOCUMENTACION CENTRALIDAD.
	Descripcion: Debe calcular la centralidad de todos los vertices. Esta se
	calcula sabiendo en cuantos caminos minimos esta incluido un vertice.
	Mientras pertenezca a mas caminos minimos, mas centralidad tiene.
	Pre: El grafo debe existir.
	Post: Devuelve una lista con las claces de los vertices con mayor centralidad
	en orden decreciente.
	"""
	ok = False
	caminos	= {}
	heap = []
	centralidad = []
	cant = 0
	for origen in grafo.valores() :
		cant += 1
		if grafo.adyacentes_cantidad(origen.clave) > 0 :
			for destino in grafo.valores() :
				if grafo.adyacentes_cantidad(destino.clave) > 0 and not grafo.adyacencia(origen,destino):
					lista = BFS_LISTA_CAMINO_MINIMO(grafo,origen,destino)
					if lista != None :
						for v in lista :
							if not caminos.has_key(v) :
								caminos[v] = 0
							caminos[v] += 1
		if cant*10 > len(grafo) : break
	for v in caminos.keys() :
		tupla = (-caminos[v],v)
		heappush(heap,tupla)
	for v in range(cantidad) :
		tupla =  heappop(heap)
		centralidad.append(tupla[1])

	return centralidad

########################################################################
#                        COMANDOS OPTATIVOS                            #
########################################################################

def camino(grafo,clave_origen,clave_destino):
	"""DOCUMENTACION CAMINO.
	Descripcion: Indica por que musicos hay que pasar como minimo de un musico
	a otro.
	Pre: Debe indicarseles las claves los vertices de origen y destino.
	Post: Devuelve una lista con las claves de los vertices que vinculan a
	origen con destino.
	"""
	origen = grafo.vertice_obtener(clave_origen)
	destino = grafo.vertice_obtener(clave_destino)
	lista = BFS_LISTA_CAMINO_MINIMO(grafo,origen,destino)
	if not lista and not grafo.adyacencia(clave_origen,clave_destino) :
		return lista
	lista.insert(0,clave_origen)
	lista.append(clave_destino)
	return lista

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

def distancias(grafo,clave_vertice):
	"""DOCUMENTACION DISTANCIAS
	Descripcion: Lista la cantidad de musicos a distancia 1, a distancia 2, etc. del
	musico dado.
	Pre: El grafo debe existir.
	Post: Devuelve una lista que en la posicion 0 tiene una lista con todos
	los adyacentes a distancia 1, en la posicion 1  tiene una lista con todos
	los adyacentes a distancia 2, etc.
	Ejemplo: [[1,5,9,6,7], [2,8,3,4] , [0,10] ]

	"""
	if grafo.vertice_pertenece(clave_vertice) :
		vertice = grafo.vertice_obtener(clave_vertice)
		distancias = BFS_DISTANCIAS(grafo,vertice)
		return distancias
	else:
		return None
