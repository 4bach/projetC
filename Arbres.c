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
	*miny=0;
	*maxx=0;
	*maxy=100;

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
	if( ( x >= a->xc ) && ( y >= a->yc ) ) {
		arbre =  a->ne;
	}
		//SUD EST
	else if ( ( x >= a->xc ) && ( y <= a->yc ) ) {
		arbre = a->se;
	}
		//SUD OUEST
	else if ( ( x <= a->xc ) && ( y <= a->yc ) ) {
		arbre = a->so;
	}
		//NORD OUEST 
	else if ( ( x <= a->xc ) && ( y >= a->yc ) ) {
		arbre = a->no;
	}
	return arbre;
}

ArbreQuat* insererNoeudArbre(Noeud* n, ArbreQuat* a, ArbreQuat* parent)
{
	if( !a ) {
		double xc, yc;
		double coteXnew = parent->coteX/2;
		double coteYnew = parent->coteY/2;

		if( ( n->x >= parent->xc ) && ( n->y >= parent->yc ) ) {
			printf( "test 1 vrai\n" );
			yc = parent->yc + (1./2.)*(parent->coteY - parent->yc);
			xc = parent->xc + (1./2.)*(parent->coteX - parent->xc);
		}

			//SUD EST
		else if ( ( n->x >= parent->xc ) && ( n->y <= parent->yc ) ) {
			printf( "test 2 vrai\n" );
			yc = parent->yc - (1./2.)*(parent->coteY - parent->yc);
			xc = parent->xc + (1./2.)*(parent->coteX - parent->xc);
		
		}
		//SUD OUEST
		else if ( ( n->x <= parent->xc ) && ( n->y <= parent->yc ) ) {
			printf( "test 3 vrai\n" );
			yc = parent->yc - (1./2.)*(parent->coteY - parent->yc);
			xc = parent->xc - (1./2.)*(parent->coteX - parent->xc);
		
		}
		//NORD OUEST 
		else if ( ( n->x <= parent->xc ) && ( n->y >= parent->yc ) ) {
			printf( "test 4 vrai\n" );
			yc = parent->yc + (1./2.)*(parent->coteY - parent->yc);
			xc = parent->xc - (1./2.)*(parent->coteX - parent->xc);
			printf( "test4 XC = %f, YC =%f \n", xc, yc );
				
		}
		a = creerArbreQuat( xc, yc, coteXnew, coteYnew );
		a->noeud = n;

		return a;
	}
	else if( a->noeud ) {
		
		Noeud* n_tmp = a->noeud;
		a->noeud = NULL;
		if( ( n_tmp->x >= a->xc ) && ( n_tmp->y >= a->yc ) ) {
			a->ne = insererNoeudArbre( n_tmp, a->ne ,a );

		}
		//SUD EST
		else if ( ( n_tmp->x >= a->xc ) && ( n_tmp->y <= a->yc ) ) {
			a->se = insererNoeudArbre( n_tmp, a->se ,a );

		}
		//SUD OUEST
		else if ( ( n_tmp->x <= a->xc ) && ( n_tmp->y <= a->yc ) ) {
			a->so = insererNoeudArbre( n_tmp, a->so ,a );

		}
		//NORD OUEST 
		else if ( ( n_tmp->x <= a->xc ) && ( n_tmp->y >= a->yc ) ) {
			a->no = insererNoeudArbre( n_tmp, a->no, a );

		}
		if( ( n->x >= a->xc ) && ( n->y >= a->yc ) ) {
			a->ne = insererNoeudArbre( n, a->ne ,a );

		}
		//SUD EST
		else if ( ( n->x >= a->xc ) && ( n->y <= a->yc ) ) {
			a->se = insererNoeudArbre( n, a->se ,a );

		}
		//SUD OUEST
		else if ( ( n->x <= a->xc ) && ( n->y <= a->yc ) ) {
			a->so = insererNoeudArbre( n, a->so ,a );

		}
		//NORD OUEST 
		else if ( ( n->x <= a->xc ) && ( n->y >= a->yc ) ) {
			a->no = insererNoeudArbre( n, a->no, a );

		}
		return a;

	}

	if( ( n->x >= a->xc ) && ( n->y >= a->yc ) ) {
		a->ne = insererNoeudArbre( n, a->ne ,a );

	}
	//SUD EST
	else if ( ( n->x >= a->xc ) && ( n->y <= a->yc ) ) {
		a->se = insererNoeudArbre( n, a->se ,a );

	}
	//SUD OUEST
	else if ( ( n->x <= a->xc ) && ( n->y <= a->yc ) ) {
		a->so = insererNoeudArbre( n, a->so ,a );

	}
	//NORD OUEST 
	else if ( ( n->x <= a->xc ) && ( n->y >= a->yc ) ) {
		a->no = insererNoeudArbre( n, a->no, a );

	}
	return a;
	

}

Noeud* chercherNoeudArbre(CellPoint* pt, Reseau* R, ArbreQuat** aptr, ArbreQuat* parent)
{
	Noeud* n;
	ArbreQuat* tmp_aptr = *aptr;
	ArbreQuat* tmp;
	if( *aptr == NULL ) {
		printf( "*aptr == NULL\n" );
		n = creerNoeud( R, pt->x, pt->y );

		*aptr = insererNoeudArbre( n, *aptr, parent );
		

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
		printf( "(*aptr)->noeud != NULL\n" );
		n = creerNoeud( R, pt->x, pt->y );
		(*aptr) = insererNoeudArbre( n, *aptr, parent );

		CellNoeud* Cl = creerCellNoeud( n );
		Cl->suiv=R->noeuds;
		R->noeuds=Cl;

		return n;
	}
	else if ( !(*aptr)->noeud && (*aptr) ){
		
		if( ( pt->x >= (*aptr)->xc ) && ( pt->y >= (*aptr)->yc ) ) {

			n = chercherNoeudArbre( pt, R, &(*aptr)->ne, (*aptr));
		}
		//SUD EST
		else if ( ( pt->x >= (*aptr)->xc ) && ( pt->y <= (*aptr)->yc ) ) {

			n = chercherNoeudArbre( pt, R, &(*aptr)->se, *aptr);
		}
		//SUD OUEST
		else if ( ( pt->x <= (*aptr)->xc ) && ( pt->y <= (*aptr)->yc ) ) {

			n = chercherNoeudArbre( pt, R, &(*aptr)->so, (*aptr) );
		}
		//NORD OUEST 
		else if ( ( pt->x <= (*aptr)->xc ) && ( pt->y >= (*aptr)->yc ) ) {

			n = chercherNoeudArbre( pt, R, &(*aptr)->no, (*aptr) );
		}
	}
	*aptr = tmp_aptr;
	return n;
}

Reseau* recreeReseauArbre(Chaines* C)
{

	double minx, miny, maxx, maxy;
	chaineCoordMinMax( C, &minx, &miny, &maxx, &maxy );
	//double coteX = maxx - minx;
	//double coteY = maxy - miny;
	double coteX = 100;
	double coteY = 100;
	//printf( "maxx = %f, minx = %f, miny = %f, maxy = %f", maxx, minx, miny, minx );
	//return NULL;
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

			if( (cpoint->x>=parent->xc ) && (cpoint->y>=parent->yc ) ) {
				enfant = parent->ne;
			}
				//SUD EST
			else if ( (cpoint->x>=parent->xc ) && (cpoint->y<=parent->yc ) ) {
				enfant =parent->se;
			}
				//SUD OUEST
			else if ( (cpoint->x<=parent->xc ) && (cpoint->y<=parent->yc ) ) {
				enfant =parent->so;
			}
				//NORD OUEST 
			else if ( (cpoint->x<=parent->xc ) && (cpoint->y>=parent->yc ) ) {
				enfant =parent->no;
			}
			if(bool==0){
				
				if( enfant == NULL ) printf( "enfant 1null\n" );
				noeudCourant = chercherNoeudArbre( cpoint, R, &enfant, parent);
				enfant = NULL;
				//if( enfant == NULL ) printf( "enfant 2null\n" );
				if( noeudCourant == NULL ) printf("noeud null\n");
				else printf( "%f %f\n",noeudCourant->x, noeudCourant->y );

				courantco->extrA=noeudCourant;
				bool++;

			}
			else{
		
				if( enfant == NULL ) printf( "enfant 1null\n" );
				noeudCourant = chercherNoeudArbre( cpoint, R, &enfant, parent);
				enfant = NULL;
				//if( enfant == NULL ) printf( "enfant 2null\n" );
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














