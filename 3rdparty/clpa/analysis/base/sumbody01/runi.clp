import "../../memory/intignore.clp".

analyze session_name("cil_sum_body").
+disable_cfg().

+no_entry_aliasing().

predicate brokeni(FN:string,X:string,WHY:string).

cil_curfn(FN), sum_body(s_func,P), ~point_location(P,_,_), tostring(P,S), +brokeni(FN,S,"point_location").
cil_curfn(FN), exp_type(_,T), ~type_string(T,_), tostring(T,S), +brokeni(FN,S,"type_string").
cil_curfn(FN), exp_point(E,_), ~exp_string(E,_), tostring(E,S), +brokeni(FN,S,"exp_string").
cil_curfn(FN), exp_point(E,_), ~exp_type(E,_), exp_string(E,S), +brokeni(FN,S,"exp_type").
cil_curfn(FN), exp_point(E,P), ~eval(P,E,_,_), exp_string(E,S), +brokeni(FN,S,"exp_eval").
cil_curfn(FN), exp_boolean(E), exp_point(E,P), ~beval(P,E,_,_), exp_string(E,S), +brokeni(FN,S,"exp_beval").

?- brokeni(FN,X,WHY).
