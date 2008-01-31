%%
% Authors:
%   Kenny Lau  <klau@cs.stanford.edu>
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

% This analysis will compute the set of functions that lead exclusively to an 
% exit point.  This will happen by first generating a known base set of 
% halting functions and then propagating this knowledge up the function call
% space to find more functions that terminate on all paths.

% NOTE: To make use of this information in other analyses, you need to add the
% predicate +prune_exit_calls().

% This analysis is sound (anything it marks as an exit function is
% indeed an exit function) but not complete (it may miss exit functions), 
% unless the use of unsound exit function roots is explicitly requested.

import "loops.clp".
import "utility.clp".

analyze session_name("cil_body").

+prune_exit_calls().

% PREDICATES- important predicates and sessions declared in cilcfg.clp

% We can reach point P without calling an exit function.
predicate reach(P:pp).

% The current function may return, so it is not an exit function.
predicate fn_may_return().

% SUMMARIES- Defined in cilcfg.clp

% SEEDS

% The default list of exit seed functions is now in cilcfg.clp.  Additional 
% lists of analysis specific exit functions are now stored in exitbaked.clp

% RULES

% Pull needed items out of the database of known exits
exit_call(F) :- dircall(_,F), exit_sum(F)->exit_fn().

% Seed reach
reach(P) :- entry(P).

% Forward propagate reach
reach(P1) :- iset(P0,P1,_), reach(P0).
reach(P1) :- iloop(P0,P1,_), reach(P0).
reach(P1) :- iasm(P0,P1,_), reach(P0).
reach(P1) :- branch(P,P1,_,_), reach(P).
reach(P1) :- branch(P,_,P1,_), reach(P).

% Calls are different, we only propagate reach if the call is not a exit fxn.
reach(P1) :- icall(P0,P1,I), dircall(I,F), ~exit_call(F), reach(P0).

% TODO: Update this for funptr analysis.
% For now, all indirect calls are non-exit functions
reach(P1) :- icall(P0,P1,I), ~dircall(I,_), reach(P0).

% We have a non-exit function if an exit point is reached
fn_may_return() :- exit(P), reach(P).

exit_fn() :- ~fn_may_return().

?- exit_fn().

% If the current function may return then mark it as an exit function. 
exit_sum(F)->exit_fn() :- ~fn_may_return(), cil_curfn(F).


% Since the way we deal with longjmp is a hack, warn where it is used
print("WARNING: longjmp used as exit base") :-
    dircall(_,"longjmp"), exit_call("longjmp").


% Generating exit <display>

using display.

predicate exit_name(in FN:string,DNAME:string).
exit_name(FN, FN ^ "_exit") :- .

% color exit calls red and make a link to the callee
predicate call_item(LINE:int,ITEM:displayitem).
exit_call(F), dircall(I,F), icall(P,_,I), point_location(P,_,LINE),
    cleanup_glob_string(F,FS), exit_name(F,FDNAME),
    TEXT = "\"" ^ FS ^ "\" is an exit function",
    +call_item(LINE,d_line_style{LINE,"pathevent"}),
    +call_item(LINE,d_line_text{LINE,"pathevent",d_right,
                                TEXT,[d_link{FDNAME,"why"}]}).

% color reachable lines (except those with an exit call) grey
predicate reach_item(LINE:int,ITEM:displayitem).
reach_item(LINE,d_line_style{LINE,"pathline"}) :-
    reach(P), point_location(P,_,LINE), ~call_item(LINE,_).

display_add(FDNAME,false,"exit",TITLE,FS,FILE,NMIN,NMAX,NMIN,ITEMS) :-
    cil_curfn(F), ~fn_may_return(), curfn_location(FS,FILE,NMIN,NMAX),
    \/call_item(_,CITEM):list_all(CITEM,CALLS),
    \/reach_item(_,RITEM):list_all(RITEM,REACHES),
    list_append(CALLS,REACHES,ITEMS),
    TITLE = "\"" ^ FS ^ "\" is an exit function",
    exit_name(F,FDNAME).

