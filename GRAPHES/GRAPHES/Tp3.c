#include "Outil.h"
#include "Graphe.h"
#include "Tas.h"
#include "Tp3.h"
#include <string.h>
int bTp3AmorceR;//ie le module a effectivement été amorcé
int bTp3OuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un Tp3 est actuellement alloué

void Tp3AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp3AmorceR=kV;
	bTp3OuverT=kF;
}//Tp3AMORCER
int nGrapheCheminerTaS3 (graf *pgG,int sSource,int sTrappe,int *pnComplexiteh){//O(S2)
	//rend le plus court chemin qui relie sSource à sTrappe; distances élémentR dans pgG->nCout[]. Algo plus court chemin, Dijkstra AVEC tas.
	const int kuInfini=9999;
	int nDist[1+pgG->nSommetEnTout];
	int nDistanceParX;
	int bFait[1+pgG->nSommetEnTout];
	int aK;
	int i;
	int sProche;
	int uSommet;
	int sX,sY;
	*pnComplexiteh=0;
	//initialiser bFait[], nDist[] et pgG->sPer[].
		/*for (sX=1; sX<=pgG->nSommetEnTout; sX++)
			bFait[sX]=0;
		for (sX=1; sX<=pgG->nSommetEnTout; sX++)
			nDist[sX]=kuInfini;
		for (sX=1; sX<=pgG->nSommetEnTout; sX++)
			pgG->sPer[sX]=0;*/
		VecteurRazer(bFait,1,pgG->nSommetEnTout);
		VecteurValuer(nDist,1,pgG->nSommetEnTout,kuInfini);
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);

		TasAllouer(pgG->nSommetEnTout);
		for (i=1;i<=pgG->nSommetEnTout;i++)
			TasInsererValuer(i,kuInfini);
		TasActualiser(sSource,0);
		//TasVoir("Tas après initialisation");
		nDist[sSource]=0;//distance entre le sommet de départ et lui-même
		pgG->sPer[sSource]=sSource;//condition d'arrêt vitale pour bGrapheCheminE()
		for (uSommet=1; uSommet<=pgG->nSommetEnTout; uSommet++) {
			//sProche:=numéro du sommet le plus proche de sSource, ou 0 si sSource ne mène à aucun nouveau sommet par un chemin quelconque)
				//TasVoir("Tas avant extraction");
				sProche=eTasExtraire();
			sX=sProche;
			if (sX!=0) {
				for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; aK++) {
					sY=pgG->sSuk[aK];
					nDistanceParX=nDist[sX]+pgG->nCout[aK];
					if ( nDist[sY]>nDistanceParX ) {
						nDist[sY]=nDistanceParX;
						pgG->sPer[sY]=sX;
						//tee("sY,nDistanceParX",sY,nDistanceParX);
						TasActualiser(sY,nDistanceParX);
						//TasVoir("Tas après TasActualiser");
					}
				}
				bFait[sX]=kV;
			}
		}//chaque sProche coûte O(S) et chaque arc est consulté 1 fois,soit une complexité au pire égale à sup( O(S*S),O(A) ), dc O(S2)
		//VecteurVoir("sPer",&pgG->sPer[0],1,pgG->nSommetEnTout);
		(*pnComplexiteh)+=nTasCout();
	TasAllouer(0);
	return(nDist[sTrappe]);
}//nGrapheCheminerTaS*/

void TP3Facturer(int sOrigine,int sDestination, int nLongueur,int nLargeur, int nHauteur){
	graf *pgG;
	GrapheAllouerInitialiseR(1,k1Afficher,&pgG);
	char cLongueur[]="AE9BE9EF7FC7FD9GA9GB9CH9DH9";
	char cLargeur[]= "AE9BE9EF9FC9FD9GA9GB9CH9DH9";
	char cHauteur[]= "AE9BE9EF5FC9FD9GA9GB9CH9DH9";
	int nComplexiteh;
	int i;
	const int nPrixKm = 100;
	const int PrixBase = 500;
	VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);

	for (i=1;i<pgG->nArcEnTout;i++)
		if ((cLongueur[3*i-1]-'0' < nLongueur) || (cLargeur[3*i-1]-'0'< nLargeur) || (cHauteur[3*i-1]-'0'< nHauteur))
				pgG->nCout[i] = 999;

	if (nGrapheCheminerTaS3(pgG,sOrigine,sDestination,&nComplexiteh) == 9999)
	{
		printf("Pas de chemin possible \n");
		exit(0);
	}

	if (nGrapheCheminerTaS3(pgG,sOrigine,sDestination,&nComplexiteh)>=99)
	{
		printf("Le camion est trop long/large/haut \n");
		exit(0);
	}
	else printf("Le trajet coute : %i €, TVA non-comprise\n",PrixBase+nGrapheCheminerTaS3(pgG,sOrigine,sDestination,&nComplexiteh)*nPrixKm);
	exit(0);
}
void TP3Router(int nHeure,int nMinute,int nSeconde,int sOrigine,int sDestination, int nLongueur,int nLargeur, int nHauteur){

	graf *pgG;
	GrapheAllouerInitialiseR(1,k1Afficher,&pgG);
	int nSecondes = 3600 * nHeure + 60 * nMinute + nSeconde;
	char cLongueur[]="AE9BE9EF7FC7FD9GA9GB9CH9DH9";
	char cLargeur[]= "AE9BE9EF9FC9FD9GA9GB9CH9DH9";
	char cHauteur[]= "AE9BE9EF5FC9FD9GA9GB9CH9DH9";
	int nComplexiteh;
	int i;
	VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);

	for (i=1;i<pgG->nArcEnTout;i++)
		if ((cLongueur[3*i-1]-'0' < nLongueur) || (cLargeur[3*i-1]-'0'< nLargeur) || (cHauteur[3*i-1]-'0'< nHauteur))
				pgG->nCout[i] = 999;

	int distance = nGrapheCheminerTaS3(pgG,sOrigine,sDestination,&nComplexiteh) * 10000;
	int temps = distance / 36;
	nSecondes += temps;
	int jours = nSecondes/86400;
	int heures = (nSecondes%86400)/3600;
	int min = ((nSecondes%86400)%3600)/60;
	int secondes = ((nSecondes%86400)%3600)%60;

	switch(jours){
		case 0: printf("Le Camion arrivera à %iH%i:%i", heures, min, secondes); break;
		case 1: printf("Le Camion arrivera demain à %iH%i:%i", heures, min, secondes); break;
		default: printf("Le Camion arrivera dans %i jours, à %iH%i:%i", jours, heures, min, secondes); break;
	}

}
void Tp3INITIALISER(){//O(?)
	//relance le présent module
	Assert2("Tp3INITIALISER",bTp3AmorceR,!bTp3OuverT);
}//Tp3INITIALISER

void Tp3TESTER(int iTest){
	//teste le présent module
	Appel0(sC2("Tp3TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: //calcul de la densité d'un graphe simple aléatoire
			TP3Facturer(1,5,2,2,2);
			break;
		case 2:
			TP3Router(15,38,16,1,5,2,1,2);
		default: ;
	}
	Appel1(sC2("Tp3TESTER,test n°",sEnt(iTest)));
}//Tp3TESTER
