#include "Outils.h"
#include "RecepteurH.h"

void Recepteur(int ** messageRecu, int * sortie, int * taille, int ** hadamard, int nbUser, int tailleMax, int tailleH)
{  
  int i, j, k;
  for( i = 0 ; i < nbUser ; i++)
  {
    for(j = 0 ; j < tailleMax ; j++)
    {
      for(k = 0 ; k < tailleH ; k++)
      {
        messageRecu[i][j] += sortie[k+tailleH*j]*hadamard[i][k];
      }
      messageRecu[i][j] /= tailleH;
      messageRecu[i][j] = (messageRecu[i][j] == -1 ? 0 : 1);
    }
  }
}
