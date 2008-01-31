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

% Utility predicates to help with scalar and guard manipulations.

import "../memory/scalar.clp".
import "./normal-forms.clp".




% given an integer expression OrigIE, construct a new integer
% expression NewIE which replaces all occurences of trace 
% OldTrace with NewTrace.
 predicate scalar_trace_rename(in OrigIE:scalar, in OldTrace: t_trace, in
NewTrace:t_trace, out NewIE:scalar).

% Given a vr, repplace all traces OldTrace with NewTrace.
predicate vr_trace_rename(in OrigVR:g_vecrep, in OldTrace:t_trace, 
	in NewTrace:t_trace, out NewVR:g_vecrep).

predicate strename_list(in GS: list[guarded_scalar], in OldTrace:t_trace, 
	in NewTrace: t_trace, NewGS:  list[guarded_scalar]).


% -------------------------------------------------------------------------------
%  vr_trace_rename rules

% Note: X's are intentially used to represent anything we don't care
% about...  
vr_trace_rename(vr_t{OldTrace},
	OldTrace, NewTrace, vr_t{NewTrace}) :- .

% Keep original trace if specified trace does not occur.
vr_trace_rename(vr_t{Trace},
	OldTrace, NewTrace, vr_t{Trace}) :- 
	~equal(Trace, OldTrace).

vr_trace_rename(vr_st{OldTrace, P, E}, OldTrace, 
	NewTrace, vr_st{NewTrace, P, E}) :- .

vr_trace_rename(vr_st{Trace, P, E}, OldTrace, 
	NewTrace, vr_st{Trace, P, E}) :- 
	~equal(Trace, OldTrace).



vr_trace_rename(X, Old, New,X):- equal(X, vr_i{_,_}).      


vr_trace_rename(vr_c{X,P,Old}, Old, New, vr_c{X, P, New}) :-.
vr_trace_rename(vr_c{X,P,T},
	OldTrace, NewTrace, vr_c{X, P, T}) :- 
	~equal(T, OldTrace). 

vr_trace_rename(E, Old, New, vr_instscalar{S, P, NewGV}) :-
	equal(E, vr_instscalar{S, P, GV}),
	vr_trace_rename(GV, Old, New, NewGV).
	


vr_trace_rename(vr_buffersize{Old}, Old, New, vr_buffersize{New}) :-.   
vr_trace_rename(vr_buffersize{T}, Old, New, vr_buffersize{T}) :- ~equal(T, Old).   


vr_trace_rename(vr_u{IE}, Old, New, vr_u{NewIE}) :-
	scalar_trace_rename(IE, Old, New, NewIE).

% ---------------------------------------------------------------------------

% scalar_trace_rename rules

scalar_trace_rename(IE, OldTrace, NewTrace, IE) :- equal(IE,  s_int_const{_, _,_}).   
scalar_trace_rename(IE, OldTrace,NewTrace, IE):-  equal(IE, s_float_const{_, _}).

scalar_trace_rename(s_unconstrained{VR, Y}, Old, New, s_unconstrained{NewVR, Y}) :-
	vr_trace_rename(VR, Old, New, NewVR).


scalar_trace_rename(s_cast{IE, X}, OldTrace, NewTrace, 
	s_cast{NewIE,X}) :-
    	scalar_trace_rename(IE, OldTrace, NewTrace, NewIE).

?scalar_trace_rename(s_guard{GS}, OldTrace, NewTrace, _),
	map_to_sorted_list(GS, GSList),
	strename_list(GSList, OldTrace, NewTrace, NewGSList),
	map_of_list(NewGSList, NewGS),
	+scalar_trace_rename(s_guard{GS}, OldTrace, NewTrace, s_guard{NewGS}).

?strename_list(List1, OldTrace, NewTrace, _),
	List1 = [pair{GS1, Guard}|Rest1],
	scalar_trace_rename(GS1, OldTrace, NewTrace, GS2),
	strename_list(Rest1, OldTrace, NewTrace, Rest2),
	List2 = [pair{GS2, Guard}|Rest2],
	+strename_list(List1, OldTrace, NewTrace, List2).

+strename_list([], _, _, []).

scalar_trace_rename(s_unop{X, IE}, OldTrace, NewTrace, s_unop{X, NewIE}) :-
    scalar_trace_rename(IE, OldTrace, NewTrace, NewIE).

scalar_trace_rename(s_binop{X, LE, RE}, OldTrace, NewTrace, s_binop{X, NewLE, NewRE}) :-
    scalar_trace_rename(LE, OldTrace, NewTrace, NewLE), 
    scalar_trace_rename(RE, OldTrace, NewTrace, NewRE).

?scalar_trace_rename(S, T1, T2, _),
	\/scalar_trace_rename(S, T1, T1, NS):list_all(NS, List),
	list_length(List, Length), ~equal(Length, 1),
	+print("Scalar trace rename failed: ", S, T1, T2, "=>", List).

% ---------------------------------------------------------------------------

predicate scalar_trace_to_scalar(in OrigIE:scalar, in OldTrace: t_trace, in
Scalar:scalar, out NewIE:scalar).

predicate tr2sc_list(in GS: list[guarded_scalar], in OldTrace:t_trace, in Scalar: scalar, NewGS:  list[guarded_scalar]).

% scalar_trace_to_scalar rules rules

scalar_trace_to_scalar(IE, OldTrace,Scalar, IE) :- equal(IE,  s_int_const{_, _,_}).   
scalar_trace_to_scalar(IE, OldTrace,Scalar, IE):-  equal(IE, s_float_const{_, _}).

scalar_trace_to_scalar(s_unconstrained{vr_t{T}, _}, T, Scalar, Scalar) :- .


scalar_trace_to_scalar(s_unconstrained{vr_st{T, _, _}, _}, T, Scalar, Scalar) :- .

scalar_trace_to_scalar(s_unconstrained{X, Y}, T, Scalar, s_unconstrained{X, Y}) :- 
	~(equal(X, vr_t{T}); equal(X, vr_st{T,_,_})).


scalar_trace_to_scalar(s_cast{IE, X}, OldTrace, Scalar, 
	s_cast{NewIE,X}) :-
    	scalar_trace_to_scalar(IE, OldTrace, Scalar, NewIE).

?scalar_trace_to_scalar(s_guard{GS}, OldTrace, Sc, _),
	map_to_sorted_list(GS, GSList),
	tr2sc_list(GSList, OldTrace, Sc, NewGSList),
	map_of_list(NewGSList, NewGS),
	+scalar_trace_to_scalar(s_guard{GS}, OldTrace,Sc, s_guard{NewGS}).

?tr2sc_list(List1, OldTrace, Sc, _),
	List1 = [pair{GS1, Guard}|Rest1],
	scalar_trace_to_scalar(GS1, OldTrace, Sc, GS2),
	tr2sc_list(Rest1, OldTrace,Sc, Rest2),
	List2 = [pair{GS2, Guard}|Rest2],
	+tr2sc_list(List1, OldTrace,Sc, List2).

+tr2sc_list([], _, _, []).

scalar_trace_to_scalar(s_unop{X, IE}, OldTrace,Sc, s_unop{X, NewIE}) :-
    scalar_trace_to_scalar(IE, OldTrace, Sc, NewIE).

scalar_trace_to_scalar(s_binop{X, LE, RE}, OldTrace,Sc, s_binop{X, NewLE, NewRE}) :-
    scalar_trace_to_scalar(LE, OldTrace,Sc, NewLE), 
    scalar_trace_to_scalar(RE, OldTrace, Sc, NewRE).





% --------------------------------------------------------------------------------------------
% Replacing expressions within guards
% -----------------------------------------------------------------------------------------
% Given a guard which involves a comparison between a return value and an integer,
% replace the return value expression with a specific numeric value.
predicate replace_exp_guard(in OrigG: g_guard, in NewExp:scalar, out ReplacedG: g_guard).

% T is a trace that originates from the return value of this function.
% Note that the representation of the return trace is determined by the 
% top-down correlation analysis.
predicate return_trace(in T:t_trace).



return_trace(T) :- 
	cil_curfn(F), trace_root(T, temp{"", F}).



% Case 1. Scalar comparison
% first integer expression is the return value expression.
replace_exp_guard(OrigG, NewExp, ReplacedG) :- 
	 #id_g(SG, OrigG), equal(SG, br_cmp{sc{OP, IE1, IE2}}),
	 scalar_trace_used(IE1, T), return_trace(T),
	 #id_g(br_cmp{sc{OP, NewExp, IE2}}, ReplacedG).



% Case 2.: Scalar comparison, not negated and
% second integer expression is the return value expr.
replace_exp_guard(OrigG, NewExp, ReplacedG) :- 
	 #id_g(SG, OrigG), equal(SG, br_cmp{sc{OP, IE1, IE2}}),
	 scalar_trace_used(IE2, T), return_trace(T),
	 #id_g(br_cmp{sc{OP, IE1, NewExp}}, ReplacedG).


% Case 3.a: sc_eqz, not negated
replace_exp_guard(OrigG,  NewExpr, ReplacedG) :- 
	 #id_g(SG, OrigG), equal(SG, br_cmp{sc_eqz{IE}}),
	 scalar_trace_used(IE, T), return_trace(T),
	 #id_g(br_cmp{sc_eqz{NewExpr}}, ReplacedG).

% Case 3: #not
replace_exp_guard(OrigG, NewExpr, ReplacedG) :-
	#not(NotOrigG, OrigG), 
	replace_exp_guard(NotOrigG, NewExpr, NotReplacedG),
	#not(NotReplacedG, ReplacedG).

% Case 4: #and 
replace_exp_guard(OrigG, NewExpr, ReplacedG) :-
	#and(G1, G2, OrigG),
	replace_exp_guard(G1, NewExpr, ReplacedG1),
	replace_exp_guard(G2, NewExpr, ReplacedG2),
	#and(ReplacedG1, ReplacedG2, ReplacedG).

% Case 5: #or 
replace_exp_guard(OrigG, NewExpr,  ReplacedG) :-
	#or(G1, G2, OrigG), 
	replace_exp_guard(G1, NewExpr, ReplacedG1), 
	replace_exp_guard(G2, NewExpr, ReplacedG2), 
	#or(ReplacedG1, ReplacedG2, ReplacedG).



% -----------------------------------------------------------------------------------
% Mapping guards that involve return values of functions
% ------------------------------------------------------------------------------------
% Why do we need this?
% If there is a correlation between the return value of a function and a property 
% of interest, the guard that needs to be translated involves the return value.
% However, the existing inst_guard cannot translate things that involve return values,
% so we must do this seperately.
% -------------------------------------------------------------------------------------

predicate replace_guard_trace(in OrigG: g_guard, in OldTrace: t_trace, in NewTrace: t_trace, out NewG:g_guard) 
	succeeds [once].

% Case 1: Boolean constant
replace_guard_trace(OrigG, OldTrace, NewTrace, OrigG) :- 
	#bool_g(_, OrigG).

% Case 2: #id_g: oveflow
replace_guard_trace(OrigG, OldTrace, NewTrace, ReplacedG) :- 
	 #id_g(SG, OrigG), equal(SG, br_ioverflow{S}),
	scalar_trace_rename(S, OldTrace, NewTrace, NewS),
	#id_g(br_ioverflow{NewS}, ReplacedG).	

% Case 3: #id_g: br_abit
replace_guard_trace(OrigG, OldTrace, NewTrace,OrigG) :- 
	 #id_g(SG, OrigG), equal(SG, br_abit{_}).	

% Case 4. id_g: br_cmp, sc Scalar comparison
replace_guard_trace(OrigG, OldTrace, NewTrace, ReplacedG) :- 
	 #id_g(SG, OrigG), equal(SG, br_cmp{sc{OP, IE1, IE2}}),	
	 scalar_trace_rename(IE1, OldTrace, NewTrace, NewExp1), 
	 scalar_trace_rename(IE2, OldTrace, NewTrace, NewExp2),
	#id_g(br_cmp{sc{OP, NewExp1, NewExp2}}, ReplacedG). 

 

% Case 5: id_g: br_cmp, sc_eqz
replace_guard_trace(OrigG, OldTrace, NewTrace, ReplacedG) :- 
	 #id_g(SG, OrigG), equal(SG, br_cmp{sc_eqz{IE}}),
	scalar_trace_rename(IE, OldTrace, NewTrace, NewExpr),
	 #id_g(br_cmp{sc_eqz{NewExpr}}, ReplacedG).

% Case 6: #not
replace_guard_trace(OrigG, OldTrace, NewTrace, ReplacedG) :-
	#not(NotOrigG, OrigG), 
	replace_guard_trace(NotOrigG, OldTrace, NewTrace, NotReplacedG),
	#not(NotReplacedG, ReplacedG).

% Case 7: #and 
replace_guard_trace(OrigG, OldTrace, NewTrace, ReplacedG) :-
	#and(G1, G2, OrigG),
	replace_guard_trace(G1, OldTrace, NewTrace, ReplacedG1),
	replace_guard_trace(G2, OldTrace, NewTrace, ReplacedG2),
	#and(ReplacedG1, ReplacedG2, ReplacedG).

% Case 8: #or 
replace_guard_trace(OrigG, OldTrace, NewTrace, ReplacedG) :-
	#or(G1, G2, OrigG), 
	replace_guard_trace(G1, OldTrace, NewTrace, ReplacedG1), 
	replace_guard_trace(G2, OldTrace, NewTrace, ReplacedG2), 
	#or(ReplacedG1, ReplacedG2, ReplacedG).

?replace_guard_trace(OrigG, OldTrace, NewTrace, _),
	\/replace_guard_trace(OrigG, OldTrace, NewTrace, Out):list_all(Out, List),
	list_length(List, Length),
	~equal(Length, 1),
	+print("ERROR: Replace guard trace failed on: ", OrigG, OldTrace, NewTrace, Length).

% ------------------------------------------------------------------------

% Replace the trace in the given gurad with the provided scalar.
% This predicate is mostly used for replacing guards used in loop
% termination conditions. For instance, it is used to convert i<size to
% 0<size if 0 is the initial value of i.This allows us to determine
% conditions under which the loop never executes.
predicate guard_trace_to_scalar(in OrigG: g_guard, in OldTrace: t_trace, in Scalar: scalar, out NewG:g_guard).

% Case 1: Boolean constant
guard_trace_to_scalar(OrigG, OldTrace, NewTrace, OrigG) :- 
	#bool_g(_, OrigG).

% Case 2: #id_g: oveflow
guard_trace_to_scalar(OrigG, OldTrace, NewTrace, ReplacedG) :- 
	 #id_g(SG, OrigG), equal(SG, br_ioverflow{S}),
	scalar_trace_to_scalar(S, OldTrace, NewTrace, NewS),
	#id_g(br_ioverflow{NewS}, ReplacedG).	

% Case 3: #id_g: br_abit
replace_guard_trace(OrigG, OldTrace, NewTrace,OrigG) :- 
	 #id_g(SG, OrigG), equal(SG, br_abit{_}).

% Case 4. id_g: Scalar comparison
guard_trace_to_scalar(OrigG, OldTrace, Scalar, ReplacedG) :- 
	 #id_g(SG, OrigG), equal(SG, br_cmp{sc{OP, IE1, IE2}}),	
	 scalar_trace_to_scalar(IE1, OldTrace,Scalar, NewExp1), 
	 scalar_trace_to_scalar(IE2, OldTrace,Scalar, NewExp2),
	 #id_g(br_cmp{sc{OP, NewExp1, NewExp2}}, ReplacedG). 

 

% Case 5: id_g: sc_eqz
guard_trace_to_scalar(OrigG, OldTrace, Scalar, ReplacedG) :- 
	 #id_g(SG, OrigG), equal(SG, br_cmp{sc_eqz{IE}}),
	scalar_trace_to_scalar(IE, OldTrace, Scalar, NewExpr),
	 #id_g(br_cmp{sc_eqz{NewExpr}}, ReplacedG).

% Case 6: #not
guard_trace_to_scalar(OrigG, OldTrace, Scalar, ReplacedG) :-
	#not(NotOrigG, OrigG), 
	guard_trace_to_scalar(NotOrigG, OldTrace,Scalar, NotReplacedG),
	#not(NotReplacedG, ReplacedG).

% Case 7: #and 
guard_trace_to_scalar(OrigG, OldTrace,Scalar, ReplacedG) :-
	#and(G1, G2, OrigG),
	guard_trace_to_scalar(G1, OldTrace,Scalar, ReplacedG1),
	guard_trace_to_scalar(G2, OldTrace,Scalar, ReplacedG2),
	#and(ReplacedG1, ReplacedG2, ReplacedG).

% Case 8: #or 
guard_trace_to_scalar(OrigG, OldTrace, Scalar, ReplacedG) :-
	#or(G1, G2, OrigG), 
	guard_trace_to_scalar(G1, OldTrace, Scalar, ReplacedG1), 
	guard_trace_to_scalar(G2, OldTrace, Scalar, ReplacedG2), 
	#or(ReplacedG1, ReplacedG2, ReplacedG).


% -------------------------------------------------------------------------
predicate check_base(in OrigG:g_guard, in OldSG:g_guard).

check_base(OrigG, OldSG) :-
	#not(OrigG, NotOrigG),
	equal(OldSG, NotOrigG).

check_base(OrigG, OldSG) :-
	equal(OldSG, OrigG).
	

% -----------------------------------------------------------------
% Same as replace subguard, but replaces ~P atomically.

predicate replace_subguard_atomic(in OrigG: g_guard, in OldSubguard:g_guard,
	 in NewSubguard:g_guard, out ReplacedG:g_guard).

predicate replace_subguard_no_neg(in OrigG: g_guard, in OldSubguard:g_guard,
	 in NewSubguard:g_guard, out ReplacedG:g_guard).


replace_subguard_atomic(OrigG, OldSG, NewSG, ReplacedG) :-
	negations_in(OrigG, NewOrigG),
	replace_subguard_no_neg(NewOrigG, OldSG, NewSG, ReplacedG).


predicate equivalent(in G1: g_guard, in G2:g_guard).

equivalent(G1, G2) :-
	#not(G1, NegG1), #and(NegG1, G2, Res1),
	~guard_sat(Res1),
	#not(G2, NegG2), #and(NegG2, G1, Res2),
	~guard_sat(Res2).

% Base case
replace_subguard_no_neg(OrigG, OldSG, NewSG, ReplacedG) :-
         equivalent(OrigG, OldSG),
	 ReplacedG=NewSG.



% Base case: Not found
replace_subguard_no_neg(OrigG, OldSG, NewSG, OrigG) :- 
	 (#id_g(_, OrigG); #not(_, OrigG); #bool_g(_, OrigG)), 
	 ~equivalent(OrigG, OldSG).


% Case 4: #and 
replace_subguard_no_neg(OrigG, OldSG, NewSG, ReplacedG) :-
	~equivalent(OrigG, OldSG),
	#and(G1, G2, OrigG),
	replace_subguard_no_neg(G1, OldSG, NewSG, ReplacedG1),
	replace_subguard_no_neg(G2, OldSG, NewSG, ReplacedG2),
	#and(ReplacedG1, ReplacedG2, ReplacedG).

% Case 5: #or 
replace_subguard_no_neg(OrigG, OldSG, NewSG, ReplacedG) :-
	~equivalent(OrigG, OldSG),
	#or(G1, G2, OrigG), 
	replace_subguard_no_neg(G1, OldSG, NewSG, ReplacedG1), 
	replace_subguard_no_neg(G2, OldSG, NewSG, ReplacedG2), 
	#or(ReplacedG1, ReplacedG2, ReplacedG).


?replace_subguard_atomic(OrigG, OldSG, NewSG, _),
	\/replace_subguard_atomic(OrigG, OldSG, NewSG, Out):list_all(Out, List),
	list_length(List, Length),
	~equal(Length, 1), 
	+print("ERROR: Replace subguard atomic: ", OrigG, OldSG, NewSG, Length, "\n => ", List).


% ---------------------------------------------------------------

predicate replace_subguard(in OrigG: g_guard, in OldSubguard:g_guard,
	 in NewSubguard:g_guard, out ReplacedG:g_guard) succeeds [once].



% Base case: found
replace_subguard(OrigG, OldSG, NewSG, ReplacedG) :-
	#not(OrigG, NotOrigG),
	equal(OldSG, NotOrigG), #not(NewSG, ReplacedG).


replace_subguard(OrigG, OldSG, NewSG, ReplacedG) :-
	equal(OldSG, OrigG), ReplacedG=NewSG.


% Base case: Not found
replace_subguard(OrigG, OldSG, NewSG, OrigG) :- 
	 #id_g(_, OrigG), ~equal(OrigG, OldSG),
	#not(OrigG, NotOrigG), ~equal(NotOrigG, OldSG).



% Case 2: #not
replace_subguard(OrigG, OldSG, NewSG, ReplacedG) :-
	~check_base(OrigG, OldSG),
	#not(NotOrigG, OrigG), 
	replace_subguard(NotOrigG, OldSG, NewSG, NotReplacedG),
	#not(NotReplacedG, ReplacedG).


% Case 4: #and 
replace_subguard(OrigG, OldSG, NewSG, ReplacedG) :-
	~check_base(OrigG, OldSG),
	#and(G1, G2, OrigG),
	replace_subguard(G1, OldSG, NewSG, ReplacedG1),
	replace_subguard(G2, OldSG, NewSG, ReplacedG2),
	#and(ReplacedG1, ReplacedG2, ReplacedG).

% Case 5: #or 
replace_subguard(OrigG, OldSG, NewSG, ReplacedG) :-
	~check_base(OrigG, OldSG),
	#or(G1, G2, OrigG), 
	replace_subguard(G1, OldSG, NewSG, ReplacedG1), 
	replace_subguard(G2, OldSG, NewSG, ReplacedG2), 
	#or(ReplacedG1, ReplacedG2, ReplacedG).


% ---------------------------------------------------------------------------
% Analyses using the correlation analysis must use corr_inst_guard instead of 
% inst_guard.

predicate corr_inst_guard(in SUM: sum, in P:pp, in G:g_guard, out TG: g_guard).

% Don't do anything special for loops.
corr_inst_guard(s_loop{I}, P, G, TG) :-
	inst_guard(s_loop{I}, P, G, TG).

corr_inst_guard(s_call{I}, P, G, TG) :-
	~callret(I, _),
	inst_guard(s_call{I}, P, G, TG).


corr_inst_guard(s_call{I}, P, G, TG) :-
	callret(I, R),
	anycall(I, F,_), 
	guard_trace_used(G, drf{root{temp{"", F}}}),
	replace_guard_trace(G, drf{root{temp{"", F}}}, drf{root{R}}, TG).

 
	
corr_inst_guard(s_call{I}, P, G, TG) :-
	callret(I, R),
	anycall(I, F, _), 
	(~guard_trace_used(G, drf{root{temp{"", F}}});
	~replace_guard_trace(G, drf{root{temp{"", F}}}, drf{root{R}}, _)),
	inst_guard(s_call{I}, P, G, TG).	

corr_inst_guard(s_call{I}, P, G, TG) :-
	~anycall(I, _,_), 
	inst_guard(s_call{I}, P, G, TG).


% -----------------------------------------------------------------------------
predicate conjoin_guard(in list[t_pair[scalar, g_guard]], in g_guard,
	 out list[t_pair[scalar, g_guard]]).

conjoin_guard([], G, []) :- .
conjoin_guard([pair{Sc, ScG}|Tl], G, NewList) :-
	#and(ScG, G, NewG),
	conjoin_guard(Tl, G, NewTl),
	list_append([pair{Sc, NewG}], NewTl, NewList).


% --------------------------------------------------------------------------

predicate merge_duplicates_sorted(in  list[t_pair[scalar, g_guard]],
			 out  list[t_pair[scalar, g_guard]]).

merge_duplicates_sorted([], []) :-.
merge_duplicates_sorted([pair{Sc, G}|Tl], NewList) :-
	merge_duplicates_sorted(Tl, NewTl),
	map_of_list(NewTl, TlMap),
	map_search(TlMap, Sc, ScG),
	#and(G, ScG,NewG),
	map_remove(Sc, TlMap, NewTlMap),
	map_to_sorted_list(NewTlMap, NewTlList),
	list_append([pair{Sc, NewG}], NewTlList, NewList).

merge_duplicates_sorted([pair{Sc, G}|Tl], NewList) :-
	merge_duplicates_sorted(Tl, NewTl),
	map_of_list(NewTl, TlMap),
	~map_search(TlMap, Sc, _),
	list_append([pair{Sc, G}], NewTl, NewList).
	

% ------------------------------------------------------------------------
predicate merge_duplicate_keys(in list[t_pair[scalar, g_guard]],
			 out  list[t_pair[scalar, g_guard]]).

merge_duplicate_keys(List, NewList) :-
	list_sort(List, SortedList),
	merge_duplicates_sorted(SortedList, NewList).

% -----------------------------------------------------------------------

predicate apply_cast_list(in list[t_pair[scalar, g_guard]], 
	in t_scalar_kind, out list[t_pair[scalar, g_guard]]).

apply_cast_list([], Kind, []) :- .
apply_cast_list([pair{Sc, G}|Tl], Kind, CastList):-
	apply_cast_list(Tl, Kind, CastTl),
	list_append([pair{s_cast{Sc, Kind}, G}], CastTl, CastList).
	

predicate apply_cast(in map[scalar, g_guard], in t_scalar_kind, out map[scalar, g_guard]).

apply_cast(InMap, Kind, OutMap) :-
	map_to_sorted_list(InMap, List),
	apply_cast_list(List, Kind, OutList),
	map_of_list(OutList, OutMap).

predicate apply_unop_list(in list[t_pair[scalar, g_guard]], 
	in scalar_unop, out list[t_pair[scalar, g_guard]]).

apply_unop_list([], Op, []) :- .
apply_unop_list([pair{Sc, G}|Tl], Op, UnopList):-
	apply_unop_list(Tl, Op, UnopTl),
	list_append([pair{s_unop{Op, Sc}, G}], UnopTl, UnopList).
	

predicate apply_unop(in map[scalar, g_guard], in scalar_unop, out map[scalar, g_guard]).

apply_unop(InMap, Op, OutMap) :-
	map_to_sorted_list(InMap, List),
	apply_unop_list(List, Op, OutList),
	map_of_list(OutList, OutMap).

predicate product_list(in t_pair[scalar, g_guard], in list[t_pair[scalar, g_guard]], 
			in scalar_binop, out list[t_pair[scalar, g_guard]]).

product_list(Elem, [], Op, []) :- .
product_list(pair{Sc1,G1}, [pair{Sc2, G2}|Tl], Op, Product) :-
	product_list(pair{Sc1,G1}, Tl, Op, TlProduct),
	#and(G1, G2, G),
	list_append([pair{s_binop{Op, Sc1, Sc2}, G}], TlProduct, Product).

predicate apply_binop_list(in list[t_pair[scalar, g_guard]], 
	in  list[t_pair[scalar, g_guard]], 
	in scalar_binop, out list[t_pair[scalar, g_guard]]).

apply_binop_list([], List, Op, []) :- .

apply_binop_list([Hd|Tl], List2, Op, BinopList):-
	product_list(Hd, List2, Op, Prod),
	apply_binop_list(Tl, List2, Op, TlList),
	list_append(Prod, TlList, BinopList).


predicate apply_binop(in map[scalar, g_guard], in map[scalar, g_guard],
	 in scalar_binop, out map[scalar, g_guard]).

apply_binop(InMap1,InMap2, Op, OutMap) :-
	map_to_sorted_list(InMap1, List1),
	map_to_sorted_list(InMap2, List2),
	apply_binop_list(List1,List2, Op, OutList),
	map_of_list(OutList, OutMap).


% -------------------------------------------------------------------------

% Takes a scalar possibly containing nested s_guard's and returns a 
% map of <scalar, guard> pairs where none of the scalars in the
% map contains nested s_guards.
predicate scalar_flatten(in scalar, out map[scalar, g_guard]).

% Helper for scalar_flatten.
predicate flatten_list(in list[t_pair[scalar, g_guard]], out  list[t_pair[scalar, g_guard]]).

flatten_list([],[]) :- .
flatten_list([pair{S, G}| Tl],Flat) :-
	scalar_flatten(S, FlatSc),
	map_to_sorted_list(FlatSc, FlatScList),
	conjoin_guard(FlatScList, G, GuardedFlatSc),
	flatten_list(Tl, FlatTl),
	list_append(GuardedFlatSc, FlatTl, Flat).


scalar_flatten(s_guard{M}, Flat) :-
	map_to_sorted_list(M, List),
	flatten_list(List, FlatList),
	merge_duplicate_keys(FlatList, MergedList),
	map_of_list(MergedList, Flat).

scalar_flatten(S, Map) :-
	(
	  equal(S, s_int_const{_,_,_})
	;
	  equal(S, s_float_const{_,_})
	;
	  equal(S, s_unconstrained{_,_})
	),
	map_empty(Empty),
	#bool_g(true, True),
	map_insert(S, True, Empty, Map).

scalar_flatten(s_cast{Sc, Kind},Map) :-
	scalar_flatten(Sc, Flat),
	apply_cast(Flat, Kind, Map). 

scalar_flatten(s_unop{Op, Sc}, Map) :-
	scalar_flatten(Sc, Flat),
	apply_unop(Flat, Op, Map).

scalar_flatten(s_binop{Op, Sc1, Sc2}, Map) :-
	scalar_flatten(Sc1, Flat1),
	scalar_flatten(Sc2, Flat2),
	apply_binop(Flat1,Flat2, Op, Map). 


% -------------------------------------------------------------------------------


predicate guard_from_flat_scalar_overf(in list[t_pair[scalar, g_guard]], 
				out g_guard).

guard_from_flat_scalar_overf([], False) :- #bool_g(false, False).

guard_from_flat_scalar_overf([pair{Sc, ScG}|Tl], G) :- 
	guard_from_flat_scalar_overf(Tl, TlG),
	#id_g(br_ioverflow{Sc}, Og),
	#and(Og, ScG, HdG),
	#or(TlG, HdG, G).

% -------------------------------------------------------------

predicate guard_from_flat_scalar_eqz(in list[t_pair[scalar, g_guard]], 
				out g_guard).

guard_from_flat_scalar_eqz([], False) :- #bool_g(false, False).

guard_from_flat_scalar_eqz([pair{Sc, ScG}|Tl], G) :- 
	guard_from_flat_scalar_eqz(Tl, TlG),
	#id_g(br_cmp{sc_eqz{Sc}}, EqzG),
	#and(EqzG, ScG, HdG),
	#or(TlG, HdG, G).

% -------------------------------------------------------

type sc_cmp_type ::=
	eq
	| lt.


predicate guard_from_flat_scalar_sc(in list[t_pair[scalar, g_guard]], 
				in list[t_pair[scalar, g_guard]], 
				in sc_cmp_type,
				out g_guard).



predicate product_guard(in t_pair[scalar, g_guard], in list[t_pair[scalar, g_guard]], 
			in sc_cmp_type, out g_guard).

product_guard(Elem, [], Op, False) :- #bool_g(false, False).
product_guard(pair{Sc1,G1}, [pair{Sc2, G2}|Tl], eq, G) :-
	product_guard(pair{Sc1,G1}, Tl, eq, TlG),
	#id_g(br_cmp{sc{sc_eq, Sc1, Sc2}}, EqG),
	and3(G1, G2, EqG, HdG),
	#or(HdG, TlG, G).

product_guard(pair{Sc1,G1}, [pair{Sc2, G2}|Tl], lt, G) :-
	product_guard(pair{Sc1,G1}, Tl, lt, TlG),
	#id_g(br_cmp{sc{sc_lt, Sc1, Sc2}}, EqG),
	and3(G1, G2, EqG, HdG),
	#or(HdG, TlG, G).
	


guard_from_flat_scalar_sc([], List, Cmp, False) :- #bool_g(false, False).

guard_from_flat_scalar_sc([Hd|Tl], List2, Cmp, G):-
	product_guard(Hd, List2, Cmp, HdG),
	guard_from_flat_scalar_sc(Tl, List2, Cmp, TlG),
	#or(HdG, TlG, G).


% ----------------------------------------------------------

% Takes a guard possibly containing nested s_guards, and produces
% a guard without s_guard's such that guards are built only using
% boolean connectives on primitives.
predicate guard_flatten(in g_guard, out g_guard).

guard_flatten(InG, InG) :-
	#bool_g(_, InG).

guard_flatten(InG, InG) :-
	#id_g(br_abit{_}, InG).


guard_flatten(InG, OutG) :-
	#id_g(br_ioverflow{S}, InG),
	scalar_flatten(S, Flat),
	map_to_sorted_list(Flat, FlatList),
	guard_from_flat_scalar_overf(FlatList, OutG).

guard_flatten(InG, OutG) :-
	#id_g(br_cmp{sc_eqz{S}}, InG),
	scalar_flatten(S, Flat),
	map_to_sorted_list(Flat, FlatList),
	guard_from_flat_scalar_eqz(FlatList, OutG).

guard_flatten(InG, OutG) :-
	#id_g(br_cmp{sc{sc_eq, Sc1, Sc2}}, InG),
	scalar_flatten(Sc1, Flat1),
	scalar_flatten(Sc2, Flat2),
	map_to_sorted_list(Flat1, FlatList1),
	map_to_sorted_list(Flat2, FlatList2),
	guard_from_flat_scalar_sc(FlatList1, FlatList2,eq, OutG).

guard_flatten(InG, OutG) :-
	#id_g(br_cmp{sc{sc_ne, Sc1, Sc2}}, InG),
	scalar_flatten(Sc1, Flat1),
	scalar_flatten(Sc2, Flat2),
	map_to_sorted_list(Flat1, FlatList1),
	map_to_sorted_list(Flat2, FlatList2),
	guard_from_flat_scalar_sc(FlatList1, FlatList2,eq, NegOutG),
	#not(NegOutG, OutG).

guard_flatten(InG, OutG) :-
	#id_g(br_cmp{sc{sc_lt, Sc1, Sc2}}, InG),
	scalar_flatten(Sc1, Flat1),
	scalar_flatten(Sc2, Flat2),
	map_to_sorted_list(Flat1, FlatList1),
	map_to_sorted_list(Flat2, FlatList2),
	guard_from_flat_scalar_sc(FlatList1, FlatList2,lt, OutG).

	
guard_flatten(InG, OutG) :-
	#id_g(br_cmp{sc{sc_le, Sc1, Sc2}}, InG),
	scalar_flatten(Sc1, Flat1),
	scalar_flatten(Sc2, Flat2),
	map_to_sorted_list(Flat1, FlatList1),
	map_to_sorted_list(Flat2, FlatList2),
	guard_from_flat_scalar_sc(FlatList1, FlatList2,lt, LtG),
	guard_from_flat_scalar_sc(FlatList1, FlatList2,eq, EqG),
	#or(LtG, EqG, OutG).	

guard_flatten(InG, OutG) :-
	#id_g(br_cmp{sc{sc_gt, Sc1, Sc2}}, InG),
	scalar_flatten(Sc1, Flat1),
	scalar_flatten(Sc2, Flat2),
	map_to_sorted_list(Flat1, FlatList1),
	map_to_sorted_list(Flat2, FlatList2),
	guard_from_flat_scalar_sc(FlatList2, FlatList1,lt, OutG).

guard_flatten(InG, OutG) :-
	#id_g(br_cmp{sc{sc_ge, Sc1, Sc2}}, InG),
	scalar_flatten(Sc1, Flat1),
	scalar_flatten(Sc2, Flat2),
	map_to_sorted_list(Flat1, FlatList1),
	map_to_sorted_list(Flat2, FlatList2),
	guard_from_flat_scalar_sc(FlatList1, FlatList2,lt, NotG),
	#not(NotG, OutG).


guard_flatten(InG, OutG) :-
	#not(G, InG),
	guard_flatten(G, FlatG),
	#not(FlatG, OutG).

guard_flatten(InG, OutG) :-
	#and(G1, G2, InG),
	guard_flatten(G1, FlatG1),
	guard_flatten(G2, FlatG2),
	#and(FlatG1, FlatG2, OutG).

guard_flatten(InG, OutG) :-
	#or(G1, G2, InG),
	guard_flatten(G1, FlatG1),
	guard_flatten(G2, FlatG2),
	#or(FlatG1, FlatG2, OutG).

% ---------------------------------------------------



% Do quick simplifications on guards to prevent blowup
% in guard size.
predicate guard_optimize(in g_guard, out g_guard) succeeds [once].

% After optimizing the guard using the above predicate,
% call the guard_simplify_predicate.  
predicate guard_optimize_aggressive(in g_guard, out g_guard) succeeds [once].

% Fold constants, e.g !0 = true, !2=false etc. 
predicate const_fold(in g_guard, out g_guard) succeeds [once].


% The scalar is an int or float.
predicate scalar_const(in scalar).


scalar_const(s_int_const{_,_,_}) :- .
scalar_const(s_float_const{_,_}) :- .
scalar_const(s_cast{S,K}) :- scalar_const(S).
scalar_const(s_unop{Op, S}) :- scalar_const(S).
scalar_const(s_binop{Op, S1, S2}) :- scalar_const(S1), scalar_const(S2).
	
	

predicate bool_guard(in g_guard, out g_guard). 

bool_guard(G1, G2):-
	(
	  (#not(G1, NG1),
	  ~guard_sat(NG1),
	   #bool_g(true, True), 
	   G2 = True)
	;
	   (~guard_sat(G1),
	   #bool_g(false, False), 
	   G2 = False)
	).

const_fold(G, G) :-
	#bool_g(_, G).

const_fold(G1, G2) :-
	#id_g(br_cmp{SC}, G1),
	equal(SC, sc_eqz{S}),
	scalar_const(S),
	bool_guard(G1, G2).	



const_fold(G1, G1) :-
	#id_g(br_cmp{SC}, G1),
	equal(SC, sc_eqz{S}),
	~(scalar_const(S), bool_guard(G1, _)).
	
const_fold(G1, G2) :-
	#id_g(br_cmp{SC},G1),
	equal(SC, sc{_, S1, S2}),
	scalar_const(S1),
	scalar_const(S2),
	bool_guard(G1, G2).

const_fold(G1, G1) :-
	#id_g(br_cmp{SC},G1),
	equal(SC, sc{_, S1, S2}),
	~(scalar_const(S1),
	scalar_const(S2),
	bool_guard(G1, _)).


const_fold(G, G) :-
	(#id_g(br_ioverflow{_}, G);
	 #id_g(br_abit{_}, G)).
	
const_fold(InG, OutG) :-
	#and(G1, G2, InG),
	const_fold(G1, G11),
	const_fold(G2, G22),
	#and(G11, G22, OutG).

const_fold(InG, OutG) :-
	#or(G1, G2, InG),
	const_fold(G1, G11),
	const_fold(G2, G22),
	#or(G11, G22, OutG).

const_fold(InG, OutG) :-
	#not(G, InG),
	const_fold(G, G1),
	#not(G1, OutG).

% Possibly more optmizations other
% than constant folding needed...
guard_optimize(InG, OutG) :-
	const_fold(InG, OutG).



guard_optimize_aggressive(InG, OutG) :-
	guard_optimize(InG, OptG),
	guard_simplify(OptG, OutG).