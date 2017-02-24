GCC_FLAGS = -Wall
all: main 

entree_sortie.o	: entree_sortie.c
	gcc $(GCC_FLAGS) -c entree_sortie.c

SVGwriter.o	: SVGwriter.c
	gcc $(GCC_FLAGS) -c SVGwriter.c

Chaine.o: Chaine.c
	gcc $(GCC_FLAGS) -c Chaine.c

main.o	: main.c
	gcc $(GCC_FLAGS) -c main.c

main	: Chaine.o main.o entree_sortie.o SVGwriter.o
	gcc $(GCC_FLAGS) -o main main.o Chaine.o entree_sortie.o SVGwriter.o

clean	:
	rm -f entree_sortie.o SVGwriter.o Chaine.o  main.o main 



