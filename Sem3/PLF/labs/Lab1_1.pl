% Problema 1.1
% Diferenta a doua multimi
% diferenta(L1:list, L2:list, R:list)
% (i,i,o)
% L1 = prima lista, cea din care se scade
% L2 = a doua lista
% R = lista obtinuta prin diferenta dintre L1 si L2, ce e in L1, dar nu
% si in L2
diferenta([],_,[]).
diferenta([H|T],L2,R) :-
	member(H,L2),
	diferenta(T,L2,R).

diferenta([H|T],L2,[H|R]) :-
	\+ member(H,L2),
	diferenta(T,L2,R).
% diferenta([1,2,3,4,5],[1,2],R).
% R=[3,4,5]
% diferenta([],[1,2,3],R).
% R=[]
% diferenta([1,2],[1,2],R).
% R=[]
%Problema 1.1 - fara member
%suplimentar: functia auxiliara
%apare(L: list, E: elem, R: bool)
%(i,i,o)
%L = lista in care se cauta elementul
%E = elementul care dorim sa vedem daca apare sau nu in lista
%R = adevarat/fals, ne arata daca apare sau nu E in L1
apare([],_,false).
apare([H|_],E,true) :-
	H =:= E.
apare([H|T],E,R) :-
	H =\= E,
	apare(T,E,R).
diferenta2([],_,[]).
diferenta2([H|T],L2,R) :-
	apare(L2,H,true),
	diferenta2(T,L2,R).

diferenta2([H|T],L2,[H|R]) :-
	apare(L2,H,false),
	diferenta2(T,L2,R).

% Problema 1.2
% Adauga intr-o lista dupa fiecare element par valoarea 1
% adauga(L1:list,R:list)
% (i,o)- determinist
% L = lista initiala
% R = lista returnata ( s-a adaugat 1 dupa elem pare)
adauga([],[]).
adauga([H|T],[H,1|R]) :-
	H mod 2 =:= 0,
	adauga(T,R).
adauga([H|T],[H|R]) :-
	H mod 2 =\= 0,
	adauga(T,R).
% adauga([1,2,3,4,5],R).
% R=[1,2,1,3,4,1,5]
% adauga([],R).
% R=[]
% adauga([1,3,7],R).
% R=[1,3,7]






