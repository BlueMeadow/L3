
#include <math.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
  int registre[5] = {1,1,1,1,1};
  int generation[2] = {5,2};
  int longueurSeq = 10;
  int lm[longueurSeq];
  lm[0] = registre[4];
  //int nblongueurMax = pow(2,5)-1;
  int i=1;
  int entree=0;
  int j;
  while(i<longueurSeq){
    //Calcul de la nouvelle entrée
    entree = registre[generation[0]-1]^registre[generation[1]-1];
    //Décalage à droite sur la taille d'un entier
    for(j=0;j<5;j++) registre[5-j] = registre[5-j-1];
    //Insertion de la nouvelle entrée dans le décaleur à registre
    registre[0] = entree;
    //Stockage de la valeur i du code LM
    lm[i] = registre[4];
    i++;
  }
  for(i=0;i<longueurSeq;i++){
    printf("%d",lm[i]);
  }
  printf("\n");
  return 0;
}
