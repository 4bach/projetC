#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entree_sortie.h"
#include "Reseau.h"
#include "Chaine.h"




Noeud* rechercheCreeNoeudListe(Reseau* R,double x,double y){
	if(R==NULL){
		printf("Reseau vide\n");
		return NULL;
	}
	CellNoeud* courantcl=R->noeuds;
	while(courantcl){
		if(courantcl->nd->x==x && courantcl->nd->y==y){
			return courantcl->nd;
		}
		courantcl=courantcl->suiv;
	}
	Noeud* nv=(Noeud*)malloc(sizeof(Noeud));
	CellNoeud* Cl=(CellNoeud*)malloc(sizeof(CellNoeud));
	if(nv==NULL || Cl==NULL){
		printf("Erreur d'allocation de noeud\n");
		return NULL;
	}
	nv->num=R->nbNoeuds+1;
	nv->x=x;
	nv->y=y;
	nv->voisins=NULL;
	Cl->nd=nv;
	R->nbNoeuds++;
	Cl=R->noeuds;
	R->noeuds=Cl;
	return nv;	
}


Reseau* reconstitueReseauListe(Chaines* C){
	int bool=0;
	CellChaine* courant=C->chaines;
	Reseau* R=(Reseau*)malloc(sizeof(Reseau));
	R->nbNoeuds=0;
	R->gamma=C->gamma;
	R->noeuds=NULL;
	R->commodites=NULL;
	CellCommodite* courantco=NULL;
	CellPoint* cpoint=NULL;
	Noeud* precedent=NULL;
	Noeud * noeudCourant= NULL;
	while(courant){
		cpoint=courant->points;
		courantco=(CellCommodite*)malloc(sizeof(CellCommodite));
		while(cpoint){
			if(bool==0){
				noeudCourant = rechercheCreeNoeudListe(R,cpoint->x,cpoint->y);
				courantco->extrA=noeudCourant;
				bool++;
			}
			else{
				noeudCourant = rechercheCreeNoeudListe(R,cpoint->x,cpoint->y);
				CellNoeud * cellPrec = (CellNoeud *) malloc(sizeof(CellNoeud));
				cellPrec->nd = precedent;
				cellPrec->suiv = noeudCourant->voisins;
				noeudCourant->voisins = cellPrec;
				
				CellNoeud * cellCour = (CellNoeud *) malloc(sizeof(CellNoeud));
				cellCour->nd = noeudCourant;
				cellCour->suiv = precedent->voisins;
				precedent->voisins = cellCour;
				
				
				if(cpoint->suiv==NULL){
					courantco->extrB=noeudCourant;
				}
				
			}
			cpoint=cpoint->suiv;
			precedent = noeudCourant;
		}
		bool=0;
		courantco=R->commodites;
		R->commodites=courantco;
		courant=courant->suiv;
	}
			
	return R;
	





}

