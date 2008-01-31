% A small test of +...->clear_old_preds() predicate. 

import "../loops.clp".

analyze session_name("cil_body").

% Similar sessions, one we clear, one we don't.
session clear_session().
session merge_session().

predicate fooarg_list(list[int]).

predicate fooarg(int).

merge_session()->fooarg_list(Xs), 
    list_mem(Xs, X), 
    +fooarg(X).

icall(_, _, I), 
    dircall(I, "foo"), 
    cil_instr_call_arg(I, 0, E),
    cil_exp_const(E, C),
    cil_const_int(C, _, N),
    +fooarg(N).

\/fooarg(X):list_all(X, Xs), +merge_session()->fooarg_list(Xs).
\/fooarg(X):list_all(X, Xs), +clear_session()->fooarg_list(Xs).

+clear_session()->clear_old_preds().

predicate c(list[int]).
predicate m(list[int]).
clear_session()->fooarg_list(Xs), +c(Xs).
merge_session()->fooarg_list(Xs), +m(Xs).
?- c(Xs).
?- m(Xs).
