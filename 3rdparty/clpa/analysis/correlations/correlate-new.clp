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

import "../memory/scalar_sat.clp".
%import "../base/cfgdot.clp".
import "../base/utility.clp".
import "./scalar-helpers.clp".

% ------------------------------------------------
% TODO:
% - Currently, we don't propagate return_pred correlations. Consider, for example:

% int bar(int*p){
%	if(p!=0) return 0;
%	else return -1;
% } 

%and some foo

% void foo(int* p){
%	if(bar(p)>=0) *p=..
% }

% We can't find necessary/sufficient conditions for the deref of p. 
% We must fix this.

%-----------------------------------------------
% FUNCTIONALITY:
% ---------------
% The predicate "necessary_cond determines an externally visible necessary (and possibly much simpler)
% condition for a given guard.
%
%
%
% The predicate "sufficient_cond" determines an externally visible sufficient condition for a given guard.
%
%
% Potential usage for these predicates: 
% Many programmers pass flags to ensure that a certain event does or does not happen in a called function.
% For example, if a flag is false, a pointer is never dereferenced or a variable is uninitialized etc. 
% These publicly exported predicates can be useful for determining these kinds of correlations between "events"
% of interest and arguments of a function. In other words, they can allow for path-sensitive function summaries that 
% do not contain unwanted noise, in the form of (potentially very long) irrelevant conditions.
% 
% ----------------------------------------

% Publicly exported predicates

% Guard G is a necessary condition for guard SG.
predicate necessary_cond(in SG:g_guard, in SUM:sum, out G:g_guard).

% Guard G is a sufficient condition for guard SG.
predicate sufficient_cond(in SG:g_guard, in SUM:sum, out G:g_guard).


% Auxiliary predicate for this analysis that may be useful for other analyses.
% Trace T is visible outside SUM, but it is not originating from heap data (i.e does not involve temp).
% This is a modigication of trace_visible implementation from traces.clp.
predicate visible_non_heap_trace(in SUM:sum, in T:t_trace).


% ----------------------------------------------------------------------
% Predicate to disable the correlation analysis.
% If this predicate is added, all sufficient conditions are computed as
% false and all necessary conditions are true.
predicate ignore_correlation().

% Predicate to make correlation analysis not do anything. implies ignore
% correlation
predicate disable_correlation().

disable_correlation(), +ignore_correlation().

%+ignore_correlation().

necessary_cond(SG, SUM, True) :- ignore_correlation(),
	#bool_g(true, True).

sufficient_cond(SG, SUM, False) :- ignore_correlation(),
	#bool_g(false, False).

% --------------------------------------------------------------------

% Predicates used by the topdown-correlation analysis that we need.

% Session associated with function F.
session td_corr(F:string).

% The relevant return condition of this function.
predicate ret_cond(G:g_guard).

% T is a trace which is known to evaluate to a particular value
% at some call site.
predicate const_arg(T:t_trace).

% ---------------------------------------------------------------

% Processed versions of necessary and sufficient condition.

predicate mod_nc(SG:g_guard, SUM:sum).
predicate mod_sc(SG:g_guard, SUM:sum).

predicate ncond(SG:g_guard, SUM:sum, G:g_guard).
predicate scond(SG:g_guard, SUM:sum, G:g_guard).


% -------------------------------------------------------------------
% Find all relevant predicates. 
% "Relevant" predicates are all of the predicates inside if statements
% and those discovered at the calling context by the topdown-correlation
% analysis.

% G is an atomic predicate inside an if statement
% in this function.
predicate pred(G:g_guard).

% All guards inside branches should be marked as pred.
~disable_correlation(), 
	branch(P, _, _, _), branch_take(P, _, G),
	guard_visible(s_func, G), 
	+pred(G).

% All guards inside branches should be marked as pred.
%split_loops(), branch(P, _, X, _), ~equal(X, p_lterm{_,_}), branch_take(P, _, G),
%	guard_visible(s_func, G), 
%	+pred(G).
% ---------------------------------------------------

predicate guard_local_trace(in G:g_guard, out T:t_trace).

guard_local_trace(G, T) :-
	guard_trace_used(G, T), trace_root(T, local{_}).



predicate guard_visible_except(in G: g_guard, in T:t_trace).

guard_visible_except(G, T) :-
    ~(guard_used(G,su_scalar{s_unconstrained{V,_}}),
      ~equal(V, vr_t{T}), guard_local_vector(s_func,V)).

% Determine condition under which a loop never executes.
% Guard involves a local trace, and trace has a write access to
% it prior to loop entry. Loop continuation conditions
% are only used as necessary conditions, never as sufficient
% conditions.
predicate loop_pred(G:g_guard, TermG: g_guard).  

~disable_correlation(), 
	split_loops(), 
	branch(P, _, p_lterm{PH, _}, _),branch_take(P, _, G),
	guard_local_trace(G, drf{T}), 
	guard_visible_except(G, drf{T}),	
	access(FuncP, T, write),~lbody(PH,FuncP), access(P1, T, read),
	lbody(PH, P1), val(p_lsum{PH}, T, nrep{Val}, ValG),
	#bool_g(true, True), guard_equivalent(ValG, True),
	guard_trace_to_scalar(G, drf{T}, Val, TermG),
	+pred(TermG),
	+loop_pred(G, TermG).




% ---------------------------------------------------------------------
% T is a trace collected as relevant at some call site.
predicate call_trace(T: t_trace). 

~disable_correlation(), 
	cil_curfn(F), td_corr(F)->const_arg(T),
	+call_trace(T).

% -----------------------------------------------------------

% The candidate predicate only uses traces that are in the original guard,
% or only uses traces that are in the return
% value guard.
predicate check_pred_trace(in G: g_guard, in Pred:g_guard).

check_pred_trace(G, Pred) :- 
	~(guard_trace_used(Pred, T), ~guard_trace_used(G, T)).

check_pred_trace(G, Pred) :-
	return_pred(_, RetG),
	~(guard_trace_used(Pred, T), ~guard_trace_used(RetG, T)).
	


	

% -------------------------------------------------------
% For a guard G, Pred is a potentially interesting predicate
% which should be checked for necessary and sufficient conditions.
% If the predicate involves a return value, Pred is the guard inside the current
% function which causes that class of return values to be returned. 
% For example, if a function returns -1 under flag, Pred1 will be flag, but
% ReturnPred will be ret{foo} == -1.
% For predicates that do not involve return values of other functions,
% these two predicates will be the same. 
% Treating relevant predicates this way allows the implementation to
% avoid special-casing.

predicate relevant_pred(in G: g_guard, in Kind:string, out Pred:g_guard, out ReturnPred: g_guard).


% An atomic predicate used within this function is deemed relevant if
% all the traces it uses are marked as relevant by the topdown analysis.
relevant_pred(G, Kind, Pred, Pred) :-  
	pred(Pred), 
	~(guard_trace_used(Pred, drf{T}), ~call_trace(T)),
	check_pred_trace(G, Pred).
	%~(guard_trace_used(Pred, T), ~guard_trace_used(G, T)),
	%+print("RELEVANT PRED: ", G, "*******************", Pred).

relevant_pred(G, Kind, G, G) :-  
	~pred(G), ~(#id_g(br_abit{_}, G); #id_g(br_ioverflow{_},G)),
	~(guard_trace_used(G, drf{T}), ~call_trace(T)).

relevant_pred(G, "necessary", ReplacedFuncPred, ReturnPred) :-
	return_pred(ReturnPred, FuncPred),
	replace_ret_corrs_nc(FuncPred, ReplacedFuncPred).

relevant_pred(G, "sufficient", ReplacedFuncPred, ReturnPred) :-
	return_pred(ReturnPred, FuncPred),
	replace_ret_corrs_sc(FuncPred, ReplacedFuncPred).

relevant_pred(G, Kind, Pred, TermPred) :-
	loop_pred(Pred, TermPred),
	~(guard_trace_used(TermPred, drf{T}), ~call_trace(T)).
	


% ----------------------------------------------------------

% G is true/false
predicate bool_cond(in G:g_guard).

% ---------------------------------------------------------
% For guard G, the current k-limiting depth Level.
% Originally, this is set to 0, and increased eventually 
% if a sufficient/necessary condition is not found.
% A k-limited sufficient condition is a disjunction of
% clauses containing at most k conjunctions, and a
% k-limited necessary condition is a conjunction
% of clauses containing at most k disjunctions.
predicate level(G:g_guard, SUM:sum, Kind: string, Level:int).

~disable_correlation(), mod_nc(G, SUM),+level(G,SUM, "necessary", 1).
~disable_correlation(), mod_sc(G, SUM), +level(G, SUM, "sufficient", 1).

% -----------------------------------------------------------

% For guard G, the maximum k-limit for Kind is MaxLevel.
% MaxLevel level also indicates the level for which a relevant
% condition is found. If none are found, MaxLevel will be the maximum number
% of predicates that are common to predicates that are common between those that
% are marked at call sites and that occur within G.
predicate max_level(G:g_guard, SUM:sum, Kind: string, MaxLevel:int).

~disable_correlation(), 
level(G, SUM, Kind, _), \/level(G, SUM, Kind, Level):list_all(Level, LevelList),
	list_length(LevelList, Length), +max_level(G, SUM, Kind, Length).
% -----------------------------------------------------------

% predicate k-level-pred
% Given Limit k and a string ("necessary" or "sufficient"),
% returns a k-limited guard. If this is queried for necessary 
% conditions, the k-limited guard involves only disjunctions,
% if its queried for sufficient conditions, it involves only
% conjunctions.
predicate k_level_pred(in Limit: int, in NS: string, in G:g_guard, 
	out Pred:g_guard, out ReturnPred:g_guard).


k_level_pred(Limit, Kind, Guard, Pred, ReturnPred):-
	equal(Kind, "necessary"),
	equal(Limit, 1), 
	relevant_pred(Guard, Kind, Pred, ReturnPred),
	guard_sat(Pred).

% Loop termination conditions are never sufficient conditions
% but if the guard involves the loop continuation condition,
% then it is a necessary condition.
k_level_pred(Limit, Kind, Guard, Pred, ReturnPred):-
	equal(Kind, "sufficient"),
	equal(Limit, 1), 
	relevant_pred(Guard, Kind, Pred, ReturnPred),
	~loop_pred(Pred, ReturnPred),
	guard_sat(Pred).



k_level_pred(Limit, Kind, Guard, SimpResultPred, ResultReturnPred):-
	~equal(Limit, 1), 
	equal(Kind, "necessary"), 
	int_add(Limit, -1, NewLimit),
	k_level_pred(NewLimit, Kind, Guard, Pred, ReturnPred),
	relevant_pred(Guard, Kind, NewPred, NewReturnPred),
	%make sure Pred does not imply NewPred
	#not(Pred, NotPred),
	#and(NotPred, NewPred,TestG),
	guard_sat(TestG),
	#or(NewPred, Pred, ResultPred), 
	#or(ReturnPred, NewReturnPred, ResultReturnPred), 
	#simplify(ResultPred, SimpResultPred),
	#bool_g(true, True), ~equal(True, SimpResultPred),
	guard_sat(SimpResultPred).
	 

k_level_pred(Limit, Kind, Guard, SimpResultPred, ResultReturnPred):-
	~equal(Limit, 1), 
	equal(Kind, "sufficient"), 
	int_add(Limit, -1, NewLimit),
	k_level_pred(NewLimit, Kind, Guard, Pred, ReturnPred),
	relevant_pred(Guard, Kind, NewPred, NewReturnPred),
	~loop_pred(NewPred, NewReturnPred),
	#not(NewPred, NotNewPred),
	#and(NotNewPred, Pred, TestG),
	guard_sat(TestG),
	#and(NewPred, Pred, ResultPred),
	#and(ReturnPred, NewReturnPred, ResultReturnPred),
	#simplify(ResultPred, SimpResultPred),
	#bool_g(false, False), ~equal(False, SimpResultPred),
%	+print("K LEVEL: ", Guard, Limit,"*******", ResultReturnPred),
	guard_sat(SimpResultPred).



% ------------------------------------------------------------

% Test one specific predicate for being necessary/sufficient cond.
predicate test_pred(SG:g_guard, SUM:sum, Pred:t_pair[g_guard,g_guard], Kind:string, Level:int).


% NECESSARY CONDITION
~disable_correlation(), 
	test_pred(SG, SUM, pair{Pred, ReturnPred}, "necessary", Level),
        #not(Pred, NG),  #and(SG, NG, TESTG), ~guard_sat(TESTG), 
 	+unify_necessary_cond(SG, SUM,  Level, ReturnPred),
	+unify_nc_return(SG, SUM, Level, Pred).

% SUFFICIENT CONDITION
~disable_correlation(), 
	test_pred(SG, SUM, pair{Pred, ReturnPred}, "sufficient", Level),
	%+print("SUFFICIENT: ", SG, "***", ReturnPred),               
        #not(SG, NG),  #and(Pred, NG, TESTG), ~guard_sat(TESTG), 
 	+unify_sufficient_cond(SG, SUM,  Level, ReturnPred),
%	equal(Pred, ReturnPred),
	+unify_sc_return(SG, SUM, Level, Pred).

% --------------------------------------------------------------
% Cdr down the list and invoke test_pred on all the preds in the list.
predicate test_pred_list(in SG:g_guard, in SUM:sum, in PredList:list[t_pair[g_guard, g_guard]],
	 in Kind:string, in Level:int).

test_pred_list(SG, SUM, [], Kind, Level) :- . 
test_pred_list(SG, SUM, [Pred|Rest], Kind, Level):-  
	test_pred_list(SG, SUM, Rest, Kind,Level),
	 +test_pred(SG, SUM, Pred, Kind, Level).




% ------------------------------------------------------------------




% Checks all possible k-limited predicates for necessary/sufficient conditions.
% Kind is either the string "sufficient" or "necessary".
predicate test_all_preds_at_depth_k(in SG:g_guard,in SUM: sum, in Kind:string, in Level:int).

test_all_preds_at_depth_k(SG, SUM, Kind, Level):-
	k_level_pred(Level, Kind, SG, _,_),
	\/k_level_pred(Level, Kind, SG, Pred, ReturnPred):
	list_all(pair{Pred, ReturnPred}, PredList),
	~equal(PredList, []),
	test_pred_list(SG,SUM,  PredList, Kind, Level).

%-----------------------------------------------------------------

% Make sure to look for necessary/sufficient conds at lower levels first
predicate next_level(in LV:int, NLV:int) order [LV,NLV].
next_level(LV, NLV) :- int_add(LV, 1, NLV).

~disable_correlation(), 
level(SG, SUM, Kind, Level), equal(Kind, "necessary"),
	test_all_preds_at_depth_k(SG, SUM, Kind, Level),
	% +print("Test all preds at depth k (necessary): ", SG, Level),
	(~unify_necessary_cond(SG,SUM,Level,_);
	(unify_necessary_cond(SG, SUM, Level, G), return_pred(G, _))),
	next_level(Level, NewLevel),
	+level(SG,SUM, Kind, NewLevel).

~disable_correlation(), 
level(SG, SUM, Kind, Level), equal(Kind, "sufficient"),
	test_all_preds_at_depth_k(SG, SUM, Kind, Level),
	% +print("Test all preds at depth k): ", SG, Level),
	(~unify_sufficient_cond(SG,SUM,Level,_);
	(unify_sufficient_cond(SG, SUM, Level, G), return_pred(G, _))),
	next_level(Level, NewLevel),
%	+print("NEXT LEVEL: ", SG, NewLevel),
	+level(SG, SUM, Kind, NewLevel).


% --------------------------------------------------------

% CallSiteGuard: a condition involving a function return value 
% used at a call site of this function.
% ReturnGuard is the guard under which the CallSiteGuard will hold
% within this function.
% Example: Consider the Call site guard return < 0,
% then, the ReturnGuard will be the guard under which return < 0
% will hold, for example, malloc()=NULL.
%
% ReturnGuard is a sufficient condition for the CallSiteGuard.


predicate return_pred(CallSiteGuard:g_guard, ReturnGuard: g_guard ).
predicate return_pred_helper(CallSiteGuard:g_guard, ReturnGuard: g_guard).

predicate unify_return_pred(CallSiteGuardG: g_guard, ReturnGuard: g_guard).


% The expression IE is returned under guard G.
predicate return_exp(IE: scalar, G:g_guard).

~disable_correlation(), 
cil_stmt_return(S), cil_stmt_return_exp(S,E), exp_point(E, P),
	evals(P, E, IE), 
	scalar_flatten(IE, Flat),
	map_to_sorted_list(Flat, FlatList),
	guard(P, G),
	+return_exps(FlatList, G).

predicate return_exps(list[t_pair[scalar, g_guard]], G:g_guard).

~disable_correlation(), 
return_exps([pair{Sc,ScG}|Tl], G), 
	#and(ScG, G, ResG),
	%replace_ret_corrs_sc(ResG, NewResG),
	%+return_exp(Sc, NewResG),
	+return_exp(Sc, ResG),
	+return_exps(Tl, G).

% For those return conditions discovered by the topdown analysis, 
% find the guard under which the comparison will hold.
% For example, if return == -1 is a predicate discovered by the
% topdown analysis and malloc()==NULL is the guard for this return
% statement, remember the relationship between the two guards
% using the return_pred predicate.

% NOTE: This is not the return guard itself, because there may be multiple 
% conditions in the function which imply the return condition. We must
% take the disjunction of all of these conditions to get the guard in this function
% that will guarantee a class of return values to be returned, and vice verca.
% Note that this has to be an equivalence relation for soundness.
~disable_correlation(), 
cil_curfn(F), td_corr(F)->ret_cond(G), 
	return_exp(IE, RG),
	replace_exp_guard(G, IE, NewG), 
	#and(NewG, RG, FuncG),
	#not(FuncG, NotFuncG), guard_sat(NotFuncG), %Not a tautology--important
	+unify_return_pred(G, FuncG).

predicate omit_return_pred(in SG:g_guard, in G:g_guard).
~disable_correlation(), 
return_pred_helper(SG1, _), return_pred_helper(SG2,G2),
	lessthan(SG1, SG2),
        guard_equivalent(SG1, SG2), 
        +omit_return_pred(SG2, G2 ).

	
% Or all the guards that imply the predicate at the call site.
~disable_correlation(), 
	unify_return_pred(G, _), \/(unify_return_pred(G, URG)):#or_all(URG, RG), 
	#simplify(RG, SimpRG),
	+return_pred_helper(G, SimpRG),
	 #not( SimpRG, NRG), #not(G, NG),
	 #simplify(NRG, SimpNRG),
	 +return_pred_helper(NG, SimpNRG).

% Uniquify return_preds so we don't get duplicates.
~disable_correlation(), 
	return_pred_helper(NG, NRG), ~omit_return_pred(NG, NRG),
	\/(return_pred_helper(NG, NRG)):list_all(pair{NG, NRG}, List),
	 equal(List, [pair{G1, G2}|_]), 
	+return_pred(G1,G2).


% -----------------------------------------------------------------
predicate unify_necessary_cond(SG:g_guard, SUM: sum, Level:int, G:g_guard).
predicate unify_sufficient_cond(SG:g_guard, SUM: sum, Level:int,G:g_guard).

% Special version of above that does not includer return values.
% Used for summary generation.
predicate unify_nc_return(SG:g_guard, SUM:sum,  Level:int , ReturnPred:g_guard).
predicate unify_sc_return(SG:g_guard, SUM:sum,  Level:int , ReturnPred:g_guard).

% ----------------------------------------------------------------------

% V is a local trace or unconstrained internal data to SUM
predicate guard_local_vector(in SUM:sum, in V:g_vecrep).

% for direct accesses to non-soft traces, make sure the trace is visible
guard_local_vector(SUM,vr_t{T}) :- ~visible_non_heap_trace(SUM,T).

% pretty much every other type of vector is bad
+guard_local_vector(_,vr_st{_,_,_}).
+guard_local_vector(_,vr_i{_,_}).
+guard_local_vector(_,vr_c{_,_,_}).
+guard_local_vector(_,vr_instscalar{_,_,_}).
+guard_local_vector(_,vr_buffersize{_}).
+guard_local_vector(_,vr_u{_}).

% Guard G is visible if it contains no local vectors
predicate guard_visible(in SUM:sum, in G:g_guard).
guard_visible(SUM,G) :-
    ~(guard_used(G,su_scalar{s_unconstrained{V,_}}), guard_local_vector(SUM,V)).


% True or False
% true
bool_cond(G) :-
	#not(G, NG), ~guard_sat(NG).

bool_cond(G) :- 
	~guard_sat(G).	





% If there are no necessary conditions, set true to be a necessary condition,
% and if there are no sufficient conditions, set false to be a sufficient condition. 

%necessary_cond(SG, SUM, TRUE) :- 
%	~ignore_correlation(),
%	~bool_cond(SG),
%	 max_level(SG, SUM, "necessary", Level),
%	~unify_necessary_cond(SG, SUM, Level, _), #bool_g(true, TRUE),
%	+print("ADD TRUE: ", SG).

%sufficient_cond(SG, SUM, FALSE) :- 
%	~ignore_correlation(),
%	~bool_cond(SG), 
%	 max_level(SG, SUM, "sufficient", Level),
%	~unify_sufficient_cond(SG, SUM,Level, _), #bool_g(false, FALSE).





% throw out redundant necessary conditions: either equivalent or
% implied by another necessary condition
predicate omit_necessary_cond(in SG:g_guard, in SUM: sum, in G:g_guard).
~disable_correlation(), 
unify_necessary_cond(SG, SUM, _, G0), unify_necessary_cond(SG, SUM, _,G1), lessthan(G0,G1),
        (guard_equivalent(G0,G1), OMIT=G1;
         ~guard_equivalent(G0,G1), guard_implies(G0,G1), OMIT=G1;
         ~guard_equivalent(G0,G1), guard_implies(G1,G0), OMIT=G0),
        +omit_necessary_cond(SG, SUM, OMIT).

~disable_correlation(), 
unify_necessary_cond(SG, SUM,_, _),
       \/(unify_necessary_cond(SG, SUM,_, G), ~omit_necessary_cond(SG, SUM, G)):#and_all(G, RG),
       #simplify(RG, SRG), 
       +ncond(SG, SUM, SRG).

% throw out redundant sufficient conditions: either equivalent or
% implying another sufficient condition
predicate omit_sufficient_cond(in SG:g_guard, in SUM: sum, in G:g_guard).
~disable_correlation(), 
unify_sufficient_cond(SG, SUM, _, G0), unify_sufficient_cond(SG, SUM, _,G1), lessthan(G0,G1),
        (guard_equivalent(G0,G1), OMIT=G1;
         ~guard_equivalent(G0,G1), guard_implies(G0,G1), OMIT=G0;
         ~guard_equivalent(G0,G1), guard_implies(G1,G0), OMIT=G1),
        +omit_sufficient_cond(SG, SUM, OMIT).

~disable_correlation(), 
unify_sufficient_cond(SG, SUM,_,  _),
       \/(unify_sufficient_cond(SG, SUM,_, G), ~omit_sufficient_cond(SG, SUM, G)):#or_all(G, RG),
       #simplify(RG, SRG), 
       +scond(SG, SUM, SRG).

% -----------------------------------------------------------------

%{
% Sufficient Condition Propagation

predicate precise_sc(G: g_guard).


% The guard is visible at the call site, so
% we can just propagate it.
propagate_sufficient_cond(InG, Sum, InG) :-
	guard_visible(Sum, InG),
	+precise_sc(InG).


% The guard is not visible, i.e it involves the
% return value of the called function. 
% We check if the return value of this
% function implies the sufficient condition
% of the called function. In this case,
% if we can show at the call site that the
% return value cond for this function
% holds, then so does the ret val of the callee.
% This case is important for wrapper functions.
% See regressions in uninit07 to understand 
% what this is doing.
propagate_sufficient_cond(InG, Sum, CallSiteG) :-
	~guard_visible(Sum, InG),
	return_pred(CallSiteG, ReturnG),
	#not(InG, NotInG),
	#and(NotInG, ReturnG, TestG),
	~guard_sat(TestG),
	+precise_sc(InG).
		
% We couldn't find any precise conditions;
% so we just over-approximate it by false.
propagate_sufficient_cond(InG, Sum, OutG) :-
	~precise_sc(InG),
	#bool_g(false, OutG).
%}

%---------------------------------------------
% Necessary Condition Propagation
%{	
predicate precise_nc(G:g_guard).

propagate_necessary_cond(InG, Sum, InG) :-
	guard_visible(Sum, InG),
	+precise_nc(InG).

propagate_necessary_cond(InG, Sum, CallSiteG) :-
	~guard_visible(Sum, InG),
	return_pred(CallSiteG, ReturnG), 
	#not(ReturnG, NotReturnG),
	#and(InG, NotReturnG, TestG),
	~guard_sat(TestG),
	+precise_nc(InG).


propagate_necessary_cond(InG, Sum, OutG) :-
	~precise_nc(InG),
	#bool_g(true, OutG).

%}	

% -----------------------------------------------------------------
% visible_non_heap_trace implementation
% -----------------------------------
% data originating from locals and stack arguments is fully visible external
% to a loop invocation
visible_non_heap_trace(s_loop{PH},T):- trace_root(T,arg{_}).
visible_non_heap_trace(s_loop{PH},T):- trace_root(T,local{_}).

% as arguments are passed by value, only non-root data originating from
% arguments are visible external to the function itself
visible_non_heap_trace(SUM,T):- trace_root(T,arg{_}), ~trace_derefs(T,0).


% globals and the return value are always visible
visible_non_heap_trace(SUM,T):- trace_root(T,glob{_}).
visible_non_heap_trace(SUM,T):- trace_root(T,return).


% --------------------------------------------------------------------------
% Summary for the correlation analysis
% -------------------------------------------------------------------------
% The summary keeps track of necessary and sufficient conditions for class of 
% return values that are tested at call sites.
% ------------------------------------------------------------------------

% Summary for the correlation analysis.
session corr_sum(F:string).

% Summary edge return_nc: NecessaryCond is a necessary condition  for
% the predicate ReturnCond involving the return value of the current
% function.
  predicate return_nc(ReturnCond:g_guard, NecessaryCond: g_guard).

% Summary edge return_sc: SufficientCond is a sufficient condition  for
% the predicate ReturnCond involving the return value of the current
% function.
  predicate return_sc(ReturnCond:g_guard, SufficientCond: g_guard).

% ------------------------------------------------------------------------
% Special version of necessary condition which discards traces involving
% return values of the current function
predicate necessary_cond_return(in G:g_guard,in SUM:sum, out NC:g_guard).
predicate sufficient_cond_return(in G:g_guard, in SUM:sum, out SC: g_guard).


% throw out redundant necessary conditions: either equivalent or
% implied by another necessary condition
predicate omit_nc_return(in SG:g_guard, in SUM: sum, in G:g_guard).
~disable_correlation(), 
unify_nc_return(SG, SUM, _, G0), unify_nc_return(SG, SUM, _,G1), lessthan(G0,G1),
        (guard_equivalent(G0,G1), OMIT=G1;
         ~guard_equivalent(G0,G1), guard_implies(G0,G1), OMIT=G1;
         ~guard_equivalent(G0,G1), guard_implies(G1,G0), OMIT=G0),
        +omit_nc_return(SG, SUM, OMIT).

% throw out redundant necessary conditions: either equivalent or
% implied by another necessary condition
predicate omit_sc_return(in SG:g_guard, in SUM: sum, in G:g_guard).
~disable_correlation(), 
unify_sc_return(SG, SUM, _, G0), unify_sc_return(SG, SUM, _,G1), lessthan(G0,G1),
        (guard_equivalent(G0,G1), OMIT=G1;
         ~guard_equivalent(G0,G1), guard_implies(G0,G1), OMIT=G1;
         ~guard_equivalent(G0,G1), guard_implies(G1,G0), OMIT=G0),
        +omit_sc_return(SG, SUM, OMIT).

necessary_cond_return(SG, SUM, SRG):-	
 unify_nc_return(SG, SUM, _, _),
      \/(unify_nc_return(SG, SUM,_, G),~omit_nc_return(SG, SUM, G) ):#and_all(G, RG),
       #simplify(RG, SRG).

sufficient_cond_return(SG, SUM, SRG):-	
 unify_sc_return(SG, SUM, _, _),
       \/(unify_sc_return(SG, SUM,_, G), ~omit_sc_return(SG, SUM, G)):#or_all(G, RG),
       #simplify(RG, SRG).

% ----------------------------------------------------------------------
predicate added_guard(G: g_guard).

~disable_correlation(), 
cil_curfn(F), return_pred(ReturnG, FuncG),
	necessary_cond(FuncG,  s_func, _),
	necessary_cond_return(FuncG,s_func, NC),
	guard_visible(s_func, NC),
	+corr_sum(F)->return_nc(ReturnG, NC).
	
%anycall(_, F, _), corr_sum(F)->return_nc(ReturnG, _), 
%	 \/corr_sum(F)->return_nc(ReturnG, NC):list_all(NC, List),
%	 list_length(List, Length), ~equal(Length, 1),
%	+print("CORR SUM-wrong summary ", F, ReturnG, "=>", List).

~disable_correlation(), 
cil_curfn(F), return_pred(ReturnG, FuncG),
	sufficient_cond(FuncG,  s_func, _), 
	sufficient_cond_return(FuncG, s_func, SC),
	guard_visible(s_func, SC),
	+corr_sum(F)->return_sc(ReturnG, SC).

% --------------------------------------------------------

 predicate translate_indirfun_guard(in G:g_guard, in Fname: string,
 				out TranslatedG: g_guard).

 translate_indirfun_guard(G, Fname, TranslatedG) :-
 	guard_trace_used(G, Trace),
 	equal(Trace, drf{root{temp{X, _}}}),
 	replace_guard_trace(G, Trace, drf{root{temp{X, Fname}}}, TranslatedG).


?translate_indirfun_guard(G, Fname, _),
	\/translate_indirfun_guard(G, Fname, T):list_all(T, List),
	list_length(List, Length), ~equal(Length, 1),
	+print("ERROR: Translate indirect fun guard uniqueness failed on: ", Fname).

% ------------------------------------------------------
% Summary application


predicate return_corr_nc(I:c_instr, F:string, ReturnG:g_guard,NC:g_guard).
predicate return_corr_sc(I:c_instr, F:string, ReturnG:g_guard,SC:g_guard).

~disable_correlation(), 
dircall(I, F), icall(P1, _,I), 
	corr_sum(F)->return_nc(ReturnG,  _),
	\/corr_sum(F)->return_nc(ReturnG, N):#and_all(N, NC),
	inst_guard(s_call{I}, P1, NC, TNC),
	+return_corr_nc(I, F, ReturnG, TNC),
	+pred(TNC).

~disable_correlation(), 
 anycall(I, F, _), ~dircall(I, F), icall(P1, _,I), 
 	corr_sum(F)->return_nc(ReturnG, _),
	\/corr_sum(F)->return_nc(ReturnG, N):#and_all(N, NC),
 	inst_guard(s_call{I}, P1, NC, TNC), 
 	cil_instr_call(I, Call), exp_string(Call, Fname),
 	translate_indirfun_guard(ReturnG,  Fname, MappedReturnG),
 	+return_corr_nc(I, F, MappedReturnG, TNC),
 	+pred(TNC).

~disable_correlation(), 
return_corr_nc(I, F, G, _),
	\/return_corr_nc(I, F, G, NC):list_all(NC, List),
	list_length(List, Length), ~equal(Length, 1),
	+print("ERROR: Return corr nc uniqueness failed on: ", F, "\n LIST: ",List, I).

~disable_correlation(), 
dircall(I, F),icall(P1, _,I), 
	corr_sum(F)->return_sc(ReturnG,  _),
	\/corr_sum(F)->return_sc(ReturnG, S):#or_all(S, SC),
	inst_guard(s_call{I}, P1, SC, TSC), 
	+return_corr_sc(I, F, ReturnG, TSC),
	+pred(TSC).

~disable_correlation(), 
 anycall(I, F, _), ~dircall(I, F), icall(P1, _,I), 
	corr_sum(F)->return_sc(ReturnG,  _),
	\/corr_sum(F)->return_sc(ReturnG, S):#or_all(S, SC),
 	inst_guard(s_call{I}, P1, SC, TSC), 
 	cil_instr_call(I, Call), exp_string(Call, Fname),
 	translate_indirfun_guard(ReturnG,  Fname, MappedReturnG),
 	+return_corr_sc(I, F, MappedReturnG, TSC),
 	+pred(TSC).
	


% ----------------------------------------------------------------
predicate replace_ret_corrs_nc(in G:g_guard, out ReplacedG: g_guard).
predicate replace_ret_corrs_nc_safe(in G:g_guard, out ReplacedG: g_guard).
predicate replace_ret_corrs_nc_helper(in G:g_guard, in list[g_guard],
			out ReplacedG: g_guard).



replace_ret_corrs_nc_safe(G, ReplacedG) :-
	get_literals(G, Literals),

	replace_ret_corrs_nc_helper(G, Literals, ReplacedG).


replace_ret_corrs_nc_helper(G, [], G) :- .

replace_ret_corrs_nc_helper(G, [Lit|Tl], FinalG) :-
	guard_trace_used(Lit, drf{root{temp{X, F}}}),
	cil_instr_call(I, Call), exp_string(Call, F),
	anycall(I, Target,_), 
	return_corr_nc(I, Target, RetG, RetNC),
	#not(RetG, NRetG), 
	return_corr_nc(I, Target, RetG2, RetNC2),
	equivalent(RetG2, NRetG),	

	replace_guard_trace(Lit,  drf{root{temp{X, F}}}, drf{root{temp{"", F}}}, NewLit),
	((
		equivalent(RetG, NewLit),
		replace_subguard_atomic(G, Lit, RetNC, ReplacedG),
		replace_ret_corrs_nc_helper(ReplacedG, Tl, FinalG)
	);

	(
		equivalent(NRetG, NewLit),
		replace_subguard_atomic(G, Lit, RetNC2, ReplacedG),
		replace_ret_corrs_nc_helper(ReplacedG, Tl, FinalG)
	);

	(
		
	 	~equivalent(RetG, NewLit),	
		~equivalent(NRetG, NewLit),
		replace_ret_corrs_nc_helper(G, Tl, FinalG)
	)).



replace_ret_corrs_nc_helper(G, [Lit|Tl], FinalG) :-
	~(guard_trace_used(Lit, drf{root{temp{X, F}}}),
	~equal(X, ""),
	cil_instr_call(I, Call), exp_string(Call, F),
	anycall(I, Target,_),
	return_corr_nc(I, Target, _, _)),
	
	replace_ret_corrs_nc_helper(G, Tl, FinalG).



replace_ret_corrs_nc(G, ReplacedG) :-
	\/replace_ret_corrs_nc_safe(G, NC):list_all(NC, List),
	list_length(List, Length),
	(
		(~equal(Length, 1), ReplacedG=G);
		(equal(Length, 1), equal(List, [ReplacedG|_]))
	).
% ----------------------------------------------------------------
predicate replace_ret_corrs_sc(in G:g_guard, out ReplacedG: g_guard).
predicate replace_ret_corrs_sc_safe(in G:g_guard, out ReplacedG: g_guard).
predicate replace_ret_corrs_sc_helper(in G:g_guard, in list[g_guard],
			out ReplacedG: g_guard).

replace_ret_corrs_sc_safe(G, ReplacedG) :-
	get_literals(G, Literals),
	replace_ret_corrs_sc_helper(G, Literals, ReplacedG).


replace_ret_corrs_sc_helper(G, [], G) :- .

replace_ret_corrs_sc_helper(G, [Lit|Tl], FinalG) :-
	guard_trace_used(Lit, drf{root{temp{X, F}}}),
	cil_instr_call(I, Call), exp_string(Call, F),
	anycall(I, Target,_),
	return_corr_sc(I, Target, RetG, RetSC),
	#not(RetG, NRetG), 
	return_corr_sc(I, Target, RetG2, RetSC2),
	equivalent(RetG2, NRetG),	

	replace_guard_trace(Lit,  drf{root{temp{X, F}}}, drf{root{temp{"", F}}}, NewLit),
	((
		equivalent(RetG, NewLit),
		replace_subguard_atomic(G, Lit, RetSC, ReplacedG),
		replace_ret_corrs_sc_helper(ReplacedG, Tl, FinalG)
	);

	(
		equivalent(NRetG, NewLit),
		replace_subguard_atomic(G, Lit, RetSC2, ReplacedG),
		replace_ret_corrs_sc_helper(ReplacedG, Tl, FinalG)
	);

	(
		
	 	~equivalent(RetG, NewLit),	
		~equivalent(NRetG, NewLit),
		replace_ret_corrs_sc_helper(G, Tl, FinalG)
	)).


replace_ret_corrs_sc_helper(G, [Lit|Tl], FinalG) :-
	~(guard_trace_used(Lit, drf{root{temp{X, F}}}),
	~equal(X, ""),
	cil_instr_call(I, Call), exp_string(Call, F),
	anycall(I, Target,_),
	return_corr_sc(I, Target, _, _)),
	replace_ret_corrs_sc_helper(G, Tl, FinalG).



replace_ret_corrs_sc(G, ReplacedG) :-
	\/replace_ret_corrs_sc_safe(G, SC):list_all(SC, List),
	list_length(List, Length),
	(
		(~equal(Length, 1), ReplacedG=G);
		(equal(Length, 1), equal(List, [ReplacedG|_]))
	).

% -----------------------------------------------------------

necessary_cond(G, SUM, NC):-
	~ignore_correlation(),
	replace_ret_corrs_nc(G, ReplacedG),
	((bool_cond(ReplacedG), NC=ReplacedG); 
	~bool_cond(ReplacedG), +mod_nc(ReplacedG, SUM),	
	(ncond(ReplacedG, SUM, NC);
	( \/ncond(ReplacedG, SUM, N):list_all(N, List),
	list_length(List, Length), equal(Length, 0), #bool_g(true, NC)))).

sufficient_cond(G, SUM, SC):-
	~ignore_correlation(),
	replace_ret_corrs_sc(G, ReplacedG),
	((bool_cond(ReplacedG), SC=ReplacedG);
	(~bool_cond(ReplacedG), 
	+mod_sc(ReplacedG, SUM), 
	(scond(ReplacedG, SUM, SC);
	 \/scond(ReplacedG, SUM, S):list_all(S, List),
	list_length(List, Length), equal(Length, 0), #bool_g(false, SC)))).


% -------------------------------------------------------------------
% sanity checking

	
?necessary_cond(G, SUM, _),
	\/necessary_cond(G, SUM, NC):list_all(NC, NCList),
	list_length(NCList, Length),
	~equal(Length, 1),
	+print("Necessary cond uniquness failed on: ", G,
	"\n ", Length, "\n =>", NCList).

?sufficient_cond(G, SUM, _),
	\/sufficient_cond(G, SUM, SC):list_all(SC, SCList),
	list_length(SCList, Length),
	~equal(Length, 1),
	+print("Sufficient cond uniquness failed on: ", G,
	"\n ", Length).

% --------------------------------------------------------------------------
