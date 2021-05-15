#######################################################################
# Homework Assignment 5, for EECS 22, Fall 2017
#
# Author: Tim Schmidt
# Date: 11/09/2017
#
# Makefile: Makefile for HW 5
#
#######################################################################

# Variables
CC = gcc
DEBUG = -g -DDEBUG
CFLAGS = -ansi -Wall -c
LFLAGS = -Wall

# Default target

######################### Generate object files #######################
# Target for MovieLab.o
MovieLab.o: MovieLab.c FileIO.h DIPs.h Movie.h Constants.h Image.h
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o

# Target for FileIO.o
FileIO.o: FileIO.h FileIO.c Constants.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

# Target for DIPs.o
DIPs.o: DIPs.h DIPs.c Constants.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

# Target for Image.o
Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c -o Image.o

# Target for ImageList.o
ImageList.o: ImageList.c ImageList.h
	$(CC) $(CFLAGS) ImageList.c -o ImageList.o

# Target for Movie.o
Movie.o: Movie.c Movie.h
	$(CC) $(CFLAGS) Movie.c -o Movie.o

######################### Generate the executable #####################
# Target for MovieLab
MovieLab: MovieLab.o FileIO.o Movie.o DIPs.o ImageList.o Image.o
	$(CC) $(LFLAGS) MovieLab.o FileIO.o DIPs.o ImageList.o Image.o Movie.o -o MovieLab

###############################  others  ##############################
# Target for clean-up
clean:
	rm -f *.o *.a $(DESIGN) 
