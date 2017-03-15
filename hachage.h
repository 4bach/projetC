#ifndef HACHAGE_H
#define HACHAGE_H
#include "Chaine.h"
#include "Reseau.h"

typedef struct {

	int nE;
	int taille;
	CellNoeud **T;

} TableHachage;

TableHachage* initTableHachage( int m );

int fonctionClef( int x, int y );

int fonctionHachage( int clef, int taille );

Noeud* rechercheCreeNoeudHachage(Reseau *R, TableHachage* H, double x, double y);

Reseau* recreeReseauHachage(Chaines *C);

#endif