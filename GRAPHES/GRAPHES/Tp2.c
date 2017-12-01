#include "Outil.h"
#include "Graphe.h"
#include "Tp2.h"
#include "Tas.h"
#define kuSommetMax 100
int bTp2AmorceR;//ie le module a effectivement été amorcé
int bTp2OuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un Tp3 est actuellement alloué

int nGrapheCheminerTaS2 (graf *pgG,int sSource,int sTrappe,int *pnComplexiteh){//O(S2)
	//rend le plus court chemin qui relie sSource à sTrappe; distances élémentR dans pgG->nCout[]. Algo plus court chemin, Dijkstra AVEC tas.
	const int kuInfini=9999;
	int nDist[1+pgG->nSommetEnTout];
	int nDistanceParX;
	int bFait[1+pgG->nSommetEnTout];
	int aK;
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
	for (sX=1; sX<=pgG->nSommetEnTout; sX++)
			TasInsererValuer(sX,kuInfini);
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
}//nGrapheCheminerTaS

void DistancierAvecFloyD(graf *pgG, int nDist[][1+kuSommetMax], int *pnComplexiteh){//(O(S3)
	//calcule le distancier de pgG supposé dense (algo de Floyd);poids des arcs dans pgG->coulh[]
	int aK,sX,sY;//a comme arc;s comme sommet
	int uL,uC;//u comme entier supérieur ou égal à un;L=ligne,C=colonne.
	int nSommet=pgG->nSommetEnTout;
	int dM[1+nSommet][1+nSommet];//matrice des distances,supposées être des entiers ou des réels déjà ramenés à des entiers
	Assert1("DistancierCalculeR",bGrapheSimple(pgG));
	//générer la matrice d'incidence sommet-sommet dM qui décrit le graphe simple pgG
		//dM:=0
			for (uL=1;uL<=nSommet;uL++)
				for (uC=1;uC<=nSommet;uC++){
					(*pnComplexiteh)++;
					dM[uL][uC]=0;
				}
		for (sX=1;sX<=nSommet;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				(*pnComplexiteh)++;
				sY=pgG->sSuk[aK];
				dM[sX][sY]=pgG->nCout[aK];//distance (sX,sY)
			}
	//exécuter l'algorithme de Floyd sur dM
		//code à compléter...
		int intMax=32767;
		//int nDist[1+nSommet][1+nSommet];
		int I,J,K,i,j;
		for(uL=1;uL<=nSommet;uL++){
			for (uC=1;uC<=nSommet;uC++){
				(*pnComplexiteh)++;
				if(uL==uC)
					nDist[uL][uC]=0;
				else
					nDist[uL][uC]=intMax;
			}
		}
		for(sX=1;sX<=nSommet;sX++){
			for(sY=1;sY<nSommet;sY++){
				(*pnComplexiteh)++;
				if(dM[sX][sY]!=0)
					nDist[sX][sY]=dM[sX][sY];
			}
		}
		for(K=1;K<=nSommet;K++){
			for(I=1;I<=nSommet;I++){
				for(J=1;J<=nSommet;J++){
					(*pnComplexiteh)++;
					//d3(I,J,K);
					if(nDist[I][J]> nDist[I][K] + nDist[K][J]){
						//m3;
						nDist[I][J]=nDist[I][K]+ nDist[K][J];
					}
				}
			}
		}

			for(i=1;i<=nSommet;i++){

				for(j=1;j<=nSommet;j++){
					printf(" %8i  ", nDist[i][j]);
				}
				printf("\n");
			}

}//DistancierAvecFloyD

void DistancierAvecDijkstrA(graf *pgG, int sSource, int nDyst[1+kuSommetMax], int *pnComplexiteh){
	int i;
	int nSommet = pgG->nSommetEnTout;

	for(i=1; i<nSommet+1; i++){
			nDyst[i]=nGrapheCheminerTaS2(pgG, sSource, i, pnComplexiteh);
	}
}//DistancierAvecDijkstrA

int nDistancierCalculeR(graf *pgG, int nSommet, int bFloydDijkstra, int bAfficher)
{

	int nComplexiteh=0;
	int sSource=2;
	int nDist1[10][1+kuSommetMax];
	int nDist2[1+kuSommetMax];

	if(bFloydDijkstra==1)
	{
			DistancierAvecFloyD(pgG, nDist1, &nComplexiteh);
	}
	else if(bFloydDijkstra==2)
	{
			DistancierAvecDijkstrA(pgG, sSource, nDist2, &nComplexiteh);
	}
	if ( (bFloydDijkstra==2 || bFloydDijkstra==1) && bAfficher){//afficher le distancier
		for(int  i=1; i<(1+nSommet); i++)
			for(int j=1; j<(1+nSommet); j++)
				if(nDist1[i][j]>0 && nDist1[i][j]<3000)
					printf("Distance [%i] [%i] : %i\n", i, j, nDist1[i][j]);
	}
	return nComplexiteh;

}

void Tp2AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp2AmorceR=kV;
	bTp2OuverT=kF;
}//Tp2AMORCER

void Tp2INITIALISER(){//O(?)
	//relance le présent module
	Assert2("Tp3INITIALISER",bTp2AmorceR,!bTp2OuverT);
}//Tp2INITIALISER

void Tp2TESTER(int iTest){
	//teste le présent module
	graf *pgG;
	int complex;
	int sSource = 2;
	Appel0(sC2("Tp2TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: //calcul de la densité d'un graphe simple aléatoire
			GrapheCreer(8,&pgG);
			complex = 0;
			int nDist[10][1+kuSommetMax];
			DistancierAvecFloyD(pgG, nDist, &complex);
			printf("Complexite de Floyd : %d\n",complex);
			GrapheCreer(0,&pgG);
			break;
		case 2:
			GrapheCreer(8,&pgG);
			complex = 0;
			int nDyst[1+kuSommetMax];
			DistancierAvecDijkstrA(pgG, sSource, nDyst, &complex);
			printf("Complexite de Dijkstra : %d\n",complex);
			GrapheCreer(0,&pgG);
			break;
		case 3:
			GrapheCreer(8,&pgG);
			complex=nDistancierCalculeR(pgG, pgG->nSommetEnTout, 2, 0);
			printf("Complexité :%i\n",complex);
			GrapheCreer(0,&pgG);
			break;
		default: ;
	}
	Appel1(sC2("Tp2TESTER,test n°",sEnt(iTest)));
}//Tp2TESTER
