#ifndef __RESEAU_H__
#define __RESEAU_H__

#include "Chaine.h"

typedef struct noeud Noeud;

/* Liste chainee de noeuds (pour la liste des noeuds du reseau ET les listes des voisins de chaque noeud) */
typedef struct cellnoeud {
    Noeud *nd;               /* Pointeur vers le noeud stock\'e */
    struct cellnoeud *suiv;         /* Cellule suivante dans la liste */
} CellNoeud;

/* Noeud du reseau */
struct noeud{
   int num;                        /* Numero du noeud */
   double x, y;                    /* Coordonnees du noeud*/
   CellNoeud *voisins;             /* Liste des voisins du noeud */
};

/* Liste chainee de commodites */
typedef struct cellCommodite {
    Noeud *extrA, *extrB;       /* Noeuds aux extremites de la commodite */
    struct cellCommodite *suiv;     /* Cellule suivante dans la liste */
} CellCommodite;

/* Un reseau */
typedef struct {
    int nbNoeuds;                   /* Nombre de noeuds du reseau */
    int gamma;                   /* Nombre maximal de fibres par cable */
    CellNoeud *noeuds;              /* Liste des noeuds du reseau */
    CellCommodite *commodites;      /* Liste des commodites a relier */
} Reseau;

/*Une Liaison*/
typedef struct liaison{
	int num1;
	double x1;
	double y1;
	int num2;
	double x2;
	double y2;
	struct liaison* suiv;
	
}Liaison;

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);
Reseau* reconstitueReseauListe(Chaines *C);
void ecrireReseauTxt(Reseau *R, FILE *f);
int nbLiaison(Reseau *R);
int nbCommodite(Reseau *R);
void afficheReseauSVG(Reseau *R, char* nomInstance);
Noeud* creerNoeud( Reseau* R,double x,double y );
Noeud* construitNoeud( double x, double y, int num );
CellNoeud* creerCellNoeud( Noeud* nv );
Reseau* intialiseReseau() ;
int comptenoeud(Reseau *R);
void afficheReseauSVG(Reseau *R, char* nomInstance);
void afficheReseau( Reseau* R );
int RechercheLiaison(Liaison* L,int n1, int n2);
Liaison* creerLiaison(int n1,double x1,double y1, int n2,double x2,double y2);
Liaison* creerListeLiaison(Reseau*R);
void min_max_r(Reseau* R,double* minx,double* miny,double* maxx,double* maxy);
void DetruireLiaison(Liaison*L);
#endif

