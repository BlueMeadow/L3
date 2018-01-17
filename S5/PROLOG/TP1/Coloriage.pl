/*
touche(1,2).
touche(1,3).
touche(1,5).
touche(1,6).

touche(2,3).
touche(2,4).
touche(2,5).
touche(2,6).

touche(3,4).
touche(3,6).

touche(5,6).
*/
couleur(rouge).
couleur(bleu).
couleur(vert).
couleur(jaune).

coloriage(A, B, C, D, E, F) :-
  couleur(A), couleur(B), couleur(C),
  couleur(D), couleur(E), couleur(F),
  A \== B, A \== C, A \== E, A \== F,
  B \== C, B \== D, B \== E, B \== F,
  C \== D, C \== F,
  E \== F.
