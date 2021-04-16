% Opérations sur les listes

% Le code du prédicat qui renvoie le premier élément de la liste est :

head([X], X).
head(X, L):- [X|_] = L.

% Le prédicat qui ajoute un élément X au début de la liste L est :

addhead([],L,L).
addhead([X|L1],L2,[X|L3]) :- addhead(L1,L2,L3).

% Le predicat qui renvoie le dernier élément d'une liste L est :

last([X],X).
last([Y|L],X) :- Y \== X, last(L,X).

% Ajoute un element à la fin d'une liste
 
addlast(X,[ ],[X]).
addlast(X,[H|T],[H|Z]) :- addlast(X,T,Z).

% L'inverse des elements d'une liste

reverse([],[]).       % l'inverse d'une liste vide est une liste vide
reverse([X|Xs],Acc) :- reverse(Xs,Acc1), append(Acc1, [X], Acc).
