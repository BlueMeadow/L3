#include "Outil.h"
#include "G4.h"

// //   L4 -> ba+ab+ba(b)+
// //Gram Algébrique
//   S->  K + J + V
//   K -> b.a
//   J -> a.b
//   V -> K.T
//   T -> B + U
//   U -> B.T
// //Gram Homogène
//  S -> K + V + J
//   V -> K.T
//   T -> B + U
//   U -> B.T
//   K -> b.a
//   J -> a.b




char *sMOT;
int bGrammaireAmorceR = kF;

int bA(int iDebut, int *piFin);
int bB(int iDebut, int *piFin);
int bJ(int iDebut, int *piFin);
int bK(int iDebut, int *piFin);
int bT(int iDebut, int *piFin);
int bU(int iDebut, int *piFin);
int bV(int iDebut, int *piFin);
int bS(int iDebut, int *piFin);

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
      case 1: sMOT="bab";   break;
      case 2: sMOT="babb";  break;
      case 3: sMOT="babbb";  break;
      case 4: sMOT="ba";  break;
      case 5: sMOT="bba";  break;
      default:Assert1("GrammaireTESTER1", 0); break;
    }
  bSucces = bS(0,&iFin);
  bEngendre=bSucces && nChaineLg (sMOT) == iFin;
  printf("%s : %s %s engendré par la grammaire décrite dans \"G4.c\".\n", (bEngendre) ? "SUCCES" : "ECHEC" , sG(sMOT), sEst(bEngendre));
}

int bA(int iDebut, int *piFin)
{
     //A->a
     int bSucces = sMOT[iDebut] == 'a';
     *piFin = (bSucces) ? iDebut+1 : iDebut;
     return (bSucces);
}

int bB(int iDebut, int *piFin)
{
     //B->b
     int bSucces = sMOT[iDebut] == 'b';
     *piFin = (bSucces) ? iDebut+1 : iDebut;
     return (bSucces);
}

int bJ(int iDebut, int *piFin)
{
  //J -> A.B
  int iX, iFin;
  int bSucces = bA(iDebut, &iX) && bB(iX, &iFin) ;
  *piFin = (bSucces) ? iFin : iDebut;
  return (bSucces);
}

int bK(int iDebut, int *piFin)
{
  //K -> B.A
  int iX, iFin;
  int bSucces = bB(iDebut, &iX) && bA(iX, &iFin) ;
  *piFin = (bSucces) ? iFin : iDebut;
  return (bSucces);
}

int bT(int iDebut, int *piFin)
{
     //T->U+B
     int iFin;
     int bSucces = bU(iDebut, &iFin) || bB(iDebut, &iFin);
     *piFin = (bSucces) ? iFin : iDebut;
     return (bSucces);
}

int bU(int iDebut, int *piFin)
{
     //U->B.T
     int iX, iFin;
     int bSucces = bB(iDebut, &iX) && bT(iX, &iFin);
     *piFin = (bSucces) ? iFin : iDebut;
     return (bSucces);
}

int bV(int iDebut, int *piFin)
{
  //V -> K.T
  int iX, iFin;
  int bSucces = bK(iDebut, &iX) && bT(iX, &iFin) ;
  *piFin = (bSucces) ? iFin : iDebut;
  return (bSucces);
}

int bS(int iDebut, int *piFin)
{
     //S->  K + J + V
     int iFin;
     int bSucces = bJ(iDebut, &iFin) || bV(iDebut, &iFin) || bK(iFin, &iFin) ;
     *piFin = (bSucces) ? iFin : iDebut;
     return (bSucces);
}
