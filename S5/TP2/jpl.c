
#include <stdio.h>
#include <stdlib.h>

//Generatin d'un code à longueur maximale, Attention le registre est modifié au cours de l'éxécution.
void clm(int registre[], int generation[],int nombreRegistres,int nbxor, int longueurSeq, int lm[]){
  int i=1;
  int entree;
  int j;
  lm[0] = registre[nombreRegistres-1];
  //Tant que l'on a pas créé toute la séquence
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

void cjpl(int *registres[],int tRegistres[],int nbCodeursLm,int *generations[],int tGenerations[],int jpl[],int nbPremiers[]){
	int *lms[nbCodeursLm];
	int g;
	int longueurSeq =1;
	//Calcul de la longueur de la sequence (l1*l2*..*lnbCodeursLm+1)
	for(g=0;g<nbCodeursLm;g++){longueurSeq *= nbPremiers[1+g];}
  printf("l = %d\n",longueurSeq);
	//Allocations mémoire
	for (g=0;g<nbCodeursLm;g++){
		lms[g]=malloc(sizeof(int)*longueurSeq);
	}
	int i,j,h;

  //Génération codes lm
	for(j=0;j<nbCodeursLm;j++){
		clm(registres[j],generations[j],tRegistres[j],tGenerations[j],nbPremiers[1+j],lms[j]);
    for(g=0;g<nbPremiers[1+j];g++){
      printf("%d",lms[j][g]);
    }
    printf("\n");
	}

  //Recopie des séquences générées
	for(j=0;j<nbCodeursLm;j++){
		for(h=0;h<longueurSeq;h+=nbPremiers[1+j]){
			for(i=0;i<nbPremiers[1+j];i++){
				lms[j][h+i]=lms[j][i];
        printf("%d",lms[j][h+i]);
			}
		}
    printf("\n");
	}
  //Calcul jpl
  for(j=0;j<longueurSeq;j++){
    jpl[j]=lms[0][j];
    for(i=1;i<nbCodeursLm;i++){
      jpl[j] ^= lms[i][j];
    }
  }
}

int main(int argc, char const *argv[]) {
 	int tableau[100000];
	int nombrePremier[10000];
	int cur1,cur2;
	int element;
	int n=50;
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
	int i;

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
  cjpl(registres,tregistres,3,generations,tgenerations,jpl,nombrePremier);
  return 0;
}
