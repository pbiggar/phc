import "../scalar.clp".
analyze session_name("cil_body").

predicate ppoint(pp).
ppoint(P) :- sum_body(_,P), P \= p_abort.

predicate avar(t_root).
+avar(local{"x"}).
+avar(local{"y"}).
+avar(local{"z"}).
+avar(arg{0}).
+avar(arg{1}).

predicate v(pp, t_trace, scalar).

v(P, T, S) :- 
    ppoint(P), 
    avar(R),
    equal(T, root{R}),
    vals(P, T, S).

predicate dummy().
v(_, _, _), +dummy().

?- v(P, T, V).
?- val(P, T, TV, G).
