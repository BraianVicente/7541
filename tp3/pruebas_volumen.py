from programa_principal import *
SALTO_LINEA = '\n'


def volumen():
	grafo = cargar_grafo(procesar_archivo())
	archivo = cargar_pruebas()
	print
	for linea in archivo :
		print SALTO_LINEA + linea[:-1]
		cola = procesar_entrada(linea)
		comando = cola.popleft()
		procesar_comandos(grafo,comando,cola)
	return

volumen()
