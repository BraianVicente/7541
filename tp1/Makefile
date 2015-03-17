all: tp1

VAL= valgrind --track-origins=yes --leak-check=full --show-reachable=yes
CC = gcc
CFLAG = -Wall -pedantic -g -std=c99

exec: tp1
	./tp1

val: tp1
	$(VAL) ./tp1

lectura: definiciones lectura.c lectura.h
	$(CC) $(CFLAG) -c lectura.c

definiciones: lista definiciones.c definiciones.h
	$(CC) $(CFLAG) -c definiciones.c

lista:  lista.c lista.h 
	$(CC) $(CFLAG) -c lista.c

tp1: lectura tp1.c
	$(CC) $(CFLAG) lista.o definiciones.o lectura.o tp1.c -o tp1

clean_screan:
	reset

clean:
	rm *.o tp1
