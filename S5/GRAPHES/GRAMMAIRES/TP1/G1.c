// #include "Outil.h"
// #include "G1.h"
//
// //   L1 -> b.a.b
// //Gram Algébrique
//      // S->bab
// //Gram Homogène
//      // S-> B.A.B
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
// void G1AMORCER()
// {
//   bGrammaireAmorceR = kV;
// }
//
// void G1INITIALISER()
// {
//   Assert1("GrammaireINITIALISER", bGrammaireAmorceR);
// }
//
// void G1TESTER(int iTest)
// {
//   int bEngendre, iFin, bSucces;
//   //Assert1("GrammaireTESTER0", bGrammaireAmorceR);
//   //sMOT:=mot à teste selon iTest
//     switch(iTest)
//     {
//       case 0: sMOT="";   break;
//       case 1: sMOT="bab";   break;
//       case 2: sMOT="baba";  break;
//       default:Assert1("GrammaireTESTER1", 0); break;
//     }
//   bSucces = bS(0,&iFin);
//   bEngendre=bSucces && nChaineLg (sMOT) == iFin;
//   printf("%s : %s %s engendré par la grammaire décrite dans \"G1.c\".\n", (bEngendre) ? "SUCCES" : "ECHEC" , sG(sMOT), sEst(bEngendre));
// }
//
// int bA(int iDebut, int *piFin){
//      //A->a
//      int bSucces = sMOT[iDebut] == 'a';
//      *piFin = (bSucces) ? iDebut+1 : iDebut;
//      return (bSucces);
// }
//
// int bB(int iDebut, int *piFin){
//      //B->b
//      int bSucces = sMOT[iDebut] == 'b';
//      *piFin = (bSucces) ? iDebut+1 : iDebut;
//      return (bSucces);
// }
//
// int bS(int iDebut, int *piFin){
//      //S->B.A.B
//      int iX, iY, iFin;
//      int bSucces = bB(iDebut, &iX) && bA(iX, &iY) && bB(iY, &iFin);
//      *piFin = (bSucces) ? iFin : iDebut;
//      return (bSucces);
// }
