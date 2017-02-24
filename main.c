#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chaine.h"

void menu()
{
	
	printf( "1: LECTURE DU FICHIER\n" );
	printf( "2: AFFICHAGE DU FICHIER\n" );
}


int main(int argc, char* *argv)
{
	Chaines C;
	int ch;
	char* nomfic = strdup(argv[1]);

	FILE* f = fopen(nomfic,"r");
	if(f == NULL){
		printf("Le fichier n'a pas pu être ouvrir\n");
		return 2;
	}

	do{

		menu();
		scanf("%d",&ch);

		switch(ch){

			case 1:
				lectureChaine( f, &C );
				printf("Lecture\n");
				
				break;
			case 2:
				afficheChaineSVG( &C, "aff_chaines" );
				printf("Lecture\n");
				
				break;
		}

	}while(ch!=0);

	printf("FIN\n");
	return 0;
	
}
