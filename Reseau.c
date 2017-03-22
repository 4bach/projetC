#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entree_sortie.h"
#include "Reseau.h"
#include "Chaine.h"
#include "SVGwriter.h"



Reseau* intialiseReseau(void) 
{
	Reseau* R=(Reseau*)malloc(sizeof(Reseau));
	R->nbNoeuds=0;
	R->gamma=0;
	R->noeuds=NULL;
	R->commodites=NULL;
	return R;
}

Noeud* construitNoeud( double x, double y, int num ) {
	Noeud* nv=(Noeud*)malloc(sizeof(Noeud));
	if(nv==NULL){
		printf("Erreur d'allocation de noeud\n");
		return NULL;
	}
	nv->num = num;
	nv->x=x;
	nv->y=y;
	nv->voisins=NULL;
	return nv;
}
//IL SEMBLE QUE TOUT LES NOEUDS NE SONT PAS CREE
Noeud* creerNoeud( Reseau* R,double x,double y )
{
	if (R==NULL){
		return NULL;
	}

	Noeud* nv = construitNoeud( x, y, R->nbNoeuds+1 );

	R->nbNoeuds++;
	return nv;
}


CellNoeud* creerCellNoeud( Noeud* nv ) 
{
	CellNoeud* Cl=(CellNoeud*)malloc(sizeof(CellNoeud));
	if(Cl==NULL){
		printf("Erreur d'allocation de Cellnoeud\n");
		return NULL;
	}
	Cl->nd=nv;
	Cl->suiv = NULL;
	return Cl;
}





 Noeud* rechercheCreeNoeudListe(Reseau* R,double x,double y){
 	if(R==NULL){
 		printf("Reseau NULL\n");
 		return NULL;
 	}
 	CellNoeud* courantcl=R->noeuds;
 	while(courantcl){
 		if(courantcl->nd->x==x && courantcl->nd->y==y){
				return courantcl->nd;
 		}
 		courantcl=courantcl->suiv;
 	}
 	Noeud* nv = creerNoeud( R, x, y );
	CellNoeud* Cl = creerCellNoeud( nv );
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
		courantco->suiv=R->commodites;
		R->commodites=courantco;
		courant=courant->suiv;
	}
			
	return R;
}

int nbCommodite(Reseau *R){
	CellCommodite* courant=R->commodites;
	int cpt=0;
	while(courant){
		cpt++;
		courant=courant->suiv;
	}
	return cpt;
}

int nbLiaison(Reseau* R){
	
	int cpt=0;
	CellNoeud* clcourant=R->noeuds;
	CellNoeud* courantbis=NULL;
	while(clcourant){
		courantbis=clcourant->nd->voisins;
		while(courantbis){
			cpt++;
			courantbis=courantbis->suiv;
		}
		clcourant=clcourant->suiv;
	}
	return cpt/2;
}
int comptenoeud(Reseau *R){
	CellNoeud* courant=R->noeuds;
	int cpt=0;
	while(courant){
		cpt++;
		courant=courant->suiv;
	}
	return cpt;
}


void ecrireReseauTxt(Reseau* R,FILE* f1 ){
	CellCommodite* comcourant=R->commodites;
	CellNoeud* ndcourant=R->noeuds;
	int cpt;
	char str[10]="";
	fprintf(f1,"NbNoeuds: ");
	cpt=comptenoeud(R);
	sprintf(str,"%d",cpt);
	fprintf(f1,"%s\n",str);
	
	fprintf(f1,"NbLiaison: ");
	cpt=nbLiaison(R);
	sprintf(str,"%d",cpt);
	fprintf(f1,"%s\n",str);
	
	fprintf(f1,"NbCommodite: ");
	cpt=nbCommodite(R);
	sprintf(str,"%d",cpt);
	fprintf(f1,"%s\n",str);
	
	fprintf(f1,"Gamma: ");
	sprintf(str,"%d",R->gamma);
	fprintf(f1,"%s\n\n",str);
	
	while(ndcourant){
		
		fprintf(f1,"v ");
		sprintf(str,"%d",ndcourant->nd->num);
		fprintf(f1,"%s ",str);
		
		sprintf(str,"%f",ndcourant->nd->x);
		fprintf(f1,"%s ",str);
		
		sprintf(str,"%f",ndcourant->nd->y);
		fprintf(f1,"%s\n",str);
		
		ndcourant=ndcourant->suiv;
		
	}
	fprintf(f1,"\n");
	
	while(comcourant){
		
		fprintf(f1,"k ");
		
		sprintf(str,"%d",comcourant->extrA->num);
		fprintf(f1,"%s ",str);
		
		sprintf(str,"%d",comcourant->extrB->num);
		fprintf(f1,"%s\n",str);
		
		comcourant=comcourant->suiv;
	}
	
}
	
void afficheReseauSVG(Reseau *R, char* nomInstance) 
{
	if( !R ) {
		printf( "Fichier Vide\n" );
		return;
	}

	double x, y;
	SVGwriter svg;
	double minx=0;
	double miny=0;
	double maxx=100;
	double maxy=100;
	//min_max_r( R, &minx, &miny, &maxx, &maxy );
	SVGinit( &svg, nomInstance, maxx-minx, maxy-miny );

	SVGlineColor( &svg, "Black" );
	
	SVGpointColor( &svg, "Red" );

	CellNoeud* tmp_noeud = R->noeuds;
	CellCommodite * tmp_commo = R->commodites;
	Noeud* a;
	Noeud* b;


	while( tmp_noeud ) {

		x = tmp_noeud->nd->x - minx;
		y = tmp_noeud->nd->y - miny;
		printf("noeud : X: %f  Y:%f\n",x,y);
		SVGpoint( &svg, x, y );

		tmp_noeud = tmp_noeud->suiv;

	}

	while( tmp_commo ) {

		a = tmp_commo->extrA;
		b = tmp_commo->extrB;
		SVGline( &svg, a->x- minx, a->y- miny, b->x- minx, b->y- miny);
		printf("coomodit : X: %f  Y:%f\n", a->x, a->y);
		tmp_commo = tmp_commo->suiv;
	}

}
	
void min_max_r(Reseau *R,double* minx,double* miny,double* maxx,double* maxy)
{
	CellNoeud* courant=R->noeuds;
	*minx=100;
	*miny=100;
	*maxx=0;
	*maxy=0;
	while(courant->nd){
		
		if(courant->nd->x < *minx)
			*minx=courant->nd->x;
		if(courant->nd->y < *miny)
			*miny=courant->nd->y;
		if(courant->nd->x > *maxx)
			*maxx=courant->nd->x;
		if(courant->nd->y > *maxy)
			*maxy=courant->nd->y;
	
		courant=courant->suiv;
	}
}	
	
	
	

	
