#include "Outil.h"
#include "G4.h"

// //   L -> autant de a que de b, non nul

// //Gram Algébrique
//  S-> T + U + V + W + X
// T -> SS // Récursivité à gauche !
// U -> ASB
// V -> BSA
// W -> AB
// X -> BA

// //Gram Homogène


char *sMOT;
int bGrammaireAmorceR = kF;

int bA(int iDebut, int *piFin);
int bB(int iDebut, int *piFin);
int bS(int iDebut, int *piFin);

int bC(int iDebut, int *piFin);
int bD(int iDebut, int *piFin);
int bE(int iDebut, int *piFin);
int bF(int iDebut, int *piFin);
int bG(int iDebut, int *piFin);
int bH(int iDebut, int *piFin);
int bJ(int iDebut, int *piFin);
int bK(int iDebut, int *piFin);
int bR(int iDebut, int *piFin);
int bT(int iDebut, int *piFin);
int bU(int iDebut, int *piFin);
int bV(int iDebut, int *piFin);
int bW(int iDebut, int *piFin);


void G4AMORCER()
{
  bGrammaireAmorceR = kV;
}

void G4INITIALISER()
{
  Assert1("GrammaireINITIALISER", bGrammaireAmorceR);
}

void G4TESTER(int iTest)
{
  int bEngendre, iFin, bSucces;
  //Assert1("GrammaireTESTER0", bGrammaireAmorceR);
  //sMOT:=mot à teste selon iTest
    switch(iTest)
    {
      case 0: sMOT="";   break;
      case 1: sMOT="b";   break;
      case 2: sMOT="ab";  break;
      case 3: sMOT="abb";  break;
      case 4: sMOT="aabbb";  break;
      case 5: sMOT="abab";  break;
      case 6: sMOT="aabbaaaaaab";   break;
      case 7: sMOT="aabb";   break;
      default:Assert1("GrammaireTESTER1", 0); break;
    }
  bSucces = bS(0,&iFin);
  bEngendre=bSucces && nChaineLg (sMOT) == iFin;
  printf("%s : %s %s engendré par la grammaire décrite dans \"G4.c\".\n", (bEngendre) ? "SUCCES" : "ECHEC" , sG(sMOT), sEst(bEngendre));
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

int bC(int iDebut, int *piFin)
{
  //   C -> A.U.B
  //printf("C\n");
     int iX, iY, iZ, iFin;
     int bSucces = bA(iDebut, &iX) && bU(iX, &iY) && bB(iY, &iFin);
     *piFin = (bSucces) ? iFin : iDebut;
     return (bSucces);
}

int bD(int iDebut, int *piFin)
{
  //   D -> A.B.B
  //printf("C\n");
     int iX, iY, iFin;
     int bSucces = bA(iDebut, &iX) && bB(iX, &iY) && bB(iY, &iFin);
     *piFin = (bSucces) ? iFin : iDebut;
     return (bSucces);
}

int bE(int iDebut, int *piFin)
{
  //   E->  G + T
  //printf("R\n");
     int iFin;
     int bSucces = bG(iDebut, &iFin) || bT(iDebut, &iFin);
     *piFin = (bSucces) ? iFin : iDebut;
     return (bSucces);
}

int bF(int iDebut, int *piFin)
{
  //   I + A
  //printf("R\n");
     int iFin;
     int bSucces = bJ(iDebut, &iFin) || bA(iDebut, &iFin);
     *piFin = (bSucces) ? iFin : iDebut;
     return (bSucces);
}

int bG(int iDebut, int *piFin)
{
  //   G-> A.E.B
  //printf("H\n");
  int iX, iY, iFin;
  int bSucces = bA(iDebut, &iX) && bE(iX, &iY) && bB(iY, &iFin);
  *piFin = (bSucces) ? iFin : iDebut;
  return (bSucces);
}

int bH(int iDebut, int *piFin)
{
  //   H->  a.R
  //printf("H\n");
  int iX, iFin;
  int bSucces = bA(iDebut, &iX) && bR(iX, &iFin) ;
  *piFin = (bSucces) ? iFin : iDebut;
  return (bSucces);
}

int bJ(int iDebut, int *piFin)
{
  //   J-> A.F
  //printf("J\n");
  int iX, iFin;
  int bSucces = bA(iDebut, &iX) && bF(iX, &iFin) ;
  *piFin = (bSucces) ? iFin : iDebut;
  return (bSucces);
}

int bK(int iDebut, int *piFin)
{
  //K -> A.T.B
  //printf("K\n");
  int iX, iY, iFin;
  int bSucces = bA(iDebut, &iX) && bT(iX, &iY) && bB(iY, &iFin);
  *piFin = (bSucces) ? iFin : iDebut;
  return (bSucces);
}

int bR(int iDebut, int *piFin)
{
  //   R->  H + a
  //printf("R\n");
     int iFin;
     int bSucces = bH(iDebut, &iFin) || bA(iDebut, &iFin);
     *piFin = (bSucces) ? iFin : iDebut;
     return (bSucces);
}


int bT(int iDebut, int *piFin)
{
  // T -> A.B
  //printf("T\n");
     int iX, iFin;
     int bSucces = bA(iDebut, &iX) && bB(iX, &iFin);
     *piFin = (bSucces) ? iFin : iDebut;
     return (bSucces);
}

int bU(int iDebut, int *piFin)
{
     //U->C+D
     //printf("U\n");
     int iX, iFin;
     int bSucces = bC(iDebut, &iFin) || bD(iDebut, &iFin);
     *piFin = (bSucces) ? iFin : iDebut;
     return (bSucces);
}

int bV(int iDebut, int *piFin)
{
  //   V-> E.F.B
  //printf("V\n");
  int iX, iY, iFin;
  int bSucces = bE(iDebut, &iX) && bF(iX, &iY) && bB(iY, &iFin);
  *piFin = (bSucces) ? iFin : iDebut;
  return (bSucces);
}

int bS(int iDebut, int *piFin)
{
     //S-> V + U + T + F + B
     //printf("S\n");
     int iFin;
     int bSucces =  bV(iDebut, &iFin) || bU(iDebut, &iFin) || bT(iDebut, &iFin) || bF(iDebut, &iFin)|| bB(iDebut, &iFin);
     *piFin = (bSucces) ? iFin : iDebut;
     return (bSucces);
}
