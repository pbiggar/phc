using map.
using set.
using translatecil.

print(S0, S1, S2, S3, S4, S5, L, S) :-
    set_empty(S0), 
    set_insert(3, S0, S1), 
    set_insert(2, S1, S2), 
    set_remove(1, S2, S3),
    set_insert(1, S3, S4),
    set_remove(3, S4, S5),
    set_to_sorted_list(S5, L),
    set_of_list(L, S).

print(M0, M1, M2, M3, M4, M5, L, M) :-
    map_empty(M0), 
    map_insert(3, "hello", M0, M1), 
    map_insert(2, "bonjour", M1, M2), 
    map_remove(1, M2, M3),
    map_insert(1, "hola", M3, M4),
    map_remove(3, M4, M5),
    map_to_sorted_list(M5, L),
    map_of_list(L, M).
    
predicate foo(int, string).
foo(1, "a") :- .
foo(2, "b1") :- .
foo(2, "b2") :- .
foo(3, "c") :- .

print("map_all", M) :-
    \/foo(K,V):map_all(K,V,M).

print("set_all", M) :-
    \/foo(K,_):set_all(K,M).
