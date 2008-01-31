
import "./guard-bounds.clp".


analyze session_name("cil_body").
+split_loops().
+no_entry_aliasing().

% Generate stats comparing original size and
% necessary/sufficient condition size to use for 
% plotting graphs.



% First, find all dereferences of a given pointer.
predicate deref(T:t_trace, G:g_guard).
predicate all_derefs(T:t_trace, G:g_guard).

cil_lval_mem(_, E, _),  exp_point(E,P), guard(P,G), 
 eval(P, E, trace{drf{T}}, _), +deref(T, G).

deref(T, _), \/deref(T, G):#or_all(G, AG), 
	+all_derefs(T, AG).


% Summary generation

all_derefs(T, SG),
	necessary_condition(SG, NC), 
	guard_optimize_aggressive(NC, SNC),
	trace_root(T, arg{_}),
	#g_size(SG, OrigSize),
	#g_size(SNC, NcSize),
	tostring(OrigSize, Orig),
	tostring(NcSize, NcStr),
	str_cat4("**NC** \t", Orig, "\t", NcStr, NCSTR), 
	+print(NCSTR).


all_derefs(T, SG),
	sufficient_condition(SG, SC), 
	guard_optimize_aggressive(SC, WSC),
	trace_root(T, arg{_}),
	#g_size(SG, OrigSize),
	#g_size(WSC, ScSize),
	tostring(OrigSize, Orig),
	tostring(ScSize, ScStr),
	str_cat4("**SC** \t", Orig, "\t", ScStr, SCSTR), 
	+print(SCSTR).
