#include "Outils.h"
#include "TestHadamard.h"
#include "TestLM.h"
#include "TestGold.h"
#include "TestJPL.h"


void FinRoutine(){
  printf("\nAppuyez sur entrée pour continuer.\n");
  getchar();
}


int main(int argc, char ** argv)
{
  int i = -1;
	int erreur = 0;
  char choix[4];
  while( i != 5 )
  {
    printf("\33[H\33[2J"); //Efface la console
    printf("faites un choix entre 1 et 5 :\n");

		if(erreur)
			printf("Erreur : le choix n'atait pas entre 1 et 5\n\n");
		else printf("\n\n");

    printf("case 1 : TestHadamard\n");
    printf("case 2 : TestLM\n");
    printf("case 3 : TestGold\n");
    printf("case 4 : TestJPL\n");
    printf("case 5 : Quitter\n");
    ScanClav(choix, 4);
    i = atoi(choix);
    switch(i)
    {
      case 1 : TestHadamard(); FinRoutine(); break;
      case 2 : TestLM(); FinRoutine(); break;
      case 3 : TestGold(); FinRoutine(); break;
      case 4 : TestJPL(); FinRoutine(); break;
      case 5 : exit(0);
      default : erreur = 1;
    }
  }
  return 0;
}
