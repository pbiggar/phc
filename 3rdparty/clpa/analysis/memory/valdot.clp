%%
% Authors:
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

% generate DOT graphs for the value of each written trace at each program
% point in each function.
% for each function foo and written trace x, file foo_x_val.dot will be created

import "scalar.clp".
analyze session_name("cil_body").

+split_loops().

using dotty.

% dotty graph

% get the graph ID to use for each trace in the current function
predicate cfgid(t_trace,dotgraph).
cil_curfn(FN), access(_,T,_), trace_string(T,TS),
    str_cat_list([FN,"_",TS,"_val"],FNTG),
    dotty_graph(FNTG,true,GID), +cfgid(T,GID).

% color all the graph nodes using global attributes
cfgid(_,GID), +dotty_attr(GID,"node","color","green"),
              +dotty_attr(GID,"node","style","filled").

% add labels for special CFG nodes
type label_info ::=
    lab_edge{P,N}
  | lab_node{P,N}.
cfgid(_,GID), cfgn_final(P,N), tostring(N,NS),
    +dotty_edge(GID,lab_edge{P,N},lab_node{P,N},P),
    +dotty_attr(GID,lab_node{P,N},"shape","box"),
    +dotty_attr(GID,lab_node{P,N},"color","cyan"),
    +dotty_attr(GID,lab_node{P,N},"label",NS).

% add edges and label attributes for CFG edges
type edge_info ::= dot_edge{P0,P1}.
cfgid(_,GID), cfge_final(P0,P1,_), 
    +dotty_edge(GID,dot_edge{P0,P1},P0,P1),
    \/cfge_final(P0,P1,E):list_all(E,Es), tostring(Es, Label),
    +dotty_attr(GID,dot_edge{P0,P1},"label",Label).

predicate val_string(in P:pp,in T:t_trace,STR:string).
val_string(P,T,STR) :-
    val(P,T,trace{VT},G), trace_string(VT,VS), guard_string(G,GS),
    str_cat4(GS," -> ",VS,", ",STR).
val_string(P,T,STR) :-
    val(P,T,nrep{SCL},G), scalar_string(SCL,VS), guard_string(G,GS),
    str_cat4(GS," -> ",VS,", ",STR).

cfgid(T,GID), guard(P,_),
    \/val_string(P,T,STR):list_all(STR,SLIST), str_cat_list(SLIST,LSTR0),
    str_cat(LSTR1,", ",LSTR0), str_cat3("[",LSTR1,"]",LSTR),
    +dotty_attr(GID,P,"label",LSTR).
