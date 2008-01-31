import "../loops.clp".
import "../cfgdot.clp".

% +preserve_loops().

analyze session_name("cil_body").

predicate node_string(in cfg_node,string).
+node_string(nentry,"entry"), +node_string(nexit,"exit"), +node_string(nlooph{_},"loophead").

predicate edge_string(in cfg_edge,string).
+edge_string(easm{_},"asm"), +edge_string(eset{_},"set").
+edge_string(ecall{_},"call"), +edge_string(eloop{_},"loop").
+edge_string(ebtrue{_},"btrue"), +edge_string(ebfalse{_},"bfalse").

predicate fnode(F:string,P:int,N:string).
cil_curfn(F), cfgn_final(P,N), node_string(N,NS), point_location(P,_,LINE), +fnode(F,LINE,NS).

predicate fedge(F:string,P0:int,P1:int,E:string).
cil_curfn(F), cfge_final(P0,P1,E), edge_string(E,ES), point_location(P0,_,LINE0), point_location(P1,_,LINE1), +fedge(F,LINE0,LINE1,ES).

?- fnode(F,P,N).
?- fedge(F,P0,P1,E).
