#include <stdio.h>
#include <commun.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include <mer.h>

/*--------------------*
 * Main demon
 *--------------------*/

int MerModificationRecente(char * fichier, int temps)
// Regarde si "fichier" a été modifié durant les "temps" dernieres secondes
{
  struct stat buffer;
  stat(fichier, &buffer);

  return( (time(NULL) - buffer.st_mtime) < temps);
}

int MerVerouillee(int MerFd)
//Renvoie 1 si la mer est vérouillée, 0 sinon
{
  struct flock lckd;

  lckd.l_whence = 0;
  lckd.l_start = 0;
  lckd.l_len = MER_TAILLE_ENTETE;

  fcntl(MerFd, F_GETLK, &lckd);

  if(lckd.l_type == F_RDLCK || lckd.l_type == F_WRLCK)
    return 1;
  return 0;
}

int main( int argc , char * argv[] )
{
     char fich_mer[128] ;
     char nomprog[256] ;
     int MerFd; //File descriptor Mer
     int NbLignes = 5; //Nombre de lignes dans la mer (10 pour la bataille navale classique)
     int NbColonnes = 5; //Nombre de colonnxes dans la mer (10 pour la bataille navale classique)
     time_t DerniereModif;
     int NbBateaux;
     int flag1 = 0, flag2 = 0;

     /*----------*/

     if( argc != 2 )
     {
	  fprintf( stderr , "Usage : %s <fichier mer>\n",
		   argv[0] );
	  exit(-1);
     }

     strcpy( nomprog , argv[0] );
     strcpy( fich_mer , argv[1] );

     printf("\n%s : ----- Debut de l'affichage de la mer ----- \n", nomprog );

     mer_initialiser(argv[1], NbLignes, NbColonnes);

     if((MerFd = open(fich_mer, O_RDONLY | O_CREAT, 0666)) == -1)
     {
       printf("Impossible d'ouvrir le fichier mer\n");
       return ERREUR;
     }

     mer_afficher(MerFd); //Affichage initial

     /* MISE A JOUR AFFICHAGE */

     DerniereModif = time(NULL);
     mer_nb_bateaux_lire(MerFd, &NbBateaux);

     while(!flag1 || !flag2)
     // Tant qu'il reste plus d'un bateau et qu'on en a eu au moins 2 à un moment
     {
       if(MerModificationRecente(argv[1],1) && DerniereModif != time(NULL))
       {
         // On vérifie si il y a une modification pendant la seconde passée
         while(MerVerouillee(MerFd));
         // On attend que la Mer ne soit plus verrouillée pour pouvoir la lire
         printf("\33[H\33[2J"); //Efface la console
         mer_afficher(MerFd);
         DerniereModif = time(NULL);
         mer_nb_bateaux_lire(MerFd, &NbBateaux);
         flag1 = (NbBateaux >= 2 || flag1); // 0 si on a déjà eu 2 bateau à un moment, 1 sinon
         flag2 = (NbBateaux == 0); // 1 s'il ne reste aucun bateau, on détruit les bateaux après la partie dans navire.c
       }
     }

     sleep(1);
     mer_nb_bateaux_lire(MerFd, &NbBateaux);
     mer_afficher(MerFd);

     printf("\n%s : --- Arret de l'affichage de la mer ---\n", nomprog );

     exit(0);
}
