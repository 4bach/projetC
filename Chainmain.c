#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chaine.h"
#include "entree_sortie.h"



int main(int argc,char* *argv){
	
	if(argc!=2){
		printf("Il faut un argument\n");
		return 1;}
	char* nomfic=strdup(argv[1]);
	FILE* f;
	f=fopen(nomfic,"r");
	if(f==NULL){
		printf("Le fichier n'a pas pu être ouvrir\n");
		return 2;
	}
	printf("Lecture\n");
	lectureChaine(f);
	printf("FIN\n");
	return 0;
	
}
