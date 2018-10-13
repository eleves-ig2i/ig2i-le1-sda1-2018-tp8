all : TP10.exe

LIBSRC=./libsrc/
LIB=./lib/
INCLUDE=./include/

TP10.exe :  $(LIB)libfichier.o  $(LIB)calculerCA.o
	gcc $(LIB)* main.c -o TP10.exe

./lib/libfichier.o : $(LIBSRC)/libfichier.c $(INCLUDE)libfichier.h
	gcc -c $(LIBSRC)libfichier.c -o  $(LIB)libfichier.o

./lib/calculerCA.o : $(LIBSRC)/calculerCA.c $(INCLUDE)calculerCA.h
	gcc -c $(LIBSRC)calculerCA.c -o  $(LIB)calculerCA.o

clean :
	rm *.exe  $(LIB)*
