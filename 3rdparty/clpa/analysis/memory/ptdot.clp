%%
% Authors:
%   Peter Hawkins  <hawkinsp@cs.stanford.edu>
%   Brian Hackett  <bhackett@stanford.edu>
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

% For each program point in a procedure, generate a dot graph representing
% the points-to relationships for all accessed traces.
% for each function foo and written trace x, file foo_x_val.dot will be created

import "scalar.clp".
import "utility.clp".
analyze session_name("cil_sum_body").

using dotty.

predicate guard_length_limit(int) succeeds [once].
guard_length_limit(25) :- .

% dotty graph

% Get the graph ID to use for each program point in the current function
predicate cfgid(pp, dotgraph).
cfgid(P, GId) :-
    cil_curfn(FN), cil_cursum(Sum), guard(P, _),
    str_rep(tostring(P), ",", "_", PS1),
    str_rep(PS1, "\"", "_", PS),
    Name = FN ^ "_" ^ tostring(Sum) ^  "_" ^ PS ^ "_val",
    dotty_graph(Name, true, GId).

% Color all the graph nodes using global attributes
dotty_attr(GId,"node","color","green")  :- cfgid(_, GId).
dotty_attr(GId,"node","style","filled") :- cfgid(_, GId).

type edge_name ::= dot_edge{string, string}.

cfgid(_, GId), access(_, T, _),
    +dotty_node(GId, trace_string(T)),
    cil_cursum(Sum), trace_soft(Sum, T, _),
    +dotty_attr(GId, trace_string(T), "color", "cyan").

cfgid(P, GId), access(_, S, _), val(P, S, trace{T}, G),
    trace_string(S, SS), trace_string(T, TS),
    GS0 = guard_string(guard_simplify(G)),
    str_len(GS0, GSLen),
    ( int_gt(GSLen, guard_length_limit()), GS = "..."
    ; int_le(GSLen, guard_length_limit()), GS = GS0
    ),
    +dotty_edge(GId, dot_edge{SS, TS}, SS, TS),
    +dotty_attr(GId, dot_edge{SS, TS}, "label", GS).

