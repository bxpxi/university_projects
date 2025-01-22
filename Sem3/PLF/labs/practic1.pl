minim([],C,C).
minim([H|T],C,M) :-
	H<C,
	minim(T,H,M).
minim([H|T],C,M) :-
	H>=C,
	minim(T,C,M).

pozMinim_aux([],_,_,[]).
pozMinim_aux([H|T],M,POZ,[POZ|R]) :-
	H=:=M,
	POZ1 is POZ+1,
	pozMinim_aux(T,M,POZ1,R).
pozMinim_aux([H|T],M,POZ,R) :-
	H=\=M,
	POZ1 is POZ+1,
	pozMinim_aux(T,M,POZ1,R).

pozMinim(L,R) :-
	minim(L,10000,M),
	pozMinim_aux(L,M,1,R).
