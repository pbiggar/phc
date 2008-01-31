 %%
% Authors:
%   Isil Dillig    <isil@stanford.edu>
%   Thomas Dillig  <tdillig@stanford.edu>
%%


import "guard-bounds.clp".

analyze session_name("cil_body").
+split_loops().
+no_entry_aliasing().
+ignore_int_casts().

% ------------------------------------------------

% Session for top-down analysis.
session td_sum(F:string).

% Guard G is a condition which depends on function F's return value.
% The idea is that it someone checks a particular rteurn value of this
% function, it must be relevant.
predicate ret_cond(g_guard).

% -----------------------------------------------

% Session for this analysis.

%session ret_bounds_sum(F:string).
%predicate ret_nc(RetG:g_guard, NC: g_guard).
%predicate ret_sc(RetG:g_guard, SC:g_guard).

% -------------------------------------------------

predicate ret_trace(in t_trace).

ret_trace(T) :- 
	trace_root(T, return).


predicate replace_return_guard(in g_guard, in scalar, out g_guard) succeeds [once].

% Case 1. Scalar comparison
% first integer expression is the return value expression.
replace_return_guard(OrigG, NewExp, ReplacedG) :- 
	 #id_g(SG, OrigG), equal(SG, br_cmp{sc{OP, IE1, IE2}}),
	 scalar_trace_used(IE1, T), ret_trace(T),
	 #id_g(br_cmp{sc{OP, NewExp, IE2}}, ReplacedG).



% Case 2.: Scalar comparison, not negated and
% second integer expression is the return value expr.
replace_return_guard(OrigG, NewExp, ReplacedG) :- 
	 #id_g(SG, OrigG), equal(SG, br_cmp{sc{OP, IE1, IE2}}),
	 scalar_trace_used(IE2, T), ret_trace(T),
	 #id_g(br_cmp{sc{OP, IE1, NewExp}}, ReplacedG).


% Case 3.a: sc_eqz, not negated
replace_return_guard(OrigG,  NewExpr, ReplacedG) :- 
	 #id_g(SG, OrigG), equal(SG, br_cmp{sc_eqz{IE}}),
	 scalar_trace_used(IE, T), ret_trace(T),
	 #id_g(br_cmp{sc_eqz{NewExpr}}, ReplacedG).

% Case 3: #not
replace_return_guard(OrigG, NewExpr, ReplacedG) :-
	#not(NotOrigG, OrigG), 
	replace_return_guard(NotOrigG, NewExpr, NotReplacedG),
	#not(NotReplacedG, ReplacedG).

% Case 4: #and 
replace_return_guard(OrigG, NewExpr, ReplacedG) :-
	#and(G1, G2, OrigG),
	replace_return_guard(G1, NewExpr, ReplacedG1),
	replace_return_guard(G2, NewExpr, ReplacedG2),
	#and(ReplacedG1, ReplacedG2, ReplacedG).

% Case 5: #or 
replace_return_guard(OrigG, NewExpr,  ReplacedG) :-
	#or(G1, G2, OrigG), 
	replace_return_guard(G1, NewExpr, ReplacedG1), 
	replace_return_guard(G2, NewExpr, ReplacedG2), 
	#or(ReplacedG1, ReplacedG2, ReplacedG).

% ----------------------------------------------


% Guard version of exit_trace_rename
predicate exit_guard_rename(in P:pp, in g_guard, out g_guard) succeeds [once].
predicate exit_guard_rename_helper(in P:pp, in g_guard, in list[g_guard], out g_guard).

exit_guard_rename(P, InG, OutG) :-
	get_literals(InG, Literals),
	exit_guard_rename_helper(P, InG, Literals, OutG).

exit_guard_rename_helper(P, InG, [], InG) :- .
exit_guard_rename_helper(P, InG, [Hd|Tl], OutG):-
	\/(guard_trace_used(Hd, Tr), trace_root(Tr, temp{_,_})):
		list_all(Tr, Traces),
	list_length(Traces, Length),
	(
	   (~equal(Length, 1), exit_guard_rename_helper(P, InG, Tl, OutG))
	;
	   (equal(Length, 1), equal(Traces, [Trace]),  
	    ~(exit_trace_rename(s_func, Trace, drf{RenamedTr}),
	     val(P, RenamedTr, trace{Trace}, _)),
	    exit_guard_rename_helper(P, InG, Tl, OutG))
	;
	   (equal(Length, 1), equal(Traces, [Trace]),  
	    exit_trace_rename(s_func, Trace, drf{RenamedTr}),
	    val(P, RenamedTr, trace{Trace}, G),
	    replace_guard_trace(Hd, Trace, drf{RenamedTr}, NewHd),
	    #and(NewHd, G,GuardedHd1),
	    #not(G, NG), #and(Hd, NG, GuardedHd2),
	    #or(GuardedHd1, GuardedHd2, RenamedHd),
	    replace_subguard(InG, Hd, RenamedHd, NewInG),
	    exit_guard_rename_helper(P, NewInG, Tl, OutG)
	   )
	).


% -----------------------------------------------

% Predicates for finding the guard in a function that
% is necessary and sufficient for a class of 
% values to be returned.

% -----------------------------------------------

% CallSiteGuard: a condition involving a function return value 
% used at a call site of this function.
% ReturnGuard is the guard under which the CallSiteGuard will hold
% within this function.
% ReturnGuard is a necessary and sufficient condition for the CallSiteGuard.
predicate return_pred(CallSiteGuard:g_guard, ReturnGuard: g_guard ).
predicate return_pred_helper(CallSiteGuard:g_guard, ReturnGuard: g_guard).
predicate unify_return_pred(CallSiteGuardG: g_guard, ReturnGuard: g_guard).


% The expression IE is returned under guard G.
predicate return_exp(IE: scalar, G:g_guard).

cil_stmt_return(S), cil_stmt_return_exp(S,E), exp_point(E, P),
	evals(P, E, IE), 
	scalar_flatten(IE, Flat),
	map_to_sorted_list(Flat, FlatList),
	guard(P, G),
	exit_guard_rename(P, G, RenamedG),
	+return_exps(FlatList, RenamedG).

predicate return_exps(list[t_pair[scalar, g_guard]], G:g_guard).


return_exps([pair{Sc,ScG}|Tl], G), 
	#and(ScG, G, ResG),
	%replace_ret_corrs_sc(ResG, NewResG),
	%+return_exp(Sc, NewResG),
	+return_exp(Sc, ResG),
	+return_exps(Tl, G).

% For those return conditions discovered by the topdown analysis, 
% find the guard under which the comparison will hold.
% For example, if return == -1 is a predicate discovered by the
% topdown analysis and malloc()==NULL is the guard for this return
% statement, remember the relationship between the two guards
% using the return_pred predicate.

cil_curfn(F), td_sum(F)->ret_cond(G),
	return_exp(IE, RG), 
	replace_return_guard(G, IE, NewG), 
	#and(NewG, RG, FuncG),
	#not(FuncG, NotFuncG), guard_sat(NotFuncG), %Not a tautology--important
	+unify_return_pred(G, FuncG).

% Omit G2 if there is another predicate that implies it.
predicate omit_return_pred(in SG:g_guard, in G:g_guard).
return_pred_helper(SG1, _), return_pred_helper(SG2,G2),
	lessthan(SG1, SG2),
        guard_equivalent(SG1, SG2), 
        +omit_return_pred(SG2, G2 ).

	
% Or all the guards that imply the predicate at the call site.
unify_return_pred(G, _), \/(unify_return_pred(G, URG)):#or_all(URG, RG), 
	#simplify(RG, SimpRG),
	+return_pred_helper(G, SimpRG).
	 %#not( SimpRG, NRG), #not(G, NG),
	 %#simplify(NRG, SimpNRG),
	 %+return_pred_helper(NG, SimpNRG).

% Uniquify return_preds so we don't get duplicates.
return_pred_helper(NG, NRG), ~omit_return_pred(NG, NRG),
	\/(return_pred_helper(NG, NRG)):list_all(pair{NG, NRG}, List),
	 equal(List, [pair{G1, G2}|_]), 
	%+print("RETURN PRED: ", G1,"========>", G2),
	+return_pred(G1,G2).

% ----------------------------------------------------------------


cil_curfn(F), return_pred(RetG, FuncG),
	necessary_condition(FuncG, NC),
	guard_simplify(NC, SimpNC),
	+ret_bounds_sum(F)->ret_nc(RetG, SimpNC),
	guard_string(RetG, RetStr), guard_string(SimpNC, NcStr),
	+print("NECESSARY COND: ", F, RetStr, NcStr).

cil_curfn(F), return_pred(RetG, FuncG),
	sufficient_condition(FuncG, SC),
	guard_simplify(SC, SimpSC),
	+ret_bounds_sum(F)->ret_sc(RetG, SimpSC),
	guard_string(RetG, RetStr), guard_string(SimpSC, ScStr),
	+print("SUFFICIENT COND: ", F, RetStr, ScStr).
