#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entree_sortie.h"
#include "Reseau.h"




Noeud* rechercheCreeNoeudListe(Reseau* R,double x,double y){
	if(R==NULL){
		printf("Reseau vide\n");
		return NULL;
	}
	CellNoeud* courantcl=R->noeuds;
	while(courantcl){
		if(courantcl->nd->x==x && courantcl->nd->y==y){
			printf("Noeud trouvé...Num:%d\n",courantcl->nd->num);
			return courantcl->nd;
		}
		courantcl=courantcl->suiv;
	}
	courantcl->nd=(Noeud*)malloc(sizeof(Noeud));
	if(courantcl->nd==NULL){
		printf("Erreur d'allocation de noeud\n");
		return NULL;
	}
	courantcl->nd->num=R->nbNoeuds+1;
	courantcl->nd->x=x;
	courantcl->nd->y=y;
	courantcl->nd->voisins=NULL;
	R->nbNoeuds++;
	printf("Noeud crée... Num:%d\n",courantcl->nd->num);
	return courantcl->nd;	
}
