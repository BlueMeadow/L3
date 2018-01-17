#include <stdio.h>

void CodeLM(int registre[], int generation[],int nbxor, int longueurSeq, int lm[]){
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
  int lm1[longueurSeq];
  int lm2[longueurSeq];
  //ATTENTION !!!!!!!! REGISTRE est MODIFIE à l'execution de CodeLM !!!!!!!!!!
  CodeLM(registre1,generation1,nbxor1,longueurSeq,lm1);
  CodeLM(registre2,generation2,nbxor2,longueurSeq,lm2);
  int i =0;
  while(i<longueurSeq){
    //Calcul de la nouvelle entrée
    gold[i] = lm1[i]^lm2[i];
    i++;
  }
}

int main(int argc, char const *argv[]) {
  int registre1[5] = {1,1,1,1,1};
  int registre2[5] = {1,1,1,1,1};
  int generation1[2] = {5,2};
  int generation2[4] = {5,4,2,1};
  int longueurSeq = 10;
  int gold[longueurSeq];
  int i;
  CodeGold(registre1,registre2,generation1,2,generation2,4,longueurSeq,gold);
  for(i=0;i<longueurSeq;i++){
    printf("%d",gold[i]);
  }
  printf("\n");
  return 0;
}
