from collections import deque
def main(cadena):
	cadena  = "difundir 44,45,38,12,25,43,32,31,28,20,3,13,11,2,4,22,5,29,9"
	lista_cadena = cadena.split()
	nueva_cadena = lista_cadena[0]
	lista = []
	i = 0
	lista.append("")
	for letra in nueva_cadena :
		if letra != ',' :
			lista[i] += letra
		else:
			i += 1
			lista.append("")
	cola = deque()
	for linea in lista:
		cola.append(linea)
	return cola

main()
