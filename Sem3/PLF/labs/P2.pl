% 6.a) Sa se inlocuiasca toate aparitiile unui element E cu o lista L1
% intr-o lista L
% inlocuieste(L: list, E: elem, L1: list, R: list)
% (i,i,i,o)-determinist
% L - lista initiala
% E - elementul care trebuie inlocuit
% L1 - lista cu care se inlocuieste elementul E in lista initiala L
% R - lista obtinuta dupa inlocuire
% inlocuieste([1,2,3,1,2],1,[10,10],R).
% R=[[10,10],2,3,[10,10],2]
% inlocuieste([1,2,3],4,[7,8,9],R).
% R=[1,2,3]
% inlocuieste([],5,[1,2,3],R).
% R=[]
inlocuieste([],_,_,[]).
inlocuieste([H|T],E,L1,R) :-
	H =:= E,
	adaugaL(L1,R1,R),
	inlocuieste(T,E,L1,R1).
inlocuieste([H|T],E,L1,[H|R]) :-
	H =\= E,
	inlocuieste(T,E,L1,R).
adaugaL([],L2,L2).
adaugaL([H|T],L2,[H|R]) :-
	adaugaL(T,L2,R).

% 6.b) Se da o lista formata din numere intregi si subliste.
% Sa se inlocuiasca in fiecare sublista toate aparitiile primului
% element din sublista cu o lista data
% inlocuiesteLista(L: list, L1: list, R: list)
% L - lista initiala
% L1 - lista cu care se inlocuieste
% R - rezultatul, lista obtinuta dupa inlocuiri
% (i,i,o)-determinist
% inlocuiesteLista([1,[4,1,4],3,6,[7,10,1,3,9],5,[1,1,1],7],[11,11],R).
% R=[1,[[11,11],1,[11,11]],3,6,[[11,11],10,1,3,9],5,[[11,11],[11,11],[11,
% 11]]
% inlocuiesteLista([1,2,3],[10,101],R).
% R=[1,2,3]
% inlocuiesteLista([],[1,2,3],R).
% R=[]
% Am folosit 2 functii auxiliare:
% prim(L: list, H: elem)
% L- lista
% H- primul element
% intoarce primul element dintr-o lista
% lista(L: list)
% L- lista
% verifica daca e lista
prim([],false).
prim([H|_],H).
lista([]).
lista([_|T]) :-
	lista(T).
inlocuiesteLista([],_,[]).
inlocuiesteLista([H|T],L1,[R1|R]) :-
	lista(H),
	prim(H,P1),
	inlocuieste(H,P1,L1,R1),
	inlocuiesteLista(T,L1,R).
inlocuiesteLista([H|T],L1,[H|R]) :-
	\+ lista(H),
	inlocuiesteLista(T,L1,R).











