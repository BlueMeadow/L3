#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include "messages.h"
#include <signal.h>

key_t cle;

void HandlerBoite(int sig)
{
  int boiteAuxLettres = msgget(cle, 0);
  requete_t coureur;
  reponse_t reponse;

	coureur.corps.dossard = getpid();
	coureur.type = PC_COURSE;
  coureur.corps.etat= ABANDON;

  msgsnd(boiteAuxLettres, &coureur, sizeof(corps_requete_t), 0);

	reponse.corps.compte_rendu=ABANDON_ACK; 

  msgrcv(boiteAuxLettres, &reponse, sizeof(corps_reponse_t), getpid(), 0);
  printf("\n---- ABANDON ----\n");
  exit(0);
}

int main(int argc, char * argv[])
{

  /* ---- USAGE ---- */

  if(argc != 2)
  {
		printf("Nombre d'argument incorrect, Usage%s : <Cle>\n", argv[0]);
		exit(0);
	}

  /* ---- COURSE ---- */

  int boiteAuxLettres; // Numéro de boite aux lettres
  requete_t coureur; // Requete coureur
  reponse_t reponse; // Réposne du PC course
  struct sigaction sig;
  sig.sa_handler=HandlerBoite;
  sigaction(SIGINT,&sig,NULL);

	cle = atoi(argv[1]); // Récupération du numéro de la clé

  boiteAuxLettres = msgget(cle, 0); //Récupération de l'id de la boite aux lettres

	coureur.corps.dossard = getpid(); // Affectation du numéro du coureur (son PID)
	coureur.corps.etat=EN_COURSE; // Etat initial du coureur -> En course
	coureur.type = PC_COURSE; // Adresse du serveur

  /* ---- REPONSE ---- */

	reponse.corps.etat = EN_COURSE; // Le coureur court toujours

	messages_initialiser_attente();

	while(reponse.corps.etat == EN_COURSE)
  {
		msgsnd(boiteAuxLettres, &coureur, sizeof(corps_requete_t), 0); // Envoie de la requete au serveur

		msgrcv(boiteAuxLettres, &reponse, sizeof(corps_reponse_t), getpid(), 0); // Attente de la réponse
		printf("\33[H\33[2J"); //Efface la console
		messages_afficher_etat(reponse.corps.etat) ; // Actualisation

		messages_afficher_reponse(&reponse);
		messages_afficher_parcours(&reponse);

		messages_attendre_tour();
	}

}
