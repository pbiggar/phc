
import "../correlate-new.clp".
import "../../base/cfgdot.clp".

analyze session_name("cil_body").

predicate deref(T:t_trace, G:g_guard).
predicate all_derefs(T:t_trace, G:g_guard).

cil_lval_mem(_, E, _),  exp_point(E,P), guard(P,G), 
 eval(P, E, trace{drf{T}}, _), +deref(T, G).

deref(T, _), \/deref(T, G):#or_all(G, AG), +all_derefs(T, AG).

all_derefs(T, SG), 
	necessary_cond(SG, s_func, NC), +print("Necessary cond: ", T, NC).

all_derefs(T, SG),
	sufficient_cond(SG, s_func, SC), +print("Sufficient cond: ", T, SC).


%?- uninit_print(P,G,FILE,LINE).
