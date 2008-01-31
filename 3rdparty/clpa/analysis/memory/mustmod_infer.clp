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
% mustmod_infer.clp 
%
% A simple must-mod analysis that attempts to determine when a trace
% was definitely modified by a summary.
%
%-----------------------------------------------------------------------------%

import "memory/scalar_sat.clp".
import "memory/mustmod.clp".

+no_rel_inst_trace().

analyze session_name("cil_sum_body").

% Split all loops.
+split_loops().
+prune_exit_calls().
%import "../base/cfgdot.clp".


% -----------------------------------------------------------------------------
    % sum_stmustmod(Sum, T)
    % Trace T must be modified before reaching any exit point of Sum.
predicate sum_stmustmod(sum, t_trace).

    % sum_exit_maynotmod(Sum, P, T)
    % Trace T may not be modified before reaching exit point P of Sum.
predicate sum_exit_maynotmod(sum, pp, t_trace).

    % sum_exit_mustmod(Sum, P, T)
    % Trace T must be modified before reaching exit point P of Sum.
predicate sum_exit_mustmod(sum, pp, t_trace).

    % trace_must_be_modified(P, T)
    % Trace T can no longer point to its original target at P.
predicate trace_must_be_modified(in pp, in t_trace).

predicate possible_mustmod(t_trace).

% -----------------------------------------------------------------------------

sum_mustmod(Fn, Sum)->stmustmod(T) :-
    cil_curfn(Fn),
    sum_stmustmod(Sum, T).

sum_stmustmod(Sum, T) :-
    sum_exit_mustmod(Sum, _, S),
    ~sum_exit_maynotmod(Sum, _, S),
    exit_trace_rename(Sum, S, T).

?- sum_stmustmod(Sum, T).

% -----------------------------------------------------------------------------

sum_exit_maynotmod(Sum, POut, T) :-
    sum_bound(Sum, _, POut),
    possible_mustmod(T),
    ~sum_exit_mustmod(Sum, POut, T).
    

% -----------------------------------------------------------------------------

sum_exit_mustmod(Sum, POut, T) :-
    sum_bound(Sum, _, POut), 
    possible_mustmod(T),
    ~trace_soft(Sum, T),
    trace_must_be_modified(POut, T).

% -----------------------------------------------------------------------------

trace_must_be_modified(P, T) :-
    ~val(P, T, trace{drf{T}}, _).
trace_must_be_modified(P, T) :-
    val(P, T, trace{drf{T}}, G),
    ~guard_sat(G).

% -----------------------------------------------------------------------------

possible_mustmod(T) :-
    access(_, T, write),
    cil_cursum(Sum),
    T \= root{return},
    trace_alloc(Sum, T, ak_external).

possible_mustmod(T) :-
    anycall(I, Fn, _),
    icall(P0, _, I),
    sum_mustmod(Fn, s_func)->stmustmod(S),
    inst_trace(s_call{I}, P0, S, trace{T}, _),
    cil_cursum(Sum),
    trace_alloc(Sum, T, ak_external).
    
possible_mustmod(T) :-
    iloop(P0, _, I),
    cil_curfn(Fn),
    sum_mustmod(Fn, s_loop{I})->stmustmod(S),
    inst_trace(s_loop{I}, P0, S, trace{T}, _),
    cil_cursum(Sum),
    trace_alloc(Sum, T, ak_external).
    
% -----------------------------------------------------------------------------
