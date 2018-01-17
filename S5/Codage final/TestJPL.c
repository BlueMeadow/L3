#include "CodeJPL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

void TestJPL()
{
 	int tableau[100000] = {0};
	int nombrePremier[10000] = {0};
	int i,j;
	int n=50;
	int a=0;
  int temp;

  int registre1[5] = {1,1,1,1,1};
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

	for (i = 1 ; i < n ; i++)
  {
		a++;
		tableau[i]=a;
	}

	nombrePremier[0] = 2;

	for ( j = 0; j < n ; j += 2)
		tableau[j]=0;

	nombrePremier[1]=3;

	for (j=0;j<n;j+=3)
		tableau[j]=0;

	i = 4;
	j = 2;
  
	while (i<n)
  {
		while (tableau[i]!=0)
    {
			nombrePremier[j]=tableau[i];
			j++;
			temp=tableau[i];
			for (int sup=0;sup<=n;sup+=temp){
				tableau[sup]=0;
			}
		}
		i++;
	}

  CodeJPL(registres,tregistres,3,generations,tgenerations,jpl,nombrePremier);
}
