/*
 * Programme pour processus navire :
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <mer.h>
#include <bateaux.h>

/*
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

int Energie ;

/*
 * Handlers
 */

void SignalRecevoir(int signal)
{
   Energie -= BATEAU_MAX_ENERGIE / 4;
}//SignalRecevoir

/*
 * Programme Principal
 */

int
main( int argc , char * argv[] )
{
  char nomprog[128] ;
  pid_t pid_amiral ;
  pid_t pid_bateau = getpid()  ;

  /*----------*/

  /*
   * Capture des parametres
   */

  if( argc != 2 )
    {
      fprintf( stderr , "Usage : %s <pid amiral>\n",
	      argv[0] );
      exit(-1);
    }

  /* Nom du programme */
  strcpy( nomprog , argv[0] );
  sscanf( argv[1] , "%d" , &pid_amiral ) ;

  /* Initialisation de la generation des nombres pseudo-aleatoires */
  srandom((unsigned int)pid_bateau);


  /* Affectation du niveau d'energie */
  Energie = random()%BATEAU_MAX_ENERGIE ;

  printf( "\n\n--- Debut bateau [%d]---\n\n" , pid_bateau );

  /*
   * Deroulement du jeu
   */

  struct sigaction bateau;
  bateau.sa_flags = 0;
  bateau.sa_handler = SignalRecevoir;
  sigaction(SIGUSR2, &bateau, NULL);

  while(Energie)
  {
    kill(pid_amiral, SIGUSR1); //kill permet d'envoyer n'importe quel signal à n'importe quel processus
    sleep(2);
  }

  printf( "\n\n--- Arret bateau (%d) ---\n\n" , pid_bateau );

  exit(0);
}
