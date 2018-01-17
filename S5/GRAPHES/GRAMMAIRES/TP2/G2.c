// #include "Outil.h"
// #include "G2.h"
//
// // //   L -> a^n.b^n.a, n>=0
// // //   L -> a^n.b^n.a + a , n > 0
//
// // //Gram Algébrique
// //   S-> T.A + A
// //   T-> A.T.B + AB
//
// // //Gram Homogène
// //   S-> V + A
// //   V-> T.A
// //   T-> K + U
// //   K-> A.T.B
// //   U-> A.B
//
// char *sMOT;
// int bGrammaireAmorceR = kF;
//
// int bA(int iDebut, int *piFin);
// int bB(int iDebut, int *piFin);
// int bH(int iDebut, int *piFin);
// int bJ(int iDebut, int *piFin);
// int bK(int iDebut, int *piFin);
// int bR(int iDebut, int *piFin);
// int bT(int iDebut, int *piFin);
// int bU(int iDebut, int *piFin);
// int bV(int iDebut, int *piFin);
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
//       case 1: sMOT="aba";   break;
//       case 2: sMOT="aabba";  break;
//       case 3: sMOT="abba";  break;
//       case 4: sMOT="aaba";  break;
//       case 5: sMOT="aabb";  break;
//       default:Assert1("GrammaireTESTER1", 0); break;
//     }
//   bSucces = bS(0,&iFin);
//   bEngendre=bSucces && nChaineLg (sMOT) == iFin;
//   printf("%s : %s %s engendré par la grammaire décrite dans \"G2.c\".\n", (bEngendre) ? "SUCCES" : "ECHEC" , sG(sMOT), sEst(bEngendre));
// }
//
// int bA(int iDebut, int *piFin)
// {
//      //A->a
//      //printf("A\n");
//      int bSucces = sMOT[iDebut] == 'a';
//      *piFin = (bSucces) ? iDebut+1 : iDebut;
//      return (bSucces);
// }
//
// int bB(int iDebut, int *piFin)
// {
//      //B->b
//      //printf("B\n");
//      int bSucces = sMOT[iDebut] == 'b';
//      *piFin = (bSucces) ? iDebut+1 : iDebut;
//      return (bSucces);
// }
//
// int bH(int iDebut, int *piFin)
// {
//   //   H->  a.R
//   //printf("H\n");
//   int iX, iFin;
//   int bSucces = bA(iDebut, &iX) && bR(iX, &iFin) ;
//   *piFin = (bSucces) ? iFin : iDebut;
//   return (bSucces);
// }
//
// int bJ(int iDebut, int *piFin)
// {
//   //   J-> b.K
//   //printf("J\n");
//   int iX, iFin;
//   int bSucces = bB(iDebut, &iX) && bK(iX, &iFin) ;
//   *piFin = (bSucces) ? iFin : iDebut;
//   return (bSucces);
// }
//
// int bK(int iDebut, int *piFin)
// {
//   //K -> A.T.B
//   //printf("K\n");
//   int iX, iY, iFin;
//   int bSucces = bA(iDebut, &iX) && bT(iX, &iY) && bB(iY, &iFin);
//   *piFin = (bSucces) ? iFin : iDebut;
//   return (bSucces);
// }
//
// int bR(int iDebut, int *piFin)
// {
//   //   R->  H + a
//   //printf("R\n");
//      int iFin;
//      int bSucces = bH(iDebut, &iFin) || bA(iDebut, &iFin);
//      *piFin = (bSucces) ? iFin : iDebut;
//      return (bSucces);
// }
//
//
// int bT(int iDebut, int *piFin)
// {
//   // T -> K + U
//   //printf("T\n");
//      int iX, iFin;
//      int bSucces = bK(iDebut, &iFin) || bU(iDebut, &iFin);
//      *piFin = (bSucces) ? iFin : iDebut;
//      return (bSucces);
// }
//
// int bU(int iDebut, int *piFin)
// {
//      //U-> A.B
//      //printf("U\n");
//      int iX, iFin;
//      int bSucces = bA(iDebut, &iX) && bB(iX, &iFin);
//      *piFin = (bSucces) ? iFin : iDebut;
//      return (bSucces);
// }
//
// int bV(int iDebut, int *piFin)
// {
//   //   V-> T.A
//   //printf("V\n");
//   int iX, iY, iFin;
//   int bSucces = bT(iDebut, &iX) && bA(iX, &iFin);
//   *piFin = (bSucces) ? iFin : iDebut;
//   return (bSucces);
// }
//
// int bS(int iDebut, int *piFin)
// {
//      //S->  V + A
//      //printf("S\n");
//      int iFin;
//      int bSucces = bV(iDebut, &iFin) || bA(iDebut, &iFin) ;
//      *piFin = (bSucces) ? iFin : iDebut;
//      return (bSucces);
// }
