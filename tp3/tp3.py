from programa_principal import *

def main():
	grafo = cargar_grafo( procesar_archivo() )

	if grafo :
		entrada = procesar_input()
		cola = procesar_entrada(entrada)
		while len(cola) > 0 :
			comando = cola.popleft()
			procesar_comandos(grafo,comando,cola)
			entrada = procesar_input()
			cola = procesar_entrada(entrada)
	print "FIN DE PROGRAMA"
	return

main()
