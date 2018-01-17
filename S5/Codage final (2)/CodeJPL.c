#include "CodeJPL.h"
#include "CodeLM.h"
#include <stdio.h>
#include <stdlib.h>

void CodeJPL(int *registres[],int tRegistres[],int nbCodeursLm,int *generations[],int tGenerations[],int jpl[],int nbPremiers[])
{
	int *lms[nbCodeursLm];
	int g;
	int longueurSeq = 1;
	//Calcul de la longueur de la sequence (l1*l2*..*lnbCodeursLm+1)
	for(g = 0 ; g < nbCodeursLm ; g++ )
		longueurSeq *= nbPremiers[1+g];
  printf("l = %d\n", longueurSeq);
	//Allocations mémoire
	for ( g = 0 ; g < nbCodeursLm ; g++ )
		lms[g] = malloc(sizeof(int)*longueurSeq);

	int i,j,h;

  //Génération codes lm
	for( j = 0 ; j < nbCodeursLm ; j++)
	{
		CodeLM(registres[j],generations[j],tRegistres[j],tGenerations[j],nbPremiers[1+j],lms[j]);
	}
	printf("\n");
  //Recopie des séquences générées
	for(j = 0 ; j < nbCodeursLm ; j++)
	{
		for( h = 0 ; h < longueurSeq ; h+=nbPremiers[1+j] )
			for( i = 0 ; i < nbPremiers[1+j] ; i++ )
			{
				lms[j][h+i] = lms[j][i];
        printf("%d",lms[j][h+i]);
			}
    printf("  X\n");
	}
  //Calcul jpl
  for(j=0;j<longueurSeq;j++)
	{
    jpl[j]=lms[0][j];
    for(i=1;i<nbCodeursLm;i++)
      jpl[j] ^= lms[i][j];
  }
	
 	printf("\n");
	for(i = 0 ; i < longueurSeq ; i++ )
		{
      printf("%d",jpl[i]);
		}
 printf("\n");
}
