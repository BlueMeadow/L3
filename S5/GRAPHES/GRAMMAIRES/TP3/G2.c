#include "Outil.h"
#include "G2.h"

	// // Langage
	//   L -> (a^n).(b^n), n carré non nul
	//   L'-> (a^n).(b^n), n>0
	//
	// // Grammaire
	//  S -> T
	//  T -> aTb + ab
	//
	//  Attributs
  // //  S       -> T(p).(p est un carré)
  // //  T(g)    -> T1(g) + T2(g)
  // //  T1(1+p) -> AT(p)B
  // //  T2(1)   -> AB


char *sMOT;
int bGrammaireAmorceR = kF;

int bA(int iDebut, int *piFin);
int bB(int iDebut, int *piFin);
int bS(int iDebut, int *piFin);

int bC(int iDebut, int *piFin,int *paAttr);
int bC1(int iDebut, int *piFin,int *paAttr);
int bC2(int iDebut, int *piFin,int *paAttr);

int bT(int iDebut, int *piFin,int *paAttr);
int bT1(int iDebut, int *piFin,int *paAttr);
int bT2(int iDebut, int *piFin,int *paAttr);


void G2AMORCER()
{
  bGrammaireAmorceR = kV;
}

void G2INITIALISER()
{
  Assert1("GrammaireINITIALISER", bGrammaireAmorceR);
}

void G2TESTER(int iTest)
{
  int bEngendre, iFin, bSucces;
  //Assert1("GrammaireTESTER0", bGrammaireAmorceR);
  //sMOT:=mot à teste selon iTest
    switch(iTest)
    {
      case 0: sMOT="";   break; // Mot vide
      case 1: sMOT="ab";   break;
      case 2: sMOT="aabb";  break;
      case 3: sMOT="aaabbb";  break;
      case 4: sMOT="aaaabbbb";  break;
      case 5: sMOT="aaabbbaaa";  break;
      case 6: sMOT="aaabbba";   break;
      case 7: sMOT="aaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbb";   break; // 25 a et 25 b
      default:Assert1("GrammaireTESTER1", 0); break;
    }
  bSucces = bS(0,&iFin);
  bEngendre=bSucces && nChaineLg (sMOT) == iFin;
  printf("%s : %s %s engendré par la grammaire décrite dans \"G2.c\".\n", (bEngendre) ? "SUCCES" : "ECHEC" , sG(sMOT), sEst(bEngendre));
}

int bA(int iDebut, int *piFin)
{
     //A->a
     //printf("A\n");
     int bSucces = sMOT[iDebut] == 'a';
     *piFin = (bSucces) ? iDebut+1 : iDebut;
     return (bSucces);
}

int bB(int iDebut, int *piFin)
{
     //B->b
     //printf("B\n");
     int bSucces = sMOT[iDebut] == 'b';
     *piFin = (bSucces) ? iDebut+1 : iDebut;
     return (bSucces);
}

int bT(int iDebut, int *piFin,int *paAttr)
{
  // //  T(g)    -> T1(g) + T2(g)
  //printf("T\n");
     int iFin, aT;
     int bSucces = bT1(iDebut, &iFin, &aT) || bT2(iDebut, &iFin, &aT);
     *piFin = (bSucces) ? iFin : iDebut;
     if(bSucces)
      *paAttr = aT;
     return (bSucces);
}

int bT1(int iDebut, int *piFin,int *paAttr)
{
    // //  T1(1+p) -> AT(p)B
  //printf("T\n");
     int iX, iY, iFin, aT;
     int bSucces = bA(iDebut, &iX) && bT(iX, &iY, &aT) && bB(iY, &iFin);
     *piFin = (bSucces) ? iFin : iDebut;
     if(bSucces)
      *paAttr = aT + 1;
     return (bSucces);
}

int bT2(int iDebut, int *piFin,int *paAttr)
{
  //  T2(1)   -> ab
  //printf("T\n");
     int iX, iFin;
     int bSucces = bA(iDebut, &iX) && bB(iX, &iFin);
     *piFin = (bSucces) ? iFin : iDebut;
     if(bSucces)
      *paAttr = 1;
     return (bSucces);
}

int bS(int iDebut, int *piFin)
{
  //  S       -> T(p).(p est un carré)
     //printf("S\n");
     int iY, iFin;
     int aP;
     int bSucces = bT(iDebut, &iFin, &aP) &&  ( (int)sqrt(i) == sqrt(i) );
     *piFin = (bSucces) ? iFin : iDebut;
     return (bSucces);
}
