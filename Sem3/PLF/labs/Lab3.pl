% Se dau N puncte in plan (prin coordonatele lor).
% Se cere sa se determine toate submultimile de puncte coliniare.

% coliniare(X1:integer,Y1:integer,X2:integer,Y2:integer,X3:integer,Y3:int
% eger)
% X1 - coordonata x a primului punct
% Y1 - coordonata y a primului punct
% X2 - coordonata x a celui de al doilea punct
% Y2 - coordonata y a celui de al doilea punct
% X3 - coordonata x a celui de al treilea punct
% Y3 - coordonata y a celui de al treilea punct
% (i,i,i,i,i,i)
% verifica daca 3 puncte sunt coliniare

% candidat(L:list,E:integer)
% L - lista initiala
% E - primul element (candidatul)
% (i,o)

% submultimi(L:list,Rez:list,Col:list,F:flag)
% L - lista care se parcurge
% Rez - lista rezultat
% Col - lista in care colectam submultimea
% F - flag(0/1) -> 1 = sunt cel putin 3 elemente
% (i,o,i,i)
% genereaza submultimile

% afis(L:list)
% L - lista care se afiseaza
% (i)
% afiseaza o lista, fiecare element pe alt rand

% submultimi_aux(L:list,R:list)
% L - lista initiala
% R - o submultime a listei de puncte coliniare
% (i,o)
% genereaza o submultime

% sub(L:list)
% L - lista
% se afiseaza submultimile de puncte coliniare
% (i)

coliniare2(X, _, X, _, X, _) :- !.
coliniare2(_, Y, _, Y, _, Y) :- !.
coliniare2(X1, Y1, X2, Y2, X3, Y3) :-
    (Y2 - Y1) * (X3 - X1) =:= (Y3 - Y1) * (X2 - X1).

coliniare(X, _, X, _, X, _) :- !.
coliniare(_, Y, _, Y, _, Y) :- !.
coliniare(X1, Y1, X2, Y2, X3, Y3) :-
    X1 =\= X2, X2 =\= X3, X1 =\= X3,
    Y1 =\= Y2, Y2 =\= Y3, Y1 =\= Y3,
    P1 is (Y3 - Y1) / (Y2 - Y1),
    P2 is (X3 - X1) / (X2 - X1),
    P1 =:= P2.

candidat([H|_],H).
candidat([_|T],E):-candidat(T,E).

submultimi(_,Col,Col,1).
submultimi(L,Rez,[[X1,Y1],[X2,Y2]|T],_) :-
    candidat(L,[X,Y]),
    not(candidat([[X1,Y1],[X2,Y2]|T],[X,Y])),
    X<X1,
    Y<Y1,
    coliniare2(X, Y, X1, Y1, X2, Y2),
    submultimi(L,Rez,[[X,Y],[X1,Y1],[X2,Y2]|T],1).

afis([]):-!.
afis([H|T]):-
    write(H),
    nl,
    afis(T).

submultimi_aux(L,R):-
    candidat(L,[X1,Y1]),
    candidat(L,[X2,Y2]),
    \+ [X1,Y1]==[X2,Y2],
    Y2>Y1,
    X2>X1,
    submultimi(L,R,[[X1,Y1],[X2,Y2]],0).

len([], 0).
len([_|T], N) :-
    len(T, N1),
    N is N1 + 1.

sub(L) :-
    len(L, Len),
    Len < 3,
    write('Nu exista submultimi coliniare cu mai putin de 3 puncte'),
    nl,
    fail.
sub(L) :-
    len(L, Len),
    Len >= 3,
    findall(R, submultimi_aux(L, R), T),
    afis(T),
    fail.















