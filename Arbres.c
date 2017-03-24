#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Hachage.h"
#include "Chaine.h"
#include "Reseau.h"
#include "entree_sortie.h"
#include "Arbre.h"



void chaineCoordMinMax(Chaines* C, double* minx, double* miny, double* maxx, double* maxy)
{
	CellChaine* courant=C->chaines;
	CellPoint* cpoint=NULL;

	*minx=100;
	*miny=100;
	*maxx=0;
	*maxy=0;

	while(courant){
		
		cpoint=courant->points;
		while(cpoint){
			if(cpoint->x < *minx)
				*minx=cpoint->x;
			if(cpoint->y < *miny)
				*miny=cpoint->y;
			if(cpoint->x > *maxx)
				*maxx=cpoint->x;
			if(cpoint->y > *maxy)
				*maxy=cpoint->y;
			cpoint=cpoint->suiv;
		}
		courant=courant->suiv;
	}
}

void afficheArbre( ArbreQuat* a ) 
{
	if( !a ) {
		return;
	}
	if( a->noeud ) {
		printf( "Noeud, X = %f, Y = %f \n", a->noeud->x, a->noeud->y );
	}
	afficheArbre( a->ne );
	afficheArbre( a->se );
	afficheArbre( a->no );
	afficheArbre( a->no );
}

ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY)
{
	ArbreQuat* arbreQuat = ( ArbreQuat* )malloc( sizeof( ArbreQuat ) );
	arbreQuat->xc = xc;
	arbreQuat->yc = yc;
	arbreQuat->coteX = coteX;
	arbreQuat->coteY = coteY;
	arbreQuat->noeud = NULL;
	arbreQuat->so = NULL;
	arbreQuat->se = NULL;
	arbreQuat->no = NULL;
	arbreQuat->ne = NULL;
	return arbreQuat;
}

ArbreQuat* orientationArbre( double x, double y, ArbreQuat* a )
{
	ArbreQuat* arbre;
	if( ( x > a->xc ) && ( y > a->yc ) ) {
			arbre =  a->ne;
		}
		//SUD EST
		else if ( ( x > a->xc ) && ( y < a->yc ) ) {
			arbre = a->se;
		}
		//SUD OUEST
		else if ( ( x < a->xc ) && ( y < a->yc ) ) {
			arbre = a->so;
		}
		//NORD OUEST 
		else if ( ( x < a->xc ) && ( y > a->yc ) ) {
			arbre = a->no;
		}
		return arbre;
}

ArbreQuat* insererNoeudArbre(Noeud* n, ArbreQuat* a, ArbreQuat* parent)
{
	
	if( !a ) {
		int coteX = parent->coteX/2;
		int coteY = parent->coteY/2;
		int yc, xc;
		printf( "3 2 1 1\n" );

		//NORD EST
		if( ( n->x > parent->xc ) && ( n->y > parent->yc ) ) {
			yc = parent->yc + (1/2)*(coteY - parent->yc);
			xc = parent->xc + (1/2)*(coteX - parent->xc);
			a = creerArbreQuat( xc, yc, coteX, coteY );
			parent->ne = a;
			a->noeud = n;
		}
		//SUD EST
		else if ( ( n->x > parent->xc ) && ( n->y < parent->yc ) ) {
			yc = parent->yc - (1/2)*(coteY - parent->yc);
			xc = parent->xc + (1/2)*(coteX - parent->xc);
			a = creerArbreQuat( xc, yc, coteX, coteY );
			parent->se = a;
			a->noeud = n;
		}
		//SUD OUEST
		else if ( ( n->x < parent->xc ) && ( n->y < parent->yc ) ) {
			yc = parent->yc - (1/2)*(coteY - parent->yc);
			xc = parent->xc - (1/2)*(coteX - parent->xc);
			a = creerArbreQuat( xc, yc, coteX, coteY );
			parent->so = a;
			a->noeud = n;
		}
		//NORD OUEST 
		else if ( ( n->x < parent->xc ) && ( n->y > parent->yc ) ) {
			yc = parent->yc + (1/2)*(coteY - parent->yc);
			xc = parent->xc - (1/2)*(coteX - parent->xc);
			a = creerArbreQuat( xc, yc, coteX, coteY );
			parent->no = a;
			a->noeud = n;
		}

		return parent;

	}
	else if( a->noeud ) {
		

		Noeud* n_tmp = a->noeud;
		a->noeud = NULL;
		printf( "3 2 1\n" );

		a = insererNoeudArbre( n_tmp, a , parent );

		printf( "3 2 2\n" );

		a = insererNoeudArbre( n, a, parent );
		return parent;
		
		
		
	}
	//A PRECISER(CEST JUSTE UNE COPIE DE CELUI DE DESSUS)
	else if( !a->noeud && a ) {
		printf( "3 2 3\n" );
		if( ( n->x > a->xc ) && ( n->y > a->yc ) ) {
			a = insererNoeudArbre( n, a->ne ,a );

		}
		//SUD EST
		else if ( ( n->x > a->xc ) && ( n->y < a->yc ) ) {
			a = insererNoeudArbre( n, a->se ,a );

		}
		//SUD OUEST
		else if ( ( n->x < a->xc ) && ( n->y < a->yc ) ) {
			a = insererNoeudArbre( n, a->so ,a );

		}
		//NORD OUEST 
		else if ( ( n->x < a->xc ) && ( n->y > a->yc ) ) {
			a = insererNoeudArbre( n, a->no, a );

		}
	}
	return parent;
}

Noeud* chercherNoeudArbre(CellPoint* pt, Reseau* R, ArbreQuat** aptr, ArbreQuat* parent)
{
	Noeud* n;
	if( *aptr == NULL ) {
		printf( "3 1\n" );
		n = creerNoeud( R, pt->x, pt->y );
		parent = insererNoeudArbre( n, *aptr, parent );
		
		CellNoeud* Cl = creerCellNoeud( n );
		Cl->suiv=R->noeuds;
		R->noeuds=Cl;

		return n;
	}
	else if( (*aptr)->noeud != NULL ) {
		
		if( ( (*aptr)->noeud->x == pt->x ) && ( (*aptr)->noeud->y == pt->y ) ) {
			printf("test vrai\n");
			return (*aptr)->noeud;
		}
		printf( "3 2\n" );
		n = creerNoeud( R, pt->x, pt->y );
		parent = insererNoeudArbre( n, *aptr, parent );

		CellNoeud* Cl = creerCellNoeud( n );
		Cl->suiv=R->noeuds;
		R->noeuds=Cl;

		return n;
	}
	else if ( !(*aptr)->noeud && (*aptr) ){
		printf( "3 3\n" );
		if( ( pt->x > (*aptr)->xc ) && ( pt->y > (*aptr)->yc ) ) {

			n = chercherNoeudArbre( pt, R, &(*aptr)->ne, (*aptr));
		}
		//SUD EST
		else if ( ( pt->x > (*aptr)->xc ) && ( pt->y < (*aptr)->yc ) ) {

			n = chercherNoeudArbre( pt, R, &(*aptr)->se, *aptr);
		}
		//SUD OUEST
		else if ( ( pt->x < (*aptr)->xc ) && ( pt->y < (*aptr)->yc ) ) {

			n = chercherNoeudArbre( pt, R, &(*aptr)->so, (*aptr) );
		}
		//NORD OUEST 
		else if ( ( pt->x < (*aptr)->xc ) && ( pt->y > (*aptr)->yc ) ) {

			n = chercherNoeudArbre( pt, R, &(*aptr)->no, (*aptr) );
		}
	}
	return n;
}

Reseau* recreeReseauArbre(Chaines* C)
{

	double minx, miny, maxx, maxy;
	chaineCoordMinMax( C, &minx, &miny, &maxx, &maxy );
	double coteX = maxx - minx;
	double coteY = maxy - miny;
	ArbreQuat* parent = creerArbreQuat( coteX/2, coteY/2, coteX, coteY );
	ArbreQuat* enfant = NULL;
	
	CellChaine* courant=C->chaines;
	int bool = 0;
	Reseau* R = intialiseReseau();
	R->gamma=C->gamma;

	CellCommodite* courantco=NULL;
	CellPoint* cpoint=NULL;
	Noeud* precedent=NULL;
	Noeud * noeudCourant= NULL;
	
	while(courant){
		cpoint=courant->points;
		courantco=(CellCommodite*)malloc(sizeof(CellCommodite));
		while(cpoint){
				
			if(bool==0){

				noeudCourant = chercherNoeudArbre( cpoint, R, &enfant, parent);
				if( noeudCourant == NULL ) printf("noeud null\n");
				else printf( "%f %f\n",noeudCourant->x, noeudCourant->y );

				courantco->extrA=noeudCourant;
				bool++;
		
			}
			else{
				noeudCourant = chercherNoeudArbre( cpoint, R, &enfant, parent);
				if( noeudCourant == NULL ) printf("noeud null\n");
				else printf( "%f %f\n",noeudCourant->x, noeudCourant->y );
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
		courantco->suiv=R->commodites;
		R->commodites=courantco;
		courant=courant->suiv;
	}
	printf( "-----ARBRE----\n" );
	afficheArbre( parent );	
	printf( "-----FINARBRE----\n" );
	return R;
}