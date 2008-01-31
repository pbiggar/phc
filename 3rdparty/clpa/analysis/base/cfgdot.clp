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

% generate DOT graphs for the generated CFG on each function
% importing this file will add, for each function foo, a file foo_cfg.dot
% which can be viewed using dotty etc.

import "cilcfg.clp".

using dotty.

% add to label points in the graph as FILE:LINE rather than PP
predicate dot_point_locations().

% use NAME instead of foo_cfg for the dotty file
predicate dot_cfg_name(NAME:string).

% Dotty graph

type dg_node_label ::=
    dg_cfg_node{pp}
  | dg_lab_node{pp, cfg_node}.

predicate dotty_node(dg_node_label, list[t_dg_attr]).
predicate dotty_edge(dg_node_label, dg_node_label, list[t_dg_attr]).

dotty_graph(Name, true, dotgraph{Nodes, Edges}, [], NodeAttrs, []) :-
    ( dot_cfg_name(Name)
    ; ~dot_cfg_name(_), cil_curfn(Fn), Name = Fn ^ "_cfg"
    ),
    \/(dotty_node(NN, NAs), N = dg_node{NN, NAs}):list_all(N, Nodes),
    \/(dotty_edge(EN1, EN2, EAs), E = dg_edge{EN1, EN2, EAs})
        :list_all(E, Edges),
    % Color all the graph nodes using global attributes
    NodeAttrs = [dg_attr{"color", "green"}, dg_attr{"style", "filled"}].
    

% add labels for special CFG nodes
dotty_node(dg_lab_node{P, N}, Attrs) :-
    cfgn_final(P, N),
    Attrs = [dg_attr{"shape", "box"}, dg_attr{"color", "cyan"},
	     dg_attr{"label", tostring(N)}].

dotty_edge(dg_lab_node{P, N}, dg_cfg_node{P}, []) :-
    cfgn_final(P, N).

   
% add edges and label attributes for CFG edges
dotty_node(dg_cfg_node{P}, [dg_attr{"label", Label}]) :-
    (cfge_final(P,_,_) ; cfge_final(_,P,_)),
    (
        dot_point_locations(),
        point_location(P, File, Line), location_string(File, Line, Label)
    ;
        ~dot_point_locations(),
        Label = tostring(P)
    ).

dotty_edge(dg_cfg_node{P0}, dg_cfg_node{P1}, Attrs) :-
    cfge_final(P0,P1,_), 
    \/cfge_final(P0,P1,E):list_all(E,Es),
    Attrs = [dg_attr{"label", tostring(Es)}].


