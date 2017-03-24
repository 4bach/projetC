GCC_FLAGS = -Wall -lm
all: Chainmain ReconstitueReseau mainHachageTest comparaison_main

entree_sortie.o	: entree_sortie.c
	gcc $(GCC_FLAGS) -c entree_sortie.c

SVGwriter.o	: SVGwriter.c
	gcc $(GCC_FLAGS) -c SVGwriter.c

Chaine.o: Chaine.c
	gcc $(GCC_FLAGS) -c Chaine.c

Hachage.o: Hachage.c
	gcc $(GCC_FLAGS) -c Hachage.c

Arbres.o: Arbres.c
	gcc $(GCC_FLAGS) -c Arbres.c

Reseau.o: Reseau.c
	gcc $(GCC_FLAGS) -c Reseau.c

Chainmain.o	: Chainmain.c
	gcc $(GCC_FLAGS) -c Chainmain.c

ReconstitueReseau.o	: ReconstitueReseau.c
	gcc $(GCC_FLAGS) -c ReconstitueReseau.c

mainHachageTest.o	: mainHachageTest.c
	gcc $(GCC_FLAGS) -c mainHachageTest.c

Chainmain		: Chaine.o Chainmain.o entree_sortie.o SVGwriter.o
	gcc $(GCC_FLAGS) -o Chainmain Chainmain.o Chaine.o entree_sortie.o SVGwriter.o

ReconstitueReseau	: ReconstitueReseau.o Reseau.o Chaine.o entree_sortie.o SVGwriter.o Hachage.o 
	gcc $(GCC_FLAGS) -o ReconstitueReseau ReconstitueReseau.o Reseau.o Chaine.o entree_sortie.o SVGwriter.o Hachage.o

mainHachageTest	: mainHachageTest.o Reseau.o Chaine.o entree_sortie.o SVGwriter.o Hachage.o Arbres.o
	gcc $(GCC_FLAGS) -o mainHachageTest mainHachageTest.o Reseau.o Chaine.o entree_sortie.o SVGwriter.o Hachage.o Arbres.o

comparaison_main : comparaison_main.o Reseau.o Chaine.o entree_sortie.o SVGwriter.o Hachage.o Arbres.o
	gcc $(GCC_FLAGS) -o comparaison_main comparaison_main.o Reseau.o Chaine.o entree_sortie.o SVGwriter.o Hachage.o Arbres.o


clean	:
	rm -f entree_sortie.o Chaine.o  Chainmain.o Chainmain SVGwriter.o Hachage.o mainHachageTest mainHachageTest.o comparaison_main comparaison_main.o




