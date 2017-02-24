#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chaine.h"
#include "entree_sortie.h"



int main(int argc,char* *argv){
	Chaines* C=NULL;
	if(argc!=3){
		printf("Il faut deux arguments\n");
		return 1;}
	char* nomfic=strdup(argv[1]);
	char* fictest=strdup(argv[2]);
	FILE* f;
	
	FILE* F=fopen(fictest,"a");
	f=fopen(nomfic,"r");
	if(f==NULL || F==NULL){
		printf("Le fichier n'a pas pu être ouvrir\n");
		return 2;
	}
	printf("Lecture\n");
	C=lectureChaine(f);
	printf("Ecriture\n");
	ecrireChaineTxt(C,F);
	printf("FIN\n");
	fclose(f);
	fclose(F);
	return 0;
	
}
