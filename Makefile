GCC_FLAGS = -Wall -lm
all: Chainmain 

entree_sortie.o	: entree_sortie.c
	gcc $(GCC_FLAGS) -c entree_sortie.c

SVGwriter.o	: SVGwriter.c
	gcc $(GCC_FLAGS) -c SVGwriter.c

Chaine.o: Chaine.c
	gcc $(GCC_FLAGS) -c Chaine.c



Chainmain.o	: Chainmain.c
	gcc $(GCC_FLAGS) -c Chainmain.c

Chainmain		: Chaine.o Chainmain.o entree_sortie.o SVGwriter.o
	gcc $(GCC_FLAGS) -o Chainmain Chainmain.o Chaine.o entree_sortie.o SVGwriter.o

clean	:
	rm -f entree_sortie.o Chaine.o  Chainmain.o Chainmain SVGwriter.o




