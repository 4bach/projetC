GCC_FLAGS = -Wall -lm
all: Chainmain ReconstitueReseau

entree_sortie.o	: entree_sortie.c
	gcc $(GCC_FLAGS) -c entree_sortie.c

SVGwriter.o	: SVGwriter.c
	gcc $(GCC_FLAGS) -c SVGwriter.c

Chaine.o: Chaine.c
	gcc $(GCC_FLAGS) -c Chaine.c

Reseau.o: Reseau.c
	gcc $(GCC_FLAGS) -c Reseau.c

Chainmain.o	: Chainmain.c
	gcc $(GCC_FLAGS) -c Chainmain.c

ReconstitueReseau.o	: ReconstitueReseau.c
	gcc $(GCC_FLAGS) -c ReconstitueReseau.c

Chainmain		: Chaine.o Chainmain.o entree_sortie.o SVGwriter.o
	gcc $(GCC_FLAGS) -o Chainmain Chainmain.o Chaine.o entree_sortie.o SVGwriter.o

ReconstitueReseau	: ReconstitueReseau.o Reseau.o Chaine.o entree_sortie.o SVGwriter.o
	gcc $(GCC_FLAGS) -o ReconstitueReseau ReconstitueReseau.o Reseau.o Chaine.o entree_sortie.o SVGwriter.o

clean	:
	rm -f entree_sortie.o Chaine.o  Chainmain.o Chainmain SVGwriter.o




