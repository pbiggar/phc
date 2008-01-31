
import "../guard-bounds.clp".

analyze session_name("cil_body").


predicate deref(T:t_trace, G:g_guard).
predicate all_derefs(T:t_trace, G:g_guard).

cil_lval_mem(_, E, _),  exp_point(E,P), guard(P,G), 
 eval(P, E, trace{drf{T}}, _), +deref(T, G).

deref(T, _), \/deref(T, G):#or_all(G, AG), +all_derefs(T, AG).

all_derefs(T, SG), 
	necessary_condition(SG, NC), guard_simplify(NC, SNC),
	guard_string(SNC, STR),
	+print("Necessary cond for deref: ", T, STR).

all_derefs(T, SG), 
	sufficient_condition(SG, SC), guard_simplify(SC, SSC),
	guard_string(SSC, STR),
	+print("Sufficient cond for deref: ", T, STR).