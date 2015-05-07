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

class Vertice(object):
	"""Vertices del grafo.
	Dispone de una tabla de adyacentes, representada como un diccionario, un
	dato extra no definido y la clave del mismo vertice."""
	def __init__(self,clave):
		self.adyacentes = {}
		self.extra = None
		self.clave = clave


class Grafo(object):
	"""TDA de un grafo no diricido y no pesado."""
	def __init__(self):
		self.tabla_vertices = {}

	def __len__(self):
		"""Indica el tamanio del grafo. Este se mide sobre la cantidad de
		vertices que tiene.
		Devuelve el valor correspondiente al tamanio del grafo."""
		return len(self.tabla_vertices)

	def valores(self):
		"""Generador para poder iterar el grafo sobre los valores(Vertices).
		Devuelve un objeto de la clase Vertice."""
		for v in self.tabla_vertices.values():
			yield v

	def claves(self):
		"""Generador para poder iterar el grafo sobre las claves.
		Devuelve la clave del vertice."""
		for v in self.tabla_vertices.keys():
			yield v

	def vertice_agregar(self,clave_vertice):
		"""Si el grafo existe y el vertine no existe lo agrega.
		Si el vertice ya existe devuelve falso, sino devuelve verdadero."""
		if ( self.vertice_pertenece(clave_vertice) ):
			return False
		vert = Vertice(clave_vertice)
		self.tabla_vertices[clave_vertice] = vert
		return True

	def vertice_borrar(self,clave_vertice):
		"""Borra el vertice del grafo. Si el vertice no existe o el grafo
		es vacio devuelve falso, sino borra el vertice del grafo y las aristas
		que llegaban a el y devuelve verdadero"""
		if ( self.grafo_esta_vacio() ): return False
		if (not self.vertice_pertenece(clave_vertice) ): return False
		vertice = self.tabla_vertices[clave_vertice]
		lista = []
		for v in vertice.adyacentes:
			lista.append(v)
		for v in lista:
			self.arista_borrar(clave_vertice,v)
		self.tabla_vertices.pop(clave_vertice)
		return True

	def vertice_pertenece(self,clave_vertice):
		"""Indica si el vertice pertenece a ese Grafo.
		Si pertenece devuleve veraddero caso contrario falso."""
		return self.tabla_vertices.has_key(clave_vertice)

	def vertice_obtener(self,clave_vertice):
		"""Devuelve el vertice.
		Si el vertice no pertenece al grafo devuelve None, sino devuelve
		un objeto de la clase Vertice."""
		if self.vertice_pertenece(clave_vertice) :
			return self.tabla_vertices.get(clave_vertice)
		return None

	def vertice_obtener_adyacentes(self,clave_vertice):
		"""Devuelve la lista de adyacencia del vertice.
		Si el vertice no pertenece al grafo, devuelve None, sino devuelve un
		diccionario con los adyacentes al vertice. """
		if self.vertice_pertenece(clave_vertice) :
			return self.tabla_vertices.get(clave_vertice).adyacentes
		return None

	def arista_agregar(self,vert_origen,vert_destino):
		"""Si el grafo existe, y los vertices pertenecen al grafo y no existe
		una arista que una ambos vertices, la agrega.
		Agrega una arista a las 'listas' de adyacencia de los vertices.
		En caso de que la arista ya exista o no exista alguno de los vertices devuelve falso, sino devuelve verdadero"""
		if (vert_origen == vert_destino):
			return False
		if not ( self.vertice_pertenece(vert_origen) or self.vertice_pertenece(vert_destino) ):
			return False
		vertice = self.tabla_vertices[vert_origen]
		if ( not vertice.adyacentes.has_key(vert_destino) ):
			vertice.adyacentes[vert_destino] = self.tabla_vertices[vert_destino]
			self.tabla_vertices[vert_origen] = vertice
			self.arista_agregar(vert_destino,vert_origen)
			return True
		return False

	def arista_borrar(self,vert_orig,vert_dest):
		"""Borra arista que une el vertice_orig con el vert_dest del grafo. Si
		algun vertice no existe o el grafo es vacio devuelve falso, sino borra
		la arista entre los vertices y devuelve verdadero"""
		if ( self.grafo_esta_vacio() ):
			return False
		if not ( self.vertice_pertenece(vert_orig) and self.vertice_pertenece(vert_dest) ):
			return False
		vertice = self.tabla_vertices[vert_orig]
		vertice.adyacentes.pop(vert_dest)
		vertice = self.tabla_vertices[vert_dest]
		vertice.adyacentes.pop(vert_orig)
		return True

	def grafo_esta_vacio(self):
		"""Funcion que indica si el grafo esta vacio.
		Si esta vacio devuelve verdadero, caso contrario devuelve falso."""
		if len(self) > 0 : return False
		return True

	def adyacencia(self,clave_v1,clave_v2):
		"""Dice si clave_v1 y clave_v2 estan unidos por una arista.
		Si no existe alguno de los vertices devuelve o no existe la arista
		devuelve falso, sino devuelve verdadero."""
		if not (self.vertice_pertenece(clave_v1) and self.vertice_pertenece(clave_v2)) :
			return False
		vertice = self.tabla_vertices[clave_v1]
		return vertice.adyacentes.has_key(clave_v2)

	def adyacentes_cantidad(self,clave_vertice):
		"""Devuelve la cantidad de adyacentes de un vertice."""
		vertice = self.tabla_vertices[clave_vertice]
		return len(vertice.adyacentes)
