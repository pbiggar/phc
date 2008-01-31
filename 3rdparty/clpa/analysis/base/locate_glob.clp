using translatecil.

analyze session_name("cil_init").
analyze analysis_name("locate_glob").

predicate linit_glob(IG:string,G:string).
predicate linit_comp(IG:string,C:string,F:string).

?- linit_glob(IG,G).
?- linit_comp(IG,C,F).

cil_init(IG), cil_var_global(X), cil_var_name(X,G,_), +linit_glob(IG,G).
cil_init(IG), cil_type_comp(_,C), cil_comp(C)->cil_comp_field(_,_,FX),
    cil_field_name(FX,F,_,_,_), +linit_comp(IG,C,F).
