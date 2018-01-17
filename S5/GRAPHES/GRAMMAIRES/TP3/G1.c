// #include "Outil.h"
// #include "G1.h"
//
// // // Langage
// //   L -> (a^n).(b^n).(a^n), n>0
// //   L'-> (a^n).(b^n).(a+), n>0
// //
//
// // // Grammaire
// //  S -> T.C
// //  T -> aTb + ab
// //  C -> aC + a
// //
// //  Attributs
// //  S       -> T(p).C(q).(p == q)
// //  T(g)    -> T1(g) + T2(g)
// //  T1(1+p) -> AT(p)B
// //  T2(1)   -> AB
// //  C(x)    -> C1(x) + C2(x)
// //  C1(1+x) -> AC(x)
// //  C2(1)   -> A
//
// char *sMOT;
// int bGrammaireAmorceR = kF;
//
// int bA(int iDebut, int *piFin);
// int bB(int iDebut, int *piFin);
// int bS(int iDebut, int *piFin);
//
// int bC(int iDebut, int *piFin,int *paAttr);
// int bC1(int iDebut, int *piFin,int *paAttr);
// int bC2(int iDebut, int *piFin,int *paAttr);
// int bD(int iDebut, int *piFin,int *paAttr);
// int bE(int iDebut, int *piFin,int *paAttr);
// int bF(int iDebut, int *piFin,int *paAttr);
// int bG(int iDebut, int *piFin,int *paAttr);
// int bH(int iDebut, int *piFin,int *paAttr);
// int bJ(int iDebut, int *piFin,int *paAttr);
// int bK(int iDebut, int *piFin,int *paAttr);
// int bR(int iDebut, int *piFin,int *paAttr);
// int bT(int iDebut, int *piFin,int *paAttr);
// int bT1(int iDebut, int *piFin,int *paAttr);
// int bT2(int iDebut, int *piFin,int *paAttr);
// int bU(int iDebut, int *piFin,int *paAttr);
// int bV(int iDebut, int *piFin,int *paAttr);
// int bW(int iDebut, int *piFin,int *paAttr);
//
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
//       case 1: sMOT="aba";   break;
//       case 2: sMOT="a";  break;
//       case 3: sMOT="b";  break;
//       case 4: sMOT="aabbaa";  break;
//       case 5: sMOT="aaabbbaaa";  break;
//       case 6: sMOT="aaabbba";   break;
//       case 7: sMOT="aaaaaaabbbbbbbaaaa";   break;
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
// int bC(int iDebut, int *piFin,int *paAttr)
// {
//   //  C(x)    -> C1(x) + C2(x)
//   //  C1(1+x) -> AC(x)
//   //  C2(1)   -> A
//   //printf("C\n");
//      int iFin, aAttr;
//      int bSucces = bC1(iDebut, &iFin, &aAttr) || bC2(iDebut, &iFin, &aAttr);
//      *piFin = (bSucces) ? iFin : iDebut;
//      if(bSucces)
//       *paAttr = aAttr;
//      return (bSucces);
// }
//
// int bC1(int iDebut, int *piFin,int *paAttr)
// {
//   //  C(x)    -> C1(x) + C2(x)
//   //  C1(1+x) -> A.C(x)
//   //  C2(1)   -> A
//   //printf("C\n");
//      int iX, iFin, aC;
//      int bSucces = bA(iDebut, &iX) && bC(iX, &iFin, &aC);
//      *piFin = (bSucces) ? iFin : iDebut;
//      if(bSucces)
//       *paAttr = aC + 1;
//      return (bSucces);
// }
//
// int bC2(int iDebut, int *piFin,int *paAttr)
// {
//   //  C(x)    -> C1(x) + C2(x)
//   //  C1(1+x) -> AC(x)
//   //  C2(1)   -> A
//   //printf("C\n");
//      int iFin;
//      int bSucces = bA(iDebut, &iFin);
//      *piFin = (bSucces) ? iFin : iDebut;
//      if(bSucces)
//       *paAttr = 1;
//      return (bSucces);
// }
//
// // int bD(int iDebut, int *piFin,int *paAttr)
// // {
// //   //   D -> A.B.B
// //   //printf("C\n");
// //      int iX, iY, iFin;
// //      int bSucces = bA(iDebut, &iX, &paAttr) && bB(iX, &iY) && bB(iY, &iFin, &paAttr);
// //      *piFin = (bSucces) ? iFin : iDebut;
// //      if(bSucces)
// //       *paAttr = 1;
// //      return (bSucces);
// // }
// //
// // int bE(int iDebut, int *piFin,int *paAttr)
// // {
// //   //   E->  G + T
// //   //printf("R\n");
// //      int iFin;
// //      int bSucces = bG(iDebut, &iFin, &paAttr) || bT(iDebut, &iFin, &paAttr);
// //      *piFin = (bSucces) ? iFin : iDebut;
// //      if(bSucces)
// //       *paAttr = 1;
// //      return (bSucces);
// // }
// //
// // int bF(int iDebut, int *piFin,int *paAttr)
// // {
// //   //   I + A
// //   //printf("R\n");
// //      int iFin;
// //      int bSucces = bJ(iDebut, &iFin, &paAttr) || bA(iDebut, &iFin, &paAttr);
// //      *piFin = (bSucces) ? iFin : iDebut;
// //      if(bSucces)
// //       *paAttr = 1;
// //      return (bSucces);
// // }
// //
// // int bG(int iDebut, int *piFin,int *paAttr)
// // {
// //   //   G-> A.E.B
// //   //printf("H\n");
// //   int iX, iY, iFin;
// //   int bSucces = bA(iDebut, &iX, &paAttr) && bE(iX, &iY) && bB(iY, &iFin, &paAttr);
// //   *piFin = (bSucces) ? iFin : iDebut;
// //   if(bSucces)
// //    *paAttr = 1;
// //   return (bSucces);
// // }
// //
// // int bH(int iDebut, int *piFin,int *paAttr)
// // {
// //   //   H->  a.R
// //   //printf("H\n");
// //   int iX, iFin;
// //   int bSucces = bA(iDebut, &iX, &paAttr) && bR(iX, &iFin, &paAttr) ;
// //   *piFin = (bSucces) ? iFin : iDebut;
// //   if(bSucces)
// //    *paAttr = 1;
// //   return (bSucces);
// // }
// //
// // int bJ(int iDebut, int *piFin,int *paAttr)
// // {
// //   //   J-> A.F
// //   //printf("J\n");
// //   int iX, iFin;
// //   int bSucces = bA(iDebut, &iX, &paAttr) && bF(iX, &iFin, &paAttr) ;
// //   *piFin = (bSucces) ? iFin : iDebut;
// //   if(bSucces)
// //    *paAttr = 1;
// //   return (bSucces);
// // }
// //
// // int bK(int iDebut, int *piFin,int *paAttr)
// // {
// //   //K -> A.T.B
// //   //printf("K\n");
// //   int iX, iY, iFin;
// //   int bSucces = bA(iDebut, &iX, &paAttr) && bT(iX, &iY) && bB(iY, &iFin, &paAttr);
// //   *piFin = (bSucces) ? iFin : iDebut;
// //   if(bSucces)
// //    *paAttr = 1;
// //   return (bSucces);
// // }
// //
// // int bR(int iDebut, int *piFin,int *paAttr)
// // {
// //   //   R->  H + a
// //   //printf("R\n");
// //      int iFin;
// //      int bSucces = bH(iDebut, &iFin, &paAttr) || bA(iDebut, &iFin, &paAttr);
// //      *piFin = (bSucces) ? iFin : iDebut;
// //      if(bSucces)
// //       *paAttr = 1;
// //      return (bSucces);
// // }
//
//
// int bT(int iDebut, int *piFin,int *paAttr)
// {
//   //  T(g)    -> T1(g) + T2(g)
//   //printf("T\n");
//      int iFin, aT;
//      int bSucces = bT1(iDebut, &iFin, &aT) || bT2(iDebut, &iFin, &aT);
//      *piFin = (bSucces) ? iFin : iDebut;
//      if(bSucces)
//       *paAttr = aT;
//      return (bSucces);
// }
//
// int bT1(int iDebut, int *piFin,int *paAttr)
// {
//   //  T1(1+p) -> aT(p)b
//   //printf("T\n");
//      int iX, iY, iFin, aT;
//      int bSucces = bA(iDebut, &iX) && bT(iX, &iY, &aT) && bB(iY, &iFin);
//      *piFin = (bSucces) ? iFin : iDebut;
//      if(bSucces)
//       *paAttr = aT + 1;
//      return (bSucces);
// }
//
// int bT2(int iDebut, int *piFin,int *paAttr)
// {
//   //  T2(1)   -> ab
//   //printf("T\n");
//      int iX, iFin;
//      int bSucces = bA(iDebut, &iX) && bB(iX, &iFin);
//      *piFin = (bSucces) ? iFin : iDebut;
//      if(bSucces)
//       *paAttr = 1;
//      return (bSucces);
// }
//
// // int bU(int iDebut, int *piFin,int *paAttr)
// // {
// //      //U->C+D
// //      //printf("U\n");
// //      int iX, iFin;
// //      int bSucces = bC(iDebut, &iFin, &paAttr) || bD(iDebut, &iFin, &paAttr);
// //      *piFin = (bSucces) ? iFin : iDebut;
// //      if(bSucces)
// //       *paAttr = 1;
// //      return (bSucces);
// // }
// //
// // int bV(int iDebut, int *piFin,int *paAttr)
// // {
// //   //   V-> E.F.B
// //   //printf("V\n");
// //   int iX, iY, iFin;
// //   int bSucces = bE(iDebut, &iX, &paAttr) && bF(iX, &iY) && bB(iY, &iFin, &paAttr);
// //   *piFin = (bSucces) ? iFin : iDebut;
// //   if(bSucces)
// //    *paAttr = 1;
// //   return (bSucces);
// // }
//
// int bS(int iDebut, int *piFin)
// {
//   //  S -> T(p).C(q).(p == q)
//      //printf("S\n");
//      int iY, iFin;
//      int aP, aQ;
//      int bSucces = bT(iDebut, &iY, &aP) && bC(iY, &iFin, &aQ) && ( aP == aQ );
//      *piFin = (bSucces) ? iFin : iDebut;
//      return (bSucces);
// }
