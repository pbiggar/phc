import "../aliasing.clp".

predicate str_usemod(FN:string,SUM:sum,T:t_trace,Y:access_type).
cil_curfn(FN), cil_cursum(SUM), filt_usemod(T,Y), +str_usemod(FN,SUM,T,Y).

?- str_usemod(FN,SUM,T,Y).
