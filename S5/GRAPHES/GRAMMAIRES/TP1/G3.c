// #include "Outil.h"
// #include "G3.h"
//
// //   L3 -> ba(b)+
// //Gram Algébrique
//      // S->baT
//      // T-> B+U
//      // U-> B.T
// //Gram Homogène
//      // S->B.A.T
//      // T->U+B
//      // U->B.T
//      // B->b
//      // A->a
//
//
// 
// char *sMOT;
// int bGrammaireAmorceR = kF;
//
// int bA(int iDebut, int *piFin);
// int bB(int iDebut, int *piFin);
// int bT(int iDebut, int *piFin);
// int bU(int iDebut, int *piFin);
// int bS(int iDebut, int *piFin);
//
// void G3AMORCER()
// {
//   bGrammaireAmorceR = kV;
// }
//
// void G3INITIALISER()
// {
//   Assert1("GrammaireINITIALISER", bGrammaireAmorceR);
// }
//
// void G3TESTER(int iTest)
// {
//   int bEngendre, iFin, bSucces;
//   //Assert1("GrammaireTESTER0", bGrammaireAmorceR);
//   //sMOT:=mot à teste selon iTest
//     switch(iTest)
//     {
//       case 0: sMOT="";   break;
//       case 1: sMOT="bab";   break;
//       case 2: sMOT="babb";  break;
//       case 3: sMOT="babbb";  break;
//       default:Assert1("GrammaireTESTER1", 0); break;
//     }
//   bSucces = bS(0,&iFin);
//   bEngendre=bSucces && nChaineLg (sMOT) == iFin;
//   printf("%s : %s %s engendré par la grammaire décrite dans \"G3.c\".\n", (bEngendre) ? "SUCCES" : "ECHEC" , sG(sMOT), sEst(bEngendre));
// }
//
// int bA(int iDebut, int *piFin)
// {
//      //A->a
//      int bSucces = sMOT[iDebut] == 'a';
//      *piFin = (bSucces) ? iDebut+1 : iDebut;
//      return (bSucces);
// }
//
// int bB(int iDebut, int *piFin)
// {
//      //B->b
//      int bSucces = sMOT[iDebut] == 'b';
//      *piFin = (bSucces) ? iDebut+1 : iDebut;
//      return (bSucces);
// }
//
// int bT(int iDebut, int *piFin)
// {
//      //T->U+B
//      int iFin;
//      int bSucces = bU(iDebut, &iFin) || bB(iDebut, &iFin);
//      *piFin = (bSucces) ? iFin : iDebut;
//      return (bSucces);
// }
//
// int bU(int iDebut, int *piFin)
// {
//      //U->B.T
//      int iX, iFin;
//      int bSucces = bB(iDebut, &iX) && bT(iX, &iFin);
//      *piFin = (bSucces) ? iFin : iDebut;
//      return (bSucces);
// }
//
// int bS(int iDebut, int *piFin)
// {
//      //S->B.A.T
//      int iX, iY, iFin;
//      int bSucces = bB(iDebut, &iX) && bA(iX, &iY) && bT(iY, &iFin) ;
//      *piFin = (bSucces) ? iFin : iDebut;
//      return (bSucces);
// }
