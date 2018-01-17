#include "Outils.h"

void ScanClav(char  chaine[], int i)
/* Fonction pour recupérer une saisie clavier */
{
  char *p, c;

  if( (chaine = fgets(chaine, i+1, stdin)) != NULL){}; /* recupère la chaine */
  if(strchr(chaine, '\n') == NULL) /* revide le buffer au cas ou il y ait plus de 30 caractères */
  {
         while ((c = getchar()) != '\n' &&  c != EOF){}
  }
  p = strchr(chaine, '\n'); /* cherche le '\n' à la fin */
  if (p) *p = 0; /* enleve le '\n' à la fin */
}


int TailleHadamard(int nbUser)
// Calcul la tailel de la matrice d'Hadamard en fonction du nombre d'utilisateurs
{
  int tailleH = 1;
  while(tailleH < nbUser)
    tailleH *= 2;
  return tailleH;
}

int ** CreationMatrice(int lignes, int colonnes)
{
  int ** matrice;
  int i,j;
  if( (matrice = malloc(lignes * sizeof(int*))) == NULL )
  {
    fprintf(stderr, "Erreur d'allocation de mémoire : Création matrice\npremière dimension");
    exit(0);
  }

  for(i = 0 ; i < lignes; i++)
  {
    if ( (matrice[i] = malloc(colonnes * sizeof(int))) == NULL)
    {
      fprintf(stderr, "Erreur d'allocation de mémoire : Création matrice\ndeuxi�me dimension");
      exit(0);
    }
    for(j = 0 ; j < colonnes ; j++)
      matrice[i][j] = 0;
  }
  //printf("Allocation mémoire ok\n");

  return matrice;
}

void DestructionMatrice(int *** matrice, int lig, int col)
{
  int i;
  for (i = 0 ; i < lig ; i++)
  {
      free((*matrice)[i]);
  }
  free(*matrice);
  *matrice = NULL;
}

void Hadamard(int ** hadamard, int tailleH)
{
  int i, j, k;

  hadamard[0][0] = 1;
  for (k = 1; k < tailleH; k += k)
    for (i = 0; i < k; i++)
      for (j = 0; j < k; j++)
      {
        hadamard[i+k][j]   =  hadamard[i][j];
        hadamard[i][j+k]   =  hadamard[i][j];
        hadamard[i+k][j+k] = -hadamard[i][j];
      }
}


int estDans(int j,int * tab, int nbxor)
{
	int i;
	for(i = 0; i < nbxor; i++)
		if(j == tab[i])
			return 1;

	return 0;
}