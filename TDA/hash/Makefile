all: hash

VAL= valgrind --track-origins=yes --leak-check=full --show-reachable=yes
CC = gcc
CFLAG = -Wall -pedantic -g -std=c99

exec: prueba_hash
	./prueba_hash

val: prueba_hash
	$(VAL) ./prueba_hash

hash: clean_screan hash.c
	$(CC) $(CFLAG) -g -c hash.c

prueba_hash: hash prueba_hash.c
	$(CC) $(CFLAG) hash.o  prueba_hash.c -o prueba_hash

clean_screan:
	reset

clean:
	rm *.o hash
