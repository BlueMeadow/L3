#ifndef _OUTILS_

#define _OUTILS_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TAILLE_MESSAGE 140 // On ne peut rentrer que des tweets

void ScanClav(char  chaine[], int i);

int TailleHadamard(int nbUser);

int ** CreationMatrice(int lignes, int colonnes);

void DestructionMatrice(int *** matrice, int lig, int col);

void Hadamard(int ** hadamard, int tailleH);

#endif
