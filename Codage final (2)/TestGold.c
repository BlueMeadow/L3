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
  printf("\33[H\33[2J"); //Efface la console
  printf("\n====== (3) Test Gold ======\n\n");
  CodeGold(registre1,registre2,5,5,generation1,2,generation2,4,longueurSeq,gold);
  printf("\n");
}