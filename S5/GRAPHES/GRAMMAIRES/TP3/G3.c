#include "Outil.h"
#include "G3.h"

	// // Langage
	//   L -> (a+).(b+)
	//
	// // Grammaire
	//  S -> T
	//  T -> aTb + ab
	//
	//  Attributs
  // //  S(nA, nB)    -> T(nA).C(nB)
  // //  T(nA)         -> T1(nA) + T2(nA)
  // //  T1(1+nA)      -> AT(nA)
  // //  T2(1)        -> A
  // //  C(nB+1)      -> C1(nB) + C2(nB)
  // //  C1(nB)       -> BC(nB)
  // //  C2(1)        -> B

char *sMOT;
int bGrammaireAmorceR = kF;

int bA(int iDebut, int *piFin);
int bB(int iDebut, int *piFin);
int bS(int iDebut, int *piFin);

int bC(int iDebut, int *piFin,int *paAttr);
int bC1(int iDebut, int *piFin,int *paAttr);
int bC2(int iDebut, int *piFin,int *paAttr);
int bD(int iDebut, int *piFin,int *paAttr);
int bE(int iDebut, int *piFin,int *paAttr);
int bF(int iDebut, int *piFin,int *paAttr);
int bG(int iDebut, int *piFin,int *paAttr);
int bH(int iDebut, int *piFin,int *paAttr);
int bJ(int iDebut, int *piFin,int *paAttr);
int bK(int iDebut, int *piFin,int *paAttr);
int bR(int iDebut, int *piFin,int *paAttr);
int bT(int iDebut, int *piFin,int *paAttr);
int bT1(int iDebut, int *piFin,int *paAttr);
int bT2(int iDebut, int *piFin,int *paAttr);
int bU(int iDebut, int *piFin,int *paAttr);
int bV(int iDebut, int *piFin,int *paAttr);
int bW(int iDebut, int *piFin,int *paAttr);


void G3AMORCER()
{
  bGrammaireAmorceR = kV;
}

void G3INITIALISER()
{
  Assert1("GrammaireINITIALISER", bGrammaireAmorceR);
}

void G3TESTER(int iTest)
{
  int bEngendre, iFin, bSucces;
  //Assert1("GrammaireTESTER0", bGrammaireAmorceR);
  //sMOT:=mot à teste selon iTest
    switch(iTest)
    {
      case 0: sMOT="";   break;
      case 1: sMOT="ab";   break;
      case 2: sMOT="aabb";  break;
      case 3: sMOT="aaabbb";  break;
      case 4: sMOT="aaaabbbb";  break;
      case 5: sMOT="aaabbbaaa";  break;
      case 6: sMOT="aaabbba";   break;
      case 7: sMOT="aaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbb";   break;
      default:Assert1("GrammaireTESTER1", 0); break;
    }
  bSucces = bS(0,&iFin);
  bEngendre=bSucces && nChaineLg (sMOT) == iFin;
  printf("%s : %s %s engendré par la grammaire décrite dans \"G3.c\".\n", (bEngendre) ? "SUCCES" : "ECHEC" , sG(sMOT), sEst(bEngendre));
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

int bC(int iDebut, int *piFin,int *paAttr)
{
  // //  C(nB+1)      -> C1(nB) + C2(nB)
  // //  C1(nB)       -> BC(nB)
  // //  C2(1)        -> B
  //printf("C\n");
     int iFin, aAttr;
     int bSucces = bC1(iDebut, &iFin, &aAttr) || bC2(iDebut, &iFin, &aAttr);
     *piFin = (bSucces) ? iFin : iDebut;
     if(bSucces)
      *paAttr = aAttr;
     return (bSucces);
}

int bC1(int iDebut, int *piFin,int *paAttr)
{

  // //  C(nB+1)      -> C1(nB) + C2(nB)
  // //  C1(nB)       -> BC(nB)
  // //  C2(1)        -> B
  //printf("C\n");
     int iX, iFin, aC;
     int bSucces = bB(iDebut, &iX) && bC(iX, &iFin, &aC);
     *piFin = (bSucces) ? iFin : iDebut;
     if(bSucces)
       *paAttr = aC + 1;
     return (bSucces);
}

int bC2(int iDebut, int *piFin,int *paAttr)
{
  // //  S(nA, nB)    -> T(nA).C(nB)
  // //  T(g)         -> T1(g) + T2(g)
  // //  T1(1+p)      -> AT(p)
  // //  T2(1)        -> A
  // //  C(nB+1)      -> C1(nB) + C2(nB)
  // //  C1(nB)       -> BC(nB)
  // //  C2(1)        -> B
  //printf("C\n");
     int iFin;
     int bSucces = bB(iDebut, &iFin);
     *piFin = (bSucces) ? iFin : iDebut;
     if(bSucces)
      *paAttr = 1;
     return (bSucces);
}

// int bD(int iDebut, int *piFin,int *paAttr)
// {
//   //   D -> A.B.B
//   //printf("C\n");
//      int iX, iY, iFin;
//      int bSucces = bA(iDebut, &iX, &paAttr) && bB(iX, &iY) && bB(iY, &iFin, &paAttr);
//      *piFin = (bSucces) ? iFin : iDebut;
//      if(bSucces)
//       *paAttr = 1;
//      return (bSucces);
// }
//
// int bE(int iDebut, int *piFin,int *paAttr)
// {
//   //   E->  G + T
//   //printf("R\n");
//      int iFin;
//      int bSucces = bG(iDebut, &iFin, &paAttr) || bT(iDebut, &iFin, &paAttr);
//      *piFin = (bSucces) ? iFin : iDebut;
//      if(bSucces)
//       *paAttr = 1;
//      return (bSucces);
// }
//
// int bF(int iDebut, int *piFin,int *paAttr)
// {
//   //   I + A
//   //printf("R\n");
//      int iFin;
//      int bSucces = bJ(iDebut, &iFin, &paAttr) || bA(iDebut, &iFin, &paAttr);
//      *piFin = (bSucces) ? iFin : iDebut;
//      if(bSucces)
//       *paAttr = 1;
//      return (bSucces);
// }
//
// int bG(int iDebut, int *piFin,int *paAttr)
// {
//   //   G-> A.E.B
//   //printf("H\n");
//   int iX, iY, iFin;
//   int bSucces = bA(iDebut, &iX, &paAttr) && bE(iX, &iY) && bB(iY, &iFin, &paAttr);
//   *piFin = (bSucces) ? iFin : iDebut;
//   if(bSucces)
//    *paAttr = 1;
//   return (bSucces);
// }
//
// int bH(int iDebut, int *piFin,int *paAttr)
// {
//   //   H->  a.R
//   //printf("H\n");
//   int iX, iFin;
//   int bSucces = bA(iDebut, &iX, &paAttr) && bR(iX, &iFin, &paAttr) ;
//   *piFin = (bSucces) ? iFin : iDebut;
//   if(bSucces)
//    *paAttr = 1;
//   return (bSucces);
// }
//
// int bJ(int iDebut, int *piFin,int *paAttr)
// {
//   //   J-> A.F
//   //printf("J\n");
//   int iX, iFin;
//   int bSucces = bA(iDebut, &iX, &paAttr) && bF(iX, &iFin, &paAttr) ;
//   *piFin = (bSucces) ? iFin : iDebut;
//   if(bSucces)
//    *paAttr = 1;
//   return (bSucces);
// }
//
// int bK(int iDebut, int *piFin,int *paAttr)
// {
//   //K -> A.T.B
//   //printf("K\n");
//   int iX, iY, iFin;
//   int bSucces = bA(iDebut, &iX, &paAttr) && bT(iX, &iY) && bB(iY, &iFin, &paAttr);
//   *piFin = (bSucces) ? iFin : iDebut;
//   if(bSucces)
//    *paAttr = 1;
//   return (bSucces);
// }
//
// int bR(int iDebut, int *piFin,int *paAttr)
// {
//   //   R->  H + a
//   //printf("R\n");
//      int iFin;
//      int bSucces = bH(iDebut, &iFin, &paAttr) || bA(iDebut, &iFin, &paAttr);
//      *piFin = (bSucces) ? iFin : iDebut;
//      if(bSucces)
//       *paAttr = 1;
//      return (bSucces);
// }


int bT(int iDebut, int *piFin,int *paAttr)
{
  // //  S(nA, nB)    -> T(nA).C(nB)
  // //  T(g)         -> T1(g) + T2(g)
  // //  T1(1+p)      -> AT(p)
  // //  T2(1)        -> A
  // //  C(nB+1)      -> C1(nB) + C2(nB)
  // //  C1(nB)       -> BC(nB)
  // //  C2(1)        -> B
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
  // //  T1(1+p)      -> AT(p)
  //printf("T\n");
     int iX, iY, iFin, aT;
     int bSucces = bA(iDebut, &iX) && bT(iX, &iFin, &aT);
     *piFin = (bSucces) ? iFin : iDebut;
     if(bSucces)
      *paAttr = aT + 1;
     return (bSucces);
}

int bT2(int iDebut, int *piFin,int *paAttr)
{
  // //  T2(1)        -> A
  //printf("T\n");
     int iX, iFin;
     int bSucces = bA(iDebut, &iX);
     *piFin = (bSucces) ? iFin : iDebut;
     if(bSucces)
      *paAttr = 1;
     return (bSucces);
}

// int bU(int iDebut, int *piFin,int *paAttr)
// {
//      //U->C+D
//      //printf("U\n");
//      int iX, iFin;
//      int bSucces = bC(iDebut, &iFin, &paAttr) || bD(iDebut, &iFin, &paAttr);
//      *piFin = (bSucces) ? iFin : iDebut;
//      if(bSucces)
//       *paAttr = 1;
//      return (bSucces);
// }
//
// int bV(int iDebut, int *piFin,int *paAttr)
// {
//   //   V-> E.F.B
//   //printf("V\n");
//   int iX, iY, iFin;
//   int bSucces = bE(iDebut, &iX, &paAttr) && bF(iX, &iY) && bB(iY, &iFin, &paAttr);
//   *piFin = (bSucces) ? iFin : iDebut;
//   if(bSucces)
//    *paAttr = 1;
//   return (bSucces);
// }

int bS(int iDebut, int *piFin)
{
  // //  S(nA, nB)    -> T(nA).C(nB)
  // //  T(g)         -> T1(g) + T2(g)
  // //  T1(1+p)      -> AT(p)
  // //  T2(1)        -> A
  // //  C(nB+1)      -> C1(nB) + C2(nB)
  // //  C1(nB)       -> BC(nB)
  // //  C2(1)        -> B
     //printf("S\n");
     int iY, iFin;
     int aA, aB;
     int bSucces = bT(iDebut, &iY, &aA) && bC(iY, &iFin, &aB);
     printf("\nOn a %d a et %d b\n", aA, aB);
     *piFin = (bSucces) ? iFin : iDebut;
     return (bSucces);
}
