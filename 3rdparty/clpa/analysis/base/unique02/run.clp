import "../loops.clp".

analyze session_name("cil_body").

session field_sum(FN:string) containing [sused].
predicate sused(C:string,F:string).

predicate field_used(FN:string,C:string,F:string).

?- field_used(FN,C,F).

cil_curfn(FN), cil_type_comp(_,C), cil_comp(C)->cil_comp_field(_,_,FLD),
    cil_off_field(_,FLD,_), cil_comp(C)->cil_field_name(FLD,F,_,_,_),
    +field_used(FN,C,F), +field_sum(FN)->sused(C,F).

cil_curfn(FN), dircall(_,CFN), field_sum(CFN)->sused(C,F),
    +field_used(FN,C,F), +field_sum(FN)->sused(C,F).
