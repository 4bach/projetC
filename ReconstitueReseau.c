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
	printf("|2: RECONSTITUER LE RESEAU AVEC TABLE DE HACHAGE\n");
	printf("|3: RECONSTITUER LE RESEAU AVEC LES ARBRES\n");
}

int main(int argc,char* *argv){
	Chaines C;
	int ch;
	if(argc!=3){
		printf("Il faut deux arguments\n");
		return 1;}
	char* nomfic=strdup(argv[1]);
	char* nomfic1=strdup(argv[2]);
	FILE* f;
	FILE* f1;
	Reseau* R;
	f=fopen(nomfic,"r");
	f1=fopen(nomfic1,"w");
	if(f==NULL || f1==NULL){
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
				ecrireReseauTxt(R,f1);
				afficheReseauSVG( R, "aff_reseauL" );
				break;

			case 2:
				printf("Reconstitution du réseau par table de hachage\n");
				R=recreeReseauHachage(&C);
				ecrireReseauTxt(R,f1);
				afficheReseauSVG( R, "aff_reseauH" );
				break;
			case 3:
				
				printf("Reconstitution du réseau en utilisant les arbres\n");
				
				break;
				
		}
	}while(ch!=0);
	
	printf("FIN\n");
	fclose(f);
	
	
	return 0;
	
}

