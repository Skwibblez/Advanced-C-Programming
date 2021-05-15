 # design names
 DESIGN = PhotoLab PhotoLabTest

 #libs
 LIBS   = libFilter.a libFileIO.a

 CC     = gcc
 DEBUG  = -DDEBUG
 CFLAGS = -ansi -Wall -c
 LFLAGS = -ansi -Wall
 AR     = ar rc
 RANLIB = ranlib

 IMAGES = bw.ppm \
          negative.ppm \
          colorfilter.ppm \
          edge.ppm \
          vflipflip.ppm \
          shuffle.ppm \
          vmirror.ppm \
          border.ppm \
          noise.ppm \
          sharpen.ppm \
          posterize.ppm \
          blur.ppm
          all: PhotoLab PhotoLabTest
                                                                                                    ########### generate object files ###########

FileIO.o: FileIO.h FileIO.c Constants.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

DIPs.o: DIPs.h DIPs.c Constants.h
	$(CC) $(CFLAGS)  DIPs.c -o DIPs.o

Advanced.o: Advanced.h Advanced.c Constants.h
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o

PhotoLab.o: PhotoLab.c DIPs.h Advanced.h FileIO.h Constants.h
	$(CC) $(CFLAGS) PhotoLab.c -o PhotoLab.o

PhotoLab_DEBUG.o: PhotoLab.c DIPs.h Advanced.h FileIO.h Constants.h
	$(CC) $(CFLAGS) $(DEBUG) -c PhotoLab.c -o PhotoLab_DEBUG.o


# generate library files

#target to generate libFilter.a
libFilter.a: DIPs.o Advanced.o
	$(AR) libFilter.a Advanced.o DIPs.o
	$(RANLIB) libFilter.a


# generate executables

#target to generate PhotoLab
PhotoLab: PhotoLab.o FileIO.o libFilter.a
	$(CC) $(LFLAGS) PhotoLab.o FileIO.o -L. -lFilter -o PhotoLab

#target to generate test
PhotoLabTest: PhotoLab_DEBUG.o FileIO.o libFilter.a
	$(CC) $(lflags) PhotoLab_DEBUG.o FileIO.o -L. -lFilter -o PhotoLabTest
	
#target to clean the directory
clean:
	rm -f *.o *.jpg $(DESIGN) $(IMAGES) $(LIBS)

