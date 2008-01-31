% Path-sensitive interprocedural locking analysis.
% computes function summary lock transitions correlated with whether the
% return value is non-zero.

% TODOs:
%   currently just compute summaries, need to filter out errors
%   summaries are only computed for locks that are formal parameters

import "../memory/scalar_sat.clp".
import "../base/cfgdot.clp".

analyze session_name("cil_body").

% PREDICATES

% the possible spinlock states
type lockstate ::= locked | unlocked | error.

% at program point P, trace T is in state S if G holds
predicate state(P:pp,T:t_trace,S:lockstate,G:g_guard).

% Summary edge on a call: if callee trace CT is in state SIN, it transitions
% to state SOUT if the call's return value matches NEZ (non-zero if NEZ=true,
% zero if NEZ=false).
predicate cedge(I:c_instr,T:t_trace,SIN:lockstate,SOUT:lockstate,NEZ:bool).

% extra unconstrained bits, true if T is locked at entry
type g_xrep ::= t_locked{t_trace}.

% SUMMARIES

% session with the lockstate summary of FN
session sum_locking(FN:string) containing [sedge].

% summary edge: if trace T is in state SIN, it transitions to state SOUT
% if the return value matches NEZ as in cedge
predicate sedge(T:t_trace,SIN:lockstate,SOUT:lockstate,NEZ:bool).

% RULES

% call transitions

% add transitions for direct calls to lock/unlock/trylock
dircall(I,"lock"),
    +cedge(I,drf{root{arg{0}}},locked,error,false),
    +cedge(I,drf{root{arg{0}}},unlocked,locked,false).
dircall(I,"unlock"),
    +cedge(I,drf{root{arg{0}}},locked,unlocked,false),
    +cedge(I,drf{root{arg{0}}},unlocked,error,false).
dircall(I,"trylock"),
    +cedge(I,drf{root{arg{0}}},locked,locked,false),
    +cedge(I,drf{root{arg{0}}},unlocked,unlocked,false),
    +cedge(I,drf{root{arg{0}}},locked,error,true),
    +cedge(I,drf{root{arg{0}}},unlocked,locked,true).

% add additional transitions according to summary information generated
% on the targets of direct calls
dircall(I,F), sum_locking(F)->sedge(T,SIN,SOUT,NEZ), +cedge(I,T,SIN,SOUT,NEZ).

% transfer functions

% adding will merge G into the condition under which T is in state S at P
predicate smerge(P:pp,T:t_trace,S:lockstate,G:g_guard).
smerge(P,T,S,_), \/smerge(P,T,S,G):#or_all(G,MG), +state(P,T,S,MG).

% LKG and UKG are conditions under which T is locked or unlocked at entry
predicate entry_locked(in T:t_trace,LKG:g_guard,UKG:g_guard).
?entry_locked(T,_,_), #id_g(br_abit{ar_extra{t_locked{T}}},LKG), #not(LKG,UKG),
    +entry_locked(T,LKG,UKG).

% compute the initial lock states for any trace T whose lock state might
% change during the function's execution (there is a call with a transition
% on T). generate a boolean variable indicating whether T is locked (LKG) or
% unlocked (UKG) at entry, and add the two states
entry(PIN), icall(P0,_,I), cedge(I,CT,_,_,_),
    inst_trace(s_call{I},P0,CT,trace{T},_), entry_locked(T,LKG,UKG),
    +state(PIN,T,locked,LKG), +state(PIN,T,unlocked,UKG).

% sets and branches don't affect lockstate
iset(P0,P1,_), state(P0,T,S,G), eguard(P0,P1,G,EG), +smerge(P1,T,S,EG).
branch(P,P0,_,_), state(P,T,S,G), eguard(P,P0,G,EG0), +smerge(P0,T,S,EG0).
branch(P,_,P1,_), state(P,T,S,G), eguard(P,P1,G,EG1), +smerge(P1,T,S,EG1).

% merge transition results in after a call I according to whether the return
% value is non-zero or not. adding smerge_nez will compute the non-zero
% return value condition on I, combine it or its negation (according to NEZ)
% with G, and merge the result into the guard on whether T is in state S at P
predicate call_merge(I:c_instr,P0:pp,P1:pp,NEZ:bool,
                     T:t_trace,S:lockstate,G:g_guard).

% calls which do not return a value are treated as returning zero
call_merge(I,P0,P1,false,T,S,G), ~callret(I,_),
    eguard(P0,P1,G,EG), +smerge(P1,T,S,EG).

% Return value of a call instruction expressed as an expression
predicate call_ret_exp(I:c_instr, E:c_exp).
cil_instr_call_ret(I,RLV),
    cil_make_exp(I,"retexp",E), +cil_exp_lval(E,RLV), +call_ret_exp(I,E).

% get a scalar for the return value of a call evaluated at P
predicate ret_scalar(in I:c_instr,in P:pp,V:scalar).
?ret_scalar(I,P,_), call_ret_exp(I,E), evals(P,E,V), +ret_scalar(I,P,V).

% merge for calls which return a value. get the nez or eqz condition
% as appropriate, combine with SG and merge
call_merge(I,P0,P1,true,T,S,SG), ret_scalar(I,P0,V),
    #id_g(br_cmp{sc_eqz{V}},EQZG), #not(EQZG,NEZG), #and(SG,NEZG,G),
    eguard(P0,P1,G,EG), +smerge(P1,T,S,EG).
call_merge(I,P0,P1,false,T,S,SG), ret_scalar(I,P0,V),
    #id_g(br_cmp{sc_eqz{V}},EQZG), #and(SG,EQZG,G),
    eguard(P0,P1,G,EG), +smerge(P1,T,S,EG).

% call transfer function for locks where a transition is known
icall(P0,P1,I), cedge(I,CT,SIN,SOUT,NEZ),
    inst_trace(s_call{I},P0,CT,trace{T},BG),
    state(P0,T,SIN,SG), #and(BG,SG,G), +call_merge(I,P0,P1,NEZ,T,SOUT,G).

% for locks which do not have known transitions on the callee, we treat the
% call as a nop. since there may be multiple aliases of the lock, we need to
% get the conjunction over the negations of all conditions under which some
% alias for the lock does NOT have a transition on the callee

% NG is a negated condition for when T has a transition on the call at P.
% we assume that if there are any transitions, there will be transitions for
% all combinations of SIN (locked/unlocked only) and return value NEZ
predicate edge_negate(P:pp,T:t_trace,NG:g_guard).
icall(P,_,I), cedge(I,CT,_,_,_),
    inst_trace(s_call{I},P,CT,trace{T},G),
    #not(G,NG), +edge_negate(P,T,NG).

% call transfer function for locks which do NOT have callee transitions.
% get the conjunction on the negated conditions and propagate forward unchanged
icall(P0,P1,_), state(P0,T,S,SG),
    \/edge_negate(P0,T,NG):#and_all(NG,MNG), #and(MNG,SG,G),
    eguard(P0,P1,G,EG), +smerge(P1,T,S,EG).

% call transfer function for locks in the error state
icall(P0,P1,_), state(P0,T,error,G),
    eguard(P0,P1,G,EG), +smerge(P1,T,error,EG).

% summary computation

% the current function returns a non-zero or zero value (according to NEZ)
% if G holds
predicate return_nez(NEZ:bool,G:g_guard).

% no returned expression, return value treated as zero
~cil_var_return(_), #bool_g(true,G), +return_nez(false,G).

% compute the non-zero and zero return conditions by constructing an expression
cil_var_return(X), cil_make_lval(X,"rlv",LV), cil_make_offset(X,"roff",OFF),
    +cil_lval_var(LV,X,OFF), +cil_off_none(OFF),
    cil_make_exp(X,"rexp",E), +cil_exp_lval(E,LV), exit(P), evals(P,E,V),
    #id_g(br_cmp{sc_eqz{V}},EQZG), +return_nez(false,EQZG),
    #not(EQZG,NEZG), +return_nez(true,NEZG).

% for trace T, the SIN -> SOUT transition occurs when G holds
predicate trace_trans(T:t_trace,G:g_guard,SIN:lockstate,SOUT:lockstate).

% compute the transition conditions for each trace T. get the lock state
% at exit and combine with the boolean variable indicating whether the lock
% was locked (LKG) or unlocked (UKG) at entry
exit(P), state(P,T,S,SG), entry_locked(T,LKG,UKG),
    #and(SG,LKG,LKGG), +trace_trans(T,LKGG,locked,S),
    #and(SG,UKG,UKGG), +trace_trans(T,UKGG,unlocked,S).

% function FN has summary edge A/SIN/SOUT/NEZ
predicate fedge(FN:string,T:t_trace,SIN:lockstate,SOUT:lockstate,NEZ:bool).

% combine the transition conditions with the return-non-zero conditions
% to compute all the summary transitions on the current function
cil_curfn(F), trace_trans(T,SG,SIN,SOUT),
    return_nez(NEZ,ZG), #and(SG,ZG,G), guard_sat(G),
    +fedge(F,T,SIN,SOUT,NEZ), +sum_locking(F)->sedge(T,SIN,SOUT,NEZ).

?- fedge(FN,A,SIN,SOUT,NEZ).
