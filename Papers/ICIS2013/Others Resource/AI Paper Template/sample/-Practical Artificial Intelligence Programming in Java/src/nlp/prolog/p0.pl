%% define words:

determiner(D) :-
	member(D,[the,a,an]).

noun(N) :-
	member(N,[dog, street, ball, bat, boy]).

adj(A) :-
	member(A,[fast, little, big]).

prep(P) :-
	member(P,[down, under]).

verb(V) :-
	member(V,[ran, caught, yelled, see, saw]).

%% parse noun phrases:

noun_phrase([D,N]) :-
	determiner(D),
	noun(N).

noun_phrase([N]) :-
	noun(N).

%% parse prepositional phase:

prep_phrase(PP) :-
	prep(P),
	noun_phrase(NP),
	append([P],NP,PP).

%% parse verb phrases:

verb_phrase(VP) :-
	verb(V),
	noun_phrase(NP),
	append(V,NP,VP).

verb_phrase(VP) :-
	verb(V),
	prep_phrase(PP),
	append([V],PP,VP).

verb_phrase([V]) :-
	verb(V).

%% parse entences:

sentence(S) :-
	noun_phrase(NP),
	verb_phrase(VP),
	append(NP,VP,S).

%% throw away test code:

test :- sentence([the,dog, ran]).
test1 :- sentence([the,dog, ran, down, the, street]).


