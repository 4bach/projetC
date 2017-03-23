#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Hachage.h"
#include "Chaine.h"
#include "Reseau.h"
#include "entree_sortie.h"



void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax);
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

ArbreQuat* insererNoeudArbre(Noeud* n, ArbreQuat* a, ArbreQuat* parent)
{
	ArbreQuat* a;
	if( !a ) {
		int coteX = parent->coteX/2;
		int coteY = parent->coteY/2;
		int yc, xc;

		//NORD EST
		if( ( n->x > parent->xc ) && ( n->y > parent->yc ) ) {
			yc = parent->yc + (1/2)*(coteY - parent->yc);
			xc = parent->xc + (1/2)*(coteX - parent->xc);
		}
		//SUD EST
		else if ( ( n->x > parent->xc ) && ( n->y < parent->yc ) ) {
			yc = parent->yc - (1/2)*(coteY - parent->yc);
			xc = parent->xc + (1/2)*(coteX - parent->xc);
		}
		//SUD OUEST
		else if ( ( n->x < parent->xc ) && ( n->y < parent->yc ) ) {
			yc = parent->yc - (1/2)*(coteY - parent->yc);
			xc = parent->xc - (1/2)*(coteX - parent->xc);
		}
		//NORD OUEST 
		else if ( ( n->x < parent->xc ) && ( n->y > parent->yc ) ) {
			yc = parent->yc + (1/2)*(coteY - parent->yc);
			xc = parent->xc - (1/2)*(coteX - parent->xc);
		}
		a = creerArbreQuat(xc, yc, coteX, coteY );
		a->noeud = n;
		return a;

	}
	else if( a->noeud ) {
		//REPOSITIONNEMENT DU NOEUD EXISTANT
		//NORD EST
		if( ( a->noeud->x > a->xc ) && ( a->noeud->y > a->yc ) ) {
			a = insererNoeudArbre( a->noeud, a->ne ,a );
		}
		//SUD EST
		else if ( ( a->noeud->x > a->xc ) && ( a->noeud->y < a->yc ) ) {
			a = insererNoeudArbre( a->noeud, a->se ,a );
		}
		//SUD OUEST
		else if ( ( a->noeud->x < a->xc ) && ( a->noeud->y < a->yc ) ) {
			a = insererNoeudArbre( a->noeud, a->so ,a );
		}
		//NORD OUEST 
		else if ( ( a->noeud->x < a->xc ) && ( a->noeud->y > a->yc ) ) {
			a = insererNoeudArbre( a->noeud, a->no ,a );
		}
		//POISIOTNNEMENT DU NOEUD N
		//NORD EST
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
			a = insererNoeudArbre( n, a->no ,a );
		}
	}
	//A PRECISER(CEST JUSTE UNE COPIE DE CELUI DE DESSUS)
	else if( a->noeud && !a ) {
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
			a = insererNoeudArbre( n, a->no ,a );
		}
	}




	return a;
}

Noeud* chercherNoeudArbre(CellPoint* pt, Reseau* R, ArbreQuat** aptr, ArbreQuat* parent)
{
	return NULL;
}

Reseau* recreeReseauArbre(Chaines* C)
{
	return NULL;
}