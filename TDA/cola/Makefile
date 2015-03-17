all: val

VAL= valgrind --track-origins=yes --leak-check=full --show-reachable=yes
CC = gcc
CFLAG = -Wall -pedantic -g -std=c99

val: prueba_cola
	$(VAL) ./prueba_cola

cola: clean_screan cola.c cola.h
	$(CC) $(CFLAG) -c cola.c

prueba_cola: cola prueba_lu.c
	$(CC) $(CFLAG) cola.c prueba_cola.c -o prueba_cola

clean_screan:
	clear

clean:
	rm *.o prueba_cola
