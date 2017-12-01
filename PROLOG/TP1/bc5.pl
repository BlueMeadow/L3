byCar(auckland,hamilton).
byCar(hamilton,raglan).
byCar(valmont,saarbruecken).
byCar(valmont,metz).

byTrain(metz,frankfurt).
byTrain(saarbruecken,frankfurt).
byTrain(metz,paris).
byTrain(saarbruecken,paris).

byPlane(frankfurt,bangkok).
byPlane(frankfurt,singapore).
byPlane(paris,losAngeles).
byPlane(bangkok,auckland).
byPlane(singapore,auckland).
byPlane(losAngeles,auckland).


/* ---- VOYAGE/2 ---- */

/*
voyage(X, Y):- byCar(X, Y).
voyage(X, Y):- byTrain(X, Y).
voyage(X, Y):- byPlane(X, Y).

voyage(X, Y):- byCar(X, Z), voyage(Z, Y).
voyage(X, Y):-	byTrain(X, Z), voyage(Z, Y).
voyage(X, Y):-	byPlane(X, Z), voyage(Z, Y).
*/

/* ---- VOYAGE/3 ---- */

voyage(X, Y, go(X,Y)):- byCar(X, Y).
voyage(X, Y, go(X,Y)):- byTrain(X, Y).
voyage(X, Y, go(X,Y)):- byPlane(X, Y).

voyage(X, Y, go(X, Z, G)):- byCar(X, Z), voyage(Z, Y, G).
voyage(X, Y, go(X, Z, G)):-	byTrain(X, Z), voyage(Z, Y, G).
voyage(X, Y, go(X, Z, G)):-	byPlane(X, Z), voyage(Z, Y, G).
