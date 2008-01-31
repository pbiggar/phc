import "../intignore.clp".

analyze session_name("cil_body").

predicate exitval(F:string,S:t_trace,T:t_trace,G:g_guard).
cil_curfn(F), exit(P), access(_,S,write), trace_alloc(s_func,S,ak_external),
    val(P,S,trace{T},G), +exitval(F,S,T,G).

?- exitval(F,S,T,_).
