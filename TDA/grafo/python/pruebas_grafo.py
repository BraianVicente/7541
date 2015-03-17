from grafo import *
from lectura import *
from random import choice
from collections import deque
from heapq import*
NO_VISITADO = False
VISITADO = True


#from <modulo> import <def_01>
# En caso de poner '*' se importan todos los modulos.
def print_test(cadena,bool):

	if (bool):
		print cadena + ": OK"
	else:
		print cadena + ": ERROR"
	return

def generar_claves():
	"""GENERA CLAVES ALEATORIAS DE UNA LONGITUD DE 10 CARACTERES"""
	longitud = 10
	valores = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

	p = ""
	p = p.join([choice(valores) for i in range(longitud)])
	return p

def pruebas_volumen(vol):
	print
	print "INICIO DE PRUEBAS EN VOLUMEN"
	grafo = Grafo()
	lista = []
	i = 0
	while i < vol :
		lista.append(generar_claves())
		i = i + 1
	#Lo que hace split es trozar la cadena a una lista

	for v in lista:
		ok = grafo.vertice_agregar(v)
		if not ok: break
	print_test("AGREGAR VERTICES EN VOLUMEN", ok)
	print "SE AGREGARON", vol, "VERTICES"
	i = 0
	for r in range(vol/100,vol):
		for w in range(0,vol/100):
			ok = grafo.arista_agregar(lista[r],lista[w])
			if not ok: break
			i = i + 1
		if not ok: break
		i = i + 1
	print_test("AGREGAR ARISTAS EN VOLUMEN", ok)
	print "SE AGREGARON", i, "ARISTAS"

	return

def pruebas_aristas():
	print
	print "INICIO PRUEBAS ARISTAS"
	lista = [0,1,2,3,4]

	grafo = Grafo()

	print_test("GRAFO ESTA VACIO", grafo.grafo_esta_vacio() )
	for v in lista:
		ok = grafo.vertice_agregar(v)
		if not ok: break
	print_test("SE AGREGARON 5 VERTICES", ok)

	print_test("GRAFO NO ESTA VACIO", not grafo.grafo_esta_vacio() )
	print_test("GRAFO NO TIENE 5 VERTICES", len(grafo) == 5 )

	print_test("AGREGAR ARISTA VERTICE_0/VERTICE_1",grafo.arista_agregar(lista[0],lista[1]) )
	print_test("AGREGAR ARISTA VERTICE_0/VERTICE_2",grafo.arista_agregar(lista[0],lista[2]) )
	print_test("VERTICE_0 Y VERTICE_1 SON ADYACENTES",grafo.adyacencia(lista[0],lista[1]) )
	print_test("VERTICE_0 Y VERTICE_2 SON ADYACENTES",grafo.adyacencia(lista[0],lista[2]) )
	print_test("VERTICE_1 Y VERTICE_2 NO SON ADYACENTES",not grafo.adyacencia(lista[1],lista[2]))
	print_test("BORRAR VERTICE_0",grafo.vertice_borrar(lista[0]) )

	print_test("VERTICE_0 Y VERTICE_1 NO SON ADYACENTES",not grafo.adyacencia(lista[0],lista[1]) )
	print_test("VERTICE_0 Y VERTICE_2 NO SON ADYACENTES",not grafo.adyacencia(lista[0],lista[2]) )
	print_test("NO SE PUEDE BORRAR ARISTA VERTICE_0/VERTICE_1",not grafo.arista_borrar(lista[0],lista[1]))
	print_test("NO SE PUEDE BORRAR ARISTA VERTICE_0/VERTICE_2",not grafo.arista_borrar(lista[0],lista[2]))
	print
	print_test("VERTICE_1 TIENE 0 ADYACENTES", grafo.adyacentes_cantidad(lista[1]) == 0 )
	print_test("AGREGAR ARISTA VERTICE_1/VERTICE_2",grafo.arista_agregar(lista[1],lista[2]) )
	print_test("AGREGAR ARISTA VERTICE_1/VERTICE_3",grafo.arista_agregar(lista[1],lista[3]) )
	print_test("AGREGAR ARISTA VERTICE_1/VERTICE_4",grafo.arista_agregar(lista[1],lista[4]) )
	print_test("VERTICE_1 TIENE 3 ADYACENTES", grafo.adyacentes_cantidad(lista[1]) == 3 )
	print
	print_test("VERTICE_2 TIENE 1 ADYACENTES", grafo.adyacentes_cantidad(lista[2]) == 1 )
	print_test("NO SE PUEDE AGREGAR ARISTA VERTICE_2/VERTICE_1",not grafo.arista_agregar(lista[2],lista[1]) )
	print_test("AGREGAR ARISTA VERTICE_2/VERTICE_3",grafo.arista_agregar(lista[2],lista[3]) )
	print_test("AGREGAR ARISTA VERTICE_2/VERTICE_4",grafo.arista_agregar(lista[2],lista[4]) )
	print_test("VERTICE_2 TIENE 3 ADYACENTES", grafo.adyacentes_cantidad(lista[2]) == 3 )
	print
	print_test("VERTICE_3 TIENE 2 ADYACENTES", grafo.adyacentes_cantidad(lista[3]) == 2 )
	print_test("NO SE PUEDE AGREGAR ARISTA VERTICE_3/VERTICE_1",not grafo.arista_agregar(lista[3],lista[1]) )
	print_test("NO SE PUEDE AGREGAR ARISTA VERTICE_3/VERTICE_2",not grafo.arista_agregar(lista[3],lista[2]) )
	print_test("AGREGAR ARISTA VERTICE_3/VERTICE_4",grafo.arista_agregar(lista[3],lista[4]) )
	print_test("VERTICE_3 TIENE 3 ADYACENTES", grafo.adyacentes_cantidad(lista[3]) == 3 )
	print
	print_test("VERTICE_4 TIENE 3 ADYACENTES", grafo.adyacentes_cantidad(lista[4]) == 3)
	print_test("NO SE PUEDE AGREGAR ARISTA VERTICE_4/VERTICE_1",not grafo.arista_agregar(lista[4],lista[1]) )
	print_test("NO SE PUEDE AGREGAR ARISTA VERTICE_4/VERTICE_2",not grafo.arista_agregar(lista[4],lista[2]) )
	print_test("NO SE PUEDE AGREGAR ARISTA VERTICE_4/VERTICE_3",not grafo.arista_agregar(lista[4],lista[3]) )
	print_test("VERTICE_4 TIENE 3 ADYACENTES", grafo.adyacentes_cantidad(lista[4]) == 3)
	print
	print "MOSTRAR CON FUNCION ADYACENTES_MOSTRAR"
	for v in grafo.claves():
		print "VERTICE: ",v
		grafo.adyacentes_mostrar(v)
	print
	print_test("BORRANDO VERTICE_4", grafo.vertice_borrar(lista[4]))
	print_test("VERTICE_1 TIENE 2 ADYACENTES", grafo.adyacentes_cantidad(lista[1]) == 2 )
	print_test("VERTICE_2 TIENE 2 ADYACENTES", grafo.adyacentes_cantidad(lista[2]) == 2 )
	print_test("VERTICE_3 TIENE 2 ADYACENTES", grafo.adyacentes_cantidad(lista[3]) == 2 )
	print
	print_test("BORRANDO VERTICE_3", grafo.vertice_borrar(lista[3]))
	print_test("VERTICE_1 TIENE 1 ADYACENTES", grafo.adyacentes_cantidad(lista[1]) == 1 )
	print_test("VERTICE_2 TIENE 1 ADYACENTES", grafo.adyacentes_cantidad(lista[2]) == 1 )
	print
	print_test("BORRANDO VERTICE_2", grafo.vertice_borrar(lista[2]))
	print_test("VERTICE_1 TIENE 0 ADYACENTES", grafo.adyacentes_cantidad(lista[1]) == 0 )
	print
	print_test("BORRANDO VERTICE_1", grafo.vertice_borrar(lista[1]))
	print_test("GRAFO ESTA VACIO",grafo.grafo_esta_vacio() )

	return

def pruebas_grafo_vacio():
	print
	print "PRUEBAS GRAFO VACIO"
	grafo = Grafo()
	print_test("GRAFO ESTA VACIO", grafo.grafo_esta_vacio() )
	print_test("NO SE PUEDE BORRAR VERTICE",not grafo.vertice_borrar(0) )
	print_test("NO SE PUEDE BORRAR ARISTA", not grafo.arista_borrar(0,1) )
	print_test("VERTICE NO PERTENECE", not grafo.vertice_pertenece(0) )
	print_test("VERTICES NO SON ADYACENTES", not grafo.adyacencia(0,1))

	return

def pruebas_archivos_iteradores():
	print
	print "PRUEBAS ARCHIVOS Y CAMINO MINIMO"
	grafo = cargar_grafo()
	print "SE BUSCA CAMINO ENTRE '5' Y '50' "
	ok = False
	for vertice in grafo.BFS(grafo.vertice_obtener('5')) :
		if vertice.clave == '50' :
			ok = True
			break
	print_test("EXISTE CAMINO ENTRE '5' Y '50' POR BFS", ok )
	ok = False
	for vertice in grafo.DFS(grafo.vertice_obtener('5')) :
		if vertice.clave == '50' :
			ok = True
			break
	print_test("EXISTE CAMINO ENTRE '5' Y '50' POR DFS", ok )
	return

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

def diametro(grafo):
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

def camino(grafo,clave_origen,destino_origen):
	print
	origen = grafo.vertice_obtener(clave_origen)
	destino = grafo.vertice_obtener(destino_origen)
	lista = BFS_LISTA_CAMINO_MINIMO(grafo,origen,destino)
	if len(lista) > 0 :
		print lista
	else:
		print "NO_EXISTE_CAMINO"

def main():
	pruebas_grafo_vacio()
	pruebas_aristas()
	pruebas_volumen(5000)
	pruebas_archivos_iteradores()
	return

main()

