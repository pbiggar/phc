import "normal-forms.clp".

% -------------------------------------------------

% Session for return_bounds analysis
session ret_bounds_sum(F:string).

predicate ret_nc(RetG:g_guard, NC: g_guard).
predicate ret_sc(RetG:g_guard, SC:g_guard).

%----------------------------------------------------
% Returns a list of all leaf predicates that contain
% a temporary trace in negated form.
predicate negative_temps(in G:g_guard, 
	out Negs:list[g_guard]) succeeds [once].

negative_temps(G, Negs) :-
	negative_literals(G, Neg),
	\/(list_mem(Neg, Elem), 
	  guard_trace_used(Elem, Tr),
	  trace_root(Tr, temp{_,_})):
	list_all(Elem, Negs).

% Returns a list of all leaf predicates that contain
% a temporary trace in negated form.
predicate positive_temps(in G:g_guard, 
	out Positives:list[g_guard]) succeeds [once].

positive_temps(G, Positives) :-
	positive_literals(G, Pos),
	\/(list_mem(Pos, Elem), 
	  guard_trace_used(Elem, Tr),
	  trace_root(Tr, temp{_,_})):
	list_all(Elem, Positives).

% ------------------------------------------------
predicate return_nc(I:c_instr, F:string, ReturnG:g_guard,NC:g_guard).
predicate return_sc(I:c_instr, F:string, ReturnG:g_guard,SC:g_guard).
predicate return_test(G: g_guard).

anycall(I, F, _), icall(P1, _,I), 
	ret_bounds_sum(F)->ret_nc(ReturnG,  _),
	\/ret_bounds_sum(F)->ret_nc(ReturnG, N):#and_all(N, NC),
	inst_guard(s_call{I}, P1, ReturnG, TRG),
	+return_test(TRG),
	inst_guard(s_call{I}, P1, NC, TNC),
	+return_nc(I, F, TRG, TNC),
	#bool_g(true, True), ~guard_equivalent(TNC, True), +return_test(TNC).

anycall(I, F, _), icall(P1, _,I), 
	ret_bounds_sum(F)->ret_sc(ReturnG,  _),
	\/ret_bounds_sum(F)->ret_sc(ReturnG, S):#or_all(S, SC),
	inst_guard(s_call{I}, P1, ReturnG, TRG),
	inst_guard(s_call{I}, P1, SC, TSC),
	+return_test(TSC),
	+return_sc(I, F, TRG, TSC),
	#bool_g(false, False), ~guard_equivalent(TSC, False), +return_test(TSC).



% A list of all (Return condition, Necessary cond for return) pairs.
predicate return_ncs(Ncs:list[t_pair[g_guard, g_guard]]).
return_ncs(Ncs):-
	\/return_nc(_, _, RetG, Nc):list_all(pair{RetG,Nc}, Ncs).

% A list of all (Return condition, Sufficient cond for return) pairs.
predicate return_scs(Scs:list[t_pair[g_guard, g_guard]]).
return_scs(Scs):-
	\/return_sc(_, _, RetG, Sc):list_all(pair{RetG,Sc}, Scs).

% -------------------------------------------

% A list of temporaries corresponding to function return values.
% predicate return_temps(out list[t_trace]).
% Declared in normal-forms.clp because of mutual dependence.

return_temps(RetTemps) :-
	\/(return_test(RetG), 
	  guard_trace_used(RetG,T), trace_root(T, temp{_,_}))
	:list_all(T, RetTemps).


% --------------------------------------------

% Given a leaf guard, returns another guard that
% should refine the original leaf guard.
% For a leaf guard containing a temp trace that
% corresponds to a function return value, the 
% refinement guard is the necessary/sufficient
% condition for that return value.
predicate refinement_guard(in g_guard, in Phase: bool, in NCorSC:string, out g_guard)
	succeeds [once].
predicate refinement_guard_helper(in g_guard, in Phase:bool, in NCorSC:string, 
	in list[t_pair[g_guard, g_guard]], 
	out g_guard) succeeds [once].

refinement_guard_helper(G, true, "necessary",[], True) :- #bool_g(true, True).
refinement_guard_helper(G, false, "necessary",[], False) :- #bool_g(false, False).
refinement_guard_helper(G, true, "sufficient",[], False) :- #bool_g(false, False).
refinement_guard_helper(G, false, "sufficient",[], True) :- #bool_g(true, True).
refinement_guard_helper(G, true, NcScType,[pair{RetG, NcSc}|Tl],OutG ) :- 
	(
	  (equivalent(G, RetG), OutG=NcSc);
	  (~equivalent(G, RetG), refinement_guard_helper(G, true, NcScType, Tl, OutG))
	).
refinement_guard_helper(G, false, NcScType,[pair{RetG, NcSc}|Tl],OutG ) :- 
	#not(RetG, NotRetG),
	(
	  ( equivalent(G, NotRetG), #not(NcSc,OutG));
	  (~equivalent(G, NotRetG), refinement_guard_helper(G, false, NcScType, Tl, OutG))
	).
		

 

refinement_guard(InG, Phase, "necessary", OutG) :-
	(return_ncs(Ncs); (~return_ncs(_), Ncs=[])),
	refinement_guard_helper(InG, Phase, "necessary", Ncs, OutG).

refinement_guard(InG, Phase, "sufficient", OutG) :-
	(return_scs(Scs); (~return_scs(_), Scs=[])),
	refinement_guard_helper(InG, Phase, "sufficient", Scs, OutG).



% -----------------------------------------------

predicate replace_returns_phased_nc(in t_dnf,in list[g_guard], 
		in bool, out t_dnf) succeeds [once].

replace_returns_phased_nc(DNF, [], Phase, DNF) :- .
replace_returns_phased_nc(InDnf, [Hd|Tl], true, OutDnf) :-
	refinement_guard(Hd, true, "necessary", RefG),
	refine_leaf_dnf_positive(InDnf,Hd, RefG, RefinedDnf),
	replace_returns_phased_nc(RefinedDnf, Tl, true, OutDnf).

replace_returns_phased_nc(InDnf, [Hd|Tl], false, OutDnf) :-
	refinement_guard(Hd, false, "necessary", RefG),
	refine_leaf_dnf_negative(InDnf,Hd, RefG, RefinedDnf),
	replace_returns_phased_nc(RefinedDnf, Tl, false, OutDnf).
	

	

predicate replace_returns_phased_sc(in t_cnf,in list[g_guard], 
		in bool, out t_cnf) succeeds [once].

replace_returns_phased_sc(CNF, [], Phase, CNF) :- .
replace_returns_phased_sc(InCnf, [Hd|Tl], true, OutCnf) :-
	refinement_guard(Hd, true, "sufficient", RefG),
	refine_leaf_cnf_positive(InCnf,Hd, RefG, RefinedCnf),
	replace_returns_phased_sc(RefinedCnf, Tl, true, OutCnf).

replace_returns_phased_sc(InCnf, [Hd|Tl], false, OutCnf) :-
	refinement_guard(Hd, false, "sufficient", RefG),
	refine_leaf_cnf_negative(InCnf,Hd, RefG, RefinedCnf),
	replace_returns_phased_sc(RefinedCnf, Tl, false, OutCnf).	


% -------------------------------------------------
predicate replace_returns(in g_guard, in NcScType:string, out g_guard) 
	succeeds [once].

replace_returns(G1, NcScType, G2) :-
	equal(NcScType, "necessary"),
	%guard_optimize_aggressive(G1, SimpG1),
	guard_optimize(G1, SimpG1),
	construct_dnf(SimpG1, DNF),
	dnf_size(DNF, SIZE), +print("DNF Size: ", SIZE),
	negative_temps(G1, Negatives),  
	replace_returns_phased_nc(DNF, Negatives, false, DNF1),
	positive_temps(G1, Positives),
%	+print("Positive temps: ", Positives),
	replace_returns_phased_nc(DNF1, Positives, true, DNF2),
	dnf_to_guard(DNF2, G2).


replace_returns(G1, NcScType, G2) :-
	equal(NcScType, "sufficient"),
	%guard_optimize_aggressive(G1, SimpG1),
	guard_optimize(G1, SimpG1),
	construct_cnf(SimpG1, CNF),
	cnf_size(CNF, SIZE), +print("CNF Size: ", SIZE),
	negative_temps(G1, Negatives),
	replace_returns_phased_sc(CNF, Negatives, false, CNF1),
	positive_temps(G1, Positives),
	replace_returns_phased_sc(CNF1, Positives, true, CNF2),
	cnf_to_guard(CNF2, G2).

% ---------------------------------------------------

% Compute necessary cond for a guard
predicate necessary_condition(in g_guard, out g_guard) 
	succeeds [once].	


necessary_condition(G, SNC) :-
	guard_optimize(G, OptG),
	guard_flatten(OptG, FG),
	negations_in(FG, NG),
	bool_snc(NG, false, BG),
	replace_returns(BG, "necessary", PreSNC),
	bool_snc(PreSNC, true, SNC).
	%guard_string(SNC, NCSTR),
	%guard_string(G, GSTR),
	%+print("NECESSARY COND: ", GSTR, "=======>", NCSTR).

% Compute necessary cond for a guard
predicate sufficient_condition(in g_guard, out g_guard) 
	succeeds [once].	


sufficient_condition(G, WSC) :-
	guard_optimize(G, OptG),
	guard_flatten(OptG, FG),
	negations_in(FG, NG),
	bool_wsc(NG, false, BG),
	replace_returns(BG, "sufficient", PreWSC),
	bool_wsc(PreWSC,true,  WSC).
	%guard_string(SNC, NCSTR),
	%guard_string(G, GSTR).
	%+print("SUFFICIENT COND: ", GSTR, "=======>", NCSTR).

	
	
