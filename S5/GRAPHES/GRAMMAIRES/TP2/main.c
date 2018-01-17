#include "Outil.h"
#include "G4.h"

int POSSIBILITE = 7;

void ModuleAmorceR()
{
	//amorce tous les modules (code à exécuter une fois pour toutes AVANT d'utiliser un quelconque module depuis le main)
	OutilAMORCER();//NE PAS DECLASSER:doit toujours être appelé en premier
	//amorcer TOUS les modules autres que Outil mentionnés dans les include de main.c
    G4AMORCER();
}//ModuleAmorceR

int main (int argc, const char * argv[])
{
	Appel0("");//NE PAS TOUCHER; ce code doit toujours être placé au début du main
		ModuleAmorceR();//NE PAS TOUCHER; ce code doit toujours suivre immédiatement Appel0("")

          printf("=Debut du programme de test de grammaire\n");
          for(int cpt = 0 ; cpt<=POSSIBILITE ; cpt++){
               printf("\n==Grammaire pour iTest = %i\n===", cpt);
               G4TESTER(cpt);
          }
          printf("\n=Fin du programme de test de grammaire\n");
	Appel1("");//NE PAS TOUCHER; ce code doit toujours être placé à la fin du main, juste avant le return()
    return 0;
}
