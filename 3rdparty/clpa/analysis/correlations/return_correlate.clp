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

import "./correlate.clp".

type return_type ::= neg 
		     | zero 
		     | pos
		     .

% -----------------------------------------------------------
% Publically exported predicates:
% ------------------------------


% Global session for the return_correlate analysis.
session ret_sum(FN:string).

% If the return value of the function is RET_TYPE, then there is a constraint on "TRACE" after
% function return as specified in CORRELATION_TYPE by client analyses.
predicate correlation(RET_TYPE: return_type, TRACE: t_trace, CORRELATION_TYPE: string).

% This function never returns this class of return types.
% This is important for the following reason:
% Suppose a function can return only 0 and - integers, but never positive.
% In this case, a chack of the form ret>=0 implies the same constraints as 
% ret ==0, but we cannot know this without explicitly stating this invariant.
predicate implausible_rets(TYPE: return_type).



% Some analyses might want to integrate the return value summary to their own
% summary-specific predicates instead of propagating the return_implication predicate.
% If this is the case, add the predicate "+no_return_implication_propagate()". In this
% case, the return_implication predicate will be introduced only at the call sites, but 
% will not be propagated to other program points by the return_correlate analysis. 
predicate no_return_implication_propagate().


% At program point P, trace T is restricted by the analysis-specific constraint
% as defined by the CORR_TYPE string (which the analysis itself can interpret)
% *if* the current statement guard implies the guard G.
% For example, suppose I have a predicate called UNINIT, which means that at program
% point P, trace T is uninitialized, and suppose that at P, we have:
% return_implication(P, T, "uninit", ret < 0), and suppose that
% the statement guard is at least as restrictive as ret < 0 (e.g ret <0 && flag).
% Then, if the CORR_TYPE string "init" has the same interpretation as the UNINIT predicate,
% we can conclude that at program point P, trace T is known not to be initialized.
% Note that some analyses might want to integrate this return value summary to their own
% summary-specific predicates instead of propagating the return_implication predicate.
% If this is the case, add the predicate "+no_return_implication_propagate()". In this
% case, the return_implication predicate will be introduced only at the call sites, but 
% will not be propagated to other program points by the return_correlate analysis. 
predicate return_implication(P: pp, T:t_trace, CORR_TYPE:string, G:g_guard).

% The guard for the return class type "RET_TYPE" is RET_G. That is,
% if RET_G is satisfied, the function is guaranteed to return
% the class of return types given by "RET_TYPE" (neg, pos, or zero).
%
% This predicate should be used by client analyses in order to get
% the guard for a certain return class. If the particular return
% class is not of interest, just ignore RET_TYPE, and use the guard RET_G
% to determine if there is a correlation between the relevant property
% and the guard for *any* kind of return class (instead of a particular one.) 
predicate query_return_correlation(RET_TYPE:return_type, RET_G:g_guard).


% If a correlation is found, the client analysis must add this predicate 
% if it wants to incorporate this correlation in the
% ret_val summary. 
% G in this predicate is the guard for the return class (so it must be the
% same guard the client analysis gets from query_return_correlation);
% the trace T is the trace for which a correlation between the return class
% guard G and the higher level property exists.
% Finally, CORR_TYPE is a string that identifies the correlation
% type between the return guard and the trace. The reason this
% is a string is that our language does not support higher-order
% predicates, and every client analysis must interpret the correlation
% between the return value and the trace by inspecting this string CORR_TYPE.
predicate return_correlation(RET_TYPE:return_type, T:t_trace, CORR_TYPE: string).


% P is the exit point for loop PH. 
% This predicate should probably be in utility.clp.
predicate loop_exit(P:pp, PH:loop).


% Add this predicate if you want to see the correlations between the return value and
% client-analysis defined higher level property.
predicate print_correlations().

% ----------------------------------------------------------------------------------------
% ----------------------------------------------------------------------------------------


predicate unify_negative_return(NRG:g_guard).
predicate unify_zero_return(ZRG: g_guard).
predicate unify_positive_return(PRG: g_guard).



% Is it possible for this function to return this class of return values?
predicate plausible_return_class(G:g_guard, TYPE:return_type).

% Print return_correlations summary for the current function
% if the print_correlations predicate is added.
predicate print_summary(RET_TYPE: return_type, T:t_trace, CORR_TYPE:string).

% ------------------------------------------------------
% Retrieve guard under which integer expression IE is greater than
% or equal to zero. 
% The correct sign and width values are used in constructed the zero integer
% based on the sign and width of the original expression.

predicate g_gtz(in IE:scalar, out G:g_guard).
predicate g_ltz(in IE:scalar, out G: g_guard).
predicate g_gez(in IE:scalar, out G:g_guard).
predicate g_lez(in IE:scalar, out G: g_guard).
% ---------------------------------------------------------------------

g_gtz(IE, G) :-  scalar_bvec(IE,_, BV), #bv_size(BV, SIGNED, WIDTH), 
	#id_g(br_cmp{sc{sc_gt, IE, s_int_const{0, SIGNED, WIDTH}}}, G).

g_ltz(IE, G) :-  scalar_bvec(IE, _, BV), #bv_size(BV, SIGNED, WIDTH), 
	#id_g(br_cmp{sc{sc_lt, IE, s_int_const{0, SIGNED, WIDTH}}}, G).

g_gez(IE, G) :-  scalar_bvec(IE, _, BV), #bv_size(BV, SIGNED, WIDTH), 
	#id_g(br_cmp{sc{sc_ge, IE, s_int_const{0, SIGNED, WIDTH}}}, G).

g_lez(IE, G) :-  scalar_bvec(IE, _, BV), #bv_size(BV, SIGNED, WIDTH), 
	#id_g(br_cmp{sc{sc_le, IE, s_int_const{0, SIGNED, WIDTH}}}, G).

% --------------------------------------------------------------------------

% Return correlations for functions that return pointers: Only 2 cases => NULL and NON-NULL return.
cil_stmt_return(S), cil_stmt_return_exp(S,E), exp_point(E, P), 
	evals(P, E, IE), g_eqz(IE, EQZ), guard(P, SG), #and(EQZ, SG, RG), 
	+unify_zero_return(RG).
cil_stmt_return(S), cil_stmt_return_exp(S,E), exp_point(E, P), exp_tptr(E),
	evals(P, E, IE), g_nez(IE, NEZ), guard(P, SG), #and(NEZ, SG, RG), 
	+unify_positive_return(RG).

% Do this so that at call site, we automatically deduce this cannot return a negative value
% without having to look at the type.
cil_stmt_return(S), cil_stmt_return_exp(S,E), exp_tptr(E),
	#bool_g(false, FALSE), +unify_negative_return(FALSE).
	


% Return correlations for functions that return integers: 3 cases => NEGATIVE, ZERO, AND POSITIVE return values.
cil_stmt_return(S), cil_stmt_return_exp(S,E), exp_point(E, P), exp_tint(E, _), 
	evals(P, E, IE), g_eqz(IE, EQZ), +print("RETURN GUARD: ", EQZ), guard(P, SG), #and(EQZ, SG, RG), +unify_zero_return(RG).
cil_stmt_return(S), cil_stmt_return_exp(S,E), exp_point(E, P), exp_tint(E, _),
	evals(P, E, IE), g_gtz(IE, GTZ), guard(P, SG), #and(GTZ, SG, RG), 
	+unify_positive_return(RG).
cil_stmt_return(S), cil_stmt_return_exp(S,E), exp_point(E, P), exp_tint(E, _),
	evals(P, E, IE), g_ltz(IE, LTZ), guard(P, SG), #and(LTZ, SG, RG), 
	+unify_negative_return(RG).
 


% Invoke analysis specific predicates.
% This analysis adds a predicate called query_return_correlation, which
% client analyses must match on in order to retrieve guards for "interesting"
% return values (i.e negative, zero, positive; but custom made ones can 
% also be added). Client analyses search a relevant state space, 
% and add a predicate called return_correlation, which the 
% return_correlation analysis can match on if there is a correlation
% between return value and the property of interest.
% An example of how this can be used from the NULL analysis:
% A negative return value sometimes indicates that the initialization of
% a previously NULL pointer value failed or use a 0 return value to indicate
% that a certain pointer is known not to be non-null.
% The null analysis looks at all traces that have a write access to them (i.e the
% state space of relevant traces is ones that have a write access to them), and
% and determines all the conditions under which a certain trace is null.
% If the return-negative (or return zero, or positive) condition is necessary and
% sufficient for this pointer to be NULL, it adds the 
% return correlation predicate with the relevant trace and a string identifying
% the kind of correlation. (e.g correlation between negative return and the pointer
% being null).

unify_zero_return(_), \/unify_zero_return(ZRG):#or_all(ZRG, RG),   %+print("ZRG: ",  RG),
	+plausible_return_class(RG, zero),
	guard_sat(RG),
	+query_return_correlation(zero, RG), return_correlation(zero, T, CORR_TYPE), 
	cil_curfn(FN), +ret_sum(FN)->correlation(zero, T, CORR_TYPE),
	+print_summary(zero, T, CORR_TYPE).

 %, +print("ZERO RETURN OR'ED: ", RG).
unify_negative_return(_), \/unify_negative_return(NEG):#or_all(NEG, RG), %+print("NRG: ",  RG),
	+plausible_return_class(RG, neg),
	guard_sat(RG),
	+query_return_correlation(neg, RG),return_correlation(neg, T, CORR_TYPE), 
	cil_curfn(FN), +ret_sum(FN)->correlation(neg, T, CORR_TYPE),
	+print_summary(neg, T, CORR_TYPE).

	
unify_positive_return(_), \/unify_positive_return(POS):#or_all(POS, RG), 
	+plausible_return_class(RG, pos),
	guard_sat(RG),
	+query_return_correlation(pos, RG), %+print("POS RETURN: ", RG), 
	return_correlation(pos, T, CORR_TYPE), %+print("PRG: ",  RG),
	cil_curfn(FN), +ret_sum(FN)->correlation(pos, T, CORR_TYPE),
	+print_summary(pos, T, CORR_TYPE).
	


% If it cannot return a certian class of return values, state it explicitly.
plausible_return_class(G, CLASS), ~guard_sat(G), cil_curfn(FN), +ret_sum(FN)->implausible_rets(CLASS).



% -------------------------------------------------------------------

% The guard under which the return value (as specified by the integer expression)
% will be of the class specified by RET_TYPE.
predicate return_guard(in FN:string, in IE:scalar, in RET_TYPE:return_type, out G: g_guard).

% CASE1: ZERO return case
% Case1.a: Can return all 3 classes (pos, neg, zero).
return_guard(FN, IE, RET_TYPE, GUARD) :-  equal(RET_TYPE, zero),
	 ~ret_sum(FN)->implausible_rets(pos),  ~ret_sum(FN)->implausible_rets(neg),  g_eqz(IE, GUARD).
% Case1.b: Can return only positive and zero.
return_guard(FN, IE, RET_TYPE, GUARD) :-  equal(RET_TYPE, zero),
	 ~ret_sum(FN)->implausible_rets(pos),  ret_sum(FN)->implausible_rets(neg),  g_lez(IE, GUARD).

% Case1.c: Can return only negative and zero
return_guard(FN, IE, RET_TYPE, GUARD) :-  equal(RET_TYPE, zero),
	 ~ret_sum(FN)->implausible_rets(neg), ret_sum(FN)->implausible_rets(pos),   g_gez(IE, GUARD).

% Case1.d: Can only return zero.
return_guard(FN, IE, RET_TYPE, GUARD) :-  equal(RET_TYPE, zero),
	 ret_sum(FN)->implausible_rets(neg), ret_sum(FN)->implausible_rets(pos), #bool_g(true, GUARD).

% CASE2: NEGATIVE return case
% Case2.a: Can return all 3 classes (pos, neg, zero).
return_guard(FN, IE, RET_TYPE, GUARD) :-  equal(RET_TYPE, neg), 
	~ret_sum(FN)->implausible_rets(zero), ~ret_sum(FN)->implausible_rets(pos), g_ltz(IE, GUARD).

% Case2.b: Can return only negative and zero.
return_guard(FN, IE, RET_TYPE, GUARD) :-  equal(RET_TYPE, neg), 
	ret_sum(FN)->implausible_rets(zero), ~ret_sum(FN)->implausible_rets(pos), g_nez(IE, GUARD).

% Case2.c: Can return only negative and pos.
return_guard(FN, IE, RET_TYPE, GUARD) :-  equal(RET_TYPE, neg), 
	~ret_sum(FN)->implausible_rets(zero), ret_sum(FN)->implausible_rets(pos), #bool_g(true, GUARD).

% Case2.d: Can return only negative.
return_guard(FN, IE, RET_TYPE, GUARD) :-  equal(RET_TYPE, neg), 
	ret_sum(FN)->implausible_rets(zero), ret_sum(FN)->implausible_rets(pos), g_lez(IE, GUARD).


% CASE3: POSITIVE return case
% Case3.a: Can return all 3 classes (pos, neg, zero).
return_guard(FN, IE, RET_TYPE, GUARD) :-  equal(RET_TYPE, pos), 
	~ret_sum(FN)->implausible_rets(zero),  ~ret_sum(FN)->implausible_rets(neg), g_gtz(IE, GUARD).

% Case3.b: Can return only positive and zero
return_guard(FN, IE, RET_TYPE, GUARD) :-  equal(RET_TYPE, pos), 
	~ret_sum(FN)->implausible_rets(zero), ret_sum(FN)->implausible_rets(neg), g_nez(IE, GUARD).

% Case3.c: Can return only positive and negative
return_guard(FN, IE, RET_TYPE, GUARD) :-  equal(RET_TYPE, pos), 
	ret_sum(FN)->implausible_rets(zero), ~ret_sum(FN)->implausible_rets(neg), g_gez(IE, GUARD).

% Case3.d: Can return only positive
return_guard(FN, IE, RET_TYPE, GUARD) :-  equal(RET_TYPE, pos), 
	ret_sum(FN)->implausible_rets(zero), ret_sum(FN)->implausible_rets(neg), #bool_g(true, GUARD).

% ------ SUMMARY-APPLICATION IN CALLING CONTEXT ---------------
% predicate return_implication(P: pp, T:t_trace, CORR_TYPE:string, G:g_guard).

% Save callees summary with the traces mapped into this calling context, 
% just in case the current function wraps a function with a return_correlation
% summary. We only concern ourselves with the case when there is no aliasing
% involving the trace involved in the summary. Otherwise, the concept of
% wrapper starts becoming ill-defined...
predicate callee_wrap(FN:string, RET_TYPE:return_type, T:t_trace, CORR_TYPE:string).

dircall(I, FN), icall(P0, P1, I), ret_sum(FN)->correlation(RET_TYPE, T, CORR_TYPE), 
	inst_trace(s_call{I}, P0, root{return}, trace{RT}, _), % the guard should always be true, so it's irrelevant.
	vals(P0, RT, IE), return_guard(FN, IE, RET_TYPE, GUARD),
	inst_trace(s_call{I}, P0, T, trace{CT}, ITG), %+print("T to CT: ", T, CT, ITG), 
	guard(P0, SG), and3(ITG, SG, GUARD, CORR_GUARD),
	+return_implication(P1, CT, CORR_TYPE, CORR_GUARD),
	#not(ITG, NITG), ~guard_sat(NITG),
	+callee_wrap(FN, RET_TYPE, CT, CORR_TYPE).
	




% Propagate return_implication if it the no_propagate predicate is not added.
~no_return_implication_propagate(), return_implication(P0, T, CORR_TYPE, CORR_GUARD), econd(P0, P1, _), 		  +return_implication(P1, T, CORR_TYPE, CORR_GUARD).


% This function has only one return statement. (looking for wrapper functions...)
predicate one_return().
\/cil_stmt_return(S):list_all(S, ALL_RETS), cil_stmt_return(RS), equal(ALL_RETS, cons{RS, nil}), +one_return(). 


% If a function wraps another one, propagate return correlation summary.
% Do this if the function has exactly one return statement and the trace used
% in the return expression involves only the temp trace from the called function with
% a return_correlation summary.

cil_curfn(CUR_FN), one_return(), cil_stmt_return(S), cil_stmt_return_exp(S,E), exp_point(E, P),
	evals(P, E, IE), \/scalar_trace_used(IE, T):list_all(T, TRACES),
	equal(TRACES, cons{drf{root{temp{_,FN}}}, nil}),
	callee_wrap(FN, RET_TYPE, CT, CORR_TYPE),
	visible_non_heap_trace(s_func, CT),
	+ret_sum(CUR_FN)->correlation(RET_TYPE, CT, CORR_TYPE), 
	+print_summary(RET_TYPE, CT, CORR_TYPE),
	ret_sum(FN)->implausible_rets(CLASS), +ret_sum(CUR_FN)->implausible_rets(CLASS).
		
% ------------------------------------------------------------------------------
predicate ret_type_to_string(in TYPE:return_type, out STR:string).
ret_type_to_string(TYPE, "ZERO") :- equal(TYPE, zero).
ret_type_to_string(TYPE, "NEGATIVE") :- equal(TYPE, neg).
ret_type_to_string(TYPE, "POSITIVE") :- equal(TYPE, pos).

% print summary
print_correlations(), print_summary(RET_TYPE, TRACE, CORR_TYPE), 
	ret_type_to_string(RET_TYPE, RET_STR),
	+print("RETURN TYPE: ", RET_STR, ", CORRELATED TRACE:", TRACE, ", CORRELATION TYPE", CORR_TYPE).


% ------------------------------------------------------------------------------
% loop_exit implementation
sum_body(SUM, P), equal(SUM, s_loop{PH}),  sum_bound(SUM, _, P),  equal(P, p_lterm{PH,_}), +loop_exit(P, PH).



%return_implication(P, T, CORR_TYPE, _), +print("RETURN IMPLICATION: ", P, T, CORR_TYPE).

% Find sufficient conditions for these return events to happen
%zero_return(ZR), sufficient_cond(ZR, s_func, SC), +print("SUFFICIENT COND FOR ZR: ", SC).
%zero_return(ZR), necessary_cond(ZR, s_func, SC), +print("NECESSARY COND FOR ZR: ", SC).

