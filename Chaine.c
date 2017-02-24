#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Chaine.h"
#include "entree_sortie.h"
#include "SVGwriter.h"

#define TMAX 50

CellPoint* creerCellPoint( double x, double y ) 
{
	CellPoint* cpts = ( CellPoint* )malloc( sizeof( CellPoint ) );
	if( !cpts ) {
		printf( "Erreur lors de l'allocation du malloc pour le CellPoint" );
		return NULL;
	}
	cpts->x = x;
	cpts->y = y;
	cpts->suiv = NULL;

	return cpts;
}

CellChaine* creerCellChaine( int numero ) 
{
	CellChaine* cpts = ( CellChaine* )malloc( sizeof( CellChaine ) );
	if( !cpts ) {
		printf( "Erreur lors de l'allocation du malloc pour le CellChaine" );
		return NULL;
	}
	cpts->numero = numero;
	cpts->suiv = NULL;
	cpts->points = NULL;

	return cpts;
}

Chaines* creerChaines( int gamma, int nbChaines ) 
{
	Chaines* cpts = ( Chaines* )malloc( sizeof( Chaines ) );
	if( !cpts ) {
		printf( "Erreur lors de l'allocation du malloc pour les Chaines" );
		return NULL;
	}
	cpts->gamma = gamma;
	cpts->nbChaines = nbChaines;
	cpts->chaines = NULL;

	return cpts;
}

void detruireListeCellPoint( CellPoint* cpts )
{
	if( !cpts ) return;
	CellPoint* tmp;
	while( cpts ) {
		tmp = cpts->suiv;
		free( cpts );
		cpts = tmp;
	}
}

void detruireListeCellChaine( CellChaine* cpts )
{
	if( !cpts ) return;
	CellChaine* tmp;
	while( cpts ) {
		tmp = cpts->suiv;
		detruireListeCellPoint( cpts->points );
		free( cpts );
		cpts = tmp;
	}
}

void detruireChaines( Chaines* cpts )
{
	if( !cpts ) return;
	//CellPoint* tmp;
	while( cpts ) {
		detruireListeCellChaine( cpts->chaines );
		free( cpts );
	}
}


void lectureChaine( FILE *f , Chaines* chaines )
{

		int nbchain,gma,nbpts;
		double x, y;
		int numero;
		//CellChaine* clchaine=NULL;
		//CellPoint* clpoint=NULL;
		fprintf(stderr, "1\n" );
		char tempo[TMAX];

		
		if( f == NULL ) {
			printf("Erreur lors de l'ouverture du fichier.\n");
			return;
		}
	
		GetChaine( f, TMAX, tempo );
		Skip( f );
		nbchain = GetEntier( f );
		
		GetChaine( f, TMAX, tempo );
		Skip( f );
		gma = GetEntier( f );

		chaines->gamma = gma;
		chaines->nbChaines = nbchain;
		chaines->chaines = NULL;

		SkipLine( f );
		
		int i,j;
		
		for( i = 0; i < chaines->nbChaines; i++ ) {

			numero = GetEntier( f );
			Skip( f );
			nbpts = GetEntier( f );
			Skip( f );

			CellChaine* cellchaine = creerCellChaine( numero );
			cellchaine->suiv = chaines->chaines;
			chaines->chaines = cellchaine;

			for( j = 0; j < nbpts; j++ ){

				x = GetReel( f );
				Skip( f );
				y = GetReel( f );
				Skip( f );
				
				CellPoint* cellpoint = creerCellPoint( x, y );
				cellpoint->suiv = cellchaine->points;
				cellchaine->points = cellpoint;
			}
		}	
}
int comptepoints(CellChaine* C){
	int cpt=0;
	if(C==NULL){
		return 0;
	}
	CellPoint* cpoint=C->points;
	
	while(cpoint){
		cpt++;
		cpoint=cpoint->suiv;
	}
	return cpt;
}


void ecrireChaineTxt(Chaines* C,FILE *f1){
	
	CellChaine* courant=C->chaines;
	CellPoint* cpoint=NULL;
	int cpt;
	char str[10]="";
	fprintf(f1,"NbChain: ");
	sprintf(str,"%d",C->nbChaines);
	fprintf(f1,"%s\n",str);
	fprintf(f1,"Gamma: ");
	sprintf(str,"%d",C->gamma);
	fprintf(f1,"%s\n\n",str);
	
	
	while(courant){
		sprintf(str,"%d",courant->numero);
		fprintf(f1,"%s ",str);
		cpoint=courant->points;
		cpt=comptepoints(courant);
		sprintf(str,"%d",cpt);
		fprintf(f1,"%s ",str);
		while(cpoint){
			sprintf(str,"%.2f ",cpoint->x);
			fprintf(f1,"%s",str);
			sprintf(str,"%.2f ",cpoint->y);
			fprintf(f1,"%s",str);
			cpoint=cpoint->suiv;
		}
		fprintf(f1,"\n");
		courant=courant->suiv;
	}
}

	
	
void min_max(Chaines* C,double* minx,double* miny,double* maxx,double* maxy){
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
	
	
	
	

		
		
		
		
		
		

void afficheChaineSVG( Chaines *C, char* nomInstance ) 
{
	if( !C ) {
		printf( "Fichier Vide\n" );
		return;
	}

	double x, y;
	double minx,miny,maxx,maxy;
	SVGwriter svg;
	min_max(C,&minx,&miny,&maxx,&maxy);
	SVGinit( &svg, nomInstance, maxx-minx, maxy-miny );

	SVGlineColor( &svg, "Black" );
	
	SVGpointColor( &svg, "Red" );

	CellChaine* tmp_chaine = C->chaines;

	while( tmp_chaine ) {
	
		CellPoint* tmp_point = tmp_chaine->points;
		while( tmp_point->suiv ) {
			
			x = tmp_point->x - minx;
			y = tmp_point->y - miny;
			SVGpoint( &svg, x, y );

			tmp_point = tmp_point->suiv;

			SVGline( &svg, x, y, tmp_point->x - minx, tmp_point->y - miny);
		}
		SVGpoint( &svg, tmp_point->x - minx , tmp_point->y -miny );
		tmp_chaine = tmp_chaine->suiv;
	}
}

double longueurChaine(CellChaine* C){
	
	CellPoint* cpoint=C->points;
	
	double longueurtot=0;
	double x,y;
	while(cpoint->suiv){
		x=pow(cpoint->x-cpoint->suiv->x,2);
		y=pow(cpoint->y-cpoint->suiv->y,2);
		longueurtot+=sqrt(x+y);
		cpoint=cpoint->suiv;
	}
	return longueurtot;
}

double longueurTotale(Chaines* C){
	
	double longueurtot=0;
	CellChaine* courant=C->chaines;
	double longchaine;
	while(courant){
		longchaine=longueurChaine(courant);
		longueurtot+=longchaine;
		courant=courant->suiv;
	}
	return longueurtot;
}
		

int comptePointsTotal(Chaines* C){
	
	
	int cpttot=0;
	int cptchaine;
	CellChaine* courant=C->chaines;
	
	while(courant){
		cptchaine=comptepoints(C);
		cpttot+=cptchaine;
		courant=courant->suiv;
		
	}
	return cpttot;
	
}	
	
		
		
		
	
	
	
	





