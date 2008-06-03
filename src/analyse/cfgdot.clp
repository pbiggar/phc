import "cfg.clp".
import "src/generated/MIR.clp".

import "3rdparty/clpa/analysis/base/utility.clp".
using dotty.

% Build a .dot file to view the CFG


% Create dotty nodes and edges
predicate dotty_node (NODE:t_cfg_node, list[t_dg_attr]).
predicate dotty_edge (E1:t_cfg_node, E2:t_cfg_node, list[t_dg_attr]).

% Nodes
dotty_node (N, []) :- cfg_node (N), N = nentry{_}.
dotty_node (N, []) :- cfg_node (N), N = nexit{_}.

% Normal statements
dotty_node (N, Attrs) :- 
	cfg_node (N), 
	N = nblock{S},
	mir()->source_rep (any{S}, SOURCE),
	tostring (S, SSTRING), str_cat4 (SOURCE, "[", SSTRING, "]", LABEL),
	Attrs = [dg_attr{"label", LABEL}].


% Branches
dotty_node (N, Attrs) :- 
	cfg_node (N), 
	N = nbranch{B}, 
	mir()->source_rep (any{B}, VARNAME),
	tostring (B, BSTRING), str_cat4 (VARNAME, "\n[", BSTRING, "]", LABEL),
	Attrs = [dg_attr{"label", LABEL}, dg_attr{"shape", "rectangle"}].

% Edges
dotty_edge (E1, E2, []) :- cfg_edge (E1, E2).

dotty_graph (Name, true, dotgraph{Nodes, Edges}, [], [], []) :-
	Name = "CFG",
	\/(dotty_node (DN, NAs), N = dg_node{DN, NAs}):list_all(N, Nodes),
	\/(dotty_edge (DE1, DE2, EAs), E = dg_edge{DE1, DE2, EAs}):list_all(E, Edges).


%?- dotty_node (A, N).
%?- dotty_edge (A, B, N).
%?- cfg_edge (A, B).
%?- cfg_node (A).
