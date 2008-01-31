using translatecil.

analyze session_name("cil_body").
analyze analysis_name("locate_func").

predicate lfunc_glob(FN:string,G:string).
predicate lfunc_comp(FN:string,C:string,F:string).

?- lfunc_glob(FN,G).
?- lfunc_comp(FN,C,F).

cil_body(FN), cil_var_global(X), cil_var_name(X,G,_), +lfunc_glob(FN,G).
cil_body(FN), cil_type_comp(_,C), cil_comp(C)->cil_comp_field(_,_,FX),
    cil_field_name(FX,F,_,_,_), +lfunc_comp(FN,C,F).
