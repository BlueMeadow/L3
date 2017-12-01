
#include <stdio.h>

void nombresPremiers( int nNombrePremiers){
	int tableau[100000];
	int cur1,cur2;
	int element;
	int n=nNombrePremiers;
	int a=0;
	for (cur1=0;cur1<10000;cur1++){
		nombrePremier[cur1]=0;	
		tableau[cur1]=0;
	}

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
	int temp;
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
}

int main(int argc, char const *argv[]) {
  int nombrepremiers[50];
  nombresPremiers(nombrepremiers,50);
  int i;
  printf("%i",nombrepremiers[0]);
  
  return 0;
}