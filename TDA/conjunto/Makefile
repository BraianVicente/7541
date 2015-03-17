CC= gcc
CFLAGS= -Wall -pedantic -std=c99

OBJECTS= conjunto.o
EXEC= pruebas_conjunto

VALGRIND= valgrind --track-origins=yes --leak-check=full
VALGRIND-V= $(VALGRIND) -v 

#Configuracion Entrega
PADRON=96542
ARCHIVOS=*.c *.h Makefile 	#Tipos de archivos que se van a agregar
CUATRIMESTRE=2014-2C
ENTREGA=Conjunto
ENCODING=ISO-8859-1
OUTPUTFILE=out.ps 		 	#archivo intermedio
FORMATO=portrait 			#portrait o landscape (vertical u horizontal)
COLUMNAS=1 	  			#paginas por hoja (en columnas)
NUMEROS_LINEA=1   			#cada cuantas lineas se imprime el numero de linea

ARCHIVO_ENTREGA=$(PADRON)-$(ENTREGA)
NOMBRE_ZIP= $(ARCHIVO_ENTREGA).zip
NOMBRE_PDF= $(ARCHIVO_ENTREGA).pdf
ENCABEZADO = "[75.41] Algoritmos y Programacion II"
PIE = "Padron $(PADRON) (curso $(CUATRIMESTRE)) Entrega: $(ENTREGA)"
#Fin configuracion



all: run

$(OBJECTS): conjunto.c conjunto.h
	$(CC) $(CFLAGS) conjunto.c -g -c

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) pruebas_conjunto.c -o $(EXEC)

run: entrega $(EXEC)
	./$(EXEC)

valgrind: $(EXEC)
	$(VALGRIND) ./$(EXEC)

valgrind-verb: $(EXEC)
	$(VALGRIND-V) ./$(EXEC)

clean:
	rm -f *.o $(EXEC)


#Seccion Entrega
pdf: $(EXEC)
	a2ps $(ARCHIVOS) -Av --header=$(ENCABEZADO) --footer=$(PIE) --line-numbers=$(NUMEROS_LINEA) --borders=yes --columns=$(COLUMNAS)  --$(FORMATO) --output=$(OUTPUTFILE) --encoding=$(ENCODING) --tabsize=4 --major=columns --toc  | ps2pdf $(OUTPUTFILE) $(NOMBRE_PDF)
	rm -f *.ps #elimino los archivos temporales

entrega: pdf
	zip $(NOMBRE_ZIP) $(ARCHIVOS) *.pdf

clean_entrega: clean
	rm *.zip *.pdf
