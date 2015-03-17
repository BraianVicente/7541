all: abb

VAL= valgrind --track-origins=yes --leak-check=full --show-reachable=yes
CC = gcc
CFLAG = -Wall -pedantic -g -std=c99

val:prueba_abb
	$(VAL) ./prueba_abb

run: prueba_abb
	./prueba_abb

prueba_abb: abb prueba_abb.c
	$(CC) $(CFLAG) abb.o pila.o prueba_abb.c -o prueba_abb

abb: pila abb.c abb.h
	$(CC) $(CFLAG) -c abb.c

pila: clean_screan pila.c pila.h
	$(CC) $(CFLAG) -c pila.c

clean_screan:
	reset
clean:
	rm *.o prueba_abb
