speed(ford, 100).
speed(chevy, 105).
speed(dodge, 95).
speed(honda, 90).
speed(toyota, 95).
speed(nissan, 100).
speed(mazda, 105).
speed(mercedes, 110).
speed(bmw, 115).
speed(japo, 200).
speed(ferarri, 300).
speed(chinchin,20).
time(ford, 10).
time(chevy, 21).
time(dodge, 11).
time(honda, 12).
time(toyota, 11).
time(nissan, 10).
time(mazda, 9).
time(mercedes, 8).
time(bmw, 7).

distance(X, Y) :- speed(X, Speed), time(X, Time), Y is Speed * Time.


faster(X,Y) :- speed(X, SpeedX), speed(Y, SpeedY), SpeedX > SpeedY, !.
slower(X,Y) :- speed(X, SpeedX), speed(Y, SpeedY), SpeedX < SpeedY, !.
equal(X,Y) :- \+ faster(X,Y), \+ slower(X,Y), !.

german(bmw).
german(mercedes).
italian(ferarri).
european(X) :- german(X); italian(X).
japanese(nissan).
japanese(mazda).
japanese(honda).
japanese(japo).
china(chinchin).
asian(X) :- japanese(X); china(X).
american(ford).
american(chevy).
american(dodge).

quality(X) :- \+garbage(X).
garbage(X) :- american(X), !.
garbage(X):- asian(X), slower(X,Y), european(Y), Y \== ferrari, !.

fact(0,1).
fact(N,X) :- N>0, M is N-1, fact(M,Y), X is N*Y, !.

bigger(X,Y,X) :- X > Y.


qs([],[]).
qs([X],[X]).
qs([H|T],S) :- partition(H, T, L, R), qs(L, LS), qs(R, RS), append(LS, [H|RS], S), !.

partition(_, [],[],[]).
partition(P, [H|T], [H|L], R) :- H =< P, partition(P, T, L, R).
partition(P, [H|T], L, [H|R]) :- H > P, partition(P, T, L, R).

longshort('','','').
longshort(X,Long,Short) :- split_string(X, " ", "", L), longest(L, Long), shortest(L, Short), !.

