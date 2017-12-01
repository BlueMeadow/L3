#include <stdio.h>
#include <stdlib.h>	/* exit */
#include <sys/stat.h>	/* mknod */
#include <sys/types.h>	/* open */
#include <fcntl.h>
#include <unistd.h>	/* close , write */
#include <sys/time.h>

#include <string.h>

#include <pipe_messages.h>


/* Codes d'erreur */
#define CREATION_ERROR -2
#define ERROR -1


int main( int nb_arg , char * tab_arg[])
{
  char nomprog[128] ;
  char nomTube[] = "TubeTp5"; // Nom du tube
  char message[MESSAGES_TAILLE]; // Message à envoyer
  int fdTube, i;
  struct timeval temps ;
  double temps_debut;
  double temps_fin;

  /*----------*/

  strcpy( nomprog , tab_arg[0] );

  if( nb_arg != 1 )
  {
    fprintf( stderr , "%s - Emetteur dans la communication par flot\n\n" , nomprog );
    fprintf( stderr , "usage : %s \n" , nomprog );
    exit(-1);
  }

  /* ---- Création du tube nommé ---- */
  if ( mknod( nomTube, S_IFIFO | 0666, 0) )
  {
    perror("Problème à la création du tube");
    exit(CREATION_ERROR);
  }

  /* ---- Ouverture du tube en écriture ---- */
  if( (fdTube = open(nomTube, O_WRONLY, 0)) == ERROR )
  {
    perror("Problème ouverture en écriture du tube nommé");
    exit(ERROR);
  }

  /* ---- Récupération du temps de début ---- */
  gettimeofday(&temps, NULL);
  temps_debut = temps.tv_sec+(temps.tv_usec/1000000.0);

  /* ---- Remplissage du message ---- */
  pipe_remplir( message , 'X') ;

  /* ---- Envoi des messages ---- */
  for ( i = 0; i < MESSAGES_NB; i++)
  {
    write( fdTube, message, sizeof(char) * MESSAGES_TAILLE );
  }

  /* ---- Récupération du temps de fin ---- */
  gettimeofday(&temps, NULL);
  temps_fin = temps.tv_sec+(temps.tv_usec/1000000.0);

  write(fdTube, &temps_debut, sizeof(double) );
  printf("\n====================================================================");
  printf("\nTemps début : %.6lf || Temps début : %.6lf", temps_debut, temps_fin);
  printf("\nTemps d'emission =  %.6lf secondes",  temps_fin - temps_debut);
  printf("\n====================================================================\n\n");

  close(fdTube);
  exit(0);
}
