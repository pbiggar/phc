
import "./guard-bounds.clp".


analyze session_name("cil_body").
+split_loops().
+no_entry_aliasing().
 
% The purpose of this file is to generate guards for pointer
% dereferences in the program, compute necessary and sufficient 
% conditions using the guard-bounds analysis. 
% The necessary and suffcient conditions for dereferences of 
% pointer arguments are propagated up tp the callers in order to
% log the size of the resulting guards. 


session deref_sum(F: string).

predicate deref_nc(T: t_trace, NC: g_guard, Depth:int).
predicate deref_sc(T: t_trace, SC: g_guard, Depth:int).



% -----------------------------------------------------------

% First, find all dereferences of a given pointer.
predicate deref(T:t_trace, G:g_guard).
predicate all_derefs_curfn(T:t_trace, G:g_guard).

cil_lval_mem(_, E, _),  exp_point(E,P), guard(P,G), 
 eval(P, E, trace{drf{T}}, _), +deref(T, G).

deref(T, _), \/deref(T, G):#or_all(G, AG), 
	+all_derefs_curfn(T, AG).



% -----------------------------------------------------
% Summary application

predicate sum_deref_nc(t_trace, g_guard, int).
predicate sum_deref_sc(t_trace, g_guard, int).

dircall(I, F), icall(P, _, I),
	deref_sum(F)->deref_nc(T, NC, SumDepth),
	inst_trace(s_call{I}, P, T, trace{TT}, TG),
	inst_guard(s_call{I}, P, NC, TNC),
	guard(P, SG),
	and3(TNC, SG, TG, DG),
	int_add(SumDepth, 1, Depth),
	trace_root(TT, arg{_}), +sum_deref_nc(TT, DG, Depth).



dircall(I, F), icall(P, _, I),
	deref_sum(F)->deref_sc(T, SC, SumDepth),
	inst_trace(s_call{I}, P, T, trace{TT}, TG),
	inst_guard(s_call{I}, P, SC, TSC),
	guard(P, SG),
	and3(TSC, SG, TG, DG),
	int_add(SumDepth, 1, Depth),
	trace_root(TT, arg{_}), +sum_deref_sc(TT, DG, Depth).

% --------------------------------------
% Unify summary edges


predicate list_max(in list[int], out int) succeeds [once].

predicate list_max_helper(in list[int], in int, out int) succeeds [once].

list_max(L, Res):-
	list_max_helper(L, 0, Res).

list_max_helper([], Res, Res):- .

list_max_helper([Hd|Tl], Cur, Res):-
	list_max_helper(Tl, Cur, Best),
	int_max(Hd, Best, Res).


predicate all_sum_deref_nc(t_trace, g_guard, int).

sum_deref_nc(T, _, _),
	\/sum_deref_nc(T, G, _):#or_all(G, NC),
	\/sum_deref_nc(T,_,D):list_all(D, DList),
	list_max(DList, Max),
	+all_sum_deref_nc(T, NC, Max).

predicate all_sum_deref_sc(t_trace, g_guard, int).

sum_deref_sc(T, _, _),
	\/sum_deref_sc(T, G, _):#or_all(G, SC),
	\/sum_deref_sc(T,_,D):list_all(D, DList),
	list_max(DList, Max),
	+all_sum_deref_sc(T, SC, Max).
	
% ---------------------------------------------------------

% Unify summary and function derefs.
predicate all_derefs_nc(t_trace, g_guard, int).

all_derefs_curfn(T, AG), all_sum_deref_nc(T, SumG, Depth),
	#or(AG, SumG, NC),
	+all_derefs_nc(T, NC, Depth).

all_derefs_curfn(T, AG), ~all_sum_deref_nc(T, _, _),
	+all_derefs_nc(T, AG, 1).

 all_sum_deref_nc(T, SumG, Depth), ~all_derefs_curfn(T, _),
	+all_derefs_nc(T, SumG, Depth).

predicate all_derefs_sc(t_trace, g_guard, int).

all_derefs_curfn(T, AG), all_sum_deref_sc(T, SumG, Depth),
	#or(AG, SumG, SC),
	+all_derefs_sc(T, SC, Depth).

all_derefs_curfn(T, AG), ~all_sum_deref_sc(T, _, _),
	+all_derefs_sc(T, AG, 1).

 all_sum_deref_sc(T, SumG, Depth), ~all_derefs_curfn(T, _),
	+all_derefs_sc(T, SumG, Depth).

% -----------------------------------------------------------
% Summary generation



% Save previous summary using preds in current function
% and then clear summary.

predicate prev_sum_nc(list[t_pair[t_trace, g_guard]]).
predicate prev_sum_sc(list[t_pair[t_trace, g_guard]]).
predicate processed_summary().

cil_curfn(F), 
	\/deref_sum(F)->deref_nc(T1, G1, _):list_all(pair{T1, G1}, List1),
	+prev_sum_nc(List1).
	
cil_curfn(F), \/deref_sum(F)->deref_sc(T2, G2, _):list_all(pair{T2, G2}, List2),
	+prev_sum_sc(List2).
	

%(prev_sum_nc(_); ~prev_sum_nc(_)), (prev_sum_sc(_); ~prev_sum_sc(_)),
%	cil_curfn(F), +deref_sum(F)->clear_old_preds().

	

predicate keep_trace(t_trace).


all_derefs_nc(T, SG, Depth), cil_curfn(F),
	%Depth=1,
	necessary_condition(SG, NC), 
	guard_optimize_aggressive(NC, SNC),
	trace_root(T, arg{_}),
	guard_sat(SNC),
	~(prev_sum_nc(List), list_mem(List, pair{T, SNC})),
	+print("Summary change: ", T, "===>", SNC, Depth),
	+deref_sum(F)->deref_nc(T, SNC, Depth),	
	+keep_trace(T),
	#g_size(SNC, SIZE),
	tostring(Depth, DS),
	tostring(SIZE, SIZES),
	str_cat4("**NC**\t", DS, "\t", SIZES, Res),
	+print(Res).


all_derefs_sc(T, SG, Depth), cil_curfn(F),
	%Depth=1,
	keep_trace(T),
	sufficient_condition(SG, SC), 
	guard_optimize_aggressive(SC, SSC),
	trace_root(T, arg{_}),
	~(prev_sum_sc(List), list_mem(List, pair{T, SSC})),
	+deref_sum(F)->deref_sc(T, SSC, Depth),	
	#g_size(SSC, SIZE),
	tostring(Depth, DS),
	tostring(SIZE, SIZES),
	str_cat4("**SC**\t", DS, "\t", SIZES, Res),
	+print(Res).


% ----------------------------------------------------------
