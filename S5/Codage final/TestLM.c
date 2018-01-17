#include "CodeLM.h"
#include "TestLM.h"
#include <stdio.h>
#include <stdlib.h>

int TestLM()
{
  int registre1[5] = {1,1,1,1,1};
  int generation1[2] = {5,2};
  int longueurSeq = 10;
  int lm[longueurSeq];
  int i;
  printf("\33[H\33[2J"); //Efface la console
  printf("\n====== (2) Test LM ======\n\n");
  CodeLM(registre1,generation1,5,2,longueurSeq,lm);
  for(i=0;i<longueurSeq;i++)
    printf("%d",lm[i]);

  printf("\n");
  return 0;
}
