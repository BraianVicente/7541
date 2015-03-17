from collections import deque
NO_VISITADO = False
VISITADO = True

class vertice(object):
	def __init__(self,clave):
		self.adyacentes = {}
		self.extra = None
		self.clave = clave


class Grafo(object):
	"""GRAFO NO DIRIGIDO"""
	def __init__(self):
		self.tabla_vertices = {}

	def __len__(self):
		return len(self.tabla_vertices)

	def valores(self):
		"""Generador para poder iterar el grafo sobre los valores(Vertices)."""
		for v in self.tabla_vertices.values():
			yield v

	def claves(self):
		"""Generador para poder iterar el grafo sobre las claves."""
		for v in self.tabla_vertices.keys():
			yield v


	def DFS(self,vert_origen):
		"""Generador para poder iterar el grafo en profundidad. Sirve para en-
		contrar si existe un camino entre 2 vertices."""
		pila = deque()
		visitados = {}
		for vertice in self.claves() :
			visitados[vertice] = NO_VISITADO
		pila.append(vert_origen)
		while pila.__len__() > 0 :
			actual = pila.pop()
			yield actual
			for ady in actual.adyacentes.values():
				if visitados[ady.clave] == NO_VISITADO :
					visitados[ady.clave] == VISITADO
					pila.append(ady)

	def BFS(self,vert_origen):
		"""Generador para poder iterar el grafo en anchura. Sirve para encon-
		trar, si existe, el camino minimo entre 2 vertices."""
		cola = deque()
		visitados = {}
		for vertice in self.claves() :
			visitados[vertice] = NO_VISITADO

		cola.append(vert_origen)

		while cola.__len__() > 0 :
			actual = cola.popleft()
			yield actual
			for ady in actual.adyacentes.values():
				if visitados[ady.clave] == NO_VISITADO :
					visitados[ady.clave] = VISITADO
					cola.append(ady)



	def vertice_agregar(self,clave_vertice):
		""" Funcion Booleana. Si el grafo existe agrega un vertice. Ademas se
		le debe pasa un diccionario con los adyacentes ya cargados y los pesos
		de las aristas."""
		if ( self.vertice_pertenece(clave_vertice) ):
			return False
		vert = vertice(clave_vertice)
		self.tabla_vertices[clave_vertice] = vert
		return True

	def arista_agregar(self,vert_origen,vert_destino):
		"""Bool. Si el grafo existe, y los vertices pertenecen al grafo y ade-
		mas no existe una arista que una los vertices, la agrega.
		Agrega una arista a las 'listas' de adyacencia de los vertices.
		En caso de que la arista ya exista, devuelve False. Sino lo agrega y
		devuelve True"""
		if (vert_origen == vert_destino):
			return False
		if not ( self.vertice_pertenece(vert_origen) or self.vertice_pertenece(vert_destino) ):
			return False
		vertice = self.tabla_vertices[vert_origen]
		if ( not vertice.adyacentes.has_key(vert_destino) ):
			# Si no existe adyacencia agrego
			vertice.adyacentes[vert_destino] = self.tabla_vertices[vert_destino]

			# Llamo recursivamente a la funcion para que agrege a la lista de
			# adyacencia del otro vertice.
			self.tabla_vertices[vert_origen] = vertice # Posiblemente innecesario
			self.arista_agregar(vert_destino,vert_origen)
			return True
		return False

	def vertice_borrar(self,clave_vertice):
		"""Bool. Borra vertice del grafo. Si el vertice no existe o el grafo
		es vacio devuelve False, sino borra el vertice del grafo y las aristas
		que llegaban a el y devuelve True"""
		#borrar referencias de vecinos a este vertice
		if ( self.grafo_esta_vacio() ): return False
		if (not self.vertice_pertenece(clave_vertice) ): return False

		vertice = self.tabla_vertices[clave_vertice]
		# Itero la lista de adyacentes, y borro las aristas.
		# No se puede usar el iterador de diccionarios porque se borran elemento.
		lista = []
		for v in vertice.adyacentes:
			lista.append(v)

		for v in lista:
			self.arista_borrar(clave_vertice,v)

		vertice.adyacentes.clear()
		# borro referencia de vertice a vecinos
		self.tabla_vertices.pop(clave_vertice)

		return True

	def arista_borrar(self,vert_orig,vert_dest):
		"""Bool. Borra arista que une el orig con el dest del grafo. Si algun
		vertice no existe o el grafo es vacio devuelve False, Sino borra la
		arista entre los vertices y devuelve True"""
		if ( self.grafo_esta_vacio() ):
			return False
		if not ( self.vertice_pertenece(vert_orig) and self.vertice_pertenece(vert_dest) ):
			return False

		#usar funcion auxiliar queda feo. Borro refencia de uno a otro y viceversa
		vertice = self.tabla_vertices[vert_orig]
		vertice.adyacentes.pop(vert_dest)
		vertice = self.tabla_vertices[vert_dest]
		vertice.adyacentes.pop(vert_orig)
		return True

	def grafo_esta_vacio(self):
		"""Bool. Dice si el grafo esta vacio."""
		if len(self) > 0 : return False
		return True

	def vertice_pertenece(self,busq_vertice):
		"""Bool. Dice si el vertice pertenece a ese Grafo.
		Si pertenece devuleve True caso contrario False."""
		return self.tabla_vertices.has_key(busq_vertice)

	def vertice_obtener(self,busq_vertice):
		return self.tabla_vertices.get(busq_vertice)

	def adyacencia(self,v1,v2):
		"""Bool. Dice si v1 y v2 estan unidos por una arista"""
		if not (self.vertice_pertenece(v1) and self.vertice_pertenece(v2)) :
			return False
		vertice = self.tabla_vertices[v1]
		return vertice.adyacentes.has_key(v2)

	def adyacentes_cantidad(self,clave_vertice):
		vertice = self.tabla_vertices[clave_vertice]
		return len(vertice.adyacentes)

	def adyacentes_mostrar(self,clave_vertice):
		print self.tabla_vertices[clave_vertice].adyacentes.keys()

	def vertices_mostrar(self):
		print self.tabla_vertices.keys()


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
				lista.append(clave.clave)
				clave = padre[clave.clave]
			return lista
	return None

def BFS_DISTANCIAS(grafo,vert_origen):
	"""Funcion que recorre el grafo en anchira(por niveles). Sirve para encon-
	trar, todos los caminos a distancia 1, 2, etc.
	Devuelve un diccionario con
	sino devuelve None"""
	cola = deque()
	visitados = {}
	tiempo = 0
	distancias = {}
	for vertice in grafo.claves() :
		visitados[vertice] = NO_VISITADO
	vert_origen.extra = tiempo
	cola.append(vert_origen)
	while len(cola) > 0 :
		actual = cola.popleft()
		visitados[actual.clave] = VISITADO
		tiempo = actual.extra + 1
		if not distancias.has_key(tiempo):
			distancias[tiempo] = 0
		for ady in actual.adyacentes.values():
			if visitados[ady.clave] == NO_VISITADO :
				visitados[ady.clave] = VISITADO
				ady.extra = tiempo
				distancias[tiempo] = distancias[tiempo] + 1
				cola.append(ady)
	return distancias
