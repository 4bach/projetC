GCC_FLAGS = -Wall
all: Chainmain 

entree_sortie.o	: entree_sortie.c
	gcc $(GCC_FLAGS) -c entree_sortie.c

Chaine.o: Chaine.c
	gcc $(GCC_FLAGS) -c Chaine.c


main.o	: Chainmain.c
	gcc $(GCC_FLAGS) -c Chainmain.c

Chainmain		: Chaine.o Chainmain.o entree_sortie.o
	gcc $(GCC_FLAGS) -o Chainmain Chainmain.o Chaine.o entree_sortie.o 

clean	:
	rm -f entree_sortie.o Chaine.o  Chainmain.o Chainmain 



