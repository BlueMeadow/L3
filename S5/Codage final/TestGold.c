#include "CodeGold.h"
#include <stdio.h>
#include <stdlib.h>

void TestGold() {
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
}