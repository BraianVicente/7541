VAL= valgrind --track-origins=yes --leak-check=full --show-reachable=yes
CC = gcc
CFLAG = -Wall -pedantic -g -std=c99
PRUEBAS = bash pruebas/correr-pruebas.sh ./tp2
PRUEBAS_VOLUMEN = python pruebas/pruebas-volumen.py 10000 | ./tp2



all: clean

exec: clean
	$(PRUEBAS)

manual: clean 
	$ ./tp2

val: clean
	$(PRUEBAS) -v

volumen: clean
	$(PRUEBAS_VOLUMEN)

clean: tp2
	rm *.o

tp2:comandos tp2.c
	$(CC) $(CFLAG) cola.o vector.o hash.o  heap.o  lista.o lectura.o comandos.o -o tp2 tp2.c

comandos:lectura comandos.c comandos.h
	$(CC) $(CFLAG)  -c comandos.c

lectura: hash lectura.c lectura.h
	$(CC) $(CFLAG) -c lectura.c

hash:lista hash.c hash.h
	$(CC) $(CFLAG) -c hash.c

lista:heap lista.c lista.h
	$(CC) $(CFLAG) -c lista.c

heap:cola heap.c heap.h
	$(CC) $(CFLAG) -c heap.c

cola:vector cola.c cola.h
	$(CC) $(CFLAG) -c cola.c

vector:clean_screen vector.c vector.h
	$(CC) $(CFLAG) -c vector.c

clean_screen:
	reset


