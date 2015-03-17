all: val

VAL= valgrind --track-origins=yes --leak-check=full --show-reachable=yes
CC = gcc
CFLAG = -Wall -pedantic -g -std=c99

val: prueba_lista
	$(VAL) ./prueba_lista

lista: clean_screan lista.c lista.h
	$(CC) $(CFLAG) -c lista.c

prueba_lista: lista prueba_lista.c
	$(CC) $(CFLAG) lista.o prueba_lista.c -o prueba_lista

clean_screan:
	clear

clean:
	rm *.o prueba_lista