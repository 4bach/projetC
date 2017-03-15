#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hachage.h"

int main(int argc,char* *argv)
{

	int i, j;
	int clef = 0;
	int position = 0;
	int taille = 10;
	for ( taille = 7; taille < 20; taille++ ) {
		printf( "TAILLE = %d\n", taille );
		for( i = 0; i < 10; i++ ){
			for( i = 0; i < 10; i++ ){
				clef = fonctionClef( i, j );
				position = fonctionHachage( clef, taille );
				printf( "clef = %d, position = %d\n", clef, position );
			}
		}
	}


	return 0;

}