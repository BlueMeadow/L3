// #include "Outil.h"
// #include "G1.h"
//
// // //   L4 -> a( (a*).b + (b*).a)
// // //      -> a(a*)b + a(b*)a
// // //      -> (a+)b + a(1 + (b+))a
// // //      -> (a+)b + aa + a(b+)a
// // //Gram Algébrique
// //   S->  T + U + V
//
// //   T->  R.b
// //   R->  T + a
// //   T->  a.R
//
// //   U-> a.a
//
// //   V-> a.K.a
// //   K-> J + b
// //   J-> b.K
//
// // //Gram Homogène
// //   S->  V + T + U
//
// //   V-> a.K.a
// //   K-> J + b
// //   J-> b.K
//
// //   T->  R.b
// //   R->  H + a
// //   H->  a.R
//
// //   U-> a.a
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
//       case 1: sMOT="aa";   break;
//       case 2: sMOT="aab";  break;
//       case 3: sMOT="aba";  break;
//       case 4: sMOT="aaba";  break;
//       case 5: sMOT="abba";  break;
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
//   //K -> J + B
//   //printf("K\n");
//   int iFin;
//   int bSucces = bJ(iDebut, &iFin) || bB(iDebut, &iFin) ;
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
//   //   T->  R.b
//   //printf("T\n");
//      int iX, iFin;
//      int bSucces = bR(iDebut, &iX) && bB(iX, &iFin);
//      *piFin = (bSucces) ? iFin : iDebut;
//      return (bSucces);
// }
//
// int bU(int iDebut, int *piFin)
// {
//      //U-> A . A
//      //printf("U\n");
//      int iX, iFin;
//      int bSucces = bA(iDebut, &iX) && bA(iX, &iFin);
//      *piFin = (bSucces) ? iFin : iDebut;
//      return (bSucces);
// }
//
// int bV(int iDebut, int *piFin)
// {
//   //   V-> a.K.a
//   //printf("V\n");
//   int iX, iY, iFin;
//   int bSucces = bA(iDebut, &iX) && bK(iX, &iY) && bA(iY, &iFin);
//   *piFin = (bSucces) ? iFin : iDebut;
//   return (bSucces);
// }
//
// int bS(int iDebut, int *piFin)
// {
//      //S->  V + T + U
//      //printf("S\n");
//      int iFin;
//      int bSucces = bV(iDebut, &iFin) || bT(iDebut, &iFin) || bU(iFin, &iFin) ;
//      *piFin = (bSucces) ? iFin : iDebut;
//      return (bSucces);
// }
