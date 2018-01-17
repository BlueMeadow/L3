// #include "Outil.h"
// #include "G2.h"
//
// //   L1 -> ba+bab
// //Gram Algébrique
//      // S->ba.bab
// //Gram Homogène
//      // S-> T+U
//      // T-> B.A.B
//      // U->B.A
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
// int bS(int iDebut, int *piFin);
//
// void G2AMORCER()
// {
//   bGrammaireAmorceR = kV;
// }
//
// void G2INITIALISER()
// {
//   Assert1("GrammaireINITIALISER", bGrammaireAmorceR);
// }
//
// void G2TESTER(int iTest)
// {
//   int bEngendre, iFin, bSucces;
//   //Assert1("GrammaireTESTER0", bGrammaireAmorceR);
//   //sMOT:=mot à teste selon iTest
//     switch(iTest)
//     {
//       case 0: sMOT="";   break;
//       case 1: sMOT="ba";   break;
//       case 2: sMOT="baba";  break;
//       case 3: sMOT="babab";  break;
//       default:Assert1("GrammaireTESTER1", 0); break;
//     }
//   bSucces = bS(0,&iFin);
//   bEngendre=bSucces && nChaineLg (sMOT) == iFin;
//   printf("%s : %s %s engendré par la grammaire décrite dans \"G1.c\".\n", (bEngendre) ? "SUCCES" : "ECHEC" , sG(sMOT), sEst(bEngendre));
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
//      //T->B.A.B
//      int iX, iY, iFin;
//      int bSucces = bB(iDebut, &iX) && bA(iX, &iY) && bB(iY, &iFin);
//      *piFin = (bSucces) ? iFin : iDebut;
//      return (bSucces);
// }
//
// int bU(int iDebut, int *piFin)
// {
//      //U->B.A
//      int iX, iFin;
//      int bSucces = bB(iDebut, &iX) && bA(iX, &iFin);
//      *piFin = (bSucces) ? iFin : iDebut;
//      return (bSucces);
// }
//
// int bS(int iDebut, int *piFin)
// {
//      //S->T+U
//      int iFin;
//      int bSucces = bT(iDebut, &iFin) || bU(iDebut, &iFin);
//      *piFin = (bSucces) ? iFin : iDebut;
//      return (bSucces);
// }
