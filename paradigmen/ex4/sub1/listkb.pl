% Define list 
lst([2,4,6,8]).

% Reverse list only keep odd numbers
rev([],[]).
rev([H|T],R) :- rev(T,R1), (H mod 2 =:= 1 -> append(R1,[H],R); R = R1).

% Get list length and qube it
listLength([],0).
listLength(L,N) :- ll(L,R), N is R**3.
% Helper function to get list length
ll([], 0).
ll([_|T], R) :- ll(T, R1), R is R1 + 1.

% Get last list element and remove it
pop([],[]).
pop(L, X, Y) :- reverse(L, Lr), Lr = [X|Yr], reverse(Yr, Y).
% Helper function to reverse list
reverse([],[]).
reverse([H|T],R) :- reverse(T,R1), append(R1,[H],R).

isPrime(2).
isPrime(X) :- X > 2, indivisible(X,2).
indivisible(X,Y) :- Y*Y>X ; X mod Y =\= 0, Y1 = Y+1, indivisible(X,Y1), !. 


/*
:- initialization(main).
main :- 
 lst(X),
 listLength(X,Y),
 rev([1,2,3,4,5,6,7,8],R),
 pop([1,2,3,4,5,6,7,8],X1,Y2),
 rev([1,2,3,4],R2), pop(R2,X4,Y5).
 */
