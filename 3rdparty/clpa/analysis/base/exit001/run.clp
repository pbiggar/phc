import "../exit.clp".
%import "../cfgdot.clp".

print(Fn, "is an exit function.") :- cil_curfn(Fn), exit_fn().

+use_may_exit_calls().
