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

% ---------------------------------------------------------------------
% Topdown pass for interprocedural path-sensitivity analysis.
% This pass determines what return values of functions are checked
% for being a certain value.
% ---------------------------------------------------------------------



import "../memory/scalar.clp".
import "../memory/scalar_sat.clp".
import "../null/lines.clp".
import "./scalar-helpers.clp".

analyze analysis_name("topdown-correlation").
analyze topdown().
 analyze eager().
analyze session_name("cil_body").


+no_entry_aliasing().

% -----------------------------------------------------------

% Session for top-down analysis.
session td_sum(F:string).

% Guard G is a condition which depends on function F's return value.
% The idea is that it someone checks a particular rteurn value of this
% function, it must be relevant.
predicate ret_cond(g_guard).

% ------------------------------------------------------------

% The input scalar does not contain any traces other than 
% trace T.
predicate more_traces(in IE: scalar, in T:t_trace).
more_traces(IE, T1):- scalar_trace_used(IE, T2), ~equal(T1, T2). 

% --------------------------------------------------------------------

predicate ret_trace(in OrigTrace: t_trace, out FnName:string).

ret_trace(OrigTrace, Fname) :-
	equal(OrigTrace, drf{root{temp{_, Fname}}}),
	dircall(_, Fname).

ret_trace(OrigTrace, TargetFun) :-
	equal(OrigTrace, drf{root{temp{_, Fname}}}),
	~dircall(_, Fname), 
	cil_instr_call(I, Call), exp_string(Call, Fname),
	anycall(I, TargetFun, _).

% -------------------------------------------------------------------


% Given a guard OrigGuard which involves a comparison between the
% return value of  a function and a constant, produces a new guard where
% traces corresponding to function return values are renamed as return.
predicate ret_cmp_guard(in OrigGuard:g_guard,
out NewGuard:g_guard, out F:string).

% Case 1.a: Scalar comparison, not negated and
% first integer expression involves a return value trace
ret_cmp_guard(OrigGuard,  RenamedGuard, Fname) :- 
	 #id_g(SG, OrigGuard), equal(SG, br_cmp{sc{OP, IE1, IE2}}),
	 scalar_trace_used(IE1, T), 
	 ~trace_soft(s_func, T, _), ~more_traces(IE1, T),
	 ~scalar_trace_used(IE2, _),
         ret_trace(T, Fname),
	 scalar_trace_rename(IE1, T, drf{root{return}}, NewIE1),
	 #id_g(br_cmp{sc{OP, NewIE1, IE2}}, RenamedGuard).

% Case 1.b sc: Scalar comparison (negated),
% first integer expression involves a return value trace
ret_cmp_guard(OrigGuard,  RenamedGuard, Fname) :- 
	 #not(NegOrigGuard, OrigGuard),
	 #id_g(SG, NegOrigGuard), equal(SG, br_cmp{sc{OP, IE1, IE2}}),
	 scalar_trace_used(IE1, T), 
	  ~trace_soft(s_func, T, _), ~more_traces(IE1, T),
	 ~scalar_trace_used(IE2, _),
         ret_trace(T, Fname),
	 scalar_trace_rename(IE1, T, drf{root{return}}, NewIE1),
	 #id_g(br_cmp{sc{OP, NewIE1, IE2}}, NegRenamedGuard),
	 #not(NegRenamedGuard, RenamedGuard).

% Case 2.a Scalar comparison, not negated,
% and second integer expression involves a return value trace
ret_cmp_guard(OrigGuard,  RenamedGuard, Fname) :- 
	 #id_g(SG, OrigGuard), equal(SG, br_cmp{sc{OP, IE1, IE2}}),
	 ~scalar_trace_used(IE1, _), 
	  scalar_trace_used(IE2, T), 
	 ~trace_soft(s_func, T, _), ~more_traces(IE2, T),
         ret_trace(T, Fname),
	 scalar_trace_rename(IE2, T, drf{root{return}}, NewIE2),
	 #id_g(br_cmp{sc{OP, IE1, NewIE2}}, RenamedGuard).

% Case 2.b Scalar comparison,  negated,
% and second integer expression involves a return value trace
ret_cmp_guard(OrigGuard,  RenamedGuard, Fname) :- 
	 #not(NegOrigGuard, OrigGuard),
	 #id_g(SG, NegOrigGuard), equal(SG, br_cmp{sc{OP, IE1, IE2}}),
	 ~scalar_trace_used(IE1, _), 
	  scalar_trace_used(IE2, T), 
 	~trace_soft(s_func, T, _),~more_traces(IE2, T),
         ret_trace(T, Fname),
	 scalar_trace_rename(IE2, T, drf{root{return}}, NewIE2),
	 #id_g(br_cmp{sc{OP, IE1, NewIE2}}, NegRenamedGuard),
	 #not(NegRenamedGuard, RenamedGuard).

% Case 3.a: sc_eqz, not negated
ret_cmp_guard(OrigGuard,  RenamedGuard, Fname) :- 
	 #id_g(SG, OrigGuard), equal(SG, br_cmp{sc_eqz{IE}}),
	 scalar_trace_used(IE, T), 
	 ~trace_soft(s_func, T, _), ~more_traces(IE, T),
         ret_trace(T, Fname),
	 scalar_trace_rename(IE, T, drf{root{return}}, NewIE),
	 #id_g(br_cmp{sc_eqz{NewIE}}, RenamedGuard).

% Case 3.b: sc_eqz  negated
ret_cmp_guard(OrigGuard,  RenamedGuard, Fname) :- 
	 #not(NegOrigGuard, OrigGuard),
	 #id_g(SG, NegOrigGuard), equal(SG, br_cmp{sc_eqz{IE}}),
	 scalar_trace_used(IE, T), 
	 ~trace_soft(s_func, T, _),~more_traces(IE, T),
         ret_trace(T, Fname),
	 scalar_trace_rename(IE, T, drf{root{return}}, NewIE),
	 #id_g(br_cmp{sc_eqz{NewIE}}, NegRenamedGuard),
	 #not(NegRenamedGuard, RenamedGuard).

branch(P, _, _, _), branch_take(P, _, G),
	 ret_cmp_guard(G, RenamedG, F),
	 +td_sum(F)->ret_cond(RenamedG),
	 +print("RETURN COMPARISON GUARD: ", F, G, "=======>", RenamedG).