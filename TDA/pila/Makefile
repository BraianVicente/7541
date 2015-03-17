all: val

VAL= valgrind --track-origins=yes --leak-check=full --show-reachable=yes
CC = gcc
CFLAG = -Wall -pedantic -g -std=c99

val:run
	$(VAL) ./prueba_pila

run: prueba_pila
	./prueba_pila

pila: pila.c pila.h
	$(CC) $(CFLAG) -c pila.c

prueba_pila: pila prueba_pila.c
	$(CC) $(CFLAG) pila.o prueba_pila.c -o prueba_pila

clean:
	rm *.o prueba_pila