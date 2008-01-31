import "memory/scalar_sat.clp".
analyze session_name("cil_body").

print("Ok") :-
    exit(P), 
    vals(P, root{return}, S),
    g_nez(S, G),
    guard_sat(G),
    #not(G, NG),
    guard_sat(NG).

