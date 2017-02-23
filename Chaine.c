#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chaine.h"
#include "entree_sortie.h"
#define TMAX 50

CellPoint* creerCellPoint( int x, int y ) 
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
	CellPoint* tmp;
	while( cpts ) {
		detruireListeCellChaine( cpts->chaines );
		free( cpts );
	}
}


Chaines* lectureChaine(FILE *f)
{

		int nbchain,gma,nbpts;
		double x, y;
		int numero;
		CellChaine* clchaine=NULL;
		//CellPoint* clpoint=NULL;

		char tempo[TMAX];

		
		if( f == NULL ) {
			printf("Erreur lors de l'ouverture du fichier.\n");
			return NULL;
		}

		GetChaine( f, TMAX, tempo );
		Skip( f );
		nbchain = GetEntier( f );
		
		GetChaine( f, TMAX, tempo );
		Skip( f );
		gma = GetEntier( f );

		Chaines* chaines = creerChaines( gma, nbchain );

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
		return chaines;
}
