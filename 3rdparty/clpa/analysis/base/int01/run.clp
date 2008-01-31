import "../loops.clp".

analyze session_name("cil_body").

print(Line, K, Val) :-
    exp_point(E, P), 
    cil_exp_const(E, C), 
    cil_const_int(C,K,Val),
    point_location(P, _, Line).
