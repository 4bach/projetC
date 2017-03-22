#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chaine.h"
#include "entree_sortie.h"
#include "SVGwriter.h"
#include "Reseau.h"
#include "Hachage.h"

void menu(void)
{
	printf("--------------------MENU--------------------\n");
	printf("|0: QUITTER LE MENU\n");
	printf("|1: RECONSTITUER LE RESEAU AVEC LISTE_CHAINEES\n");
	printf("|2: METHODE A DEFINIR\n");
	printf("|3: METHODE A DEFINIR\n");
}

int main(int argc,char* *argv){
	Chaines C;
	int ch;
	if(argc!=2){
		printf("Il faut un argument\n");
		return 1;}
	char* nomfic=strdup(argv[1]);
	FILE* f;
	Reseau* R;
	f=fopen(nomfic,"r");
	if(f==NULL){
		printf("Le fichier n'a pas pu être ouvrir\n");
		return 2;
	}
	printf("Lecture\n");
	lectureChaine(f,&C);
	//afficheChaineSVG(&C,"graphe_chaine");
	do{

		menu();
		scanf("%d",&ch);

		switch(ch){

			case 1:
				printf("Reconstitution du réseau par liste chainée.\n");
				R=reconstitueReseauListe(&C);
				break;

			case 2:
				printf("Reconstitution du réseau par table de hachage\n");
				R= recreeReseauHachage(&C);
				break;
			case 3:
				
				printf("Methode à definir\n");
				
				break;
				
		}
	}while(ch!=0);
	
	printf("FIN\n");
	fclose(f);
	
	
	return 0;
	
}

