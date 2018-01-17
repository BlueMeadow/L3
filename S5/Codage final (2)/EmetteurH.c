#include "Outils.h"
#include "EmetteurH.h"

void Emetteur ( int * sortie, int ** message, int ** hadamard, int nbUser, int * taille, int tailleMax)
{
    int i, j, k;
    int tailleH = TailleHadamard(nbUser);

    int ** prelim = CreationMatrice(nbUser, tailleH*tailleMax);

		//codage des messages
    for(i = 0 ; i < nbUser ; i++)
    {
      for(j = 0 ; j < taille[i] ; j++)
      {
        for(k = 0 ; k < tailleH ; k ++)
        {
          if(message[i][j] == 1)
          {
            prelim[i][(j*tailleH)+k] = hadamard[i][k];
          }
          else  if(message[i][j] == 0)
          {
            prelim[i][(j*tailleH)+k] = -hadamard[i][k];
          }
        }
      }
    }

   printf("\n=================================\n|        MESSAGES CODES         |\n=================================\n");
   for( i = 0 ; i < nbUser ; i++)
   { 
		 printf("Message de l'utilisateur %3i:\t", i+1);
     for(j = 0 ; j < (tailleMax * tailleH) ; j++)
     {
         printf("%3i", prelim[i][j]);
     }
     printf("\n");
   }
		
		//somme des messages
    for( i = 0 ; i < (tailleH * tailleMax) ; i++)
        for(j = 0 ; j < nbUser ; j++)
				{
            sortie[i] += prelim[j][i];
				}

    DestructionMatrice(&prelim, nbUser, tailleH*tailleMax);
}
