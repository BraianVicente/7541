all: clean

VAL= valgrind --track-origins=yes --leak-check=full --show-reachable=yes
CC = gcc
CFLAG = -Wall -pedantic -g -std=c99


clean: prueba_vector
	rm *.o

exec: clean
	./prueba_vector

val: clean
	$(VAL) ./prueba_vector


prueba_vector: vector prueba_vector.c
	$(CC) $(CFLAG) vector.o -o prueba_vector prueba_vector.c

vector: clean_screan vector.c vector.h
	$(CC) $(CFLAG) -c vector.c

clean_screan:
	reset


