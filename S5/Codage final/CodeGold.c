#include "CodeGold.h"
#include <stdio.h>
#include <stdlib.h>

void clmg(int registre[], int generation[],int nbxor, int longueurSeq, int lm[]){
  int i=1;
  int entree;
  int j;
  lm[0] = registre[4];
  while(i<longueurSeq){
    entree=registre[generation[0]-1];
    //Calcul de la nouvelle entrée
    for(j = 1 ; j< nbxor ; j++){
      entree ^= registre[generation[j]-1];
    }
    //Décalage à droite sur la taille d'un entier
    for(j=0;j<5;j++) registre[5-j] = registre[5-j-1];
    //Insertion de la nouvelle entrée dans le décaleur à registre
    registre[0] = entree;
    //Stockage de la valeur i du code LM
    lm[i] = registre[4];
    i++;
  }
}


void CodeGold(int registre1[], int registre2[], int generation1[],int nbxor1, int generation2[],int nbxor2, int longueurSeq, int gold[]){
  int CodeLM1[longueurSeq];
  int CodeLM2[longueurSeq];
  //ATTENTION : REGISTRE est MODIFIE à l'execution de CodeLM 
  clmg(registre1,generation1,nbxor1,longueurSeq,CodeLM1);
  clmg(registre2,generation2,nbxor2,longueurSeq,CodeLM2);
  int i = 0;
  while( i < longueurSeq )
  {
    //Calcul de la nouvelle entrée
    gold[i] = CodeLM1[i]^CodeLM2[i];
    i++;
  }
}
