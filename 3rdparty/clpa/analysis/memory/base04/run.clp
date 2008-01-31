import "../intbvec.clp".

analyze session_name("cil_body").

+split_loops(), +fixed_vectors(4).

predicate exitval(S:t_trace,T:t_trace_val).
exit(P), access(_,S,write), val(P,S,T,_), +exitval(S,T).  % force val() eval

predicate overlap(FN:string,pp,t_trace,t_trace_val,t_trace_val).
predicate missing(FN:string,pp,t_trace).

cil_curfn(FN), ?val(P,S,_,_), val(P,S,T0,G0), val(P,S,T1,G1), guard(P,GG),
    tostring(T0,T0S), tostring(T1,T1S), lessthan(T0S,T1S),
    #and(G0,G1,TG), #and(TG,GG,TGG), #sat(TGG), +overlap(FN,P,S,T0,T1).
cil_curfn(FN), ?val(P,S,_,_), \/val(P,S,_,G):#or_all(G,MG),
    #not(MG,NMG), #sat(NMG), +missing(FN,P,S).

?- overlap(FN,P,S,T0,T1).
?- missing(FN,P,S).
