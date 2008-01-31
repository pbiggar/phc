import "../loops.clp".

analyze session_name("cil_body").

predicate dircall_line(FILE:string,LINE:int,FN:string,CFN:string).

cil_curfn(FN), icall(P,_,I), dircall(I,CFN), point_location(P,FILE,LINE),
    +dircall_line(FILE,LINE,FN,CFN).

?- dircall_line(FILE,LINE,FN,CFN).
