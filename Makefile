GCC_FLAGS = -Wall
all: Chainmain 

entree_sortie.o	: entree_sortie.c
	gcc $(GCC_FLAGS) -c entree_sortie.c

SVGwriter.o	: SVGwriter.c
	gcc $(GCC_FLAGS) -c SVGwriter.c

Chaine.o: Chaine.c
	gcc $(GCC_FLAGS) -c Chaine.c

<<<<<<< HEAD

main.o	: Chainmain.c
	gcc $(GCC_FLAGS) -c Chainmain.c

Chainmain		: Chaine.o Chainmain.o entree_sortie.o
	gcc $(GCC_FLAGS) -o Chainmain Chainmain.o Chaine.o entree_sortie.o 

clean	:
	rm -f entree_sortie.o Chaine.o  Chainmain.o Chainmain 
=======
main.o	: main.c
	gcc $(GCC_FLAGS) -c main.c

main	: Chaine.o main.o entree_sortie.o SVGwriter.o
	gcc $(GCC_FLAGS) -o main main.o Chaine.o entree_sortie.o SVGwriter.o

clean	:
	rm -f entree_sortie.o SVGwriter.o Chaine.o  main.o main 
>>>>>>> bc68ee71c06d564f7c76afcbbad62d9d4275a992



