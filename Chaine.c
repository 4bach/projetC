#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chaine.h"
#include "entree_sortie.h"
#define TMAX 50



Chaines* lectureChaine(FILE *f){
		int nbchain,gma,nbpts;
		CellChaine* clchaine=NULL;
		//CellPoint* clpoint=NULL;
		char tempo[TMAX];
		
		if(F==NULL){
			printf("Erreur lors de l'ouverture du fichier.\n");
			return NULL;
		}
		GetChaine(f,T,tempo);
		nbchain=GetEntier(f);
		free(tempo);
		
		
		GetChaine(f,T,tempo);
		gma=GetEntier(f);

		SkipLine(f);
		
		
		clchaine->num=GetEntier(f);
		
		nbpts=GetEntier(f);
		for (i = 0; i <gma ; i++)
		{
			clchaine->points->x=GetReel(f);
			clchaine->points->y=GetReel(f);
			clchaine->points=clchaine->points->suiv;
		}
		
		
		
		
		
		
		
		
	
}
