% interprocedural locking analysis.

import "../memory/scalar_sat.clp".

analyze session_name("cil_sum_body").

% PREDICATES

% the possible spinlock states
type lockstate ::= locked | unlocked | error.

% at program point P, trace T is in state S if G holds
predicate state(P:pp,T:t_trace,S:lockstate,G:g_guard).

% Summary edge on a call: if callee trace CT is in state SIN, it transitions
% to state SOUT.
predicate cedge(I:sum,T:t_trace,SIN:lockstate,SOUT:lockstate).

% extra unconstrained bits, true if T is locked at entry
type g_xrep ::= t_locked{t_trace}.

% SUMMARIES

% session with the lockstate summary of FN
session sum_locking(FN:string, S:sum) containing [sedge].

% summary edge: if trace T is in state SIN, it transitions to state SOUT
predicate sedge(T:t_trace,SIN:lockstate,SOUT:lockstate).

% RULES

% call transitions

% add transitions for direct calls to lock/unlock/trylock
dircall(I,"lock"), 
    +cedge(s_call{I},drf{root{arg{0}}},locked,error),
    +cedge(s_call{I},drf{root{arg{0}}},unlocked,locked).
dircall(I,"unlock"),
    +cedge(s_call{I},drf{root{arg{0}}},locked,unlocked),
    +cedge(s_call{I},drf{root{arg{0}}},unlocked,error).

% add additional transitions according to summary information generated
% on the targets of direct calls
isum_target(I,F,S,_), sum_locking(F,S)->sedge(T,SIN,SOUT), +cedge(I,T,SIN,SOUT).

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
cil_cursum(S), sum_bound(S,PIN,_), isum(P0,_,I), cedge(I,CT,_,_),
    inst_trace(I,P0,CT,trace{T},_), entry_locked(T,LKG,UKG),
    +state(PIN,T,locked,LKG), +state(PIN,T,unlocked,UKG).

% sets and branches don't affect lockstate
iset(P0,P1,_), state(P0,T,S,G), eguard(P0,P1,G,EG), +smerge(P1,T,S,EG).
branch(P,P0,_,_), state(P,T,S,G), eguard(P,P0,G,EG0), +smerge(P0,T,S,EG0).
branch(P,_,P1,_), state(P,T,S,G), eguard(P,P1,G,EG1), +smerge(P1,T,S,EG1).

% call transfer function for locks where a transition is known
isum(P0,P1,I), cedge(I,CT,SIN,SOUT),
    inst_trace(I,P0,CT,trace{T},BG),
    state(P0,T,SIN,SG), #and(BG,SG,G),
    eguard(P0,P1,G,EG), +smerge(P1,T,SOUT,EG).

% for locks which do not have known transitions on the callee, we treat the
% call as a nop. since there may be multiple aliases of the lock, we need to
% get the conjunction over the negations of all conditions under which some
% alias for the lock does NOT have a transition on the callee

% NG is a negated condition for when T has a transition on the call at P.
% we assume that if there are any transitions, there will be transitions for
% all combinations of SIN (locked/unlocked only)
predicate edge_negate(P:pp,T:t_trace,NG:g_guard).
isum(P,_,I), cedge(I,CT,_,_),
    inst_trace(I,P,CT,trace{T},G),
    #not(G,NG), +edge_negate(P,T,NG).

% call transfer function for locks which do NOT have callee transitions.
% get the conjunction on the negated conditions and propagate forward unchanged
isum(P0,P1,_), state(P0,T,S,SG),
    \/edge_negate(P0,T,NG):#and_all(NG,MNG), #and(MNG,SG,G),
    eguard(P0,P1,G,EG), +smerge(P1,T,S,EG).

% call transfer function for locks in the error state
isum(P0,P1,_), state(P0,T,error,G),
    eguard(P0,P1,G,EG), +smerge(P1,T,error,EG).

% summary computation

% for trace T, the SIN -> SOUT transition occurs when G holds
predicate trace_trans(T:t_trace,G:g_guard,SIN:lockstate,SOUT:lockstate).

% compute the transition conditions for each trace T. get the lock state
% at exit and combine with the boolean variable indicating whether the lock
% was locked (LKG) or unlocked (UKG) at entry
cil_cursum(S), sum_bound(S,_,POUT), state(POUT,T,ST,SG), entry_locked(T,LKG,UKG),
    #and(SG,LKG,LKGG), +trace_trans(T,LKGG,locked,ST),
    #and(SG,UKG,UKGG), +trace_trans(T,UKGG,unlocked,ST).

% function FN has summary edge A/SIN/SOUT
predicate fedge(FN:string,S:sum,T:t_trace,SIN:lockstate,SOUT:lockstate).

% combine the transition conditions with the return-non-zero conditions
% to compute all the summary transitions on the current function
cil_curfn(F), cil_cursum(S), trace_trans(T,SG,SIN,SOUT), guard_sat(SG),
    +fedge(F,S,T,SIN,SOUT), +sum_locking(F,S)->sedge(T,SIN,SOUT).

% print out the results
?- fedge(FN,S,A,SIN,SOUT).
