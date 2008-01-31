import "../aliasinginit.clp".

+omit_comp_spoints(_,_,_).

?drop_spoints(S,T), trace_type(s_func,T,y_func), +drop_spoints(S,T).
