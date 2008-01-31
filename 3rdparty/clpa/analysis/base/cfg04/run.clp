import "../loops.clp".
import "../cfgdot.clp".

analyze session_name("cil_sum_body").

cil_curfn(F), sum_bound(S,_,_), tostring(S,SS), str_cat(F,"_",F0), str_cat(F0,SS,F1), str_cat(F1,"_cfg",FNAME), +dot_cfg_name(FNAME).

predicate node_string(in cfg_node,string).
+node_string(nentry,"entry"), +node_string(nexit,"exit"), +node_string(nlooph{_},"loophead").

predicate edge_string(in cfg_edge,string).
+edge_string(easm{_},"asm"), +edge_string(eset{_},"set").
+edge_string(ecall{_},"call"), +edge_string(eloop{_},"loop").
+edge_string(ebtrue{_},"btrue"), +edge_string(ebfalse{_},"bfalse").

predicate fnode(F:string,S:sum,P:int,N:string).
cil_curfn(F), sum_bound(S,_,_), cfgn_final(P,N), node_string(N,NS), point_location(P,_,LINE), +fnode(F,S,LINE,NS).

predicate fedge(F:string,S:sum,P0:int,P1:int,E:string).
cil_curfn(F), sum_bound(S,_,_), cfge_final(P0,P1,E), edge_string(E,ES), point_location(P0,_,LINE0), point_location(P1,_,LINE1), +fedge(F,S,LINE0,LINE1,ES).

?- fnode(F,S,P,N).
?- fedge(F,S,P0,P1,E).
