#include <stdio.h>
#include <unistd.h>	/* close, read, write */
#include <stdlib.h>	/* exit */
#include <sys/types.h>	/*open */
#include <sys/stat.h>
#include <fcntl.h>
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
  int fdTube, i = 0;
  struct timeval temps_debut ;
  struct timeval temps_fin ;
  double tempsDebut, tempsDebutEmission;
  double tempsFin;

  /*-----*/
  strcpy( nomprog , tab_arg[0] );

  if( nb_arg != 1 )
  {
  fprintf( stderr , "%s - Recepteur dans la communication par flot\n\n" , tab_arg[0] );
  fprintf( stderr , "usage : %s \n" , nomprog );
  exit(-1);
  }

  /* ---- Ouverture du tube en lecture ---- */
  if( (fdTube = open(nomTube, O_RDONLY, 0)) == ERROR )
  {
    perror("Problème ouverture en lecture du tube nommé \n");
    exit(ERROR);
  }

  /* ---- Récupération du temps de début ---- */
  gettimeofday(&temps_debut, NULL);
  tempsDebut = temps_debut.tv_sec+(temps_debut.tv_usec/1000000.0);

  /* ---- Réception des messages ---- */
  for ( i = 0; i < MESSAGES_NB; i++)
  {
    read( fdTube, message, sizeof(char) * MESSAGES_TAILLE );
    //printf("Message n°%i\n", i);
  }
  /* ---- Récupération du temps de fin ---- */
  gettimeofday(&temps_fin, NULL);

  tempsFin = temps_fin.tv_sec+(temps_fin.tv_usec/1000000.0);

  printf("\n====================================================================");
  printf("\nTemps début réception : %.6lf || Temps fin réception : %.6lf", tempsDebut, tempsFin);
  printf("\nTemps de reception =  %.6lf secondes\n", tempsFin - tempsDebut);

  read(fdTube, &tempsDebutEmission, sizeof(double) );

  printf("\nTemps début Emission :  %.6lf || Temps fin réception : %.6lf", tempsDebutEmission, tempsFin);
  printf("\nTemps de transfert =  %.6lf secondes", tempsFin - tempsDebutEmission);
  printf("\n====================================================================\n\n");

  remove(nomTube);
  exit( 0 );
}
