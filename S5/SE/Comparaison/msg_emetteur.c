#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <msg_messages.h>

#define CLE 13

int main( int nb_arg , char * tab_arg[] )
{
  char nomProg[128] ;
  int i;
  int idBal;
  message_t message;
  struct timeval debut, fin, temps;
  double duree, tempsDebut, tempsFin;

  /*-----*/

  if( nb_arg !=1 )
  {
    fprintf( stderr , "%s - Emetteur dans la communication par paquet\n\n" , tab_arg[0] );
    fprintf( stderr , "usage : %s \n" , tab_arg[0] );
    exit(-1);
  }
  strcpy( nomProg , tab_arg[0] );

  /* ---- Récupération de l'id de la boite aux lettres ---- */
  printf("1\n");
  if( (idBal = msgget(CLE, IPC_CREAT | IPC_EXCL | 0666)) == -1)
  {
    fprintf(stderr, "%s : Erreur dans la recuperation de l'identifiant de la boite aux lettres\n\n", nomProg);
    exit(-1);
  }

  /* ---- Remplissage du message à envoyer ----*/
  msg_remplir(&message, 'X');
  printf("Debut de l'émission\n");
  gettimeofday(&debut, NULL);

  /*Boucle d envoi de messages au recepteur*/

  for(i = 0; i < MESSAGES_NB; i ++)
  {
    if( (msgsnd(idBal, &message, sizeof(corps_t), 0)) == -1)
    {
      fprintf(stderr, "%s : Erreur lors de l envoi du message %d\n\n", nomProg, (i+1));
      exit(-1);
    }
  }

  /* ---- Récuperation du temps après l'envoi des messages ---- */

  gettimeofday(&fin, NULL);

  /* ---- Calcul de la durée d'émission ---- */

  printf("Fin de l emission\n");

  /* ---- Envoi de la date de début d'émission ---- */

  tempsDebut = debut.tv_sec + (debut.tv_usec /1000000);
  tempsFin = fin.tv_sec + (fin.tv_usec /1000000);
  duree = tempsFin - tempsDebut;
  sprintf(message.corps.buffer, "%lf", tempsDebut);

  if( (msgsnd(idBal, &message, sizeof(corps_t), 0)) == -1)
  {
    fprintf(stderr, "%s : Erreur lors de l'envoi du message de date de transmission\n", nomProg);
    exit(-1);
  }

  printf("\n====================================================================\n");
  printf("Temps Début : %.6lf || Temps Fin : %.6lf\n", tempsDebut, tempsFin);
  printf("La duree d'émission de %d messages de taille %d est : %.6f secondes\n", MESSAGES_NB, MESSAGES_TAILLE, duree);
  printf("\n====================================================================");
  /* ---- transmission de la date de debut d emission pour calcul de duree de transmission ---- */

  exit(0);
}
