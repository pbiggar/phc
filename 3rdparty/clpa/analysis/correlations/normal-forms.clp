%%
% Authors:
%   Isil Dillig    <isil@stanford.edu>
%   Thomas Dillig  <tdillig@stanford.edu>
%%

% Library for converting guards to normal forms.

import "../memory/scalar.clp".
import "../memory/scalar_sat.clp".
import "./scalar-helpers.clp".


% Do +br_abit_enable if you don't want
% br_abit's to be discarded by this analysis.
predicate br_abit_enable().


% By default, theis analysis discard leaf guards
% containing integer arithmetic. 
% Add this predicate to override this behavior.
predicate arithmetic_ops_enable().


% ---------------------------------------------------
predicate leaf_pred(in G:g_guard).

leaf_pred(G) :- (#bool_g(_,G); #id_g(_,G)).

% -------------------------------------------------

% G is a literal. (i.e either an atomic predicate or a
% negated atomic predicate.
predicate literal(in G:g_guard).

literal(G) :- leaf_pred(G).
literal(G) :- #not(NG, G), leaf_pred(NG).


% ---------------------------------------------------



predicate negations_in(in InG:g_guard, out OutG:g_guard). 


% G, G is atomic.		 	
negations_in(InG, InG) :-
	leaf_pred(InG).

% ~G, G is atomic.
negations_in(InG, InG) :-
	#not(G,InG), leaf_pred(G).

% ~~G: get rid of double negations.
negations_in(InG, OutG):-
	#not(NegG, InG),
	#not(OutG, NegG).


% ~(G1&G2)<=>~G1||~G2 
negations_in(InG, OutG) :- 
	#not(G, InG), #and(G1, G2, G),
	#not(G1, NG1), #not(G2, NG2),
	negations_in(NG1, NewG1),
	negations_in(NG2, NewG2),
	#or(NewG1, NewG2, OutG).

% ~(G1||G2)<=>~G1&&~G2 
negations_in(InG, OutG) :- 
	#not(G, InG), #or(G1, G2, G),
	#not(G1, NG1), #not(G2, NG2),
	negations_in(NG1, NewG1),
	negations_in(NG2, NewG2),
	#and(NewG1, NewG2, OutG).	

% G1&G2
negations_in(InG, OutG) :-
	#and(G1, G2, InG),
	negations_in(G1, NewG1),
	negations_in(G2, NewG2),
	#and(NewG1, NewG2, OutG).

% G1||G2
negations_in(InG, OutG) :-
	#or(G1, G2, InG),
	negations_in(G1, NewG1),
	negations_in(G2, NewG2),
	#or(NewG1, NewG2, OutG).


% --------------------------------------------

predicate get_literals(in G:g_guard, out list[g_guard]).

get_literals(G, List) :-
	negations_in(G, NewG),
	literals(NewG, List).

predicate literals(in G:g_guard, out list[g_guard]).


% G, G is atomic.			
literals(InG, [InG]) :-
	leaf_pred(InG).

% ~G, G is atomic.
literals(InG, [InG]) :-
	#not(G,InG), leaf_pred(G).

% G1&G2
literals(InG, Literals) :-
	#and(G1, G2, InG),
	literals(G1, Literals1),
	literals(G2, Literals2),
	list_append(Literals1, Literals2, Literals).
% G1||G2
literals(InG, Literals) :-
	#or(G1, G2, InG),
	literals(G1, Literals1),
	literals(G2, Literals2),
	list_append(Literals1, Literals2, Literals).



% ---------------------------------------------------

% The list of positive literals that occur in a guard. 
% Assumes the input guard has negations pushed in.
predicate positive_literals(in g_guard, out list[g_guard])
	succeeds [once].

positive_literals(G, Pos) :-
	#and(G1, G2, G),
	positive_literals(G1, Pos1),
	positive_literals(G2, Pos2),
	list_append(Pos1, Pos2, Pos).

positive_literals(G, Pos) :-
	#or(G1, G2, G),
	positive_literals(G1, Pos1),
	positive_literals(G2, Pos2),
	list_append(Pos1, Pos2, Pos).

positive_literals(G, [G]) :-
	~#bool_g(_, G),
	leaf_pred(G).

positive_literals(G, []) :-
	#not(_, G).

positive_literals(G, []) :-
	#bool_g(_, G).


% -----------------------------------------------

% The list of negative literals that occur in a guard.
% The list of negative literals that occur in a guard.
predicate negative_literals(in g_guard, out list[g_guard]) 
	succeeds [once].


negative_literals(G, Neg) :-
	#and(G1, G2, G),
	negative_literals(G1, Neg1),
	negative_literals(G2, Neg2),
	list_append(Neg1, Neg2, Neg).

negative_literals(G, Neg) :-
	#or(G1, G2, G),
	negative_literals(G1, Neg1),
	negative_literals(G2, Neg2),
	list_append(Neg1, Neg2, Neg).

negative_literals(G, []) :-
	leaf_pred(G).

negative_literals(G, [NegG]) :-
	#not(NegG, G),
	~#bool_g(_, NegG).

negative_literals(G, []) :-
	#not(NegG, G),
	#bool_g(_, NegG).





% -------------------------------------------------

% In guard G, LeafG occurs in mixed phases.
% Assumes that negations are pushed in in G.
predicate mixed_phase(in G:g_guard, in LeafG:g_guard).

mixed_phase(G, Leaf):-
	negative_literals(G, Neg),
	positive_literals(G, Pos),
	list_mem(Neg, Leaf),
	list_mem(Pos, Leaf).


% ----------------------------------------------
% Compute the strongest necessary condition of G
% not containing unknown predicate Pred.
predicate remove_pred_nc(in G:g_guard, in Pred:g_guard, 
	out NewG:g_guard) succeeds [once].

% guard unsat; just return false.
remove_pred_nc(G, Pred, False) :-
	~guard_sat(G),
	#bool_g(false, False).

% mixed phase - we recurse on or parts.
remove_pred_nc(G, Pred, NewG) :-
	guard_sat(G),
	mixed_phase(G, Pred),
	#or(G1, G2, G),
	remove_pred_nc(G1, Pred, NewG1),
	remove_pred_nc(G2, Pred, NewG2),	
	#or(NewG1, NewG2, NewG).

% mixed phase without an "or"; do Boole's method
remove_pred_nc(G, Pred, NewG) :-
	guard_sat(G),
	mixed_phase(G, Pred),
	~#or(_, _, G),
	#bool_g(true, True),
	replace_subguard(G, Pred, True, NewG1),
	#bool_g(false, False),
	replace_subguard(G, Pred, False, NewG2),
	#or(NewG1, NewG2, NewG).

% only positive
remove_pred_nc(G, Pred, NewG) :-
	guard_sat(G),
	~mixed_phase(G, Pred),
	positive_literals(G, Pos),
	list_mem(Pos, Pred),	
	#bool_g(true, True),
	replace_subguard(G, Pred, True, NewG).
	


% only negative
remove_pred_nc(G, Pred, NewG) :-
	guard_sat(G),
	~mixed_phase(G, Pred),
	negative_literals(G, Neg),
	list_mem(Neg, Pred),	
	#bool_g(false, False),
	replace_subguard(G, Pred, False, NewG).	

%  pred has already been wiped out.
% E.g. this can happen when we have something of the form
% p || q, and replacing p by true caused q to disappear 
% from the formula.
remove_pred_nc(G, Pred, G) :-
	guard_sat(G),
	~mixed_phase(G, Pred),
	negative_literals(G, Neg),
	positive_literals(G, Pos),
	~list_mem(Neg, Pred),
	~list_mem(Pos, Pred).

% -------------------------------------------

% Compute the weakest sufficient condition of G
% not containing unknown predicate Pred.
predicate remove_pred_sc(in G:g_guard, in Pred:g_guard, out NewG:g_guard).

% Guard is tautological.
predicate tautology(in g_guard).

tautology(G) :- 
	#not(G, NG), ~guard_sat(NG).

% guard is tautological; return true.
remove_pred_sc(G, Pred, True) :-
	tautology(G),
	#bool_g(true, True).

% mixed phase - we recurse on conjuncts.
remove_pred_sc(G, Pred, NewG) :-
	~tautology(G),
	mixed_phase(G, Pred),
	#and(G1, G2, G),
	remove_pred_sc(G1, Pred, NewG1),
	remove_pred_sc(G2, Pred, NewG2),	
	#and(NewG1, NewG2, NewG).

% mixed phase without an "and"; do Boole's method
remove_pred_sc(G, Pred, NewG) :-
	~tautology(G),
	mixed_phase(G, Pred),
	~#and(_, _, G),
	#bool_g(true, True),
	replace_subguard(G, Pred, True, NewG1),
	#bool_g(false, False),
	replace_subguard(G, Pred, False, NewG2),
	#and(NewG1, NewG2, NewG).

% only positive
remove_pred_sc(G, Pred, NewG) :-
	~tautology(G),
	~mixed_phase(G, Pred),
	positive_literals(G, Pos),
	list_mem(Pos, Pred),	
	#bool_g(false, False),
	replace_subguard(G, Pred, False, NewG).


% only negative
remove_pred_sc(G, Pred, NewG) :-
	~tautology(G),
	~mixed_phase(G, Pred),
	negative_literals(G, Neg),
	list_mem(Neg, Pred),	
	#bool_g(true, True),
	replace_subguard(G, Pred, True, NewG).

%  pred has already been wiped out.
% E.g. this can happen when we have something of the form
% p || q, and replacing p by true caused q to disappear 
% from the formula.
remove_pred_sc(G, Pred, G) :-
	~tautology(G),
	~mixed_phase(G, Pred),
	negative_literals(G, Neg),
	positive_literals(G, Pos),
	~list_mem(Neg, Pred),
	~list_mem(Pos, Pred).

% --------------------------------------

% The input trace doesn't contain any fake fields.
predicate contains_fake_field(in t_trace).

contains_fake_field(drf{T}) :- contains_fake_field(T).
contains_fake_field(fld{T, F, _}) :-
	(str_sub(F, 0, 1, "$");
	contains_fake_field(T)).
contains_fake_field(rfld{T, F, _}) :-
	(str_sub(F, 0, 1, "$");
	contains_fake_field(T)).
contains_fake_field(index{T, _}) :-
	contains_fake_field(T).

% ---------------------------------------

predicate legal_binop(in OP: scalar_binop).

legal_binop(OP) :- arithmetic_ops_enable().

legal_binop(OP) :- 
	~arithmetic_ops_enable(),
	(
	  equal(OP, sb_or)
	;
	  equal(OP, sb_and)
	;
	  equal(OP, sb_xor)
	).

% -------------------------------------------
% This is coming from guard-bounds.clp.
predicate return_temps(out list[t_trace]).

% ----------------------------------------

% Contains a vr_t with trace whose
% root is an imprecise temp.
predicate imprecise_temp_vecrep(in g_vecrep, in bool).

% Temps are not externally visible
% if they don't correspond to a function for
% which a return value summary has been computed.
  imprecise_temp_vecrep(VR, false) :-
	equal(VR, vr_t{T}),
	trace_root(T, R),
	equal(R, temp{_, _}),
	return_temps(RetTemps),
	~list_mem(RetTemps, drf{root{R}}).

% Temps are not externally visible
% if we haven't computed a return summary.
imprecise_temp_vecrep(VR, false) :-
	equal(VR, vr_t{T}),
	trace_root(T, temp{_,_}),
	 ~return_temps(_).

imprecise_temp_vecrep(VR, true) :-
	equal(VR, vr_t{T}),
	trace_root(T, temp{_,_}).


% --------------------------------------
predicate imprecise_vecrep(in g_vecrep, in bool).

% Soft traces are necessarily imprecise.
imprecise_vecrep(VR, B) :-
	equal(VR, vr_st{_, _,_}).

% Locals aren't externally visible.
imprecise_vecrep(VR, B) :-
	equal(VR, vr_t{T}),
	trace_root(T, local{_}).


imprecise_vecrep(VR, B) :-
 	imprecise_temp_vecrep(VR, B).

% Discard traces that have hidden fields,
% i.e. those that have fields that start
% with a $ sign.
imprecise_vecrep(VR, B) :-
	~imprecise_temp_vecrep(VR, B),
	equal(VR, vr_t{T}),
	~trace_root(T, local{_}),
	contains_fake_field(T).


% The rest is inherently imprecise.
imprecise_vecrep(VR, B) :-
	equal(VR, vr_i{_, _}).

imprecise_vecrep(VR, B) :-
	equal(VR, vr_c{_,_, _}).


imprecise_vecrep(VR, B) :-
	equal(VR, vr_instscalar{_,_, _}).

imprecise_vecrep(VR, B) :-
	equal(VR, vr_u{_}).

% -----------------------------------------


% The input scalar has inherent imprecision and cannot be 
% mapped at the callsite.
predicate imprecise_scalar(in scalar, in bool).

imprecise_scalar(S, B) :-
	equal(S, s_unconstrained{VR, _}),
	imprecise_vecrep(VR, B).

imprecise_scalar(S, B) :-
	equal(S, s_cast{CastS, _}),
	imprecise_scalar(CastS, B).

imprecise_scalar(S, B) :-
	equal(S, s_guard{_}).

imprecise_scalar(S, B) :-
	equal(S, s_unop{_, S}),
	imprecise_scalar(S, B).

imprecise_scalar(S, B) :-
	equal(S, s_binop{OP, S1, S2}),
	legal_binop(OP),
	(imprecise_scalar(S1, B); imprecise_scalar(S2,B)).

imprecise_scalar(S, B) :-
	equal(S, s_binop{OP, _, _}),
	~legal_binop(OP).


% -------------------------------------------
% Remove all "junk", i.e. never outside the caller
% visible predicates from the guard.


predicate remove_nondeterministic_preds(in g_guard, out g_guard).


% add all non-deterministic leafes to list
predicate list_nondeterministic_preds(in g_guard, in bool,
	 out list[g_guard]) succeeds [once] .

list_nondeterministic_preds(G,B, ListRes) :-
	#and(G1, G2, G),
	list_nondeterministic_preds(G1, B, List1),
	list_nondeterministic_preds(G2, B, List2),
	list_append(List1, List2, ListRes).

list_nondeterministic_preds(G, B, ListRes) :-
	#or(G1, G2, G),
	list_nondeterministic_preds(G1,B, List1),
	list_nondeterministic_preds(G2, B, List2),
	list_append(List1, List2, ListRes).

list_nondeterministic_preds(G, B, ListRes) :-
	#not(G1, G),
	list_nondeterministic_preds(G1,B, ListRes).


list_nondeterministic_preds(G, B, []) :- 
	#bool_g(_,G).

% Bases cases:
% 1. br_abit is considered deterministic
% if the br_abit_enable flag is on; 
% otherwise non-deterministic.
list_nondeterministic_preds(G,B, []) :- 
	#id_g(IG,G),
	equal(IG, br_abit{_}),
	br_abit_enable().

list_nondeterministic_preds(G, B, [G]) :- 
	#id_g(IG,G),
	equal(IG, br_abit{_}),
	~br_abit_enable().

% br_ioverflow is deterministic if the scalar associated 
% with is is precise.
list_nondeterministic_preds(G, B, List) :- 
	#id_g(IG,G),
	equal(IG, br_ioverflow{Sc}),
	(
	  imprecise_scalar(Sc, B), List = [G];
	  ~imprecise_scalar(Sc, B), List = []
	).

% 2. Guard containing br_cmp is non-deterministic if
% any of the scalars contained within are non-deterministic.
list_nondeterministic_preds(G, B, List) :- 
	#id_g(br_cmp{SC},G),
	equal(SC, sc_eqz{S}),
	(
	  (imprecise_scalar(S, B), List=[G]);
	  (~imprecise_scalar(S, B),List=[])
	).

list_nondeterministic_preds(G, B, List) :- 
	#id_g(br_cmp{SC},G),
	equal(SC, sc{_, S1, S2}),
	(
	  (imprecise_scalar(S1, B); imprecise_scalar(S2, B)), List = [G];
	  ~(imprecise_scalar(S1, B); imprecise_scalar(S2, B)), List= []
	).

% -------------------------------------------------
% Find the strongest necessary cond for a guard not 
% containing any of the predicates in the list.
predicate apply_bool_snc(in g_guard,  in list[g_guard], out g_guard)
	 succeeds [once].

apply_bool_snc(G, [], G) :- .


apply_bool_snc(G, [Hd|Tl] , SNC) :-
	remove_pred_nc(G, Hd, NC),
	apply_bool_snc(NC, Tl, SNC).

% -----------------------------------------------
% Find the weakest sufficient cond for a guard not 
% containing any of the predicates in the list.
predicate apply_bool_wsc(in g_guard, in list[g_guard], out g_guard).

apply_bool_wsc(G, [], G) :- .


apply_bool_wsc(G,[Hd|Tl] , WSC) :-
	remove_pred_sc(G, Hd, SC),
	apply_bool_wsc(SC, Tl, WSC).

% -------------------------------------------------

% Remove imprecise parts of a guard by applying optimized Boole.
predicate bool_snc(in g_guard, in bool, out g_guard) succeeds [once].

bool_snc(G, TempOption, SNC) :-
	list_nondeterministic_preds(G,TempOption,  List),
	apply_bool_snc(G, List, SNC).

% ----------------------------------------------

% Remove imprecise parts of a guard by applying optimized Boole.
predicate bool_wsc(in g_guard, in bool, out g_guard) succeeds [once].

bool_wsc(G, TempOption, WSC) :-
	list_nondeterministic_preds(G, TempOption, List),
	apply_bool_wsc(G, List, WSC). 


% --------------------------------------------------

predicate no_or(in G:g_guard).

no_or(G):- literal(G).

no_or(NG):- #not(G, NG), literal(G).

no_or(G):- #and(G1, G2, G), no_or(G1), no_or(G2).

% ------------------------------------------------
predicate no_and(in G:g_guard).

no_and(G):- literal(G).

no_and(NG):- #not(G, NG), literal(G).

no_and(G):- #or(G1, G2, G), no_and(G1), no_and(G2).
% -------------------------------------------------


predicate not_contradicted_in_list(in G:t_pair[g_guard, bool], 
				in list[t_pair[g_guard, bool]]).

not_contradicted_in_list(G, [Hd|Tl]):-
	G = pair{L, false},
	~(Hd = pair{L, true}),
	not_contradicted_in_list(G, Tl).

not_contradicted_in_list(G, [Hd|Tl]):-
	G = pair{L, true},
	~(Hd = pair{L, false}),
	not_contradicted_in_list(G, Tl).

not_contradicted_in_list(G, []):-.

predicate no_contradicting_literals(in list[t_pair[g_guard, bool]]).

no_contradicting_literals([Hd|Tl]):-
	not_contradicted_in_list(Hd, Tl),
	no_contradicting_literals(Tl).

no_contradicting_literals([]):-.

% -------------------------------------------------

% Here, we convert G to DNF/ CNF form using our own
% types in order to bypass the normal simplification
% that is eagerly applied to all guards.

% -------------------------------------------
% ID is guard, bool indicates phase
type t_df = list[t_pair[g_guard, bool]].
type t_cf = list[t_pair[g_guard, bool]].

type t_cnf = list[t_df].

type t_dnf = list[t_cf].


% --------------------------------------------------------

predicate inner_list_product(in list[t_pair[g_guard, bool]],
			in list[list[t_pair[g_guard, bool]]], 
			out list[list[t_pair[g_guard, bool]]]).

inner_list_product(List1, [], []) :- .
inner_list_product(List1, [Hd|Tl], Result) :- 
	list_append(List1, Hd, Result1),
	inner_list_product(List1, Tl, Result2),
	list_append([Result1], Result2, Result).
	

% Takes the cartesian product of two lists of lists.
predicate cross_product_lists(in list[list[t_pair[g_guard, bool]]],
			in list[list[t_pair[g_guard, bool]]], 
			out list[list[t_pair[g_guard, bool]]]).




cross_product_lists([Hd|Tl], List2, Result) :-
	inner_list_product(Hd, List2, Result1),
	cross_product_lists(Tl, List2, Result2),
	list_append(Result1, Result2, Result).


cross_product_lists([], List2, []) :- .





% ----------------------------------------------------------

predicate construct_dnf(in G:g_guard, out DNF:t_dnf) succeeds [once].

% Base case 1: G = literal
construct_dnf(G, DNF):-
	leaf_pred(G),
	DNF = [[pair{G, true}]].

% Base case 2: G = ~literal
construct_dnf(Gnot, DNF):-
	#not(G, Gnot),
	leaf_pred(G),
	DNF = [[pair{G, false}]].


% Case 1: G = G1 || G2
% Convert G1 and G2 to DNF and combine.
construct_dnf(G, DNF):-
	#or(G1, G2, G), 
	construct_dnf(G1, DNF1),
	construct_dnf(G2, DNF2),
	list_append(DNF1, DNF2, DNF).

% Case 2: G1 & G2 (Either G1 or G2 has an &)
% Take the cartesian product of the two lists 
% after converting each to DNF.
construct_dnf(G, DNF):-
	#and(G1, G2, G),
	(	
	~no_or(G1);
	~no_or(G2)
	),
	construct_dnf(G1, DNFG1),
	construct_dnf(G2, DNFG2),
	cross_product_lists(DNFG1, DNFG2, DNF).


% Case 3: G = NoOR1 & NoOR2 => [[NoOR1, NoOR2]]
% No contradicting literals in the resulting clause.
construct_dnf(G, DNF):-
	#and(G1, G2, G),
	no_or(G1),
	no_or(G2),
	construct_dnf(G1, DNFG1),
	construct_dnf(G2, DNFG2),
	DNFG1=[L1],
	DNFG2=[L2],
	list_append(L1, L2, L12),
	no_contradicting_literals(L12),
	DNF = [L12].

% Case 4: G = NoOR1 & NoOR2 => [[NoOR1, NoOR2]]
% If there are contradicting literals, drop that clause.
construct_dnf(G, DNF):-
	#and(G1, G2, G),
	no_or(G1),
	no_or(G2),
	construct_dnf(G1, DNFG1),
	construct_dnf(G2, DNFG2),
	DNFG1=[L1],
	DNFG2=[L2],
	list_append(L1, L2, L12),
	~no_contradicting_literals(L12),
	#bool_g(false, False),
	DNF = [[pair{False, true}]].


% ----------------------------------------------------------

predicate construct_cnf(in G:g_guard, out DNF:t_cnf) succeeds [once].

% Base case 1: G = literal
construct_cnf(G, CNF):-
	leaf_pred(G),
	CNF = [[pair{G, true}]].

% Base case 2: G = ~literal
construct_cnf(Gnot, CNF):-
	#not(G, Gnot),
	leaf_pred(G),
	CNF = [[pair{G, false}]].


% Case 1: G = G1 && G2
% Convert G1 and G2 to CNF and combine.
construct_cnf(G, CNF):-
	#and(G1, G2, G), 
	construct_cnf(G1, CNF1),
	construct_cnf(G2, CNF2),
	list_append(CNF1, CNF2, CNF).

% Case 2: G1 || G2 (Either G1 or G2 has an &)
% Take the cartesian product of the two lists 
% after converting each to CNF.
construct_cnf(G, CNF):-
	#or(G1, G2, G),
	(	
	~no_and(G1);
	~no_and(G2)
	),
	construct_cnf(G1, CNFG1),
	construct_cnf(G2, CNFG2),
	cross_product_lists(CNFG1, CNFG2, CNF).


% Case 3: G = NoAND1 || NoAND2 => [[NoAND1, NoAND2]]
% No contradicting literals in the resulting clause
% which means we know there is no tautology.
construct_cnf(G, CNF):-
	#or(G1, G2, G),
	no_and(G1),
	no_and(G2),
	construct_cnf(G1, CNFG1),
	construct_cnf(G2, CNFG2),
	CNFG1=[L1],
	CNFG2=[L2],
	list_append(L1, L2, L12),
	no_contradicting_literals(L12),
	CNF = [L12].

% Case 4: G = NoAND1 || NoAND2 => [[NoAND1, NoAND2]]
% If there are contradicting literals, drop that clause
% because it is true.
construct_cnf(G, CNF):-
	#or(G1, G2, G),
	no_and(G1),
	no_and(G2),
	construct_cnf(G1, CNFG1),
	construct_cnf(G2, CNFG2),
	CNFG1=[L1],
	CNFG2=[L2],
	list_append(L1, L2, L12),
	~no_contradicting_literals(L12),
	#bool_g(true, True),
	CNF = [[pair{True, true}]].


% --------------------------------------------------
% Priting functions

predicate phase_string(in bool, out string) succeeds [once].

phase_string(true, "+") :-.
phase_string(false, "-") :-.	


predicate cf_string(in CF:t_cf, out string) succeeds [once].

cf_string([pair{G, Phase}|Tl], Res):-
	guard_string(G, Gs),
	phase_string(Phase, Ps),
	str_cat4(Ps, "(", Gs, ")", Hds),
	cf_string(Tl, Tls),
	str_cat3(Hds, ", ", Tls, Res).

cf_string([], ""):-.



predicate dnf_string(in DNF:t_dnf, out string) succeeds [once].

dnf_string([Hd|Tl], Res):-
	cf_string(Hd, Hds),
	dnf_string(Tl, Tls),
	str_cat4("[", Hds, "], ", Tls, Res).

dnf_string([], ""):-.

% --------------------------------------------------
% Routines for performing replacement of DNF/CNF
% leafs.

% Replaces all occurences of +Leaf (i.e. non-negated)
% with Refined in DNF.
predicate refine_leaf_dnf_positive(in DNF:t_dnf, in Leaf:g_guard,
			in Refined:g_guard, out RefinedDNF:t_dnf)
			succeeds [once]. 

% Replaces all occurences of -Leaf (i.e. negated)
% with Refined in DNF.
predicate refine_leaf_dnf_negative(in DNF:t_dnf, in Leaf:g_guard,
			in Refined:g_guard, out RefinedDNF:t_dnf)
			succeeds [once].


predicate refine_leaf_cf_positive(in CF:t_cf, in Leaf:g_guard,
			in Refined:g_guard, out RefinedCF:t_cf)
			succeeds [once].


predicate refine_leaf_cf_negative(in CF:t_cf, in Leaf:g_guard,
			in Refined:g_guard, out RefinedCF:t_cf)
			succeeds [once].

% -------------------------------------------------------------
% Replaces all occurences of +Leaf (i.e. non-negated)
% with Refined in CNF.
predicate refine_leaf_cnf_positive(in CNF:t_dnf, in Leaf:g_guard,
			in Refined:g_guard, out RefinedCNF:t_dnf)
			succeeds [once].

predicate refine_leaf_cnf_negative(in CNF:t_cnf, in Leaf:g_guard,
			in Refined:g_guard, out RefinedCNF:t_cnf)
			succeeds [once].


predicate refine_leaf_df_positive(in DF:t_df, in Leaf:g_guard,
			in Refined:g_guard, out RefinedDF:t_df)
			succeeds [once].


predicate refine_leaf_df_negative(in DF:t_df, in Leaf:g_guard,
			in Refined:g_guard, out RefinedDF:t_df)
			succeeds [once].

% -----------------------------------------------------------

%Base case
refine_leaf_dnf_positive([], Leaf, Refined, []):-.

%Inductive steps
refine_leaf_dnf_positive([Hd|Tl], Leaf, Refined, Res):-	
	refine_leaf_cf_positive(Hd, Leaf, Refined, HdRef),
	refine_leaf_dnf_positive(Tl, Leaf, Refined, TlRef),
	list_append([HdRef], TlRef, Res).
% -------------------------------------------------------------

%Base case
refine_leaf_cnf_positive([], Leaf, Refined, []):-.

%Inductive steps
refine_leaf_cnf_positive([Hd|Tl], Leaf, Refined, Res):-	
	refine_leaf_df_positive(Hd, Leaf, Refined, HdRef),
	refine_leaf_cnf_positive(Tl, Leaf, Refined, TlRef),
	list_append([HdRef], TlRef, Res).

% -------------------------------------------------------
refine_leaf_cf_positive([], Leaf, Refined, []):-.

%We substitute
refine_leaf_cf_positive([pair{G, Phase}|Tl], Leaf, Refined, Res):-
	equal(Phase, true),
	equal(G, Leaf),
	NewHd = pair{Refined, true},
	refine_leaf_cf_positive(Tl, Leaf, Refined, NewTl),
	list_append([NewHd], NewTl, Res).

% We do not substitute (phase mismatch)
refine_leaf_cf_positive([pair{G, Phase}|Tl], Leaf, Refined, Res):-
	equal(Phase, false),
	refine_leaf_cf_positive(Tl, Leaf, Refined, NewTl),
	NewHd = pair{G, Phase},
	list_append([NewHd], NewTl, Res).

% We do not substitute (not the same thing)
refine_leaf_cf_positive([pair{G, Phase}|Tl], Leaf, Refined, Res):-
	equal(Phase, true),
	~equal(G, Leaf),
	refine_leaf_cf_positive(Tl, Leaf, Refined, NewTl),
	NewHd = pair{G, Phase},
	list_append([NewHd], NewTl, Res).
%- -------------------------------------------------------
refine_leaf_df_positive([], Leaf, Refined, []):-.

%We substitute
refine_leaf_df_positive([pair{G, Phase}|Tl], Leaf, Refined, Res):-
	equal(Phase, true),
	equal(G, Leaf),
	NewHd = pair{Refined, true},
	refine_leaf_df_positive(Tl, Leaf, Refined, NewTl),
	list_append([NewHd], NewTl, Res).

% We do not substitute (phase mismatch)
refine_leaf_df_positive([pair{G, Phase}|Tl], Leaf, Refined, Res):-
	equal(Phase, false),
	refine_leaf_df_positive(Tl, Leaf, Refined, NewTl),
	NewHd = pair{G, Phase},
	list_append([NewHd], NewTl, Res).

% We do not substitute (not the same thing)
refine_leaf_df_positive([pair{G, Phase}|Tl], Leaf, Refined, Res):-
	equal(Phase, true),
	~equal(G, Leaf),
	refine_leaf_df_positive(Tl, Leaf, Refined, NewTl),
	NewHd = pair{G, Phase},
	list_append([NewHd], NewTl, Res).
% -------------------------------
%Base case
refine_leaf_dnf_negative([], Leaf, Refined, []):-.

%Inductive steps
refine_leaf_dnf_negative([Hd|Tl], Leaf, Refined, Res):-	
	refine_leaf_cf_negative(Hd, Leaf, Refined, HdRef),
	refine_leaf_dnf_negative(Tl, Leaf, Refined, TlRef),
	list_append([HdRef], TlRef, Res).

% ---------------------------------

%Base case
refine_leaf_cnf_negative([], Leaf, Refined, []):-.

%Inductive steps
refine_leaf_cnf_negative([Hd|Tl], Leaf, Refined, Res):-	
	refine_leaf_df_negative(Hd, Leaf, Refined, HdRef),
	refine_leaf_cnf_negative(Tl, Leaf, Refined, TlRef),
	list_append([HdRef], TlRef, Res).

% ---------------------------------

refine_leaf_cf_negative([], Leaf, Refined, []):-.

%We substitute
refine_leaf_cf_negative([pair{G, Phase}|Tl], Leaf, Refined, Res):-
	equal(Phase, false),
	equal(G, Leaf),
	NewHd = pair{Refined, false},
	refine_leaf_cf_negative(Tl, Leaf, Refined, NewTl),
	list_append([NewHd], NewTl, Res).

% We do not substitute (phase mismatch)
refine_leaf_cf_negative([pair{G, Phase}|Tl], Leaf, Refined, Res):-
	equal(Phase, true),
	refine_leaf_cf_negative(Tl, Leaf, Refined, NewTl),
	NewHd = pair{G, Phase},
	list_append([NewHd], NewTl, Res).

% We do not substitute (not the same thing)
refine_leaf_cf_negative([pair{G, Phase}|Tl], Leaf, Refined, Res):-
	equal(Phase, false),
	~equal(G, Leaf),
	refine_leaf_cf_negative(Tl, Leaf, Refined, NewTl),
	NewHd = pair{G, Phase},
	list_append([NewHd], NewTl, Res).


% ---------------------------------

refine_leaf_df_negative([], Leaf, Refined, []):-.

%We substitute
refine_leaf_df_negative([pair{G, Phase}|Tl], Leaf, Refined, Res):-
	equal(Phase, false),
	equal(G, Leaf),
	NewHd = pair{Refined, false},
	refine_leaf_df_negative(Tl, Leaf, Refined, NewTl),
	list_append([NewHd], NewTl, Res).

% We do not substitute (phase mismatch)
refine_leaf_df_negative([pair{G, Phase}|Tl], Leaf, Refined, Res):-
	equal(Phase, true),
	refine_leaf_df_negative(Tl, Leaf, Refined, NewTl),
	NewHd = pair{G, Phase},
	list_append([NewHd], NewTl, Res).

% We do not substitute (not the same thing)
refine_leaf_df_negative([pair{G, Phase}|Tl], Leaf, Refined, Res):-
	equal(Phase, false),
	~equal(G, Leaf),
	refine_leaf_df_negative(Tl, Leaf, Refined, NewTl),
	NewHd = pair{G, Phase},
	list_append([NewHd], NewTl, Res).


% --------------------------------------------
predicate dnf_size(in DNF:t_dnf, out int) succeeds [once].

dnf_size([], 0):- .

dnf_size([Hd|Tl], S) :-
	cf_size(Hd, S1),
	dnf_size(Tl, S2),
	int_add(S1, S2, S).

predicate cf_size(in CF:t_cf, out int) succeeds [once].

cf_size([], 0):- .

cf_size([_|Tl], S) :-
	cf_size(Tl, S2),
	int_add(1, S2, S).
% --------------------------------------------
predicate cnf_size(in CNF:t_cnf, out int) succeeds [once].

cnf_size([], 0):- .

cnf_size([Hd|Tl], S) :-
	df_size(Hd, S1),
	cnf_size(Tl, S2),
	int_add(S1, S2, S).

predicate df_size(in DF:t_df, out int) succeeds [once].

df_size([], 0):- .

df_size([_|Tl], S) :-
	df_size(Tl, S2),
	int_add(1, S2, S).


% --------------------------------------------------
% Converting back from DNF to g_guard

predicate dnf_to_guard(in t_dnf, out g_guard) succeeds [once].

predicate cf_to_guard(in t_cf, out g_guard) succeeds [once].

dnf_to_guard([], G):- #bool_g(false, G).

dnf_to_guard([Hd|Tl], G):-
	cf_to_guard(Hd, G1),
	dnf_to_guard(Tl, G2),
	#or(G1, G2, G).


cf_to_guard([], G):- #bool_g(true, G).

cf_to_guard([pair{G1, true}|Tl], G):-
	cf_to_guard(Tl, G2),
	#and(G1, G2, G).

cf_to_guard([pair{G1, false}|Tl], G):-
	#not(G1, G1not),
	cf_to_guard(Tl, G2),
	#and(G1not, G2, G).

% --------------------------------------------------
% Converting back from CNF to g_guard

predicate cnf_to_guard(in t_cnf, out g_guard) succeeds [once].

predicate df_to_guard(in t_df, out g_guard) succeeds [once].

cnf_to_guard([], G):- #bool_g(true, G).

cnf_to_guard([Hd|Tl], G):-
	df_to_guard(Hd, G1),
	cnf_to_guard(Tl, G2),
	#and(G1, G2, G).


df_to_guard([], G):- #bool_g(false, G).

df_to_guard([pair{G1, true}|Tl], G):-
	df_to_guard(Tl, G2),
	#or(G1, G2, G).

df_to_guard([pair{G1, false}|Tl], G):-
	#not(G1, G1not),
	df_to_guard(Tl, G2),
	#or(G1not, G2, G).



% -------------------------------------------------

