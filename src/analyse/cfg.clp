import "src/generated/MIR.clp".
import "3rdparty/clpa/analysis/base/utility.clp".
using dotty.


session cfg (METHOD:string).


% Phase 2: Build the CFG
type t_cfg_node ::=
	nentry{t_Method}				% function entry
|	nexit{t_Method}				% function exit
|	nblock{t_Statement}			% basic block (BBs only have 1 statement in them)
|	nbranch{t_VARIABLE_NAME}	% branch (branches on the condition in t_VARIABLE_NAME)
.

predicate cfg_node (N:t_cfg_node).
predicate cfg_edge (N0:t_cfg_node, N1:t_cfg_node).


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
	source_rep (any{S}, SOURCE), 
	Attrs = [dg_attr{"label", SOURCE}].

% Branches
dotty_node (N, Attrs) :- 
	cfg_node (N), 
	N = nbranch{B}, 
	source_rep (any{B}, VARNAME),
	Attrs = [dg_attr{"label", VARNAME}, dg_attr{"shape", "rectangle"}].

% Edges
dotty_edge (E1, E2, []) :- cfg_edge (E1, E2).

dotty_graph (Name, true, dotgraph{Nodes, Edges}, [], [], []) :-
	Name = "CFG",
	\/(dotty_node (DN, NAs), N = dg_node{DN, NAs}):list_all(N, Nodes),
	\/(dotty_edge (DE1, DE2, EAs), E = dg_edge{DE1, DE2, EAs}):list_all(E, Edges).
