# Makefile: PhotoLab

#variable definitinos
CC	= gcc
DEBUG	= -g -ddebug
#DEBUG 	= -O2 -DNDEBUG
CFLAGS	= -Wall -ansi -std=c99 $(DEBUG) -c
LFLAGS	= -Wall $(DEBUG)


#convenience targets
all: PhotoLab
		
clean: 
	rm -f PhotoLab.o
	rm -f Advanced.o
	rm -f DIPs.o
	rm -f FileIO.o
	rm -f PhotoLab

PhotoLabTest: PhotoLab DIPs.o Advanced.o PhotoLab.o FileIO.o
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o
	$(CC) $(CFLAGS) PhotoLab.c -o PhotoLab.o
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o
	$(CC) $(LFLAGS) Advanced.o FileIO.o DIPs.o PhotoLab.o
	./PhotoLabTest

PhotoLab: Advanced.o FileIO.o PhotoLab.o DIPs.o
	$(CC) -Wall -ansi -std=c99 -o PhotoLab Advanced.o FileIO.o PhotoLab.o DIPs.o


#compilation rules
Advanced.o: Advanced.c Advanced.h Constants.h  
	$(CC) -Wall -ansi -std=c99 -c Advanced.c -o Advanced.o 

FileIO.o: FileIO.c FileIO.h Constants.h
	$(CC) -Wall -ansi -std=c99 -c FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h FileIO.h Advanced.h
	$(CC) -Wall -ansi -std=c99 -c DIPs.c -o DIPs.o

PhotoLab.o: PhotoLab.c Constants.h FileIO.h Advanced.h DIPs.h Debug.h
	$(CC) -Wall -ansi -std=c99 -c PhotoLab.c -o PhotoLab.o

