#include "CodeLM.h"


void CodeLM(int registre[], int generation[],int tailleRegistre,int nbxor, int longueurSeq, int lm[])
{
  int i=1;
  int entree;
  int j=0;
  lm[0] = registre[tailleRegistre-1];

	while(j = 0; j < nbxor; j++)
		if(generation[j])
				printf("  v");
		else printf("   ");
		printf("\n");
	
  while( i < longueurSeq )
  {

		for(j = 0; j < tailleRegistre; j++)
			printf("%3i",registre[j]);		
		printf("\n");

    entree = registre[generation[0]-1];
    //Calcul de la nouvelle entrée
    for(j = 1 ; j< nbxor ; j++)
      entree ^= registre[generation[j]-1];

    //Décalage à droite sur la taille d'un entier
    for( j = 0 ; j < tailleRegistre ; j++ )
      registre[tailleRegistre-j] = registre[tailleRegistre-j-1];
    //Insertion de la nouvelle entrée dans le décaleur à registre
    registre[0] = entree;
    //Stockage de la valeur i du code LM
    lm[i] = registre[tailleRegistre-1];
    i++;
  }
}