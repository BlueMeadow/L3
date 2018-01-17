#include "CodeJPL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

void TestJPL()
{
 	int tableau[100000]={0};
	int nombrePremier[10000]={0};
	int cur1,cur2;
	int n=50;
	int a=0;

	int temp;

	int registre1[5] = {1,1,0,1,1};
  int registre2[5] = {1,1,1,1,1};
	int registre3[6] = {1,1,1,1,1,1};
  int generation1[2] = {5,2};
  int generation2[4] = {5,4,2,1};
	int generation3[4] = {5,4,2,1};
	int *registres[3] =  {registre1,registre2,registre3};
	int *generations[3] = {generation1,generation2,generation3};
	int tregistres[3] = {5,5,6};
	int tgenerations[3] = {2,4,4};
  int jpl[105];

  printf("\33[H\33[2J"); //Efface la console
  printf("\n====== (4) Test JPL ======\n\n");

	for (cur1=1;cur1<n;cur1++){
		a++;
		tableau[cur1]=a;
	}

	nombrePremier[0]=2;
	for (cur2=0;cur2<n;cur2+=2){
		tableau[cur2]=0;
	}
	nombrePremier[1]=3;
	for (cur2=0;cur2<n;cur2+=3){
		tableau[cur2]=0;
	}

	cur1=4;
	cur2=2;
	while (cur1<n){
		while (tableau[cur1]!=0){
			nombrePremier[cur2]=tableau[cur1];
			cur2++;
			temp=tableau[cur1];
			for (int sup=0;sup<=n;sup+=temp){
				tableau[sup]=0;
			}
		}
		cur1++;
	}

  CodeJPL(registres,tregistres,3,generations,tgenerations,jpl,nombrePremier);
}
