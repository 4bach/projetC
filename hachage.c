#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Hachage.h"
#include "Chaine.h"
#include "Reseau.h"
#include "entree_sortie.h"



TableHachage* initTableHachage( int taille ) 
{
	TableHachage* th = (TableHachage*)malloc(sizeof( TableHachage) );

	if( th == NULL ) {
		printf("Erreur lors de l'allocation de la table de hachage\n");
		return NULL;
	}
	int i;
	th->nE = 0;
	th->taille = taille;
	th->T = ( CellNoeud** )malloc( sizeof( CellNoeud * ) * th->taille );
	if( th->T == NULL ) {
		printf("Erreur lors de l'allocation des cases de la table de hachage\n");
		return NULL;
	}
	for( i = 0; i < taille; i++ ) {
		th->T[i] = creerCellNoeud(NULL);
	}
	return th;
}

int fonctionClef( int x, int y ) 
{

	int val = 0;
	
	val = y + (( x + y )*( x + y + 1 ))/2;
	
	return val;
}

int fonctionHachage( int clef, int taille )
{	
	int tmp;
	double A = (sqrt(5) - 1)/2;
	tmp = (int)(clef * A);
	tmp = (int)(taille * ( clef * A - tmp ));
	return tmp;
}

Noeud* rechercheCreeNoeudHachage(Reseau *R, TableHachage* H, double x, double y)
{
	if(R==NULL){
		printf("Reseau vide\n");
		return NULL;
	}
	if(H==NULL){
		printf("Table Hachage Vide\n");
		return NULL;
	}
	int clef = fonctionClef( x, y );
	int i = fonctionHachage( clef, H->taille );

	CellNoeud* courantcl = H->T[i];
	while( courantcl->nd != NULL ) {
		if(courantcl->nd->x==x && courantcl->nd->y==y){
			return courantcl->nd;
		}
		courantcl=courantcl->suiv;
	}
	//ajout dans la liste des noeuds de R
	Noeud* nv = creerNoeud( R, x, y );
	CellNoeud* Cl = creerCellNoeud( nv );
	Cl->suiv=R->noeuds;
	R->noeuds=Cl;

	//ajout dans la table de hachage
	CellNoeud* Cl2 = creerCellNoeud( nv );
	Cl2->suiv = H->T[i];
	H->T[i] = Cl2->suiv;

	return nv;	

}


Reseau* recreeReseauHachage(Chaines *C) 
{

	return NULL;
}









