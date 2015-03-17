all: prueba_heap

VAL= valgrind --track-origins=yes --leak-check=full --show-reachable=yes
CC = gcc
CFLAG = -Wall -pedantic -g -std=c99

val:prueba_heap
	$(VAL) ./prueba_heap

exec: prueba_heap
	./prueba_heap

prueba_heap: heap prueba_heap.c
	$(CC) $(CFLAG) heap.o prueba_heap.c -o prueba_heap

heap: clean_screan heap.c heap.h
	$(CC) $(CFLAG) -c heap.c

clean_screan:
	reset
clean:
	rm *.o prueba_heap
