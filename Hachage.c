#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Hachage.h"
#include "Chaine.h"
#include "Reseau.h"
#include "entree_sortie.h"

#define TAILLE 10


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

Noeud* rechercheCreeNoeudHachage( Reseau *R, TableHachage* H, double x, double y)
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
	H->T[i] = Cl2;
	H->nE++;
	return nv;	

}

void afficheHachage( TableHachage* tH ) 
{
	if( tH == NULL || tH->nE == 0) {
		printf("La table est vide\n");
		return;
	}
	int i;
	int cpt = 0;
	for( i = 0; i < tH->taille; i++ ) {
		CellNoeud* tmp = tH->T[i];
		while( tmp->nd != NULL ) {
			printf("X: %f  Y:%f\n",tmp->nd->x,tmp->nd->y);
			tmp = tmp->suiv;
			cpt++;
		}
		if( tmp->nd == NULL ) printf( "Position I = %d nulle\n", i  );
	}

}

//NE SERT A RIEN
TableHachage* creerTableHachage( Chaines *C ) 
{

	if(C==NULL) {
		return NULL;
	}

	TableHachage* tH = initTableHachage( TAILLE );
	CellChaine* tmp = C->chaines;
	Noeud* nv = NULL;
	int clef = 0;
	int i = 0;

	
	while( tmp ) {
	
		CellPoint* point_courant = tmp->points;
		printf("X: %f  Y:%f\n",point_courant->x,point_courant->y);
		while( point_courant ) {
			
			nv = construitNoeud( point_courant->x, point_courant->y, tH->nE );
			CellNoeud* cn = creerCellNoeud( nv );	
			clef = fonctionClef( nv->x, nv->y );
			i = fonctionHachage( clef, tH->taille );
			cn->suiv = tH->T[i];
			tH->T[i] = cn;
			tH->nE++;
			//printf("X: %f  Y:%f\n",point_courant->x,point_courant->y);
			point_courant = point_courant->suiv;
		}
		tmp = tmp->suiv;
	}
	return tH;

}

//NE MARCHE PAS
Reseau* recreeReseauHachage(Chaines *C) 
{	
	TableHachage* th = initTableHachage( TAILLE );
	int bool=0;
	CellChaine* courant=C->chaines;

	Reseau* R = intialiseReseau();
	R->gamma=C->gamma;

	CellCommodite* courantco=NULL;
	CellPoint* cpoint=NULL;
	Noeud* precedent=NULL;
	Noeud * noeudCourant= NULL;

	while( courant ) {

		cpoint=courant->points;
		courantco=(CellCommodite*)malloc(sizeof(CellCommodite));

		while( cpoint ) {
			if( bool==0 ) {
				noeudCourant = rechercheCreeNoeudHachage( R, th, cpoint->x,cpoint->y);
				courantco->extrA = noeudCourant;
				bool++;
			}
			else{
				noeudCourant = rechercheCreeNoeudHachage( R, th, cpoint->x, cpoint->y );
				CellNoeud * cellPrec = ( CellNoeud* )malloc( sizeof( CellNoeud ) );
				cellPrec->nd = precedent;
				cellPrec->suiv = noeudCourant->voisins;
				noeudCourant->voisins = cellPrec;
				
				CellNoeud* cellCour = ( CellNoeud* )malloc( sizeof( CellNoeud ) );
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
		courantco->suiv=R->commodites;
		R->commodites=courantco;
		courant=courant->suiv;
	}
	//afficheHachage( th );
	return R;
}









