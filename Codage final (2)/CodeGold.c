#include "CodeGold.h"
#include <stdio.h>
#include <stdlib.h>
#include "CodeLM.h"


void CodeGold(int registre1[], int registre2[], int tailleR1, int tailleR2, int generation1[],int nbxor1, int generation2[],int nbxor2, int longueurSeq, int gold[]){
	int CodeLM1[longueurSeq];
  int CodeLM2[longueurSeq];
  //ATTENTION : REGISTRE est MODIFIE à l'execution de CodeLM 
  CodeLM(registre1,generation1,tailleR1,nbxor1,longueurSeq,CodeLM1);
  CodeLM(registre2,generation2,tailleR1,nbxor2,longueurSeq,CodeLM2);
  int i = 0;  
	int j;	


  while( i < longueurSeq )
  {
    //Calcul de la nouvelle entrée
    gold[i] = CodeLM1[i]^CodeLM2[i];
    i++;
  }
	
	printf("\n");
	printf("  X  X\n");	
	for(j = 0; j < longueurSeq; j++)
			printf("%3i%3i  =%3i\n",CodeLM1[j],CodeLM2[j], gold[j]);		
	printf("\n");
}
