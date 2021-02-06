%% define words:

determiner([D],determiner(D) ) :-
	member(D,[the,a,an]).

noun([N], noun(N)) :-
	member(N,[dog, street, ball, bat, boy]).

adj([A], adj(A)) :-
	member(A,[fast, little, big]).

prep([P], prep(P)) :-
	member(P,[down, under]).

verb([V], verb(V)) :-
	member(V,[ran, caught, yelled, see, saw]).

%% parse noun phrases:

noun_phrase(NP,noun_phrase(DTree,NTree)) :-
	append(D,N,NP),
	determiner(D,DTree),
	noun(N,NTree).

%% parse prepositional phase:

prep_phrase(PP, prep_phrase(PTree, NPTree)) :-
	append(P,NP,PP),
	prep(P, PTree),
	noun_phrase(NP, NPTree).

%% parse verb phrases:

verb_phrase(VP, verb_phrase(VTree, NPTree)) :-
	append(V,NP,VP),
	verb(V, VTree),
	noun_phrase(NP, NPTree).

verb_phrase(VP, verb_phrase(VTree, PPTree)) :-
	append(V,PP,VP),
	verb(V, VTree),
	prep_phrase(PP, PPTree).

verb_phrase(VP, verb_phrase(VTree)) :-
	verb(V, VTree).

%% parse entences:

sentence(S, sentence(NPTree,VPTree) ) :-
	append(NP,VP,S),
	noun_phrase(NP,NPTree),
	verb_phrase(VP,VPTree).

%% throw away test code:

%% test :- sentence([the,dog, ran], Tree), print(Tree).
%% test1 :- sentence([the,dog, ran, down, the, street], Tree), print(Tree).


