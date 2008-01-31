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

% ---------------------------------------------------------------------
% First pass of correlation analysis to discover relevant return values.
% ---------------------------------------------------------------------



import "../memory/scalar.clp".
import "../memory/scalar_sat.clp".
import "../null/lines.clp".
import "./scalar-helpers.clp".

analyze analysis_name("topdown-correlation").
analyze topdown().
 analyze eager().
analyze session_name("cil_body").

%+no_trace_casting().

+no_entry_aliasing().


% -----------------------------------------------
% Session for top-down correlation.
session td_corr(F:string).


%Summary predicate: ret_cond

% Guard G is a condition which depends on function F's return value.
% The idea is that it someone checks a particular rteurn value of this
% function, it must be relevant.

predicate ret_cond(G:g_guard).


% Summary predicate: const_arg.  
% Trace T always evaluates to a
% constant at the call site.

predicate const_arg(T: t_trace).

% ----------------------------------------------

% Auxiliary session just to keep track of how many edges has been 
% added per function. This information is used to discard 
% return values of functions which are not necessarily meaningful,
% but create gigantic summaries and potentially really slow down 
% later analyses.

session td_counter(F:string).

% Counter
predicate count(I:int).

% -----------------------------------------------------------------------
% Predicate to serve as a #define.

% Threshold number of collected conditions after which we clear the summary.
predicate threshold(I:int).

% Set it to 10 for now.
+threshold(10).


% --------------------------------------------------------------- %
% TODO:
% ---- 

% 1. There are some functions such as buffer_get_char
% which return a character, and every calling context checks the return
% value for some random character of the alphabet, resulting ina huge 
% number of "relevant" guards. We must keep track of the size of the 
% collected guards, and discard them if necessary.

% 2. Probelm related to #1:
% We can't just discard all collected information. There are functions which 
% can  return a large number of  positive integers, but the return value
% -1 or 0 might indicate something special.
% We need a heuristic to deal with this case; otherwise we either end up with
% huge summaries or discard useful information.

%3. Casts
% If a return value is used as short vs. normal int, duplicate entries are added
% to summaries. This might blow up summary size.

% ---------------------------------------------------------------
% Rules
% ---------------------------------------------------------------

% If a trace is the return value from a function call, rename it using
% the canonical naming scheme used by the memory analysis.
% OrigTrace is the original trace, Renamed Trace is the canonicalized name,
% and FnName is the name of the function whose return value produces this
% temporary trace.
predicate renamed_ret_trace(in OrigTrace: t_trace, out RenamedTrace:t_trace, out FnName:string).

renamed_ret_trace(OrigTrace,  drf{root{temp{"", Fname}}}, Fname) :-
	equal(OrigTrace, drf{root{temp{_, Fname}}}),
	dircall(_, Fname).

renamed_ret_trace(OrigTrace,  drf{root{temp{"", TargetFun}}}, TargetFun) :-
	equal(OrigTrace, drf{root{temp{_, Fname}}}),
	~dircall(_, Fname), 
	cil_instr_call(I, Call), exp_string(Call, Fname),
	anycall(I, TargetFun, _).





predicate more_traces(in IE: scalar, in T:t_trace).
more_traces(IE, T1):- scalar_trace_used(IE, T2), ~equal(T1, T2). 

% -------------------------------------------------------------

% Given a guard OrigGuard which involves a comparison between the return value of 
% a function and a constant, produces a new guard with renamed traces. F is the
% function whose return value is involved as a trace in the guard.
predicate ret_cmp_guard(in OrigGuard:g_guard, out NewGuard:g_guard, out F:string).

% Case 1.a: Scalar comparison, not negated and
% first integer expression involves a return value trace
ret_cmp_guard(OrigGuard,  RenamedGuard, Fname) :- 
	 #id_g(SG, OrigGuard), equal(SG, br_cmp{sc{OP, IE1, IE2}}),
	 scalar_trace_used(IE1, T), ~more_traces(IE1, T),
	 ~scalar_trace_used(IE2, _),
         renamed_ret_trace(T, RT, Fname),
	 scalar_trace_rename(IE1, T, RT, NewIE1),
	 #id_g(br_cmp{sc{OP, NewIE1, IE2}}, RenamedGuard).

% Case 1.b sc: Scalar comparison (negated),
% first integer expression involves a return value trace
ret_cmp_guard(OrigGuard,  RenamedGuard, Fname) :- 
	 #not(OrigGuard, NegOrigGuard),
	 #id_g(SG, NegOrigGuard), equal(SG, br_cmp{sc{OP, IE1, IE2}}),
	 scalar_trace_used(IE1, T), ~more_traces(IE1, T),
	 ~scalar_trace_used(IE2, _),
         renamed_ret_trace(T, RT, Fname),
	 scalar_trace_rename(IE1, T, RT, NewIE1),
	 #id_g(br_cmp{sc{OP, NewIE1, IE2}}, NegRenamedGuard),
	 #not(NegRenamedGuard, RenamedGuard).

% Case 2.a Scalar comparison, not negated,
% and second integer expression involves a return value trace
ret_cmp_guard(OrigGuard,  RenamedGuard, Fname) :- 
	 #id_g(SG, OrigGuard), equal(SG, br_cmp{sc{OP, IE1, IE2}}),
	 ~scalar_trace_used(IE1, _), 
	  scalar_trace_used(IE2, T), ~more_traces(IE2, T),
         renamed_ret_trace(T, RT, Fname),
	 scalar_trace_rename(IE2, T, RT, NewIE2),
	 #id_g(br_cmp{sc{OP, IE1, NewIE2}}, RenamedGuard).

% Case 2.b Scalar comparison,  negated,
% and second integer expression involves a return value trace
ret_cmp_guard(OrigGuard,  RenamedGuard, Fname) :- 
	 #not(OrigGuard, NegOrigGuard),
	 #id_g(SG, NegOrigGuard), equal(SG, br_cmp{sc{OP, IE1, IE2}}),
	 ~scalar_trace_used(IE1, _), 
	  scalar_trace_used(IE2, T), ~more_traces(IE2, T),
         renamed_ret_trace(T, RT, Fname),
	 scalar_trace_rename(IE2, T, RT, NewIE2),
	 #id_g(br_cmp{sc{OP, IE1, NewIE2}}, NegRenamedGuard),
	 #not(NegRenamedGuard, RenamedGuard).

% Case 3.a: sc_eqz, not negated
ret_cmp_guard(OrigGuard,  RenamedGuard, Fname) :- 
	 #id_g(SG, OrigGuard), equal(SG, br_cmp{sc_eqz{IE}}),
	 scalar_trace_used(IE, T), ~more_traces(IE, T),
         renamed_ret_trace(T, RT, Fname),
	 scalar_trace_rename(IE, T, RT, NewIE),
	 #id_g(br_cmp{sc_eqz{NewIE}}, RenamedGuard).

% Case 3.b: sc_eqz  negated
ret_cmp_guard(OrigGuard,  RenamedGuard, Fname) :- 
	 #not(OrigGuard, NegOrigGuard),
	 #id_g(SG, NegOrigGuard), equal(SG, br_cmp{sc_eqz{IE}}),
	 scalar_trace_used(IE, T), ~more_traces(IE, T),
         renamed_ret_trace(T, RT, Fname),
	 scalar_trace_rename(IE, T, RT, NewIE),
	 #id_g(br_cmp{sc_eqz{NewIE}}, NegRenamedGuard),
	 #not(NegRenamedGuard, RenamedGuard).



	  
% ---------------------------------------------------------------
% Initializing and Updating counter
% ---------------------------------------------------------



predicate update_counter(F:string, Count:int).

update_counter(F, C), 
	+td_counter(F)->clear_old_preds(),
	+td_counter(F)->count(C).



% -----------------------------------------------------------------


% Add the guard to the summary only if a stronger guard has not already been discovered.
predicate uniquify_guard(G:g_guard, F:string).



% Find if statements which check for the return value of a function
branch(P, _, _, _), branch_take(P, _, G), 
	 ret_cmp_guard(G, RenamedG, F), #simplify(RenamedG, SimpG),
	+uniquify_guard(SimpG, F).

% If this guard has already been added by someone else, don't create duplicates.
% Problem: Equal doesn't help for the reason below:
% "Add: " "strlen" br_cmp{sc{sc_ge,s_unconstrained{vr_t{drf{root{temp{"__$"#420"","strlen"}}}},sk_int{false,32}},s_int_const{4,false,32}}}
%"Add: " "strlen" !br_cmp{sc{sc_ge,s_unconstrained{vr_t{drf{root{temp{"__$"#608"","strlen"}}}},sk_int{false,32}},s_int_const{4,false,32}}}
% We have to deconstruct the guards...



% The collected guard is a duplicate, i.e it has already been added to the summary.
predicate duplicate(G:g_guard, F:string).

% Add to summary if not duplicate and adding edges are allowed 
% (i.e we don't exceed threshold # of edges for this function)
 uniquify_guard(G, F),
	~duplicate(G, F),
	add_edges(F),
	+print("ADDING RETURN COND: ", F, G),
 	+td_corr(F)->ret_cond(G).

% --------------------------------------------------------------------

predicate edge_count(in F:string, out Count:int).

edge_count(F, 0) :-
	~td_counter(F)->count(_).

edge_count(F, Val) :-
	td_counter(F)->count(Val).


% This predicate is added if threshold is not exceeded, and 
% we can keep adding to F's summary.
predicate add_edges(F:string).
	
% Determine if this function exceeds its threshold
uniquify_guard(_, F),
	 \/(uniquify_guard(G, F), ~duplicate(G,F)):list_all(pair{G, F}, 
		GuardsByFunction),
	edge_count(F, Count),	
	list_length(GuardsByFunction, Size), 
	threshold(Limit),
	int_add(Count, Size, NewCount),
	((~int_gt(NewCount, Limit),
	+add_edges(F),
	+update_counter(F, NewCount)); 
	int_gt(NewCount, Limit),+print("Threshold exceeded...")).

	




% Check for duplicates.
% First do a cheap equality comparison, then if you can't show they are syntactically equal, do a sat query.
% The reason for this is to eliminate duplication when constants are cast to other types.
% For instance, (int)0 is not syntactically identical to 0, but the sat query should tell us they are identical. 
% NOTE: The SAT query idea does not solve this issue; need to try something smarter.
 uniquify_guard(G1, F), 
 	td_corr(F)->ret_cond(G1),
	%equal(G1, G2),
	%#not(G1, NG1), #and(G2, NG1, NotEqG),
	%~#sat(NotEqG),
	+duplicate(G1, F).

% -----------------------------------------------------------------------
predicate const_exp(E:c_exp).

const_exp(E) :- cil_exp_const(E, _). %, ~cil_const_str(C, _).
const_exp(E) :- cil_exp_const(CE, _), cil_exp_cast(E, CE,_).
const_exp(E) :- cil_exp_x_intval(E,_).

% ---------------------------------------------------------------------

% If a trace definitely evaluates to a constant, 
% it may be used as a flag.

% Case 1: A variable which evaluates to a constant.
anycall(I, F, _), icall(P1,_,I), 
	access(_, T, _),  val(P1, T, nrep{_}, _),
	\/val(P1, T, nrep{_}, G):#or_all(G, ConstG), 
	#not(ConstG, NotConstG), ~guard_sat(NotConstG),
	td_inst_trace(s_call{I}, P1, T, CT, _),
	trace_root(CT, arg{_}), % we don't want globals
	+print("ADDING CONST TRACE:", CT),
	~td_corr(F)->const_arg(CT),	
	+td_corr(F)->const_arg(CT).


% Case 2: Constants directly passed as arguments.
anycall(I, F, _),  cil_instr_call_arg(I, A, E),
	const_exp(E),
	CalleeTr = root{arg{A}},
	+print("ADDING CONST TRACE (2): ", F, CalleeTr),
	~td_corr(F)->const_arg(CalleeTr),
	+td_corr(F)->const_arg(CalleeTr).


% ---------------------------------------------------------------

% Collect all arguments passed by address because we know they are non-null,
% and this is a very common check.

anycall(I, F, _), cil_instr_call_arg(I, A, E), 
	cil_exp_addr(E,_),
	CalleeTr = root{arg{A}},
	+print("ADDING ADDRESS OF: ", F, CalleeTr),
	~td_corr(F)->const_arg(CalleeTr),
	+td_corr(F)->const_arg(CalleeTr).

% ---------------------------------------------------------------

predicate branch_access(in P:pp, out T:t_trace).
branch_access(P, BT):-
	branch(AnyP, _, _, _), branch_take(AnyP, _, G),
	guard_trace_used(G, T),
	val(P, T, trace{drf{BT}}, _).

% -----------------------------------

% Collect all arguments used in if statements.

anycall(I, F, _), icall(P1, _, I), 
	branch_access(P1, BT),
	td_inst_trace(s_call{I}, P1, BT, drf{CalleeTr}, _),
	+print("ADDING BRANCH TRACE: ", F, CalleeTr),
	~td_corr(F)->const_arg(CalleeTr),
	+td_corr(F)->const_arg(CalleeTr).
	


% ----------------------------------------------------------
% If a relevant trace is collected for the current function, we
% should pass it on to callees.

anycall(I, F,_), icall(P1,_, I),
	cil_curfn(CurFn), td_corr(CurFn)->const_arg(T),
	cil_instr_call_arg(I, A, E),
	evals(P1, E, SE), 
	 scalar_trace_used(SE, drf{T}),
	~access(_,T, write),
	CalleeTr = root{arg{A}},
	~td_corr(F)->const_arg(CalleeTr),	
	+td_corr(F)->const_arg(CalleeTr).
	

% ---------------------------------------------------------


% Just for now:

cil_curfn(F), td_corr(F)->const_arg(T), 
	+print("RELEVANT ARG FOR CURRENT FUNC: ", T).

cil_curfn(F), +print("**CURRENT FUNC**: ", F),

cil_curfn(F), \/td_corr(F)->const_arg(T):list_all(T, List),
	list_length(List, Length),
	+print("**Number of arguments collected: ", Length).

cil_curfn(F), \/td_corr(F)->ret_cond(G):list_all(G, List),
	list_length(List, Length),
	+print("**Number of return values collected: ", Length).