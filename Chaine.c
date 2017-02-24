#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
		fprintf(stderr, "2\n" );

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



void ecrireChaineTxt(Chaines* C,FILE *f1){
	
	CellChaine* courant=C->chaines;
	
	
	char str[10]="";
	fprintf(f1,"NbChain:");
	sprintf(str,"%d",C->nbChaines);
	fprintf(f1,"%s\n",str);
	fprintf(f1,"Gamma:");
	sprintf(str,"%d",C->gamma);
	fprintf(f1,"%s\n\n",str);
	
	
	while(courant){
		sprintf(str,"%d",courant->numero);
		fprintf(f1,"%s ",str);
		while(courant->points){
			sprintf(str,"%.2f ",courant->points->x);
			fprintf(f1,"%s",str);
			sprintf(str,"%.2f ",courant->points->y);
			fprintf(f1,"%s",str);
			courant->points=courant->points->suiv;
		}
		fprintf(f1,"\n");
		courant=courant->suiv;
	}
}

	
	
		
		
		
		
		
		
		

void afficheChaineSVG( Chaines *C, char* nomInstance ) 
{
	if( !C ) {
		printf( "Fichier Vide\n" );
		return;
	}

	int i;
	double x, y;
	fprintf(stderr, "1\n" );
	SVGwriter svg;

	SVGinit( &svg, nomInstance, 100, 100 );

	SVGlineColor( &svg, "Black" );
	fprintf(stderr, "2\n" );
	SVGpointColor( &svg, "Red" );

	CellChaine* tmp_chaine = C->chaines;

	while( tmp_chaine ) {
		fprintf(stderr, "3\n" );
		CellPoint* tmp_point = tmp_chaine->points;
		while( tmp_point->suiv ) {
			fprintf(stderr, "4\n" );
			x = tmp_point->x;
			y = tmp_point->y;
			SVGpoint( &svg, tmp_point->x, tmp_point->y );

			tmp_point = tmp_point->suiv;

			SVGline( &svg, x, y, tmp_point->x, tmp_point->y );
		}
		SVGpoint( &svg, tmp_point->x, tmp_point->y );
		tmp_chaine = tmp_chaine->suiv;
	}
}





