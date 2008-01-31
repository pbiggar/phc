%%
% Authors:
%   Peter Hawkins  <hawkinsp@cs.stanford.edu>
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

%-----------------------------------------------------------------------------%
% livecode_infer.clp 
%
% Live function inference analysis. 
% A function is considered live if:
% * it is a root function, typically main() for most programs, or
% * its address is passed to a function that is missing
% * its address is passed to a function that installs signals
%
% This file contains the inference code.
%
%-----------------------------------------------------------------------------%

import "../memory/intignore.clp".
import "livecode.clp".
import "rootfns.clp".

analyze session_name("cil_body").
analyze topdown().

%-----------------------------------------------------------------------------%

    % Is the current function live?
predicate live(t_live_reason).

    % The current function is live if it is a root function.
live(l_root) :-
    cil_body(Fn),
    root_fn(Fn).

    % If we're not a root, then we're live only if the analysis has deduced
    % us to be live.
live(Reason) :-
    cil_body(Fn),
    ~root_fn(Fn),
    sum_livecode(Fn)->live_fn(Reason).

%-----------------------------------------------------------------------------%
% Update the liveness of the current function

sum_livecode(Fn)->clear_old_preds() :-
    cil_body(Fn).

sum_livecode(Fn)->live_fn(Reason) :-
    cil_body(Fn),
    live(Reason).
sum_livecode(Fn)->dead_fn() :-
    cil_body(Fn),
    ~live(_).

%-----------------------------------------------------------------------------%
% Infer liveness of callees

    % A function is live if it is called by a live function
sum_livecode(CFn)->live_fn(l_called) :-
    live(_),
    anycall(_,CFn,_).

%-----------------------------------------------------------------------------%

    % Does a call instruction call a function whose target we do not know or
    % whose source we do not have?
predicate missing_call_target(c_instr).

    % A function is live if its address is passed to a function that is
    % missing (since the missing function may use the function as a 
    % callback).
    % XXX: Implement me.
%sum_livecode(CFn)->live_fn(l_escaped) :-
%    icall(_,_,I),
%    missing_call_target(I),
%    cil_instr_call_arg(I,_,E),
    

    % Do we have the body of a function that is a call target?
missing_call_target(I) :-
    anycall(I, CFn, _),
    ~cil_body(CFn)->cil_curfn(_). % XXX: Need a better way to test for a 
                                  % missing session.

    % Is the target of an indirect call unknown?
missing_call_target(I) :-
    icall(_,_,I),
    ~dircall(I,_),
    cil_instr_call(I,_),
    cil_body(Fn),
    ~sum_funptr(Fn)->sindirect(I,_).

%-----------------------------------------------------------------------------%
% Code stolen from the function pointer analysis. It really needs to be
% restructured a little bit to publish these interfaces.

?- anycall(A,B,C).

% the extra entry global points-to relationships
session sum_funptr_entry(string) containing [sglob_points].

+no_entry_aliasing().

predicate trace_alias(in T:t_trace,AT:t_trace).
+trace_alias(T,T).

?trace_alias(T,_), trace_sub(T,drf{ST},RT),
    entry_points(s_func,ST,DST), trace_compose(s_func,DST,RT,AT),
    trace_simplify(s_func,AT,NAT), +trace_alias(T,NAT).

?trace_alias(root{glob{G}},_),
    sum_glob(G)->spoints(fld{root{glob{G}},"next"},fld{root{glob{OG}},_}),
    +trace_alias(root{glob{G}},root{glob{OG}}).
?trace_alias(root{glob{G}},_),
    cil_var_name(_,G,TYP), cil_type_comp(TYP,CNAME),
    sum_comp(CNAME)->spoints(fld{empty,"next"},root{glob{OG}}),
    +trace_alias(root{glob{G}},root{glob{OG}}).


% trace T may point to global trace GT at entry
predicate sglob_points(T:t_trace,GT:t_trace).

predicate glob_points(T:t_trace,GT:t_trace).
cil_curfn(FN), sum_funptr_entry(FN)->sglob_points(T,GT), +glob_points(T,GT).

%?- glob_points(A,B).

% add points-to relationships according to global pointers at function entry.
% other relationships due to global and composite type invariants
% were added by memory.clp
glob_points(T,GT), +entry_points(s_func,T,GT).

    % A function is live if it is installed as a signal handler
sum_livecode(CFn)->live_fn(l_sighandler) :-
    live(_),
    anycall(I, "signal", _),
    icall(P0, _, I),
    cil_instr_call_arg(I, 1, HandlerExp),
    eval(P0, HandlerExp, trace{drf{T}}, _),
    trace_alias(T, TT),
    trace_alias(TT, root{glob{CFn}}).

sum_livecode(CFn)->live_fn(l_sighandler) :-
    live(_),
    anycall(I, "sigaction", _),
    icall(P0, _, I),
    cil_instr_call_arg(I, 1, SigActionExp),
    eval(P0, SigActionExp, trace{T}, _),
    (
        val(P0, fld{fld{T, "__sigaction_handler"}, "sa_handler"}, trace{TF}, _)
    ;
        val(P0, fld{fld{T, "__sigaction_handler"}, "sa_sigaction"}, 
            trace{TF}, _)
    ),
    trace_alias(TF, TT),
    trace_alias(TT, root{glob{CFn}}).

