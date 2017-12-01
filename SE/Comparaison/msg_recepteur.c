#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif

#include <msg_messages.h>
#define CLE 13

int cle;

void HandlerArret(int sig)
{
  msgctl(cle, IPC_RMID, 0);
  printf("Destruction de la Boite aux Lettres\n");
  exit(0);
}

int main( int nb_arg , char * tab_arg[] )
{
  char nomprog[128] ;
  message_t recu;
  int i;
  struct timeval debut, fin;
  double dureeReception, dureeTransmission, tempsDebut, tempsFin;

  if( nb_arg !=1 )
  {
    fprintf( stderr , "%s - Recepteur dans la communication par paquet\n\n" , tab_arg[0] );
    fprintf( stderr , "usage : %s \n" , tab_arg[0] );
    exit(-1);
  }
  strcpy( nomprog , tab_arg[0] );

  /* ---- Création de la boite aux lettres ---- */

  if( (cle = msgget(CLE, 0)) == -1)
  {
    fprintf(stderr, "%s : Erreur lors de la création de la Boite aux lettres\n\n", nomprog);
    exit(-1);
  }

  printf("Debut de la réception\n");

  /* ---- Récuperation du temps avant la réception ---- */

  gettimeofday(&debut, NULL);

  /* ---- Boucle de reception des messages ---- */

  for(i = 0; i < MESSAGES_NB; i ++)
  {
    /* ---- Attente de la recuperation d un message ---- */
    if( ( msgrcv(cle, &recu, sizeof(corps_t), MSG_TYPE_RECEPTEUR, 0)) == -1)
    {
      fprintf(stderr, "%s : Erreur lors de la reception d un message\n\n", nomprog);
      exit(-1);
    }
  //msg_afficher(&recu);
  }

  /* ---- Recuperation du temps apres reception des messages ---- */

  gettimeofday(&fin, NULL);

  /* ---- Recuperation de la duree de reception du temps et affichage ---- */

  tempsDebut = debut.tv_sec + (debut.tv_usec /1000000);
  tempsFin = fin.tv_sec + (fin.tv_usec /1000000);
  dureeReception = tempsFin - tempsDebut;

  printf("Fin de la reception\n");

  /* ---- reception de la date de debut d emission ---- */
  if( ( msgrcv(cle, &recu, sizeof(corps_t), MSG_TYPE_RECEPTEUR, 0)) == -1)
  {
    fprintf(stderr, "%s : Erreur lors de la reception d un message\n\n", nomprog);
    exit(-1);
  }

  /* ---- Transformation du corps du message en duree ---- */

  tempsDebut = strtod(recu.corps.buffer, NULL);

  /* ---- Calcul de la duree de transmission ---- */

  dureeTransmission = tempsFin - tempsDebut;

  printf("\n====================================================================\n");
  printf("Temps Début : %.6lf || Temps Fin : %.6lf\n", tempsDebut, tempsFin);
  printf("La duree pour la reception de %d mesages de taille %d est : %.3f secondes\n", MESSAGES_NB, MESSAGES_TAILLE, dureeReception);
  printf("La duree pour la transmission de %d messages de tailles %d est : %.3f secondes\n", MESSAGES_NB, MESSAGES_TAILLE, dureeTransmission);
  printf("\n====================================================================\n\n");

  /* ---- Suppression de la boite aux lettres ---- */

  if( (msgctl(cle, IPC_RMID, 0)) == -1)
  {
    fprintf(stderr, "%s : Erreur lors de la suppression de la la Boite aux Lettres", nomprog);
    exit(-1);
  }

  exit(0);
}
