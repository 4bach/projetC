#ifndef __CHAINE_H__
#define __CHAINE_H__	
#include<stdio.h>

/* Liste chainee de points */
typedef struct cellPoint{
  double x,y;                   /* Coordonnees du point */
  struct cellPoint *suiv;       /* Cellule suivante dans la liste */
} CellPoint;

/* Celllule d une liste (chainee) de chaines */
typedef struct cellChaine{
  int numero;                   /* Numero de la chaine */
  CellPoint *points;            /* Liste des points de la chaine */
  struct cellChaine *suiv;      /* Cellule suivante dans la liste */
} CellChaine;

/* L'ensemble des chaines */
typedef struct {
  int gamma;                    /* Nombre maximal de fibres par cable */
  int nbChaines;                /* Nombre de chaines */
  CellChaine *chaines;          /* La liste chainee des chaines */
} Chaines;

void lectureChaine(FILE *f , Chaines* chaines);
void ecrireChaineTxt(Chaines *C, FILE *f);
void afficheChaineSVG(Chaines *C, char* nomInstance);
double longueurTotale(Chaines *C);
int comptePointsTotal(Chaines *C);
CellPoint *creerCellPoint( double x, double y );
CellChaine *creerCellChaine( int numero );
Chaines* creerChaines( int gamma, int NbChaines );
void detruireListeCellPoint( CellPoint* cpts );
void detruireListeCellChaine( CellChaine* cpts );
void detruireChaines( Chaines* cpts );
void afficheChaineSVG( Chaines *C, char* nomInstance ) ;

#endif	
