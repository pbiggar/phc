
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

predicate deref_nc(T: t_trace, NC: g_guard).
predicate deref_sc(T: t_trace, SC: g_guard).

% ---------------------------------------------------------

predicate print_stat_nc(t_trace, g_guard).
predicate print_stat_sc(t_trace, g_guard).


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

predicate sum_deref_nc(t_trace, g_guard).
predicate sum_deref_sc(t_trace, g_guard).

dircall(I, F), icall(P, _, I),
	deref_sum(F)->deref_nc(T, NC),
	inst_trace(s_call{I}, P, T, trace{TT}, TG),
	inst_guard(s_call{I}, P, NC, TNC),
	guard(P, SG),
	and3(TNC, SG, TG, DG),
	(
	  (trace_root(TT, arg{_}), +sum_deref_nc(TT, DG))
	;
	  (~trace_root(TT, arg{_}), +print_stat_nc(TT, DG))	
	).



dircall(I, F), icall(P, _, I),
	deref_sum(F)->deref_sc(T, SC),
	inst_trace(s_call{I}, P, T, trace{TT}, TG),
	inst_guard(s_call{I}, P, SC, TSC),
	guard(P, SG),
	and3(TSC, SG, TG, DG),
	(
	  (trace_root(TT, arg{_}), +sum_deref_sc(TT, DG))
	;
	  (~trace_root(TT, arg{_}), +print_stat_sc(TT, DG))	
	).

% --------------------------------------
% Unify summary edges

predicate all_sum_deref_nc(t_trace, g_guard).

sum_deref_nc(T, _),
	\/sum_deref_nc(T, G):#or_all(G, NC),
	+all_sum_deref_nc(T, NC).

predicate all_sum_deref_sc(t_trace, g_guard).

sum_deref_sc(T, _),
	\/sum_deref_sc(T, G):#or_all(G, SC),
	+all_sum_deref_sc(T, SC).
	
% ---------------------------------------------------------

% Unify summary and function derefs.
predicate all_derefs_nc(t_trace, g_guard).

all_derefs_curfn(T, AG), all_sum_deref_nc(T, SumG),
	#or(AG, SumG, NC),
	+all_derefs_nc(T, NC).

all_derefs_curfn(T, AG), ~all_sum_deref_nc(T, _),
	+all_derefs_nc(T, AG).

 all_sum_deref_nc(T, SumG), ~all_derefs_curfn(T, _),
	+all_derefs_nc(T, SumG).

predicate all_derefs_sc(t_trace, g_guard).

all_derefs_curfn(T, AG), all_sum_deref_sc(T, SumG),
	#or(AG, SumG, SC),
	+all_derefs_sc(T, SC).

all_derefs_curfn(T, AG), ~all_sum_deref_sc(T, _),
	+all_derefs_sc(T, AG).

 all_sum_deref_sc(T, SumG), ~all_derefs_curfn(T, _),
	+all_derefs_sc(T, SumG).

% -----------------------------------------------------------
% Summary generation

all_derefs_nc(T, SG), cil_curfn(F),
	necessary_condition(SG, NC), 
	guard_optimize_aggressive(NC, SNC),
	trace_root(T, arg{_}),
	+deref_sum(F)->deref_nc(T, SNC),	
	#g_size(SNC, SIZE),
	+print("Summary deref, NC: ", SIZE).


all_derefs_sc(T, SG), cil_curfn(F),
	sufficient_condition(SG, SC), 
	guard_optimize_aggressive(SC, SSC),
	trace_root(T, arg{_}),
	+deref_sum(F)->deref_sc(T, SSC),	
	#g_size(SSC, SIZE),
	+print("Summary deref, SC", SIZE).

% ----------------------------------------------------------

% Print stats for pointers generated in this function.

print_stat_nc(T, G),
	~trace_root(T, glob{_}),
	necessary_condition(G, NC),
	guard_optimize(NC, SimpNC),
	trace_string(T, TStr),
	guard_string(SimpNC, NCStr),
	#g_size(SimpNC, Size),
	+print("NECESSARY CONDITION SIZE: ",
		 TStr, "===>", Size, "===>", NCStr).

print_stat_sc(T, G),
	~trace_root(T, glob{_}),
	sufficient_condition(G, SC),
	guard_optimize(SC, SimpSC),
	trace_string(T, TStr),
	guard_string(SimpSC, SCStr),
	#g_size(SimpSC, Size),
	+print("SUFFICIENT CONDITION SIZE: ",
		 TStr, "===>", Size, "===>", SCStr).