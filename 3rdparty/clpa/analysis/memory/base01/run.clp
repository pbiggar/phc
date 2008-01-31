import "../intbvec.clp".
import "../memoryui.clp".

analyze session_name("cil_body").

% mark modified heap data or globals live at exit.
predicate interesting(T:t_trace).
access(_,T,write), trace_alloc(s_func,T,ak_external), +interesting(T).
cil_curfn("maybe"), +interesting(root{arg{0}}).

predicate exitval(F:string,S:t_trace,T:t_trace,G:g_guard).
predicate exitval_display(F:string,S:t_trace,T:t_trace,DISPLAY:string).
cil_curfn(F), exit(P), interesting(S), val(P,S,trace{T},G), +exitval(F,S,T,G),
    #satasn(G,ASN), get_val_display(P,ASN,S,trace{T},DISPLAY),
    +exitval_display(F,S,T,DISPLAY).

predicate exitalias(F:string,S0:t_trace,S1:t_trace).
exitval(F,S0,T,G0), exitval(F,S1,T,G1), #and(G0,G1,G), #sat(G), +exitalias(F,S0,S1).

?- exitval(F,S,T,_).

?- exitalias("maybe",drf{root{arg{1}}},root{arg{0}}).
?- exitalias("maybe",drf{root{arg{2}}},root{arg{0}}).
?- exitalias("maybe",drf{root{arg{1}}},drf{root{arg{2}}}).

?- exitalias("maybeswap",S0,S1).
