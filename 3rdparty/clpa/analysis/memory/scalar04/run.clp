import "../scalar_sat.clp".
analyze session_name("cil_body").

session sum_bvec(string).
predicate deref(t_trace,g_guard).
predicate may_deref(string,t_trace).

cil_lval_mem(LV,ME,_), lval_point(LV,P),
    eval(P,ME,trace{T},G0), guard(P,G1), #and(G0,G1,G), +deref(T,G).
icall(P,_,I), dircall(I,FN), sum_bvec(FN)->deref(CT,CG),
    inst_trace(s_call{I},P,CT,trace{T},WG0),
    inst_guard(s_call{I},P,CG,WG1),
    guard(P,WG2), #and(WG0,WG1,G0), #and(G0,WG2,G), +deref(T,G).

cil_curfn(FN), deref(T,G), guard_sat(G), +may_deref(FN,T), 
    +sum_bvec(FN)->deref(T,G).

?- may_deref(FN,T).
