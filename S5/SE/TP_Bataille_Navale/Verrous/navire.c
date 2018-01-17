#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* fcntl */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> /* errno */
#include <string.h>

#include <bateau.h>
#include <mer.h>

#define FERMER 1
#define OUVRIR 0

// struct flock {
//     ...
//     short l_type;    /* Type de verrouillage : F_RDLCK,
//                         F_WRLCK, F_UNLCK */
//     short l_whence;  /* Interprétation de l_start:
//                         SEEK_SET, SEEK_CUR, SEEK_END */
//     off_t l_start;   /* Décalage de début du verrouillage */
//     off_t l_len;     /* Nombre d'octets du verrouillage */
//     pid_t l_pid;     /* PID du processus bloquant notre verrou
//                         (F_GETLK seulement) */
//     ...
// };
// Structure de verrou, http://manpagesfr.free.fr/man/man2/fcntl.2.html

void BateauDetruire(int fd, int * nbBateaux, bateau_t * bateau)
{
	mer_nb_bateaux_ecrire(fd, --(*nbBateaux));
	bateau_destroy(&bateau);
}

int VerrouMer(int fd, bateau_t * bateau, int lckd)
{
  // Verouille le fichier mer
  struct flock verrou;
  verrou.l_whence = 0;
  verrou.l_start = 0;
  verrou.l_len = 0;

  if(lckd) verrou.l_type = F_WRLCK;
  else verrou.l_type = F_UNLCK;

  if(fcntl(fd, F_SETLKW, &verrou) == ERREUR)
  {
    if(lckd) fprintf(stderr, "Erreur fermeture");
    else fprintf(stderr, "Erreur ouverture");
    return ERREUR;
  }
  return CORRECT;
}//VerrouMer

int VerrouBouclier(const int fd, bateau_t * bateau, int lockn)
{
	//Verrouille chaque case appartenant au bateau, une à une
	int i;
	coords_t * bateauCellules = bateau_corps_get(bateau);
	coord_t * bateauCellule = bateauCellules->coords;

	struct flock verrou;

	verrou.l_whence = 0;
	verrou.l_len = MER_TAILLE_CASE;

	// Pose du verrou sur chaque case
	if(lockn)
	{
		verrou.l_type = F_WRLCK;
		for(i = 0; i < bateauCellules->nb; i++)
		{
			verrou.l_start = bateauCellule[i].pos;

			if(fcntl(fd, F_SETLKW, &verrou) == ERREUR)
			{
				printf("Erreur lors de la pose du verrou bouclier\n");
				return ERREUR;
			}
		}
	}
	// Levee du verrou de chaque case
	else
	{
		verrou.l_type = F_UNLCK;
		for(i = 0; i < bateauCellules->nb; i++)
		{
			verrou.l_start = bateauCellule[i].pos;
			if(fcntl(fd, F_SETLKW, &verrou) == ERREUR)
			{
				printf("Erreur lors de la levee du verrou bouclier\n");
				return ERREUR;
			}
		}
	}
	if(lockn)
		printf("\n - Bateau %c : Bouclier pose -\n", bateau_marque_get(bateau));
	else
		printf("\n - Bateau %c : Bouclier leve -\n", bateau_marque_get(bateau));
	return CORRECT;
}// VerrouBouclier


int VerrouHeader(const int fd, bateau_t * bateau, int lckd)
{
	// Verrouille le header du fichier mer pour empecher vision de le lire
	struct flock verrou;

	verrou.l_whence = 0;
	verrou.l_start = 0;
	verrou.l_len = MER_TAILLE_ENTETE;

	if(lckd)
		verrou.l_type = F_WRLCK;
	else
		verrou.l_type = F_UNLCK;
	if(fcntl(fd, F_SETLKW, &verrou) == -1) // Si un verrou est deja pose, on ne peut pas mettre celui-ci par dessus
		return ERREUR;
	return CORRECT;
}// VerrouHeader

int VerrouVoisins(const int fd, bateau_t * bateau, const coords_t listeVoisins, int lckd)
{
	int i;
	case_t merCase;
	struct flock verrou;

	verrou.l_whence = 0;
	verrou.l_len = 0;

	if(lckd)
		verrou.l_type = F_WRLCK;
	else
		verrou.l_type = F_UNLCK;
	bateau_marque_get(bateau);
	for(i = 0; i < listeVoisins.nb; i++)
	{
		mer_case_lire(fd, listeVoisins.coords[i], &merCase);
		if(merCase == MER_CASE_LIBRE) { // Si la case est libre, on la lckd
			verrou.l_start = listeVoisins.coords[i].pos;
			if(fcntl(fd, F_SETLK, &verrou) == -1)
			{
				if(lckd)
					printf("Erreur lors de la pose du verrou pour les voisins\n");
				else
					printf("Erreur lors de la levee du verrou pour les voisins\n");
				return ERREUR;
			}
		}
	}
	return CORRECT;
}// VerrouVoisins

int VerrouCible(const int fd, bateau_t * bateau, coord_t cible, int lockn) {
	// Pose un verrou sur une case en particulier
	struct flock verrou;

	verrou.l_whence = 0;
	verrou.l_start = cible.pos;
	verrou.l_len = MER_TAILLE_CASE;

	if(lockn)
	{
		verrou.l_type = F_WRLCK;
		printf("\n - Bateau %c : Pose verrou en [%i, %i] -\n", bateau_marque_get(bateau), cible.l, cible.c);
		if(fcntl(fd, F_SETLK, &verrou))
		{
			printf("Erreur lors de la pose du verrou\n");
			return ERREUR;
		}
	}
	else
	{
		verrou.l_type = F_UNLCK;
		printf("\n - Bateau %c : Levee verrou en [%i, %i] -\n", bateau_marque_get(bateau), cible.l, cible.c);
		if(fcntl(fd, F_SETLKW, &verrou))
		{
			printf("Erreur lors de la levee du verrou\n");
			return ERREUR;
		}
	}
	return CORRECT;
}//VerrouCible

/*
 *  Programme principal
 */


int main( int argc , char * argv[] )
{
  char fich_mer[128] ;
  case_t marque = MER_CASE_LIBRE ;
  char nomprog[128] ;
  float energie = 0.0 ;

  /*----------*/

  strcpy( nomprog , argv[0] ) ;

  if( argc != 4 )
    {
      fprintf( stderr , "Usage : %s <fichier mer> <marque> <energie>\n",
	       nomprog );
      exit(-1);
    }

  if( strlen(argv[2]) !=1 )
    {
      fprintf( stderr , "%s : erreur marque <%s> incorrecte \n",
	       nomprog , argv[2] );
      exit(-1) ;
    }


  strcpy( fich_mer , argv[1] );
  marque = argv[2][0] ;
  sscanf( argv[3] , "%f" , &energie );

  /* Initialisation de la generation des nombres pseudo-aleatoires */
  srandom((unsigned int)getpid());

  printf( "\n\n%s : ----- Debut du bateau %c (%d) -----\n\n ",
	  nomprog , marque , getpid() );

/*******************************
							DEBUT
********************************/

		bateau_t * bateau = BATEAU_NULL ;
		int nbBateaux = 0 ;
		int fd;								// Descripteur du fichier mer
		int no_error;

		if( ( fd = open( fich_mer , O_RDWR | O_CREAT , 0666)) == -1 )
		{
			printf("Erreur lors de l'ouverture du fichier mer");
			return(ERREUR);
		}

		bateau	= bateau_new(NULL, marque, energie);

		/*
		* POSE DES BATEAUX DANS LA MER
		*/

		// Verrouillage de la mer
		if((no_error = VerrouMer(fd, bateau, FERMER)))
		{
			printf("Erreur dans le verrouillage de la mer\n");
			exit(no_error);
		}

		if((no_error = mer_bateau_initialiser(fd, bateau)))
		{
			printf("Erreur dans l'initialisation de la mer\n");
			bateau_destroy(&bateau); //Si le bateau n'a pas pu être posé, on le supprime pour éviter les mauvaises surprises
			exit(no_error);
		}

		mer_nb_bateaux_lire(fd, &nbBateaux);
		mer_nb_bateaux_ecrire(fd, ++nbBateaux);

		printf("Merci d'attendre que les bateaux soient en place\n");
		if((no_error = VerrouMer(fd, bateau, OUVRIR)))
		{
			printf("Erreur dans le deverrouillage de la mer\n");
			exit(no_error);
		}

		sleep(5); //Attente pour que tous les bateaux soient placés
		printf("Allumage des boucliers\n");

		/*
		 * INITIALISATION DU BOUCLIER
		 */

		if(energie >= BATEAU_SEUIL_BOUCLIER)
		{
			if((no_error = VerrouBouclier(fd, bateau, FERMER)))
			{
				printf("Erreur lors du placement du bouclier\n");
				exit(no_error);
			}
		}
		sleep(5); // Attente pour que le bateau n'attaque pas qu'un bateau qui n'a pas encore son bouclier

		/*
		 * BOUCLE PRINCIPALE
		 */

		booleen_t coule = FAUX;
		booleen_t deplacement = VRAI;
		booleen_t acquisition;
		coords_t * listeVoisins = NULL;
		coord_t cible;
		char bateauMarque;

		while(1)
		{
			sleep(1);
			bateauMarque = bateau_marque_get(bateau);

			printf("\n - Bateau %c -\n", bateauMarque);

			if((no_error = mer_bateau_est_touche(fd, bateau, &coule)))
			// Destruction d'un bateau si on a un probleme lors de l'acces a ses donnees
			{
				printf("Erreur dans la vérification de l'attaque sur un bateau\n");
				BateauDetruire(fd,&nbBateaux, bateau);
				exit(no_error);
			}

			mer_nb_bateaux_lire(fd, &nbBateaux);

			if(coule && energie < BATEAU_SEUIL_BOUCLIER)
			// Destruction du bateau si touche par un autre
			{
				printf("\n - Bateau %c : Destruction -\n", bateauMarque);
				mer_nb_bateaux_ecrire(fd, --nbBateaux);
				mer_bateau_couler(fd, bateau);
				bateau_destroy(&bateau);
				close(fd);

				exit(0);
			}

			if(nbBateaux == 1)
			// Condition de victoire : Un seul bateau restant
			{
				printf("\n - Bateau %c : Vainqueur -\n", bateauMarque);
				printf("\n - Bateau %c : Fin -\n", bateauMarque);
				sleep(1);
				BateauDetruire(fd,&nbBateaux, bateau);
				close(fd);

				exit(0);
			}

			listeVoisins = coords_new();
			if((no_error = mer_voisins_rechercher(fd, bateau, &listeVoisins)))
			{
				printf("Erreur lors de la recherche de voisins\n");
				BateauDetruire(fd,&nbBateaux, bateau);

				exit(no_error);
			}

			/* DEPLACEMENT */

			if(energie > 0)
			{
				if(VerrouVoisins(fd, bateau, *listeVoisins, FERMER) == ERREUR)
				// On verifie que le bateau peut se deplacer et que les cases autour sont libres
				{
					printf("Erreur lors du deplacement du bateau %c\n", marque);
					deplacement = FAUX;
				}
				else
				{
					if((no_error = VerrouBouclier(fd, bateau, OUVRIR)))
					{
						printf("Erreur lors de la desactivation du bouclier\n");
						BateauDetruire(fd,&nbBateaux, bateau);

						exit(no_error);
					}
				}

				// On empeche la lecture du fichier
				VerrouHeader(fd, bateau, FERMER);

				if((no_error = mer_bateau_deplacer(fd, bateau, listeVoisins, &deplacement)))
				{
					// On deplace enfin le bateau
					printf("Erreur dans le deplacement du bateau sur la mer\n");
					BateauDetruire(fd,&nbBateaux, bateau);

					exit(no_error);
				}
				else
					energie -= BATEAU_MAX_ENERGIE * 0.05;

				// On permet la lecture
				VerrouHeader(fd, bateau, 0);
			}

			printf("\n - Bateau %c : %f d'energie restante -\n", bateauMarque, energie);

			if(energie >= BATEAU_SEUIL_BOUCLIER)
			{
				// On verifie si l'energie du bateau est suffisante pour reactiver les boucliers
				if((no_error = VerrouBouclier(fd, bateau, 1)))
				{
					printf("Erreur lors de l'activation du bouclier\n");
					BateauDetruire(fd,&nbBateaux, bateau);

					exit(no_error);
				}
			}

			if(VerrouVoisins(fd, bateau, *listeVoisins, OUVRIR) == ERREUR)
			{
				printf("Erreur lors du deverouillage des cases adjacentes au bateau %c", marque);
				BateauDetruire(fd,&nbBateaux, bateau);

				exit(no_error);
			}

			if(deplacement)
				printf("\n Deplacement acheve\n");
			else
				printf("\n Deplacement annule\n");

			coords_destroy(&listeVoisins);

			/*
			 * ACQUISITION D'UN BATEAU
			 */

			if((no_error = mer_bateau_cible_acquerir(fd, bateau, &acquisition, &cible)))
			{
				printf("Erreur lors de l'acquisition d'un bateau");
				BateauDetruire(fd,&nbBateaux, bateau);

				exit(no_error);
			}

			if(acquisition)
			// Si on peut tirer sur la cible
			// La cible est-elle deja verrouillee (bouclier) ?
			{
				if(VerrouCible(fd, bateau, cible, FERMER) != ERREUR)
				// On peut tirer
				{
					VerrouCible(fd, bateau, cible, OUVRIR);
					if((no_error = mer_bateau_cible_tirer(fd, cible)))
					{
						printf("Erreur lors du tir du bateau %c\n", marque);
						BateauDetruire(fd,&nbBateaux, bateau);

						exit(no_error);
					}

					if(VerrouCible(fd, bateau, cible, OUVRIR) == ERREUR)
					{
						printf("Erreur lors du deverouillage du bateau %c\n", marque);
						BateauDetruire(fd,&nbBateaux, bateau);

						exit(no_error);
					}
				}
				else printf("Erreur lors du verrouillage de la cible en [%i, %i]\n", cible.l, cible.c);
			}
			else printf("Erreur lors de l'acquisition d'une cible pour le bateau %c\n", marque);

			printf("\n\n");
		}

/*******************************
********************************
********************************/

  printf( "\n\n%s : ----- Fin du navire %c (%d) -----\n\n ",
	  nomprog , marque , getpid() );

  exit(0);
}
