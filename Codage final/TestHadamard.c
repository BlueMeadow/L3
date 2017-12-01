#include "TestHadamard.h"


int TestHadamard()
{
  int ** hadamard;
  int ** message;
  int ** messageRecu;
  int * sortie;
  int * taille;
  int nbUser, i, j;
  int tailleH, tailleMax;
  char messageStr[TAILLE_MESSAGE];

  printf("\33[H\33[2J"); //Efface la console
  printf("\n====== (1) Test Hadamard ======\n\n");
  printf("Entrez le nombre d'utilisateurs\n>>");
  ScanClav(messageStr, TAILLE_MESSAGE);
  nbUser = atoi(messageStr);
  message = CreationMatrice(nbUser, TAILLE_MESSAGE);
  messageRecu = CreationMatrice(nbUser, TAILLE_MESSAGE);
  tailleH = TailleHadamard(nbUser);
  hadamard = CreationMatrice(tailleH, tailleH);
  Hadamard(hadamard, tailleH);
	taille = malloc(sizeof(int) * nbUser);

  for( i = 0 ; i < nbUser ; i ++)
  {
    printf("Entrez le message du %ie%s utilisateur\n>> ", i+1, (i>0?"":"r"));
    ScanClav(messageStr, TAILLE_MESSAGE);
    for(j = 0 ; j < strlen(messageStr) ; j++)
    {
      message[i][j] = messageStr[j]-48;
      taille[i] = strlen(messageStr);
    }

    memset(messageStr, 0, strlen(messageStr)); // Vide la chaine
  }

  tailleMax = 0;
  for (i = 0; i < nbUser ; i++)
  {
    tailleMax = (taille[i]<tailleMax ? tailleMax : taille[i]);
  }
  sortie = malloc(tailleH * tailleMax * sizeof(int));


   printf("\n==========================================");
   printf("\n|                                        |");
   printf("\n|               EMETTEUR                 |");
   printf("\n|                                        |");
   printf("\n==========================================\n");

  Emetteur(sortie, message, hadamard, nbUser, taille, tailleMax);
	printf("\n==========================\n|         SORTIE         |\n==========================\n");
	for( i = 0 ; i < (tailleH * tailleMax) ; i++)
  	printf("%3i", sortie[i]);
  printf("\n");

  printf("\n==========================================");
  printf("\n|                                        |");
  printf("\n|                 CANAL                  |");
  printf("\n|                                        |");
  printf("\n==========================================\n");

  sortie = Canal(sortie);
	

  printf("\n==========================================");
  printf("\n|                                        |");
  printf("\n|               RECEPTEUR                |");
  printf("\n|                                        |");
  printf("\n==========================================\n");

  Recepteur(messageRecu, sortie, taille, hadamard, nbUser, tailleMax, tailleH);

  printf("\n====================================\n|         MESSAGES DECODES         |\n====================================\n");

  for( i = 0 ; i < nbUser ; i++)
  {
		printf("Message de l'utilisateur %3i:\t", i+1);
		for(j = 0 ; j < taille[i]; j++)
        printf("%3i", messageRecu[i][j]);
    printf("\n");
  }

  free(taille);
  free(sortie);
  DestructionMatrice(&message, nbUser, TAILLE_MESSAGE);
  DestructionMatrice(&messageRecu, nbUser, TAILLE_MESSAGE);
  DestructionMatrice(&hadamard, tailleH, tailleH);
  return 0;
}
