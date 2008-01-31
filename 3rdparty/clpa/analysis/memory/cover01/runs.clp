import "../scalar.clp".
analyze session_name("cil_body").

+no_entry_aliasing().

predicate brokens(FN:string,X:string,WHY:string).

cil_curfn(FN), sum_body(s_func,P), ~point_location(P,_,_), tostring(P,S), +brokens(FN,S,"point_location").
cil_curfn(FN), exp_type(_,T), ~type_string(T,_), tostring(T,S), +brokens(FN,S,"type_string").
cil_curfn(FN), exp_point(E,_), ~exp_string(E,_), tostring(E,S), +brokens(FN,S,"exp_string").
cil_curfn(FN), exp_point(E,_), ~exp_type(E,_), exp_string(E,S), +brokens(FN,S,"exp_type").
cil_curfn(FN), exp_point(E,P), ~eval(P,E,_,_), exp_string(E,S), +brokens(FN,S,"exp_eval").

?- brokens(FN,X,WHY).
