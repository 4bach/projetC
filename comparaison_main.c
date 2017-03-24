#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Chaine.h"
#include "entree_sortie.h"
#include "SVGwriter.h"
#include "Reseau.h"
#include "Hachage.h"

void menu(void)
{
	printf("--------------------MENU--------------------\n");
	printf("|0: QUITTER LE MENU\n");
	printf("|1: CALCULER\n");
}






int main(int argc,char* *argv){
	Chaines C;
	int ch;
	float tmps1,tmps2;
	clock_t t1,t2;
	if(argc!=3){
		printf("Il faut deux arguments\n");
		return 1;}
	char* nomfic=strdup(argv[1]);
	char* nomfic1=strdup(argv[2]);
	FILE* f;
	FILE* f1;
	Reseau* R;
	Reseau* R1;
	//Reseau* R2;
	f=fopen(nomfic,"r");
	f1=fopen(nomfic1,"a");
	if(f==NULL || f1==NULL){
		printf("Le fichier n'a pas pu être ouvrir\n");
		return 2;
	}
	printf("Lecture\n");
	lectureChaine(f,&C);
	
	fprintf(f1,"Test pour le fichier %s\n",nomfic);
	do{

		menu();
		scanf("%d",&ch);

		switch(ch){

			case 1:
				
				
				t1=clock();
				R=reconstitueReseauListe(&C);
				t2=clock();
				tmps1=(float)(t2-t1)/CLOCKS_PER_SEC;
				fprintf(f1,"Temps de calcul de reconstitution par Liste Chainée %f\n",tmps1);
				
				t1=clock();
				R1=recreeReseauHachage(&C);
				t2=clock();
				tmps2=(float)(t2-t1)/CLOCKS_PER_SEC;
				fprintf(f1,"Temps de calcul de reconstitution par table de hachage %f\n",tmps2);
				break;
				
		}
	}while(ch!=0);
	fprintf(f1,"\n\n");
	printf("FIN\n");
	fclose(f);
	
	
	return 0;
	
}
	
	
