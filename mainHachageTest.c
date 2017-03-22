#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hachage.h"

int main(int argc,char* *argv)
{
	Chaines C;
	if(argc!=2){
		printf("Il faut au moins un argument\n");
		return 1;}
	char* nomfic=strdup(argv[1]);
	FILE* f;
	
	f=fopen(nomfic,"r");
	if(f==NULL){
		printf("Le fichier n'a pas pu être ouvrir\n");
		return 1;
	}
	printf("Lecture\n");
	lectureChaine(f,&C);
	fclose(f);

	//TableHachage* th = creerTableHachage( &C );
	//afficheHachage( th );
	//Reseau* R = reconstitueReseauListe(&C);
	Reseau* R = recreeReseauHachage(&C);
	afficheReseauSVG( R, "aff_reseau" );



	return 0;

}