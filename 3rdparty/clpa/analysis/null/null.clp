%%
% Authors:
%   Isil Dillig    <isil@stanford.edu>
%   Thomas Dillig  <tdillig@stanford.edu>
%
% Copyright (c) 2006,
%   The Board of Trustees of The Leland Stanford Junior University
% All rights reserved.
%
% Redistribution and use in source and binary forms, with or without
% modification, are permitted provided that the following conditions are met:
% 
% 1. Redistributions of source code must retain the above copyright notice,
% this list of conditions and the following disclaimer.
% 
% 2. Redistributions in binary form must reproduce the above copyright notice,
% this list of conditions and the following disclaimer in the documentation
% and/or other materials provided with the distribution.
% 
% 3. The names of the contributors may not be used to endorse or promote
% products derived from this software without specific prior written
% permission.
% 
% THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
% AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
% IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
% ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
% LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
% CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
% SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
% INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
% CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
% ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
% POSSIBILITY OF SUCH DAMAGE.
%%

% NULL dereference analysis
% ~~~~~~~~~~~~~~~~~~~~~~~~~~
% General approach:
%
% The errors tracked by the null analysis are of three kinds: 1. A
% variable is set to *explicitly* set to null (or a program variable
% known to be null), and there exists a feasible execution patj through
% which this null value can flow to a site of dereference.
% 2. The condition under which a statement executes implies that a
% dereferenced pointer is null. (e.g. if(!p) *p = ...)
% 3. Inconsistency errors:
%
% Informally, this means that there exist two different program points
% at one of which a certain variable is checked for being NULL, then
% dereferenced, and another program point at which this variable is
% derefernced, but not checked for being NULL.  Consider expressions E1
% and E2 that get dereferenomit_entryced at two different program points
% P1 and P2, with guards P1G and P2G. Let GLS (a guarded location set)
% for an expression E be a list of <memory location, guard> pairs such
% that expression E points to memory location ML under its respective
% guard MLG.For an inconsistency warning to be generated, the following
% conditions must hold:
%
% 1) SAT(E1 = NULL, P1G) i.e Expression E1 may evaluate to NULL under
% the condition guarding this program point.
%
% 2) UNSAT(E2 = NULL, P2G). i.e Expression E2 may not evaluate to NULL
% under the current guard.
%
% 3) GLS(E1) = GLS(Eside_effect_edg2).  i.e It is not provable under our
% system that expressions E1 and E2 may point to different memory
%locations.



% IMPORTANT: DO NOT RUN THIS ANALYSIS WITH THE ALIAS ANALYSIS
% ENABLED-the two are not compatible.


% Don't report null return errors.
predicate no_null_return().

% Introduce disjoint guards when incorporating functions side effects.
predicate use_disjoint_guards().


predicate ignore_soft_trace_errors().
predicate certain_deref_only().


import "../memory/scalar_sat.clp".
import "../correlations/correlate.clp".
import "./lines.clp".
import "./exp_simp.clp".
import "./error.clp".
%import "../base/cfgdot.clp".
import "../base/utility.clp".
import "./nullbaked.clp".

analyze session_name("cil_body").

+prune_exit_calls(), +use_may_exit_calls().
+use_null_exit().
+omit_trace_recurse(_,_).

+ignore_int_casts().

%+certain_deref_only().

using error.

using intops.

+nesting_split_loops().
+split_loops().
+omit_entry_alias_summary(_).
+omit_exit_alias_summary(_).

% Since the inconsistency analysis generates false positives when
% pointers are compared against one another, we want to treat pointers
% as signed rather than unsigned in some special cases. The reason for
% this is that a comparison such as if(p>q) happens to imply that p
% cannot be null if the branch is taken, but the intended meaning of
% this comparison is not to ensure that p is non-null.

compare_op(OP), notequal(OP,b_eq), notequal(OP,b_ne),  % only <,<=,>,>=
    cil_exp_binop(E,OP,LE,RE,_), 
    cil_exp_cast(LE,LCE,_), exp_tptr(LCE), % LHS is a pointer exp
    cil_exp_cast(RE,RCE,_), exp_tptr(RCE), % RHS is a pointer exp
    +omit_beval(_,E),  % don't evaluate this like normal
    ?beval(P,E,_,_),   % supply new evaluation method
    evals(P,LE,LI), evals(P,RE,RI),  
    sc_cast(LI,sk_int{true,32},CLI), sc_cast(RI,sk_int{true,32},CRI),
    cil_cmp_binop_to_scalar_cmp(OP, CMP),
    #id_g(br_cmp{sc{CMP, CLI, CRI}}, BG),
    #bool_g(true,G), +beval(P,E,BG,G).


% guarded_loc_type
type guarded_loc_type ::= guarded_loc{TRACE: t_trace_val, GUARD: g_guard}.

% trace_deref: Marks traces that involve at least one drf{} using the
% existing trace_derefs predicate.  
predicate trace_deref(in T:t_trace).
trace_deref(T):- ~trace_derefs(T,0).



%Session with the null anaysis summary of FN.
session null_sum(FN:string).


%
% ----------------------------------------------------------------------
% Important note: The predicates below are all sumarry edges. Note that
% the guard included in these predicates may not be the actual
% guard. The interprocedural null analysis uses heuristics to replace
% some guards by "true", even though a side effect or dereference may
% not have happened unconditionally.
% Summary edge: deref_edge.  Trace T is dereferenced inside a called
% function (or the callchain identified by CALL_STACK). The TRACE_GUARD
% is the guard under which the dereferenced expression is accessible
% through T. TRACE_GUARD is useful for the inconsistency analysis. (NB:
% the trace guard is TRUE almost 99% of the time; but if we don't have
% this, we get really strange messages in the rest of the
% cases). NECESSARY_COND indicates a necessary condition for the
% dereference of T to occur.  
% For example, consider a function call such as: foo (0, true); In many
% cases, foo's arguments may be correlated: For example, passing true
% for the second argument may indicate that the first argument of foo is
% non-null. If we can determine that a necessary condition is violated,
% then we can supress all obvious false positives. This would also be
% sound because all program points whpse guards don't violate the
% NECESSARY_COND would still report an error.



predicate deref_edge(CALL_STACK:list[deref_location_type],T:t_trace, 
	TRACE_GUARD:g_guard, NECESSARY_COND:g_guard, EXACT_GUARD: bool).

% This dummy edge gets added to every analyzed function. It's used to 
% determine whether a callee has been analyzed or not.
predicate dummy_edge().

% Summary edge that represents side effects of a function. 
% (This is a more refined form of the same results obtained by the 
% alias analysis).
predicate side_effect_edge(S:t_trace, T:t_trace, G:g_guard). 

% Another summary edge. Trace S is set to NULL in the called function
% under guard G.
predicate null_edge(S:t_trace, G:g_guard).

% Summary edge that is added if the function may retrun null under guard G.
predicate return_edge_null(G:g_guard).

%---------------------------------------------------------------------

% Predicate used to collect side_effect and null_effect edges in one predicate.
predicate all_side_effects(SUM:sum, P:pp, S:t_trace, T:t_trace_val, G:g_guard) order [SUM,P].


% Predicates that denote summary information for loops. 
predicate loop_null_effect(SUM: sum, T:t_trace, G:g_guard).
predicate loop_side_effect(SUM: sum, T1:t_trace, T2:t_trace, G:g_guard).
	

% certain_deref: At program point P, the statement guard G implies that 
% dereference expression ME
% results in a null dereference. (i.e error kind #2 in the intro)
predicate certain_deref(in P:pp, in ME:c_exp, in G:g_guard). 

% certain_deref2: At program point P, the statement guard G does not 
% prevent a null pointer from flowing 
% to the dereference expression ME.(i.e error kind #1 in the intro)
predicate certain_deref2(in P:pp, in ME:c_exp, in G:g_guard). 

%At program point P, memory expression ME may (but is not guaranteed to)
% result in a null dereference.
%A potential null dereference does not cause us to report any errors 
%within the current function, but
%is used to generate function summaries.
predicate potential_deref(P:pp, T:t_trace, TRACE_GUARD:g_guard, 
	STMT_GUARD:g_guard).


% funsum_var: Marks trace V to be included in the deref_edge summary edge.
predicate funsum_var(V:t_trace, TRACE_GUARD:g_guard, 
	STMT_GUARD:g_guard, CALL_STACK:list[deref_location_type]).

% Final version of funsum var to be included in the summary. If there
% are multiple dereferences of the same variable under different guards,
% we collapse them into one entry in the function summary by or'ing all
% the guards under which the dereference is possible.  
predicate filtered_funsum(V:t_trace, TRACE_GUARD:g_guard, STMT_GUARD:g_guard,
CALL_STACK:list[deref_location_type]).


% The predicate below is a heuristic to cut down on false positive
% rate with inconsistencies.Some guards such as if(p | 4 == 1) happen to
% imply that p can never be null under the statement guard,but their
% intended meaning is not to dheck a pointer for being null.
predicate actual_null_guard(in P:pp, in G:g_guard, in ME:c_exp, RES:bool).



% predicate fail_free_inst_guard is another variation on
% inst_guard. If inst_guard fails, fail_free_inst_guard fabriactes the
% guard "true."
predicate fail_free_inst_guard(in SUM:sum, in P:pp, in G1:g_guard, G2:g_guard).
fail_free_inst_guard(SUM, P, G1, G2):- #simplify(G1, SG1), 
	inst_guard(SUM, P, SG1, G2).

%?fail_free_inst_guard(SUM, P, G1, _), ~inst_guard(SUM, P, G1, _),
%  #bool_g(true, TRUE), +fail_free_inst_guard(SUM, P, G1, TRUE).

% Function FN may return null under some possible execution path.
predicate null_return(FN:string, G:g_guard).
dircall(I, F), icall(P0, _, I),  null_sum(F)->return_edge_null(G), 
	fail_free_inst_guard(s_call{I}, P0, G, RG),  +null_return(F, RG). 


% Propagate exit conditions for loops. The reason we need to do this
% is that if a loop terminates if there is a termination condition of
% the form p!=0, this is not visible in the calling context.
 
predicate loop_term_cond(P:pp, G:g_guard).


%Various predicates used for the inconsistency part of the analysis:
% ------------------------------------------------------------
% At expression E, memory location L is known to be not NULL.
predicate checked_loc(EXP:c_exp, L:t_trace_val, G:g_guard, OP:pp).

% auxilary predicate that adds checked_loc when queried if the 
% pointer is indeed checked for being null.
predicate query_checked(P:pp, E:c_exp, G:g_guard, OP:pp).

% same as checked loc, but in the loop denoted by SUM.
predicate loop_checked_loc(S:sum, E:c_exp, T:t_trace, TG:g_guard,OP:pp).
 %The guard is the trace guard to construct GLS later.

% At expression E, memory location L is *NOT* known to be  non-NULL.
predicate unchecked_loc(E:c_exp, L:t_trace_val, G:g_guard, OP:pp).

%At expression E, memory location L may be NULL.
%OP is the original program point where deref occurs
predicate loop_unchecked_loc(S:sum, E:c_exp, L:t_trace, G:g_guard,
	 TG:g_guard, CC:g_guard, OP:pp).

% An unchecked location that was bubbled back up to the outer loop.
predicate mapped_unchecked_loc(P: pp, E:c_exp, L:t_trace, G:g_guard,
	 TG: g_guard, CC:g_guard, OP:pp).
predicate mapped_unchecked_sumloc(P: pp, L:t_trace, G:g_guard,
	 TG: g_guard, CC:g_guard, OP:pp, CALLSTACK:list[deref_location_type],
	 EXACT: bool).

% auxilary predicate that adds unchecked_loc when queried if the
%  pointer is not checked for being null.
predicate query_unchecked(P:pp, E:c_exp, G:g_guard, OP:pp).


% Trace TRACE was dereferenced without being checked for being non-null
% some where down the call chain.  
predicate unchecked_funsum_loc(P:pp,
	CALLSTACK:list[deref_location_type], TRACE:t_trace,
	TRACE_GUARD:g_guard, STMT_GUARD:g_guard, EXACT: bool).

predicate loop_unchecked_funsum_loc(S:sum, CALLSTACK:list[deref_location_type],
	TRACE:t_trace, G:g_guard,
	STMT_GUARD:g_guard, CONT_COND:g_guard, ORIG_PP:pp, EXACT: bool).

%Variable V is checked for NULL at some point in the program. MACRO
%identifies the macro where the check occurs, or 'no' if the check does
% not occur within an expanded macro 

predicate checked_var(LOC:int,
	GLS:list[guarded_loc_type], MACRO:maybe[c_macro]).


% Variables that have not been checked for null.
predicate unchecked_var(P:pp, EXP_STR:string, GLS:list[guarded_loc_type], 
	OP:pp, MACRO:maybe[c_macro]).


%Variables that have been dereferenced without a null check in the callee.
predicate unchecked_funsum_var(P:pp, CALLSTACK: list[deref_location_type],
	 GLS: list[guarded_loc_type], STRING_LOC_LIST:list[string]).


% Guard G is the continuation condition for loop PH.
predicate cont_cond(PH:loop, G:g_guard).


%Returns the body PH of any validly lower-nested sumbody
predicate propagation_point(P:pp, PH:c_stmt, OUT_SUM:sum).


% Need to filter out &*p b/c this is not actually a dereference.
predicate actual_deref(LV:c_lval, ME:c_exp, OFF:c_offset).



actual_deref(LV, ME, OFF):- cil_lval_mem(LV, ME, OFF), 
	~cil_exp_addr(_, LV).

% -----------------------------------------------
% Utility predicate:
% And two booleans: and_bools
predicate and_bools(in G1: bool, in G2: bool, out G: bool).
and_bools(G1, G2, false) :- equal(G1, false).
and_bools(G1, G2, false) :- equal(G2, false).
and_bools(G1, G2, true) :- equal(G1, true), equal(G2, true).

predicate and_bool_list(in BOOL_LIST: list[bool], out RESULT: bool).
and_bool_list(BOOLS, false) :- list_mem(BOOLS, false).
and_bool_list(BOOLS, true) :- ~list_mem(BOOLS, false).





% Predicates that do the namespace conversion for traces included in the
% function summary.
% ----------------------------- 
% new_trace: The trace T inside called function with summary SUM is
% mapped to the trace value NT under guard G in the current calling
%context. Rather than doing just the name space conversion, theis
% predicate retrieves the points-to set associated with the mapped
%pointer, which is necessary for processing deref edges.

predicate new_trace_deref(in SUM: sum, in P:pp, in T:t_trace,
	 NT:t_trace, G:g_guard).


% new_trace: The trace T inside called function with summary SUM is
% mapped to the trace NT under guard G in the current calling context.
predicate new_trace_se(in SUM: sum, in P:pp, in T:t_trace, NT:t_trace,
	 G:g_guard).

% null_trace: Trace T in the called function is mapped to NULL in the 
% current calling context.
predicate null_trace(in SUM: sum, in P:pp, in T:t_trace, G:g_guard).


new_trace_deref(SUM, P, T, TT, TG):-  
   inst_trace(SUM, P, drf{T}, trace{drf{TT}}, TG).

% This is for side effect merging If a pointer is set to NULL, but a
% called function causes it to be initialized, we need to know the
% original trace so we can merge the side effect in the calling context
new_trace_se(SUM, P, T, TT, TG) :-  
   %inst_trace(SUM, P, drf{T}, nrep{_}, _),
   inst_trace(SUM, P, T, trace{TT}, TG).


% This case is for malloc's which have no valid mapping in the 
% calling context -- keep the trace name same.
new_trace_se(SUM, P, T, T ,TRUE) :-
   %~no_second_try_new(SUM, P, T),
   trace_root(T,  temp{_,_}),
   #bool_g(true, TRUE).


predicate no_second_try(SUM:sum, P:pp, T:t_trace).


   null_trace(SUM, P, T, TG):-
  ~no_second_try(SUM, P, T),
   inst_trace(SUM, P, drf{T}, nrep{CONST}, TG), 
   g_nez(CONST, NEZ), ~guard_sat(NEZ).

?null_trace(SUM, P, T, _),
   inst_trace(SUM, P, drf{T}, trace{drf{TT}}, _), 
   trace_soft(SUM, TT, _), +no_second_try(SUM, P, T).

null_trace(SUM, P, T, RG):-
   ~no_second_try(SUM, P, T),
   inst_trace(SUM, P, T, TTT, TG),equal(TTT, trace{TT}),
   ~trace_soft(SUM, TT, _), 
   val(P, TT, nrep{CONST}, G), 
   g_nez(CONST, NEZ), ~guard_sat(NEZ),
   #and(G, TG, RG).

% ---------------------------------------------------------------------

predicate anded_loop_terms(in P:pp, out EXITG:g_guard).

anded_loop_terms(P, EXITG) :- 
	\/loop_term_cond(P, CV):#and_all(CV, EXITG).



% If there is a double derefrence (i.e **p) add the implicit guard that
% p is not null; otherwise we would have found the error earlier.
predicate get_implicit_guard(in SUM:sum, in T:t_trace, out G:g_guard).


get_implicit_guard(SUM, T, NEZ):- sum_body(SUM, P), equal(T, drf{TT}), 
	trace_type(s_func, TT, y_ptr{_}), 
	%type_scalar_kind(y_ptr{PTR}, KIND), 
	traceval_scalar(P, no, trace{T}, sk_int{true, 32}, SCALAR), 
	g_nez(SCALAR, NEZ).

?get_implicit_guard(SUM, T, _), equal(T, drf{TT}), 
	trace_type(s_func, TT, Y), ~equal(Y, y_ptr{_}),
	#bool_g(true, TRUE), +get_implicit_guard(SUM, TT, TRUE).

get_implicit_guard(SUM, T, TRUE) :- ~equal(T, drf{_}), 
	#bool_g(true, TRUE).



% ----------------------------------------------------------------------
predicate get_deref_funcall_loc(in P:pp, in F:string, 
	out DL:deref_location_type).


get_deref_funcall_loc(P, F, deref_location{F, LINE, FILE}):-
	source_line(P, LINE), source_file(P, FILE).
	
	


%------RULES TO DETECT INTERPROCEDURAL & LOOP ERRORS AFTER MAPPING----
% Sum is the summary of called fn/inner loop.

% certain_deref_sum and certain_deref_sum2 are interprocedural versions
% of certain_deref and certain_deref2.
predicate certain_deref_sum(SUM:sum, P:pp, OLD_TRACE:t_trace, 
	NEW_TRACE:t_trace).

predicate certain_deref_sum2(SUM:sum, P:pp, OLD_TRACE:t_trace).

% auxilary predicate used for querying certain_deref_sum and
% certain_deref_sum2.
predicate check_sum_deref(in SUM:sum, in P: pp, 
	in DEREF_TRACE:t_trace, in TRACE_GUARD:g_guard, 
	in STMT_GUARD:g_guard).


% If the ignore_soft_trace flag is on, don't report errors.
predicate check_soft_trace(in P: pp, in T: t_trace).
check_soft_trace(P, T) :- ignore_soft_trace_errors(), 
	sum_body(SUM, P), ~trace_soft(SUM, T, _).

check_soft_trace(P, T) :- ~ignore_soft_trace_errors().



% Conditional misuse=> The statement guard implies that a pointer is
% NULL, but that same pointer is passed to a function which dereferences
% it.
check_sum_deref(SUM, P, DT, FTG, FSG):-
	inst_guard(SUM, P, FSG, NSG),  %can't map guard out.
        inst_guard(SUM, P, FTG, NTG), 

   	inst_trace(SUM, P, drf{DT}, trace{drf{NT}}, TG), 
        check_soft_trace(P, NT),
	%trace_type(s_func, drf{NT}, TYPE), type_scalar_kind(TYPE, KIND), 
	traceval_scalar(P, no, trace{drf{NT}}, sk_int{true, 32}, SCALAR), 
        g_nez(SCALAR, NEZ), g_eqz(SCALAR, EQZ), 

	guard(P, SG),
	anded_loop_terms(P, EXITG),
        and6(SG, NSG, NTG, EQZ, TG, EXITG, TESTG), guard_sat(TESTG), 
	%+print("CHECK SUM DEREF 3: ", DT, NT),
	#and(SG, NEZ, RESG), ~guard_sat(RESG),   
	+certain_deref_sum(SUM, P, DT, NT).

% If the certain_deref_only predicate is on, only report dereferences
% that occur unconditionally.


predicate check_certain_deref_flag(in GI: g_guard, G:g_guard).

check_certain_deref_flag(GI, G) :- certain_deref_only(), #not(GI, NGI),
	 ~guard_sat(NGI), #bool_g(true, G).
check_certain_deref_flag(GI, GI) :- ~certain_deref_only().


% A NULL pointer is passed to a function which dereferences it.
check_sum_deref(SUM, P, DT, FTG, FSGI):-
	check_certain_deref_flag(FSGI, FSG), 
	inst_guard(SUM, P, FSG, NSG),  %if sat fails, can't map guard out.
        inst_guard(SUM, P, FTG, NTG), 
   	null_trace(SUM, P, DT, NULLG), 
	guard(P, SG), 
%	traceval_scalar(P, no, trace{drf{DT}}, sk_int{true, 32}, SCALAR),
	% g_eqz(SCALAR, ISZ),
	anded_loop_terms(P, EXITG), 
	and5(NSG,EXITG,   NTG,NULLG, SG,  RES),
	%+print("STATEMENT GUARD & NULL guard: ", SG,"**********", NULLG),
        guard_sat(RES),
	+certain_deref_sum2(SUM, P, DT).



% -------------------------------------------------------

% inst_side_effect and inst_null_effect predicates are used for
% unifying loop and function summary information.


predicate inst_side_effect(SUM:sum, T1: t_trace, T2:t_trace, G:g_guard).
predicate inst_null_effect(SUM:sum, T:t_trace, G:g_guard).

% --------------------------------------------------
% find enclosing loop or function body for loop summary propagation.
predicate outer_body(in P:pp, in IN_SUM:sum, SUM: sum).


outer_body(P0, IN_SUM, SUM):- ~equal(IN_SUM, s_call{_}),
  sum_body(SUM, P0), SUM \= IN_SUM.

outer_body(P0, IN_SUM, SUM):- equal(IN_SUM, s_call{_}),
  sum_body(SUM, P0).

% -------------------------------------------------

% "dummy predicates" for wrapping function summary edges. 
predicate simulate_side_effects(SUM:sum, T1: t_trace, T2:t_trace, G:g_guard).
predicate simulate_null_effects(SUM:sum, T:t_trace, G:g_guard).
predicate map_unchecked_funsum_loc(in SUM:sum, in P:pp, in T:t_trace,
	 in TG: g_guard, in SG:g_guard, NT:t_trace, NTG:g_guard, NRG:g_guard).


icall(_, _, I), dircall(I, F), null_sum(F)->side_effect_edge(CS, CT, NG), 
+simulate_side_effects(s_call{I}, CS, CT, NG).

iloop(_, _, I), loop_side_effect(s_loop{I}, T, TT, G),  
	+simulate_side_effects(s_loop{I},  T, TT, G).

icall(_, _, I), dircall(I, F), null_sum(F)->null_edge(CS,  NG),  
	+simulate_null_effects(s_call{I},  CS, NG).

iloop(_, _, I), loop_null_effect(s_loop{I}, T, G),  
	+simulate_null_effects(s_loop{I},  T, G).

% -------------------------------------------


% If a variable is passed to a function that initializes it & that
% function is not analyzed, we want to suppress errors on this trace the
% first time this function is analyzed.This is only useful for
% eliminating false positives that arise from the circular structures of
% mutually recursive functions or functions for which source code is not
% available

dircall(I, F), icall(P0, P1, I), 
   ~null_sum(F)->dummy_edge(), cil_instr_call_arg(I,N,_), 
    new_trace_se(s_call{I}, P0, drf{root{arg{N}}}, S, RG), 
    #not(RG, NEG),% +print("MERGE 1: ", P1, S, T),
   +inst_transfer_necessary(s_call{I}, P0, S, NEG), 
   eguard(P0, P1, RG, EG),
   +access(P1, S, write), %IS THIS CORRECT? 
   tostring(P0, ID1), tostring(N, ID2), str_cat(ID1, ID2, ID),
   +vmerge(P1, S, trace{drf{root{temp{ ID, "unknown"}}}}, EG). 


% If a variable is passed as an argument to an indirect call 
% (e.g. a function pointer), invalidate its old traces 
% to avoid false positives. 
% TO DO: Integrate with function pointer analysis.
icall(P0, P1, I), ~dircall(I, _), 
   cil_instr_call_arg(I,N,_), 
    new_trace_se(s_call{I}, P0, drf{root{arg{N}}}, S, RG), 
    #not(RG, NEG),% +print("MERGE 1: ", P1, S, T),
   +inst_transfer_necessary(s_call{I}, P0, S, NEG), 
   eguard(P0, P1, RG, EG),
   +access(P1, S, write), %IS THIS CORRECT?
    tostring(P0, ID1), tostring(N, ID2), str_cat(ID1, ID2, ID),
   +vmerge(P1, S, trace{drf{root{temp{ID, "unknown"}}}}, EG). 

% -------------------------------------------------------------------------
predicate get_nc(in NCI:g_guard, NC:g_guard, EXACT_GUARD: bool).
get_nc(NCI, SNC, true):- #simplify(NCI, SNC), #g_size(SNC, SIZE), 
	lessthan(SIZE, 12).

get_nc(NCI, NC, false):- #simplify(NCI, SNC), #g_size(SNC, SIZE), 
	~lessthan(SIZE, 12), #bool_g(true, NC).




% Process deref_edges & report errors if necessary (i.e based on
% predicates introduced by check_sum_deref). interprocedural error case
% #1: Null pointer is passed to a function which dereferences it. For
% this error kind to be reported, we require an exact necessary
% condition that we computed. If no necessary condition was found or the
% statement guard for the deref was not certain, we don't report an
% error to eliminate false positives.


dircall(I, F), null_sum(F)->deref_edge(CALL_STACK, T, DTG, NC, true),
	equal(CALL_STACK, cons{deref_location{HEAD, _, _}, _}), 
	% use HEAD for error reporting
	icall(P0, _, I), 
	check_sum_deref(s_call{I}, P0, T, DTG, NC), 
	%+print("Deref edge: ", F, T, NC),
	certain_deref_sum2(s_call{I}, P0, T),
	~certain_deref_sum(s_call{I}, P0, T, _),
	trace_string(T, TRACE),
	str_cat(TRACE, " of function ", TEMP1),	
	str_cat(TEMP1, HEAD, TEMP2),
	str_cat(TEMP2, " can evaluate to NULL ", TEMP),
	get_deref_funcall_loc(P0, F, DL),
	+report_error_callstack (P0, "warning_blue", TEMP , 
	"Null pointer is passed to a function which dereferences it.",
	cons{DL, CALL_STACK}).

% interprocedural error case #2: Conditional misuse
dircall(I, F), null_sum(F)->deref_edge(CALL_STACK, T, DTG, NC, _), 
	icall(P0, _, I),
	check_sum_deref(s_call{I}, P0, T, DTG, NC),
	certain_deref_sum(s_call{I}, P0, T, NT),
	trace_string(NT, T_STR),
	str_cat("Variable ", T_STR, TEMP1),	
	str_cat(TEMP1, " evaluates to NULL ", TEMP),
	get_deref_funcall_loc(P0, F, DL),
	+report_error_callstack (P0, "warning_blue", TEMP , 
	"Conditional misuse before function call.",cons{DL, CALL_STACK}).


predicate loop_term_compatible(in P:pp, in T:t_trace, in G:g_guard).

loop_term_compatible(P, T, G):-  
	traceval_scalar(P, no, trace{drf{T}}, sk_int{true, 32}, S),  
	g_eqz(S, EQZ), anded_loop_terms(P, EXITG), 
	and3(EQZ, EXITG, G, TESTG), guard_sat(TESTG).

% Map trace from function summary and mark as unchecked if the loop
% termination condition does not preclude it.

dircall(I, F),
  null_sum(F)->deref_edge(CALL_STACK, T, DTG, NC, EXACT),  
  icall(P0, _, I),  ~lbody(_, P0),
  map_unchecked_funsum_loc(s_call{I}, P0, T, DTG, NC,  L, NTG, RG), 
  check_soft_trace(P0, L),  
  loop_term_compatible(P0, L, RG),
  get_deref_funcall_loc(P0, F, DL),  %+print("L: ", L, NC, "->", RG),
  +unchecked_funsum_loc(P0, cons{DL, CALL_STACK}, L, NTG, RG, EXACT).



% Same as above, but function call happens inside loop.
dircall(I, F), 
  null_sum(F)->deref_edge(CALL_STACK, T, DTG, NC, EXACT), 
  icall(P0, _, I),  sum_body(s_loop{LOOP}, P0),
  map_unchecked_funsum_loc(s_call{I}, P0, T, DTG, NC,  L, NTG, RG), 
  check_soft_trace(P0, L),
  cont_cond(LOOP, CC),
  loop_term_compatible(P0, L, RG), 
  get_deref_funcall_loc(P0, F, DL), 
  +loop_unchecked_funsum_loc(s_loop{LOOP}, cons{DL, CALL_STACK}, 
  L, NTG, RG, CC, P0, EXACT).

% Translate traces and guards to their equivalents in the calling context.
map_unchecked_funsum_loc(SUM, P0, T, DTG,NC, L,  STG,RFG):- 
  new_trace_deref(SUM, P0, T, V, TG), guard_sat(TG), 
  check_soft_trace(P0, V), 
  val(P0, V, trace{drf{L}}, LG), 
  traceval_scalar(P0, no, trace{drf{L}}, sk_int{true, 32}, SCALAR),
  fail_free_inst_guard(SUM, P0, NC, RFG), 
  %If necessary condition is not satisfied, it won't be marked as unchecked.
  fail_free_inst_guard(SUM, P0, DTG, NTG), 
  and3(NTG, TG,LG, RTG), %new trace guard
  guard(P0, SG), 
  #and(SG, RFG, RG),
  guard_sat(RG), 
  %trace_type(s_func, drf{L}, TYPE),  type_scalar_kind(TYPE, KIND), 
    get_implicit_guard(s_func, L, IG), 
  anded_loop_terms(P0, EXITG),  g_eqz(SCALAR, ISZ), 
  and3(EXITG, RG,ISZ,TESTG), and3(TESTG, RTG, IG,  SATG), 
   guard_sat(SATG),
  #simplify(RTG, STG).

  

isum(P0, _, SUM), simulate_side_effects(SUM,  CS, CT, SEG), 
  new_trace_se(SUM,P0,CS,S,SG), 
  new_trace_se(SUM,P0,CT,TT,TG), 
  inst_guard(SUM, P0, SEG, NSEG), 
  #and(SG, TG, TEMPG),
  #and(TEMPG , NSEG, RG),
  ~equal(drf{S}, TT),
  +all_side_effects(SUM, P0, S, trace{TT}, RG).


isum(P0,_, SUM),
    simulate_null_effects(SUM,  CS, SEG),
    new_trace_se(SUM, P0, CS, S, SG), 
    inst_guard(SUM, P0, SEG, NSEG), 
    #and(SG, NSEG, RG),    
    +all_side_effects(SUM, P0, S, nrep{s_int_const{0, false, 32}}, RG).

% -----------------------------------------------

predicate soft_exp(in E:c_exp).
soft_exp(E):- exp_point(E, P), eval(P, E, trace{T}, _), sum_body(SUM, P), 
  trace_soft(SUM, T, _).



% statement guard implies dereferenced pointer is null (case #2 in the intro)
certain_deref(P, E, G):- evals(P, E, S),  %exp_string(E, EXP), 
  %+print("Certain deref at: ", P, EXP),
  ~soft_exp(E),
  guard_sat(G), 
  g_nez(S, NEZ), 
  #and(G,NEZ,TESTG), 
  ~guard_sat(TESTG), 
  anded_loop_terms(P, EXITG), g_eqz(S, ISZ), and3(ISZ, G, EXITG, TESTG2), 
  guard_sat(TESTG2).

% a possible exceution path exists through which a null pointer
% can reach a deref site. (Case #1 in intro)
certain_deref2(P, E, G):- ~certain_deref(P, E, G), 
  ~soft_exp(E),
  eval(P, E, nrep{CONST}, EG), 
  g_nez(CONST, C_NEZ), ~guard_sat(C_NEZ), 
  evals(P, E, BV),
  g_eqz(BV, ISZ), 
  #and(EG, ISZ, RISZ), 
  #and(RISZ, G, RG), 
  guard_sat(RG), 
  anded_loop_terms(P, EXITG), % make sure no exit condition prevents
  % it from being null.
  and3(G, EXITG, ISZ,TESTG), 
  guard_sat(TESTG).

% -------ERROR REPORTING ---------

actual_deref(_,ME,_), exp_point(ME,P), guard(P, G),
   certain_deref(P, ME, G),
   exp_string(ME, ME_STR), 
   str_cat("Possible NULL dereference of ", ME_STR, TEMP),
   +report_error (P, "warning_red", TEMP, "Intraprocedural  Null error").
   
actual_deref(_,ME,_), 
    exp_point(ME,P), 
    guard(P,GG), 
    certain_deref2(P, ME, GG),
    exp_string(ME, ME_STR), 
   str_cat("Possible NULL dereference of ", ME_STR, TEMP),
   +report_error (P, "warning_red", TEMP, "Intraprocedural Null error").

% ---------------------------------------------------

% The idea here is to check (in theory) that the
% current statemetn guard ONLY excludes NULL.
% In practice, we try to filter out checks of
% the form: if(a & 3)...

actual_null_guard(P, G,ME,true):-
evals(P,ME,SCALAR),
%first,we make sure all 0's with one 1 is possible :..01000000000 (512)
g_eq(s_int_const{512, true, 32}, SCALAR,G1), #and(G, G1, G1RES), 
  guard_sat(G1RES),
  %second,we make sure all 1's is possible :..00000011111111111 (2057)
  g_eq(s_int_const{2057, true, 32}, SCALAR,G2), #and(G, G2, G2RES), 
  guard_sat(G2RES),g_eq(s_int_const{1048575, true, 32}, SCALAR, G3), 
  #and(G, G3, G3RES), guard_sat(G3RES),
  % If this is an actual null check, then the negation of the guard 
  % should imply the pointer is null.
  #not(G, NG), g_nez(SCALAR, NEZ), #and(NG, NEZ, SATG), ~guard_sat(SATG).



%query_loop_guard(P, E, T, G), 
sum_bound(s_loop{PH},_,p_lterm{PH,P}),guard(p_lterm{PH,P},EXITG), 
	%+print("EXITG: ",G, "***", EXITG), 
	iloop(P0,P,PH),  econd(P0,P,CG), % match up P!
	% translate EXITG!!!!
	%sum_body(SUM, P),
        %inst_guard(s_loop{PH}, P0, EXITG0, EXITG),
	#and(EXITG, CG, RG),  %+print("LOOP TERM COND 2: ", PH,  EXITG),
	+loop_term_cond(P, RG).

sum_bound(s_loop{PH},_,p_lterm{PH,P}),guard(p_lterm{PH,P},EXITG0), 
	%+print("EXITG: ",G, "***", EXITG), 
	iloop(P0,P,PH),  econd(P0,P,CG), % match up P!
	% translate EXITG!!!!
	%sum_body(SUM, P),
        inst_guard(s_loop{PH}, P0, EXITG0, EXITG),
	#and(EXITG, CG, RG),  %+print("LOOP TERM COND 2: ", PH,  EXITG),
	+loop_term_cond(P, RG).




loop_term_cond(P0, EXITG), econd(P0, P1, G), 
	%+print("LOOP TERM COND 1: ", EXITG, "AND HERE IS G: ", G),
	guard_sat(G), +loop_term_cond(P1, EXITG).

% -----------------------------------------------------------------------


% The trace guard TG implies T is non-null. If p aliases q only when
% q!=NULL, we don't want to mark dereference as a potential deref. This
% is meant to prevent an issue that comes up for deref edges in function
% summaries.


predicate tg_implies(in P: pp, in T: t_trace, in TG: g_guard, in SG:g_guard).
tg_implies(P, T, TG, SG) :- 
        #and(TG, SG, G),
	traceval_scalar(P, no, trace{drf{T}}, sk_int{true, 32}, SCALAR), 
	g_eqz(SCALAR, EQZ),
	#and(EQZ, G, RG), ~guard_sat(RG).





%Mark unchecked locations. Special treatment of loops.
query_unchecked(P, E, G, OP), ~lbody(_, P),  
 eval(P, E, trace{drf{T}}, TG), 
 check_soft_trace(P, T), 
 get_implicit_guard(s_func, T, IG),
 evals(P,E,S), 
 g_nez(S,NEZ), 
 #and(G,NEZ,TESTG1), guard_sat(TESTG1),   %not a certain dereference
 %~loop_return_checks_scalar(P, S, G),
 anded_loop_terms(P, EXITG), 
 g_eqz(S, ISZ), 
 #and(G,ISZ,TEMP), #and(TEMP, EXITG, TESTG), #and(TESTG, IG, TESTG2),
 guard_sat(TESTG2),  %but can potentially be null
 and3(TG, G, IG, RG), guard_sat(RG), 
 #simplify(TG, STG), 
 ~tg_implies(P, T, STG, G),
 +potential_deref(P, T, STG, G),

 +unchecked_loc(E, trace{T}, STG, OP).



%Mark unchecked locations. Special treatment of loops.
query_unchecked(P, E, G, OP), ~lbody(_, P),
 eval(P, E, nrep{C}, TG),
 evals(P,E,S), 
 g_nez(S,NEZ),#and(G,NEZ,TESTG1), guard_sat(TESTG1), 
 %not a certain dereference
 anded_loop_terms(P, EXITG),
 g_eqz(S, ISZ), #and(G,ISZ,TEMP), #and(TEMP, EXITG, TESTG), 
 guard_sat(TESTG),  %but can potentially be null
 #and(TG, G, RG), guard_sat(RG),
 #simplify(TG, STG), 
 +unchecked_loc(E, nrep{C}, STG, OP).



query_unchecked(P, E, G, OP), lbody(PH, P), 
 eval(P, E, trace{drf{T}}, TG),  
 check_soft_trace(P, T),
 evals(P,E,S), 
 g_nez(S,NEZ),#and(G,NEZ,TESTG1), guard_sat(TESTG1), 
 %not a certain dereference
 g_eqz(S, ISZ), #and(G,ISZ,TESTG), guard_sat(TESTG), 
 %but can potentially be null
 #and(TG, G, RG), guard_sat(RG), 
 #simplify(TG, STG), 
 %#and(STG, G, RES),
 cont_cond(PH, CC), 
 %exp_string(E, STR), +print("LOOP UNCHECKED: ", STR, T),
 ~tg_implies(P, T, STG, G),
 +loop_unchecked_loc(s_loop{PH}, E, T, STG, G, CC, OP).

% -------------------------------------------------------------------

actual_deref(_,ME,_),  exp_point(ME,P), guard(P,G), 
    +query_unchecked(P,  ME, G, P),
    unchecked_loc(ME, trace{T}, _,_),
    %Check for the dereference of variable coming from a function 
    %that could return null!
    equal(T, root{temp{_, FN_NAME}}),  null_return(FN_NAME, RETG), 
    #and(G, RETG, TESTG), #not(TESTG, NTESTG), ~guard_sat(NTESTG), 
    str_cat("Return value from function ", FN_NAME, TEMP1), 
    str_cat(TEMP1, " may be null.", TEMP),
    +report_error (P, "warning_green", TEMP, "Return Null error").

% Remember continuation condition for loops.
lentry(PH,_), 
    guard(p_lnext{PH},XG), 
    +cont_cond(PH,XG). 

% ISZ is not implied by the continuation condition of loop PH.
predicate not_loop_guard(in PH: loop, in ISZ:g_guard).
not_loop_guard(PH, ISZ):- cont_cond(PH, CONT),% +print("CONT: ",CONT),
  #and(ISZ, CONT, REAL_CHECK), %+print("ISZ: ", ISZ),
  guard_sat(REAL_CHECK).

% same as not_loop_guard; takes a guard as input instead of the loop. 
predicate not_loop_guard_prop(in CC:g_guard, in ISZ:g_guard).

not_loop_guard_prop(CONT, ISZ):-
  #and(ISZ, CONT, REAL_CHECK),
  guard_sat(REAL_CHECK).
% --------------------------------------------------------------------

predicate prop_loop(P:pp, PH:c_stmt, OUT_SUM:sum, CONT:g_guard).

% Find closest enclosing loop.
predicate direct_nested_loop(in P:pp, in PH:c_stmt, SUM:sum). 
direct_nested_loop(P0,PH, SUM):- sum_body(SUM, P0), SUM \= s_loop{PH},
	lbody(LOOP,P0), cont_cond(LOOP, CONT),
	+prop_loop(P0, PH, SUM, CONT).

% Is P a propagation point for loop summaries?
propagation_point(P0, PH, SUM):- iloop(P0, _, PH), 
	direct_nested_loop(P0, PH, SUM).


propagation_point(P0, PH, SUM):- iloop(P0, _, PH), 
	~lbody(_, P0), sum_body(SUM, P0).

% map traces between different name spaces.
predicate inst_map_trace(in P:pp, in OT:t_trace, in OG:g_guard, 
	NT:t_trace, NTG:g_guard). 

inst_map_trace(P0, OT, OG, DT, SRES):- iloop(P0, _, PH),  
	new_trace_deref(s_loop{PH}, P0, OT, NT, TG), 
	val(P0, NT, trace{drf{DT}}, DTG), % IS THIS CORRECT?
	fail_free_inst_guard(s_loop{PH}, P0, OG, NG), 
        #and(NG, TG, TEMP),
	#and(TEMP, DTG, RES), %new trace guard
	#simplify(RES, SRES).

% --------------------------------------------------------------------

%Takes care of both unchecked_funsum_loc and normal unchecked_loc.
predicate map_unchecked_locs(in SUM:sum, in P0:pp, in T:t_trace, 
	in STG:g_guard, in RG:g_guard, in CC:g_guard, NT:t_trace, 
	NSTG: g_guard, NRG:g_guard, NCC:g_guard).

map_unchecked_locs(SUM, P0, T, STG, RG, CC, NT, RES1, RES2,NCC):-
	fail_free_inst_guard(SUM, P0, RG, NRG),  
	fail_free_inst_guard(SUM, P0, CC, NCC),
	inst_map_trace(P0, T, STG, NT, RES1),
	guard(P0, SG),
	#and(NRG, SG, RES2).
% ------------------------------------------------------------

% propagate dereferences across loops, report error if a dereferenced
% pointer is resolved to be null in one of the outer loops/function
% body.

propagation_point(P0, PH, _),
	loop_unchecked_loc(s_loop{PH}, E, T, STG, RG, CC, OP),
        map_unchecked_locs(s_loop{PH}, P0,T, STG, RG, CC, NT, RES1, RES2, NCC),
        +mapped_unchecked_loc(P0, E, NT, RES1, RES2, NCC, OP).

propagation_point(P0, PH, _),
	loop_unchecked_funsum_loc(s_loop{PH}, CALLSTACK, T, STG, 
	RG, CC, OP, EXACT),
        map_unchecked_locs(s_loop{PH}, P0, T, STG, RG, CC, NT, RES1, 
	RES2, NCC),
        +mapped_unchecked_sumloc(P0, NT, RES1, RES2, NCC, OP, 
	CALLSTACK, EXACT).


propagation_point(P0, PH, _), 
	loop_unchecked_loc(s_loop{PH}, E, T, STG, RG, _, OP),
	check_soft_trace(P0, T),
	%lbody(PH, PP), ~access(PP, T, write), 
	check_sum_deref(s_loop{PH},P0, T, STG, RG), 
	certain_deref_sum2(s_loop{PH}, P0, T),
        ~certain_deref_sum(s_loop{PH}, P0, T, _),
        trace_string(T, TRACE),
        exp_string(E, EXP),
        str_cat4("Possible NULL dereference of ", EXP, " with trace ",
	TRACE, TEMP4),
        +report_error (OP, "warning_red", TEMP4, 
	"Intraprocedural error with loop summary propagation").

propagation_point(P0, PH, _), 
	loop_unchecked_funsum_loc(s_loop{PH}, CALLSTACK, T, STG, RG, 
	_, OP, true), %require us to know the correct necessary cond
	#bool_g(true, RG),
	check_soft_trace(P0, T), 
	equal(CALLSTACK, cons{deref_location{HD, _, _}, _}),
	check_sum_deref(s_loop{PH},P0, T, STG, RG), 
	certain_deref_sum2(s_loop{PH}, P0, T),
        ~certain_deref_sum(s_loop{PH}, P0, T, _),
        trace_string(T, T_STR),
	str_cat("Trace ", T_STR, TEMP1),
	str_cat(TEMP1, " of function ", TEMP2),
	str_cat(TEMP2, HD, TEMP3), 
	str_cat(TEMP3, 
	" evaluates to NULL and is dereferenced through call chain: ", TEMP),
	+report_error_callstack(OP, "warning_blue", TEMP, 
	"Interprocedural Null error with loop summary propagation", CALLSTACK).


propagation_point(P0, PH, _),
	loop_unchecked_loc(s_loop{PH}, E, T, STG, RG, _, OP),
	check_soft_trace(P0, T),
	check_sum_deref(s_loop{PH}, P0, T, STG, RG),
	certain_deref_sum(s_loop{PH}, P0, T, NT),
        exp_string(E, EXP),
        trace_string(NT, TRACE),
        str_cat4("Possible Null dereference of ", EXP, " with trace ", 
	TRACE, TEMP4),
        +report_error (OP, "warning_red", TEMP4, 
	"Intraprocedural conditional error with loop summary propagation").

propagation_point(P0, PH, _),
	loop_unchecked_funsum_loc(s_loop{PH}, CALLSTACK, T, STG, RG, _, 
	OP, true),
	check_soft_trace(P0, T), equal(CALLSTACK, 
	cons{deref_location{HD, _, _}, _}),
	check_sum_deref(s_loop{PH}, P0, T, STG, RG),
	certain_deref_sum(s_loop{PH}, P0, T, NT),
        trace_string(NT, T_STR),
        str_cat("Variable", T_STR, TEMP1),
	str_cat(TEMP1,  " of function ", TEMP2),
	str_cat(TEMP2, HD, TEMP3),
	str_cat(TEMP3, 
	"evaluates to NULL and is dereferenced through callchain: ", TEMP),
        +report_error_callstack (OP, "warning_blue", TEMP, 
	"Interprocedural Null error with loop summary propagation", CALLSTACK).
%--------------------------------------------------------------------
% propagate checked location across loops
iloop(P0, _, PH), loop_checked_loc(s_loop{PH}, E, T, G, OP),
   	direct_nested_loop(P0, PH, SUM),
	inst_map_trace(P0, T, G, NT, RES),
        +loop_checked_loc(SUM, E, NT, RES, OP).

iloop(P0, _, PH), loop_checked_loc(s_loop{PH}, E, T, G, OP),
        ~lbody(_, P0),
	inst_map_trace(P0, T, G, NT, RES),
        +checked_loc(E, trace{NT}, RES, OP).

% map checked locations
mapped_unchecked_loc(P, E, NT, TG, FG, _, OP), 
   check_soft_trace(P, NT),
   ~prop_loop(P, _, _, _), 
  % trace_type(s_func, drf{NT}, TYPE), type_scalar_kind(TYPE, KIND), 
   traceval_scalar(P, yes{E}, trace{drf{NT}}, sk_int{true, 32}, SCALAR),  
   g_eqz(SCALAR, ISZ), anded_loop_terms(P, EXITG),
   and4(ISZ, FG,TG, EXITG, RG), 
   guard_sat(RG),
   ~tg_implies(P, NT, TG, FG),
   +potential_deref(OP, NT, TG, FG), 
   +unchecked_loc(E, trace{NT}, TG, OP).
% -----------------------------------------------

% map unchecked locations originating from function calls
mapped_unchecked_sumloc(P,  NT, TG, FG, _, OP, CALLSTACK, EXACT),
   check_soft_trace(P, NT),
   ~prop_loop(P, _, _, _),
    % trace_type(s_func, drf{NT}, TYPE), type_scalar_kind(TYPE, KIND), 
   traceval_scalar(P, no, trace{drf{NT}}, sk_int{true, 32}, SCALAR),  
   g_eqz(SCALAR, ISZ), anded_loop_terms(P, EXITG),
   and4(ISZ, FG,TG, EXITG, RG), 
   guard_sat(RG),
   %+potential_deref(OP, NT, TG, FG), 
   +unchecked_funsum_loc(OP,  CALLSTACK, NT, TG, FG, EXACT).

mapped_unchecked_loc(P, E, NT, TG, SG, CC1, OP), 
   check_soft_trace(P, NT),
   prop_loop(P, _, SUM, CC2), 
    %trace_type(s_func, drf{NT}, TYPE), type_scalar_kind(TYPE, KIND), 
   traceval_scalar(P, yes{E}, trace{drf{NT}}, sk_int{true, 32}, SCALAR),  
   g_eqz(SCALAR, ISZ), 
   #and(CC1, CC2, RCC),
   not_loop_guard_prop(RCC, ISZ), 
   anded_loop_terms(P, EXITG), and4(ISZ, EXITG, SG,TG, RG),
   guard_sat(RG),
   +loop_unchecked_loc(SUM, E, NT, TG, SG, RCC, OP).

mapped_unchecked_sumloc(P,  NT, TG, SG, CC1, OP, CALLSTACK, EXACT), 
   check_soft_trace(P, NT),
   prop_loop(P, _, SUM, CC2), 
  %  trace_type(s_func, drf{NT}, TYPE), type_scalar_kind(TYPE, KIND), 
   traceval_scalar(P, no, trace{drf{NT}}, sk_int{true, 32}, SCALAR),  
   g_eqz(SCALAR, ISZ), 
   #and(CC1, CC2, RCC),
   not_loop_guard_prop(RCC, ISZ), 
   and3(ISZ, SG,TG, RG),
   guard_sat(RG),
   %guard(P, LG), #and(LG, SG, NSG),
   +loop_unchecked_funsum_loc(SUM, CALLSTACK, NT, TG, SG, RCC, OP, EXACT).

mapped_unchecked_loc(P, E, NT, TG, SG, CC, OP), 
   check_soft_trace(P, NT),
   ~prop_loop(P, _, _, _),
   %evalbv(P, E, BV),
  % trace_type(s_func, drf{NT}, TYPE), type_scalar_kind(TYPE, KIND), 
  % +print("KIND: ", KIND),
   traceval_scalar(P, yes{E}, trace{drf{NT}}, sk_int{true, 32}, SCALAR), 
   g_eqz(SCALAR, ISZ), 
   #and(ISZ, SG, RG), %not sure if this should include trace guard
   ~guard_sat(RG),
   actual_null_guard(P, SG, E, true),
   not_loop_guard_prop(CC, ISZ),
   +checked_loc(E, trace{NT}, TG, OP).

mapped_unchecked_loc(P, E, NT, TG, SG, CC1, OP), 
   check_soft_trace(P, NT),
   prop_loop(P, LOOP, SUM, CC2),
   %  trace_type(s_func, drf{NT}, TYPE), type_scalar_kind(TYPE, KIND), 
   traceval_scalar(P, yes{E}, trace{drf{NT}}, sk_int{true, 32}, SCALAR),   
   g_eqz(SCALAR, ISZ), 
   #and(ISZ, SG, RG), %not sure if trace guard should be anded in.
   ~guard_sat(RG),
   actual_null_guard(P, SG, E, true),
   not_loop_guard(LOOP, ISZ),
   #and(CC1, CC2, RCC),
    not_loop_guard_prop(RCC, ISZ),
   +loop_checked_loc(SUM, E, NT, TG, OP).

%---------------------------------------------------------
% someone queried whether a pointer is checked for null by invoking 
% query_checked. 
% Add checked_loc predicate is statement guard ensures the dereferenced 
% pointer cannot be null.
query_checked(P, E, G, OP), ~lbody(_, P),
    actual_null_guard(P, G, E, true),
    evals(P,E,S), guard_sat(G),
    eval(P, E, trace{drf{T}}, TG),   %match on traces
    check_soft_trace(P, T),
    g_eqz(S, ISZ), #and(G,ISZ,TESTG), 
    ~guard_sat(TESTG),
    actual_null_guard(P,G,E,true),
    #simplify(TG, STG),
    #and(TG, G, RG), guard_sat(RG),
   %exp_string(E, STR), +print("CHECKED: ", STR, T),
    +checked_loc(E, trace{T}, STG, OP).

query_checked(P, E, G, OP), ~lbody(_, P),
    actual_null_guard(P, G, E, true),
    evals(P,E,S), guard_sat(G),
    eval(P, E, nrep{C}, TG),  %match on constant
     % exp_string(E, STR), +print("CHECKED: ", STR),
    g_eqz(S, ISZ), #and(G,ISZ,TESTG), 
   ~guard_sat(TESTG),
    actual_null_guard(P,G,E,true), 
    #simplify(TG, STG),
    #and(TG, G, RG), guard_sat(RG),
    +checked_loc(E, nrep{C}, STG, OP).

query_checked(P, E, G, OP), sum_body(S, P),
   sum_body(s_loop{LOOP}, P),
   actual_null_guard(P, G, E,true),
    evals(P,E,SCALAR), guard_sat(G),
    eval(P, E, trace{drf{T}}, TG),
    check_soft_trace(P, T),
    g_eqz(SCALAR, ISZ), #and(G,ISZ,TESTG), 
    ~guard_sat(TESTG),
    actual_null_guard(P,G,E,true),
    not_loop_guard(LOOP, ISZ),
    #simplify(TG, STG),
    #and(TG, G, RG), guard_sat(RG),
    +loop_checked_loc(S, E, T, STG, OP).

actual_deref(_,ME,_),  exp_point(ME,P), 
  guard(P, G), +query_checked(P, ME, G, P).

  
% --------------------------------------------------------------

% Branch statements can also check that a pointer is null or 
% non-null even though that pointer may never be dereferenced.
% Match on explicit branches to check this.

branch(P,P0,_,E), ~lbody(_, P),  
  branch_take(P,P0,G), guard_sat(G), pointer_exp(E, PE),  
   evals(P,PE,S),  
  g_eqz(S, ISZ), 
  #and(G, ISZ, RG),  ~guard_sat(RG), 
  actual_null_guard(P0,G,PE,true),
  eval(P, PE, trace{drf{L}}, TG), 
  check_soft_trace(P, L),
  #simplify(TG, STG),
 +checked_loc(PE, trace{L}, STG, P).

branch(P,P0,_,E), ~lbody(_, P),  
  branch_take(P,P0,G), guard_sat(G), pointer_exp(E, PE),  
   evals(P,PE,S),  
  g_eqz(S, ISZ), 
  #and(G, ISZ, RG),  ~guard_sat(RG), 
  actual_null_guard(P0,G,PE,true),
  eval(P, PE, nrep{C}, TG), 
  #simplify(TG, STG),
 +checked_loc(PE, nrep{C}, STG, P).

branch(P,_,P1,E), ~lbody(_, P), 
  branch_take(P,P1,G), guard_sat(G), pointer_exp(E, PE), 
  evals(P,PE,S),  
  g_eqz(S, ISZ), 
  #and(G, ISZ, RG),   ~guard_sat(RG),
  actual_null_guard(P1,G,PE,true),
  eval(P, PE, trace{drf{L}}, TG),
  check_soft_trace(P, L),
  #simplify(TG, STG),
  +checked_loc(PE, trace{L}, STG, P).

branch(P,_,P1,E), ~lbody(_, P), 
  branch_take(P,P1,G), guard_sat(G), pointer_exp(E, PE), 
  evals(P,PE,S),  
  g_eqz(S, ISZ), 
  #and(G, ISZ, RG),   ~guard_sat(RG),
  actual_null_guard(P1,G,PE,true),
  eval(P, PE, nrep{C}, TG),
  #simplify(TG, STG),
  +checked_loc(PE, nrep{C}, STG, P).

branch(P,P0,_,E), sum_body(s_loop{PH}, P),
  branch_take(P,P0,G), guard_sat(G), pointer_exp(E, PE),  
   evals(P,PE,S),  
  g_eqz(S, ISZ), 
  g_nez(S, NEZ),
    not_loop_guard(PH, ISZ),
    not_loop_guard(PH, NEZ),
  #and(G, ISZ, RG),  ~guard_sat(RG), 
  actual_null_guard(P0,G,PE,true),
  eval(P, PE, trace{drf{L}}, TG), 
  #simplify(TG, STG),
 check_soft_trace(P, L),
 +checked_loc(PE, trace{L}, STG, P).

branch(P,P0,_,E), sum_body(s_loop{PH}, P),
  branch_take(P,P0,G), guard_sat(G), pointer_exp(E, PE),  
   evals(P,PE,S),  
  g_eqz(S, ISZ), 
  g_nez(S, NEZ),
    not_loop_guard(PH, ISZ),
    not_loop_guard(PH, NEZ),
  #and(G, ISZ, RG),  ~guard_sat(RG), 
  actual_null_guard(P0,G,PE,true),
  eval(P, PE, nrep{C}, TG), 
  #simplify(TG, STG),
 +checked_loc(PE, nrep{C}, STG, P).

branch(P,_,P1,E), sum_body(s_loop{PH}, P),
  branch_take(P,P1,G), guard_sat(G), pointer_exp(E, PE), 
  evals(P,PE,S),  
  g_eqz(S, ISZ), 
  g_nez(S, NEZ), 
  not_loop_guard(PH, ISZ),
  not_loop_guard(PH, NEZ),
  #and(G, ISZ, RG),   ~guard_sat(RG),
  actual_null_guard(P1,G,PE,true),
  eval(P, PE, trace{drf{L}}, TG),
  #simplify(TG, STG),
  check_soft_trace(P, L),
  +checked_loc(PE, trace{L}, STG, P).


branch(P,_,P1,E), sum_body(s_loop{PH}, P),
  branch_take(P,P1,G), guard_sat(G), pointer_exp(E, PE), 
  evals(P,PE,S),  
  g_eqz(S, ISZ), 
  g_nez(S, NEZ), 
  not_loop_guard(PH, ISZ),
  not_loop_guard(PH, NEZ),
  #and(G, ISZ, RG),   ~guard_sat(RG),
  actual_null_guard(P1,G,PE,true),
  eval(P, PE, nrep{C}, TG),
  #simplify(TG, STG),
  +checked_loc(PE, nrep{C}, STG, P).

% -------------------------------------------------------------------------
% Unification of checked and unchecked locations.

predicate unified_checked_loc(E:c_exp, T:t_trace_val, G:g_guard, P:pp, 
	MACRO:maybe[c_macro]).
predicate unified_unchecked_loc(E:c_exp, T:t_trace_val, G:g_guard, P:pp, 
	MACRO:maybe[c_macro]).
predicate unified_unchecked_sumloc(P:pp, 
	CALLSTACK:list[deref_location_type], TRACE_CALLER:t_trace_val, 
	TRACE_GUARD:g_guard, EXACT: bool).

% We don't want to report inoncistency errors that result from a macro
% checking a pointer for being NULL; thus, we need to remember which
% macro (if any) the check is coming from. We want to report an
% inconsistency error only if: 1. A pointer is not checked in a used
% macro, but the function checks this pointer for NULL. 2. There is an
% inconsistency within the same macro. Note that we don't report errors
% that result from a macro using another macro, with the first one
% checking the pointer for NULL, and the other one not checking it for
% NULL. The reason for this is that although macros are generally
% inconsistent with each other about the assumptions they make about
% pointers, they usually don't result in errors, and are likely to be
% considered false positives by the developers. Also, nested macros are
% impossible to inspect, see the red-black tree macros in OpenSSH.



predicate checked_loc_with_macro_id(E:c_exp, T:t_trace_val, G:g_guard, 
	P:pp, MACRO:maybe[c_macro]).
predicate unchecked_loc_with_macro_id(E:c_exp, T:t_trace_val, G:g_guard, 
	P:pp, MACRO:maybe[c_macro]).

% get the macro containing an expression, or 'no' if none exists
predicate maybe_exp_macro(in E:c_exp,MACRO:maybe[c_macro]).
maybe_exp_macro(E,yes{MACRO}):- cil_exp_x_macro(E,MACRO).


maybe_exp_macro(E,no):- ~cil_exp_x_macro(E,_).

checked_loc(E, T, G, P), maybe_exp_macro(E,MACRO), 
	+checked_loc_with_macro_id(E, T, G, P, MACRO).
unchecked_loc(E, T, G, P), maybe_exp_macro(E,MACRO), 
	+unchecked_loc_with_macro_id(E, T, G, P, MACRO).

% Make sure every trace occurs exactly once. 
checked_loc_with_macro_id(E, T, _, P, MACRO), 
	\/checked_loc_with_macro_id(E, T, G, P, MACRO):#or_all(G, RG), 
	#simplify(RG, SRG), +unified_checked_loc(E, T, SRG, P, MACRO).


unchecked_loc_with_macro_id(E, T, _, P, MACRO_ID), 
	\/unchecked_loc_with_macro_id(E, T, G, P, MACRO_ID):#or_all(G, RG),  
	#simplify(RG, SRG), +unified_unchecked_loc(E, T, SRG, P, MACRO_ID).


unchecked_funsum_loc(P, CALLSTACK,TRACE_CALLER ,_, _, _),
  \/unchecked_funsum_loc(P, CALLSTACK, TRACE_CALLER, LG,_, _):#or_all(LG, G), 
  #simplify(G, SRG), 
   \/unchecked_funsum_loc(P, CALLSTACK, TRACE_CALLER, _,_, EX):list_all(EX, 
  EXACT_LIST), and_bool_list(EXACT_LIST, EXACT), 
  +unified_unchecked_sumloc(P, CALLSTACK, trace{TRACE_CALLER}, SRG, EXACT).

unified_checked_loc(ME, _, _, _, MACRO_ID),  
  \/unified_checked_loc(ME, L, MG, _, MACRO_ID):list_all(guarded_loc{L, MG}, 
  LIST),  
 %list_all( guarded_loc{drf{L}, MG}, LIST),
  exp_point(ME, P),
  source_line(P, LOC),
 % +print("CHECKED VAR: ",LOC, LIST),
  +checked_var(LOC, LIST, MACRO_ID).

% Same process as above. Map unchecked locations to unchecked variables, 
% i.e GLS's, which in our analysis
% represent variables. 
unified_unchecked_loc(ME, _,_, OP, MACRO_ID), 
   \/unified_unchecked_loc(ME, L, LG, OP, MACRO_ID):
   list_all(guarded_loc{L, LG}, LIST),
 % list_all(guarded_loc{drf{L}, LG}, LIST), 
   exp_point(ME, P),
   exp_string(ME, ME_STR), %source_loc(P, LOC),
   %+print("UNCHECKED VAR: ",LOC,  LIST),
   +unchecked_var(P, ME_STR, LIST, OP, MACRO_ID).
   

predicate trace_val_string(in T:t_trace_val, out STR:string).
trace_val_string(trace{T}, STR):- trace_string(T, STR).

trace_val_string(nrep{C}, "NULL"):-.

predicate unchecked_funsum_trace(P:pp, CALLSTACK:list[deref_location_type], 
	T:t_trace_val,T_STR:string).

unchecked_funsum_trace(P, CALLSTACK, TRACE, T_STR):- 
	unified_unchecked_sumloc(P, CALLSTACK, TRACE, _, _),
	trace_val_string(TRACE, T_STR).
   
unified_unchecked_sumloc(P, CALLSTACK,_ ,_, _ ),
  \/unified_unchecked_sumloc(P, CALLSTACK, TRACE_CALLER, LG, _): 
  list_all(guarded_loc{TRACE_CALLER, LG}, LIST), 
  \/unchecked_funsum_trace(P, CALLSTACK, _, L_STR):
  list_all(L_STR, STRING_LIST), +unchecked_funsum_var(P, CALLSTACK, 
  LIST, STRING_LIST).



% -----------------------------------------------------------------------

% get the macro name callstack, such that MACRO is at the end and 
% all enclosing macro names precede it

predicate macro_callstack(in MACRO:c_macro,in TAIL:list[string],
	out CALLSTACK: list[string]).
macro_callstack(MACRO,TAIL,cons{NAME,TAIL}) :-
    ~cil_macro_x_parent(MACRO,_), cil_macro_x_name(MACRO,NAME).
macro_callstack(MACRO,TAIL,CALLSTACK) :-
    cil_macro_x_parent(MACRO,PMACRO), cil_macro_x_name(MACRO,NAME),
    macro_callstack(PMACRO,cons{NAME,TAIL},CALLSTACK).

% If there are two occurrences where a variable is once null checked 
% and the other null checked,
% report an inconsistency.


% Inconsistency error #1: 
% This is the case where both the checked and the not checked 
% dereference occurs outside a macro
checked_var(_, V, no), \/checked_var(ME, V, no):list_all(ME, CHECK_LIST),  
  unchecked_var(_, E, V, OP2, no), %source_loc(P, LOC), 
  str_cat("(INCONSISTENT USE) Possible null dereference of variable ", 
  E, TEMP),
  +report_error_check (OP2, "warning_orange", TEMP, "Inconsistency error", 
  CHECK_LIST).

% Inconsistency error #2: 
% This is the case where the check does not occur inside a macro
checked_var(_, V, no), \/checked_var(ME, V, no):list_all(ME, CHECK_LIST),  
  unchecked_var(_, E, V, OP2, yes{MACRO}), %source_loc(P, LOC),
  macro_callstack(MACRO, nil, MACRO_CALLSTACK),
  str_cat("(INCONSISTENT USE) Possible null dereference of variable ", 
  E, TEMP),
  +report_error_check_macro (OP2, "warning_orange", TEMP, 
  "Inconsistency error: Check omitted in macro", CHECK_LIST, MACRO_CALLSTACK).


% Inconsistency error #3: This is the case that involves an
% inconsistency within a macro. NOTE: If there is an inconsistency
% within a widely-used macro, an error will be reported for every
% expansion of this macro. We should do something about this.

checked_var(_, V, yes{MACRO}), \/checked_var(ME, V, yes{MACRO}):
  list_all(ME, CHECK_LIST),  
  unchecked_var(_, E, V, OP2, yes{MACRO}),  
  %the unchecked deref occurs in the same macro as the checked deref.
  cil_macro_x_name(MACRO, MACRO_NAME),
  str_cat("(INCONSISTENT USE) Possible null dereference of variable ", 
  E, TEMP1),
  str_cat(TEMP1, " inside macro ", TEMP2), str_cat(TEMP2, MACRO_NAME, TEMP),
  +report_error_check (OP2, "warning_orange", TEMP, 
  "Inconsistency error: Inconsistency within a macro", CHECK_LIST).

% Inconsistency error #4: Report interprocedural inconsistencies: A
% pointer is checked for being null inside the currently analyzed
% function, but that check is omitted in a function called by the
% currently analyzed function.

checked_var(_, V, no),  \/checked_var(ME, V, no):list_all(ME, CHECK_LIST),
  unchecked_funsum_var(P, CALLSTACK, GLS, STRING_LIST),  %source_loc(P, LOC), 
  equal(GLS, V), 
  str_cat("(INCONSISTENT USE) Possible null dereference ","", TEMP),
	+report_error_check_callstack (P, "warning_violet", TEMP, 
  "Interprocedural inconsistency error", STRING_LIST, CHECK_LIST, CALLSTACK).

% ---------------------------------------------------------------------

% Figure out which pointers should be included in the summary. 
% Note that variable is somewhat misnamed; here it refers to a trace.

% Propagate the dereference of trace T to caller functions.
% TG is the trace guard, SG is the statement guard, 
% NC is the necessary condition for the deref (from the called function).
predicate propagated_funsum_var(T:t_trace, TG:g_guard, SG: g_guard, 
	NC: g_guard, CALL_SITE: deref_location_type, 
	CALLSTACK:list[deref_location_type], 
	EXACT: bool).


% 1. Deereferenced inside a called function
unchecked_funsum_loc(P, cons{CALL_SITE, CALLSTACK}, L, TG, NC, EXACT),  
   guard(P, SG), 
   trace_root(L, arg{_}),
   +propagated_funsum_var(L, TG, SG, NC, CALL_SITE, CALLSTACK, EXACT).

unchecked_funsum_loc(P, cons{CALL_SITE, CALLSTACK},  L, TG, NC, EXACT), 
   guard(P, SG), 
   trace_root(L, glob{_}),
   +propagated_funsum_var(L, TG,SG, NC, CALL_SITE, CALLSTACK, EXACT).

% 2. Dereferenced in the currently unanlyzed function
potential_deref(P, L, TG, SG), cil_curfn(F),
   trace_root(L, arg{_}), get_deref_funcall_loc(P, F, DL),
   +funsum_var(L, TG,SG, [DL]).


potential_deref(P, L, TG, SG), cil_curfn(F),
   trace_root(L, glob{_}),get_deref_funcall_loc(P, F, DL),
   +funsum_var(L, TG,SG, [DL]).

%----------------------------------------------------------------



% Add to function summaries
% If there are dereferences with different call stacks, keep all of them.
% Although keeping all call stacks around is more precise,
% can change this to shortest call stack if scalability becomes a problem.


% If the same trace is dereferenced under many guards, or them 
% together for summary generation.
funsum_var(X, TG,_, _), \/funsum_var(X, TG,G, _):#or_all(G, GR), 
	%only keep one deref site per deref to keep summarysize in control
	\/funsum_var(X, TG, _, DEREF_LOC):list_all(DEREF_LOC, DEREF_LIST), 
	equal(DEREF_LIST, cons{HD, _}),
	+filtered_funsum(X, TG, GR, HD).

% Unify propagated summary dereferences: i.e take the disjunction of
% the guards under which the call occurs (for finding a new necessary
% condition for the dereference) and only include one dereference site
% for this function. Note that NC is the necssary condition for the
% deref inside the called function; so we don't touch this.


predicate filtered_propagated_funsum_var(T:t_trace, TG:g_guard, 
	SG:g_guard, NC: g_guard, CALLSTACK:list[deref_location_type], 
	EXACT: bool).

propagated_funsum_var(T, TG, _, NC, _, CALLSTACK, _), 
	\/propagated_funsum_var(T, TG, SG, _, _, CALLSTACK, _):#or_all(SG, RG),
	\/propagated_funsum_var(T, TG, _, _, LOC, CALLSTACK, _):
	list_all(LOC, LOC_LIST),
	\/propagated_funsum_var(T, TG, _, _, _, CALLSTACK, EX):
	list_all(EX, EXACT_LIST), and_bool_list(EXACT_LIST, EXACT),
	equal(LOC_LIST, cons{HD, _}),
	+filtered_propagated_funsum_var(T, TG, RG, NC, cons{HD, CALLSTACK}, 
	EXACT).


% Given a guard G which is the disjunction of all guards under which a
% certain trace is dereferenced, find a necessary condition for that
% dereference. If there is no such necessary condition is found, then
% assume conservatively that the deref always happens. EXACT_GUARD
% indicates whether the guard we collect is the actual necessary
% condition or the made-up true guard, which corresponds to dereferences
% for which a necessary condition cannot be found.  
predicate necessary_cond_for_deref(in G:g_guard, out NC:g_guard, 
	out EXACT_GUARD:bool).

necessary_cond_for_deref(G, NC, true) :- necessary_cond(G, s_func, NC).
necessary_cond_for_deref(G,NC, false) :- ~necessary_cond(G,s_func,  _),  
	#bool_g(true, NC).


predicate deref_ui(CALL_STACK:list[deref_location_type],T:t_trace, 
	NECESSARY_COND:g_guard).


% Add summary edges after determining necessry condition for the
% dereference if one exists. If no necessary condition for the
% dereference exists, then be conservative and assume the dereference
% always happens.

cil_curfn(F), filtered_funsum(T,TG, G, CALL_STACK), 
	necessary_cond_for_deref(G, NCI, EG1), 
	get_nc(NCI, NC, EG2),  #bool_g(false, FALSE), ~equal(NC, FALSE),
         #simplify(TG, STG), and_bools(EG1, EG2, EXACT_GUARD), 
	+deref_ui(CALL_STACK, T, NC),
	+null_sum(F)->deref_edge(CALL_STACK, T,STG, NC, EXACT_GUARD).

cil_curfn(F), filtered_propagated_funsum_var(T,TG, SG, NC, CALL_STACK, EG1), 
	necessary_cond_for_deref(SG, NNCI, EG2), 
	get_nc(NNCI, NNC, EG3),   #bool_g(false, FALSE), ~equal(NC, FALSE),
	#and(NC, NNC, RNC), and_bools(EG1, EG2, TEMP), 
	and_bools(TEMP, EG3, EXACT_GUARD),
 	+deref_ui(CALL_STACK, T, NC), 
	+null_sum(F)->deref_edge(CALL_STACK, T,TG, RNC, EXACT_GUARD).


%-----------------------------------------------------------------------


% If a function could possibly return NULL and a variable is set to
% the return value of this function, we flag this variable with
% predicate null_return. If it is ever dereferenced without being
% checked we issue a warning. The reason we do this is the following: If
% a function returns NULL, it generalyy does not have to do with the
% flags used by the programmer, but more to do with some kind of
% internal failing. (e,g malloc returns NULL or list_find returns null
% etc.)  

predicate null_return_collect(G:g_guard).

~no_null_return(), cil_stmt_return(S), cil_stmt_return_exp(S,E), 
  exp_point(E, P), exp_tptr(E), eval(P, E, nrep{SCALAR}, EG),
  g_nez(SCALAR, NEZ), ~guard_sat(NEZ), %make sure it's actually null
  guard(P, G),  #and(G, EG, RG),  guard_sat(RG), +null_return_collect(G).


predicate get_return_guard(in RG:g_guard, out NRG:g_guard).
get_return_guard(RG, RG) :- guard_visible(s_func, RG).
get_return_guard(RG, TRUE) :- ~guard_visible(s_func, RG), #bool_g(true, TRUE).

cil_curfn(F),  \/null_return_collect(G):#or_all(G, RG),
	get_return_guard(RG, NRG), 
	 guard_sat(NRG),  +null_sum(F)->return_edge_null(NRG). 

%**************************SIDE EFFECTS*************************

predicate get_side_effects(SUM:sum, P:pp, T:t_trace) order [P,SUM].

% MARK indicates if it is pointer or pointee. If it's a pointee (i.e
% the target deref trace, then MARK is true, meaning that, if the trace
% is a temp, it needs to be marked. This bool is only meaningful for
% functions.

predicate include_loc(in SUM:sum , in T:t_trace, in MARK:bool).

predicate add_summary_edges(FN:string, T:t_trace).
predicate add_loop_edges(SUM:sum, T:t_trace).


% Predicate for debugging
predicate print_loop_effects(SUM:sum, P:pp, T:t_trace).

% Visibility excludes return values.
predicate visible(in SUM:sum, in T:t_trace).
visible(SUM, T):- ~trace_alloc(SUM, T, ak_stack_local), ~trace_root(T, return).

include_loc(SUM, T, M):- equal(SUM, s_loop{_}), ~trace_alloc(SUM, T, ak_stack_local),
	~trace_root(T, cstr{_}).

include_loc(s_func, T, false):- visible(s_func, T),  
	~trace_root(T, cstr{_}), ~trace_root(T, temp{_, _}).

include_loc(s_func, T, true):- ~trace_alloc(s_func, T, ak_stack_local).


% determine side effects of the current function at the exit points
get_side_effects(SUM, P, T),
	%+print("INST SIDE EFFECT: ", SUM, T),
	val(P, T, trace{PT},G), 
	%+print("INST SIDE EFFECT 2: ", SUM, T, PT).
	~equal(drf{T}, PT),
	include_loc(SUM, T, false),
   	include_loc(SUM, PT, true),
	+inst_side_effect(SUM, T, PT, G).

get_side_effects(SUM, P, T),
	val(P, T, nrep{SCALAR},G),
	g_nez(SCALAR, NEZ), ~guard_sat(NEZ), 
	include_loc(SUM, T, false),
	+inst_null_effect(SUM, T,G).

 
cil_curfn(F), sum_bound(s_func,_,P), access(XP,X,write), sum_body(s_func,XP),
   +get_side_effects(s_func, P, X),
   +add_summary_edges(F, X).


% For the null analysis, object sensitivity is not very important. 
%We do not want to keep track of different allocation sites in the summary.
predicate unify_side_effects(in X:t_trace, Y:t_trace, G:g_guard).
unify_side_effects(X, Y, RG):- 
	inst_side_effect(s_func, X, Y, _), 
	~equal(Y, drf{root{temp{_, _}}}), 
	\/inst_side_effect(s_func, X, Y, G):#or_all(G, RG).


unify_side_effects(X, drf{root{temp{RESULT_ID, FNNAME}}}, RG):-
	 inst_side_effect(s_func, X, 
	drf{root{temp{_, FNNAME}}}, _), 
	\/inst_side_effect(s_func, X, drf{root{temp{_, FNNAME}}}, G):
	#or_all(G, RG),
        \/inst_side_effect(s_func, X, drf{root{temp{ID, FNNAME}}}, _):
	list_all(ID, LIST), 
        str_cat_list(LIST, RESULT_ID).




predicate unify_null_effects(in T:t_trace, G:g_guard).
unify_null_effects(S, RG):- \/inst_null_effect(s_func, S, G):#or_all(G, RG).


add_summary_edges(F,  X), 
   unify_side_effects(X, Y, G),
   %+print("SIDE EFFECT: ", X, Y),
   #bool_g(true, TRUE),
   guard_sat(G),

   +null_sum(F)->side_effect_edge(X, Y, TRUE).


add_summary_edges(F, S),
  unify_null_effects(S, G),
  #not(G, NG),
  ~guard_sat(NG), 
  #bool_g(true, TRUE), 
  +null_sum(F)->null_edge(S, TRUE).



% add predicates that denote loops ummaries 
add_loop_edges(SUM, X),
   inst_side_effect(SUM, X, Y, RG),
   ~equal(X, drf{Y}),
   guard_sat(RG), 
   #bool_g(true, TRUE),
   +loop_side_effect(SUM, X, Y, TRUE).
 
add_loop_edges(SUM,S), 
  inst_null_effect(SUM, S, RG), guard_sat(RG),
 #not(RG, NG), 
 ~guard_sat(NG), 
 #bool_g(true, TRUE), 
 +loop_null_effect(SUM, S, TRUE).

% add summary edges for loops
sum_body(SUM, P), equal(SUM, s_loop{PH}),  sum_bound(SUM, _, P), 
	equal(P, p_lterm{PH,_}), 
	access(PP, T, write), sum_body(SUM, PP),
	+get_side_effects(SUM, P, T),
	+add_loop_edges(SUM, T).

% just for debugging
print_loop_effects(SUM, P, T),
	inst_null_effect(SUM, T, G),
	+print("LOOP NULL EFFECT: ", SUM, P, T, G).

print_loop_effects(SUM,P,  T),
	inst_side_effect(SUM, T, TT, G),
	+print(SUM, P, T, TT, G).

%--------------------disjoint----------------------------
% use entry_bit() to compute the initial targets and (disjoint) guards for S.
% TGTS includes all traces besides drf{S} that S might point to, and DTGTS
% includes drf{S} as well (with all leftover conditions as the guard)

predicate disjoint_guards(in P:pp,in S:t_trace,in TGTS:list[t_trace_val],
	in PG:g_guard, DTGTS:list[t_pair[t_trace_val,g_guard]]).

% Rules to introduce disjoint guards instead of just true for
% may-happen side effects.Currently not in use because our heuristics
% lose meaning with multiple nested loops.


disjoint_guards(P,S,nil,PG,cons{pair{trace{drf{S}},PG},nil}):-.

disjoint_guards(P,S,cons{trace{T},TAIL},PG,cons{pair{trace{T},CPG},DTAIL}):- entry_bit(P,S,T,BG),
    #and(BG,PG,CPG), #not(BG,NBG), #and(NBG,PG,NPG),
    disjoint_guards(P,S,TAIL,NPG,DTAIL).


disjoint_guards(P,S,cons{nrep{BV},TAIL},PG,
    cons{pair{nrep{BV},CPG},DTAIL}):-
    entry_bit(P,S,drf{root{arg{999}}},BG),  
    #and(BG,PG,CPG), #not(BG,NBG), #and(NBG,PG,NPG),
    disjoint_guards(P,S,TAIL,NPG,DTAIL).

% simulate side effects of functions at call sites.

use_disjoint_guards(), isum(P0, P1, SUM), 
	outer_body(P0, SUM, _),
	all_side_effects(SUM,P0, S,_,_), 
	\/all_side_effects(SUM,P0, S,RT,_):list_all(RT, LIST),
        #bool_g(true,TG),  disjoint_guards(P1,S,LIST,TG,DTGTS),
        list_mem(DTGTS,pair{T,G}),
	eguard(P0, P1, G, EG),
        +access(P1, S, write), %IS THIS CORRECT?
	+vmerge(P1, S, T, EG).

~use_disjoint_guards(), isum(P0, P1, SUM), 
	outer_body(P0, SUM, _),
	all_side_effects(SUM,P0, S,T,_), 
	\/all_side_effects(SUM,P0,  S, T, G):#or_all(G, RG), 
         #not(RG, NEG), %+print("MERGE 1: ", P1, S, T),
        +inst_transfer_necessary(SUM, P0, S, NEG), 
        eguard(P0, P1, RG, EG),
        +access(P1, S, write), %IS THIS CORRECT? 
	+vmerge(P1, S, T, EG).

%add dummy edge
cil_curfn(FN), +null_sum(FN)->dummy_edge().

