import "src/generated/MIR.clp".


session cfg (METHOD:string).


% Phase 2: Build the CFG
type t_cfg_node ::=
	nentry{t_Method}				% function entry
|	nexit{t_Method}				% function exit
|	nblock{t_Statement}			% basic block (BBs only have 1 statement in them)
|	nbranch{t_VARIABLE_NAME}	% branch (branches on the condition in t_VARIABLE_NAME)
.

predicate cfg_edge (N0:t_cfg_node, N1:t_cfg_node).

% CFG nodes are inferred from cfg_edges
predicate cfg_node (N:t_cfg_node).
cfg_node (N) :- cfg_edge (N, _).
cfg_node (N) :- cfg_edge (_, N).
