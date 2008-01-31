%%
% Authors:
%   Isil Dillig    <isil@stanford.edu>
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

% Uninitialized variable checker to use for testing the correlation analysis
% This is modified from Kenny Lau's analysis to integrate with the
% selective path-sensitivity framework and to work with recent changes to SATURN.
% ---------------------------------------------------------------------------

import "../memory/memory.clp".
import "../memory/scalar.clp".
import "../memory/scalar_sat.clp".
import "../null/lines.clp".
import "./correlate-new.clp".
%import "../base/cfgdot.clp".

+prune_exit_calls().
+use_null_exit().

analyze session_name("cil_body").


% -----------------------------------------------------------------------------------------
% Flags to control analysis behavior

% Use the correlation analysis for interprocedural path sensitivity.
% If this predicate is not added, the default behavior is path-insensitive
% interprocedurally.
predicate use_correlation().

+use_correlation().

% ---------------------------------------------------------------------------------------
% Session and summary Preds
session init_sum(F:string).

% The function initializes trace T under guard G, where G is a sufficient 
% condition computed by the correlation analysis.
predicate fun_init(T:t_trace, SufficientCond:g_guard).

% The function requires this argument T to be initialized
predicate fun_use(T:t_trace).

% This function has been analyzed. It is used to filter out error messages for
% functions we don't have the source code for.
predicate analyzed().

% This function calls a function which has not been analyzed.
predicate call_unanalyzed().


% -------------------------------------------------------------------------------------------
% Mapping between summary preds to preds used in this function:

% T is initialized in a function call. P is the point of the call, 
% and CG is the guard under which the call happens.
predicate call_init(P:pp, T: t_trace, CG:g_guard, PropGuard: g_guard). 

% T is used in a call. P is the point of the call, and CG is the 
% guard under which call happens.
predicate call_use(P: pp, T: t_trace, CG: g_guard).

% --------------------------------------------------------------------------------------------

% Trace T is initialized in this function (not in a called function) under guard G.
predicate fn_init(P:pp, T:t_trace, G:g_guard).

% ----------------------------------------------------------------------------------------------
% Predicates: 

% Trace T is used (written to or modified) somewhere in the function or passed to another fuinction.
predicate used(T: t_trace).

% At point P, trace T is initialized in this function if CurFnGuard and PropGuard holds.
% CurFnGuard is the guard under which 1. either a variable is initialized within this function
% or 2. the guard under which a function which initializes this variable is called.
% PropGuard is the guard under which a called function initializes T.
predicate point_init(P: pp, T: t_trace, CurFnGuard: g_guard, PropGuard:g_guard).

% merged version of the above
predicate init(P: pp, T:t_trace, CUR_FN_GUARD:g_guard, CALLED_FN_GUARD:g_guard).

% T must be initialzed at point P under G because it is used
predicate point_use(P: pp, T: t_trace, G: g_guard).

% T is used, but potentially not initialized at point P.
predicate uninit(P:pp, T:t_trace).




% -----------------------------------------------------------------------------------------------
cil_curfn(F), +init_sum(F)->analyzed().

%---------------------------------------------------------------------------------------------

% We need to know all the used or modifies traces so that 
% we can set their entry initialization state.
access(_, T, _), +used(T).
call_init(_, T, _, _), +used(T).
call_use(_, T, _), +used(T).

entry(P), used(T), #bool_g(false, False), +point_init(P, T, False, False).



% -----------------------------------------------------------------

% Merge initialization info
point_init(P,S,_, _),
    \/point_init(P,S,G, _):#or_all(G,AG), 
    \/point_init(P,S,_, PropG):#or_all(PropG, APG),
    +init(P,S,AG, APG).

% -----------------------------------------------------------------
% Initializations inside this function

access(P,S,write), guard(P,G),  +fn_init(P, S, G).


% All initialization information must be propagated down the call tree
init(P0,T,FG, PG), icall(P0,P1,_),  +point_init(P1,T,FG, PG).
init(P0,T,FG, PG), iloop(P0,P1,_), +point_init(P1,T,FG, PG).
init(P0,T,FG, PG), iset(P0,P1,_), +point_init(P1,T,FG, PG).
init(P,T,FG, PG), branch(P,P0,P1,_),
   +point_init(P0,T,FG, PG),
   +point_init(P1,T,FG, PG).

% ---------------------------------------------------------------------------
% Express both fn_init and call_init in terms of point_init

call_init(P, T, CallGuard, PropGuard), +point_init(P, T, CallGuard, PropGuard).
fn_init(P, T, G), #bool_g(true, True), +point_init(P, T, G, True).

% ------------------------------------------------------------------------------


% If an expression reads from a variable, it should be initialized
access(P,T,read), guard(P,G), +point_use(P,T,G).
call_use(P, T, G), +point_use(P, T, G).

% UNINITIALIAZED USE:
% ------------------

predicate report_trace(in T:t_trace).
report_trace(T) :- trace_root(T, local{_}).
report_trace(T) :- trace_root(T, temp{_, _}), ~trace_derefs(T,0).

point_use(P, T, UG), 
	init(P, T, FG, PG),
	 #and(FG, PG, IG), report_trace(T), 
	#not(IG, NIG), #and(NIG, UG, UNINIT), guard_sat(UNINIT), 
	+uninit(P, T).

% ------------------------------------------
% Mostly interprocedural work

% Convert summary predicates to their corresponding intraprocedural versions.
dircall(I,F), init_sum(F)->fun_init(CT, CG),
    icall(P,P2,I), 
    inst_trace(s_call{I},P,CT,trace{T},_), 
    corr_inst_guard(s_call{I}, P, CG, TCG), 
    guard(P,PG),
    +print("Call init: ",  T, TCG),
    +call_init(P2, T, PG, TCG).


dircall(I,F), init_sum(F)->fun_use(CT), icall(P,P2,I),
   inst_trace(s_call{I},P,CT,trace{T},_), guard(P,G), +call_use(P2, T, G). 

% ------------------------------------------------------------
% INIT SUMMARY
% ------------------------------------------------------------
predicate arg_trace(in T:t_trace,out NT:t_trace).

%predicate s_unify(T:t_trace, NT:t_trace).

arg_trace(T, T) :- trace_root(T, arg{_}).  arg_trace(T, NT) :-
exit_trace_rename(s_func, T, NT), (trace_root(NT, arg{_});
trace_root(NT, return)).


cil_curfn(F), point_use(P,T,UG), 
   init(P,T,FG, PG), #and(FG, PG, IG),   
   #not(IG,NIG), #and(NIG,UG,UNINIT), #sat(UNINIT), 
   trace_root(T, arg{_}),
   +print("Use edge: ", T),
   +init_sum(F)->fun_use(T).

use_correlation(),
   cil_curfn(F), exit(EXIT), 
   init(EXIT,T,FG, PG), ~trace_soft(s_func, T,_),
   ~trace_alloc(s_func,T,ak_stack_local),
   arg_trace(T, NT), % doesn't deal with globals
   %propagate_sufficient_cond(PG, s_func, NPG),
   #and(FG, PG, RG), 
   sufficient_cond(RG, s_func, SG), 
   %#and(SG, NPG, IG),
   #sat(SG), %don't add unsatisfiable guard
   +init_sum(F)->fun_init(NT, SG).

~use_correlation(),
   cil_curfn(F), exit(EXIT), 
   init(EXIT,T,FG, _), %Propagated guard should always be true
   ~trace_soft(s_func, T,_),
   ~trace_alloc(s_func,T,ak_stack_local),
   arg_trace(T, NT), % doesn't deal with globals
   #not(FG, NFG), ~guard_sat(NFG),
   #bool_g(true, True),
   +print("Init edge: ", NT), 
   +init_sum(F)->fun_init(NT, True).


% Source of unsoundness
cil_curfn(F), exit(EXIT), 
   init(EXIT,T,FG, PG), trace_soft(s_func, T, _),
   ~trace_alloc(s_func,T,ak_stack_local),
   arg_trace(T, NT), % doesn't deal with globals
   %propagate_sufficient_cond(PG, s_func, NPG),
   #and(FG, PG, IG),
   #sat(IG), %don't add unsatisfiable guard
   +print("Init edge (soft): ", NT, IG), 
   +init_sum(F)->fun_init(NT, IG).


% SOURCE OF UNSOUNDNESS
% If we have an indirect call, we assume it initializes all its arguments
icall(P,P2,I), ~dircall(I,_), 
   rel_inst_trace(s_call{I},P,_,T,_), 
   guard(P,G), #bool_g(true, True), 
   +call_init(P2,T,G, True).

% If we haven't analyzed a function, assume everything is initialized.
% This, however, cannot get rid of all false positives related to unanalyzed
% functions because of how td_inst_trace works. 
icall(P,P2,I),dircall(I,F), ~init_sum(F)->analyzed(), 
   access(_, T, _), td_inst_trace(s_call{I}, P, T, _,_), 
   guard(P,G), #bool_g(true, True), 
    +print("Unanalyzed function init: ", P2),
   +call_init(P2,T,G, True).



%--------------------------------- ----------------------------------------



% ----------------------------------------
predicate location(in P:pp, out Str:string).

location(P, Loc) :- point_location(P, File, Line), 
	tostring(Line,LineStr), str_cat(LineStr, ":", Temp), 
	str_cat(Temp, File, Loc).

% Error reporting
predicate uninit_print(string,int,t_trace,pp).
uninit(P, T), location(P, LOC),  +print("*UNINITIALIAZED VARIABLE*: ", LOC, T).




