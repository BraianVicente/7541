#!/usr/bin/env python
import sys
import re
from random import choice, randint


def parsear(palabras):
	return [p.strip() for p in palabras.splitlines() if p.strip()]

palabras = parsear("""
agua
animal
azul
barracas
biblioteca
birome
blanco
botella
calle
carton
cartucho
casa
chau
compu
cortina
cuaderno
elefante
emergencia
entrada
escritorio
facultad
FIUBA
fumar
gato
hash
hola
kiosko
lapicera
libreria
lista
madero
maquina
mochila
notepad
palermo
papel
paper
pared
paseo
perro
pizarron
plastico
plaza
pluma
probabilidad
prohibido
puerto
salida
tinta
tubo
ventilador
verde
zapatilla
""")

usuarios = parsear("""
rosita
fedeB
manuB
martinB
javi
diego
fedeE
mile
nacho
eze
fabri
fedeL
debbie
gaston
pabloN
daniR
sebas
daniS
jenny
""")

tags = {
	r'\{hashtag\}': lambda twits: choice(palabras),
	r'\{usuario\}': lambda twits: choice(usuarios),
	r'\{palabra\}': lambda twits: choice(palabras),
	r'\{cosa\}': lambda twits: choice((
		choice(palabras),
		'#' + choice(palabras),
		'@' + choice(usuarios),
	)),
	r'\{orden\}': lambda twits: choice(('cronologico', 'popular')),
	r'\{texto\}': lambda twits: ' '.join(palabra() for i in xrange(4)),
	r'\{id\}': lambda twits: str(randint(0, twits - 1)) if twits > 0 else "0",
}

def aleatorizar(cmd, twits):
	for r, f in tags.iteritems():
		cmd = re.subn(r, lambda x: f(twits), cmd)[0]
	return cmd

def generar_twits(n):
	comandos = (
		lambda twits: ("buscar #{hashtag} {orden} 10", twits),
		lambda twits: ("buscar @{usuario} {orden} 10", twits),
		lambda twits: ("twittear @{usuario} {cosa} {cosa} {cosa} {cosa}", twits + 1),
		lambda twits: ("favorito {id}", twits),
	)

	twits = 0

	for i in xrange(n):
		cmd, twits = choice(comandos)(twits)
		print aleatorizar(cmd, twits)

def uso():
	print "Enviar comandos aleatorios 'twittear', 'favorito' y 'buscar'"
	print
	print "Modo de uso:"
	print "   ", sys.argv[0], "[cantidad] | programa"
	print
	print "Parametros:"
	print "    cantidad: Cantidad de comandos a enviar. Por omision: 10000"
	print "    programa: Comando para ejecutar el TP. Por ejemlpo: ./tp2"

def main():
	if len(sys.argv) == 1 and sys.stdout.isatty():
		uso()
		return
	n = 10000
	if len(sys.argv) > 1:
		n = int(sys.argv[1])
	generar_twits(n)

if __name__ == '__main__':
	main()
