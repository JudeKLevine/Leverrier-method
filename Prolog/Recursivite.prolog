#La fonction factorielle.

fac(0,1) :- !.
fac(N,F) :- P is N-1, fac(P,G), F is G * N.

#La fonction somme

sum(0,0) :- !.
sum(1,1) :- !.
sum(N,F) :- P is N-1, fac(P,G), F is G + N.

#La fonction Fibonacci

fib(1, 1) :- !.
fib(2, 1) :- !.
fib(N, F) :-N > 2,N1 is N-1,N2 is N-2,fib(N1, F1),fib(N2, F2),F is F1+F2.

#La fonction d’Ackermann

ackermann(0,N,X) :- X is N+1.
ackermann(M, 0, X) :- M>0, M1 is M-1, ackermann(M1, 1, X).
ackermann(M, N, X) :- M>0, N>0, M1 is M-1, N1 is N-1, ackermann(M, N1, X1), ackermann(M1, X1, X).
