#include <stdio.h>

void clm(int registre[], int generation[],int nombreRegistres,int nbxor, int longueurSeq, int lm[]){
  int i=1;
  int entree;
  int j;
  lm[0] = registre[nombreRegistres-1];
  while(i<longueurSeq){
    entree=registre[generation[0]-1];
    //Calcul de la nouvelle entrée
    for(j = 1 ; j< nbxor ; j++){
      entree ^= registre[generation[j]-1];
    }
    //Décalage à droite sur la taille d'un entier
    for(j=0;j<nombreRegistres;j++) registre[nombreRegistres-j] = registre[nombreRegistres-j-1];
    //Insertion de la nouvelle entrée dans le décaleur à registre
    registre[0] = entree;
    //Stockage de la valeur i du code LM
    lm[i] = registre[nombreRegistres-1];
    i++;
  }
}


int main(int argc, char const *argv[]) {
  int registre1[5] = {1,1,1,1,1};
  int registre2[5] = {1,1,1,1,1};
  int generation1[2] = {5,2};
  int generation2[4] = {5,4,2,1};
  int longueurSeq = 10;
  int lm[longueurSeq];
  int i;
  clm(registre1,generation1,5,2,longueurSeq,lm);
  for(i=0;i<longueurSeq;i++){
    printf("%d",lm[i]);
  }
  printf("\n");
  /*cgold(registre1,registre2,generation1,2,generation2,4,longueurSeq,lm);
  for(i=0;i<longueurSeq;i++){
    printf("%d",lm[i]);
  }
  printf("\n");*/
  return 0;
}