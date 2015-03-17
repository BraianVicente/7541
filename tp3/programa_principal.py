from lectura import *
from comandos import *
from grafo import *
from collections import deque

RECOMENDAR = "recomendar"
DIFUNDIR = "difundir"
CENTRALIDAD = "centralidad"
CAMINO = "camino"
DIAMETRO = "diametro"
DISTANCIAS = "distancias"
IDENTACION = '\t'
COMA = ','
ESPACIO = ' '

ERROR_COMANDO = "ERROR COMANDO INVALIDO"
ERROR_PARAMETROS = "ERROR DE TIPEO"
ERROR_MUSICO = "ERROR NO EXISTE MUSICO"
ERROR_CANTIDAD = "ERROR CANTIDAD INVALIDA"
ERROR_CAMINO = "ERROR NO EXISTE CAMINO"


def comando_recomendar(grafo,cola):
	"""Si el musico no existe muestra por pantalla 'ERROR NO EXISTE MUSICO',
	sino lista los musicos recomendados para ese musico.
	Si se resiven mal los parametros devuelve 'ERROR DE TIPEO'
	Si la cantidad recomendaciones es mayor a la cantidad posible de recomen-
	dacines o si la cantidad es igual o menor a 0, muestra por pantalla
	'ERROR CANTIDAD INVALIDA'.
	"""
	try:
		musico = cola.popleft()
		if musico[-1] == COMA :
			print ERROR_PARAMETROS
			return
		if not grafo.vertice_pertenece(musico):
			print ERROR_MUSICO
			return
		cant = int(cola.popleft())
		if cant <= 0 :
			print ERROR_CANTIDAD
			return
		lista = recomendar(grafo,cola,musico,cant)
		if cant > len(lista):
			print ERROR_CANTIDAD
			return
		for i in lista :
			print i
	except:
		print ERROR_PARAMETROS

def comando_difundir(grafo,cola):
	"""Muestra por pantalla los musico a los cuales les llego la informacion.
	En caso de que el musico indicado no pertenezca a la red muestra por pan-
	talla 'ERROR NO EXISTE MUSICO'
	"""
	try:
		lista = difundir(grafo,cola)
		if len(lista) > 0:
			for clave in lista:
				print clave
	except:
		print ERROR_MUSICO

def comando_centralidad(grafo,cola):
	"""Muestra los musicos mas ce	ntrales.
	Si la cantidad de mayor a la cantidad de nodos centrales muestra por pan-
	talla 'ERROR CANTIDAD INVALIDA'
	Si se resiven mal los parametros devuelve 'ERROR DE TIPEO'
	"""
	cantidad = 0
	try:
		cantidad = int(cola.popleft())
		if cantidad <= 0 :
			print ERROR_CANTIDAD
			return
		lista_centralidad = centralidad(grafo,cantidad)
		for v in lista_centralidad :
			print v
	except:
		if not cantidad :
			print ERROR_PARAMETROS
			return
		print ERROR_CANTIDAD

def comando_camino(grafo,cola):
	""" Muestra el camino de un musico a otro(incluyendo ambos musico).
	El formato esperado es el siguiente:
	camino Musico_01, Musico_02
	Si se resiven mal los parametros devuelve 'ERROR DE TIPEO'
	Si no existe un camino entre los musicos muestra 'ERROR NO EXISTE CAMINO'
	Si no existe alguno de los musicos muestra 'ERROR NO EXISTE MUSICO'
	En caso de un error inesperado muestra 'ERROR NO ESPERADO'."""
	try:
		clave_origen = cola.popleft()
		clave_destino = cola.popleft()
		if (clave_origen[-1] != COMA ) :
			print ERROR_PARAMETROS
		else:
			clave_origen = clave_origen[:-1]
			if grafo.vertice_pertenece(clave_origen) and grafo.vertice_pertenece(clave_destino):
				lista_camino = camino(grafo,clave_origen,clave_destino)
				if lista_camino :
					for v in lista_camino :
						print v
				else :
					print ERROR_CAMINO
			else:
				print ERROR_MUSICO
	except:
		print ERROR_PARAMETROS

def comando_distancias(grafo,cola):
	"""Muestra la cantidad y los musicos a distancia 1, 2, 3, etc. del musico
	indicado.
	Si no existe el musico indicado muestra 'ERROR NO EXISTE MUSICO'
	Si se resiven mal los parametros devuelve 'ERROR DE TIPEO'
	"""
	try:
		clave_vertice = cola.popleft()
		if len(cola) > 0 :
			print ERROR_PARAMETROS
			return
		if not grafo.vertice_pertenece(clave_vertice) :
			print ERROR_MUSICO
			return
		lista_distancias = distancias(grafo,clave_vertice)
		for v in range(len(lista_distancias) - 1) :
			lista = lista_distancias[v].lista
			tiempo = len(lista_distancias[v].lista)
			cadena = ""
			for vert in lista:
				cadena += vert
				cadena += ESPACIO
			print tiempo,IDENTACION + cadena
	except:
		print ERROR_PARAMETROS

def comando_diametro(grafo,cola):
	"""Muestra los musicos que compenen el maximo camino minimo.
	Si se resiven mal los parametros devuelve 'ERROR DE TIPEO'"""
	try:
		if len(cola) != 0 :
			print ERROR_PARAMETROS
			return
		lista_diametro = diametro(grafo)
		diametro_grafo = len(lista_diametro) - 1
		print diametro_grafo
		for v in lista_diametro :
			print v
	except:
		print ERROR_PARAMETROS

def procesar_comandos(grafo,comando,cola):
	if comando == RECOMENDAR :
		comando_recomendar(grafo,cola)
		return
	if comando == DIFUNDIR :
		comando_difundir(grafo,cola)
		return
	if comando == CENTRALIDAD :
		comando_centralidad(grafo,cola)
		return
	if comando == CAMINO :
		comando_camino(grafo,cola)
		return
	if comando == DIAMETRO :
		comando_diametro(grafo,cola)
		return
	if comando == DISTANCIAS :
		comando_distancias(grafo,cola)
		return
	print ERROR_COMANDO
	return
