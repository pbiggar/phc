import "src/generated/MIR.clp".


session cfg (METHOD:string).


% Phase 2: Build the CFG
type t_cfg_node ::=
	nentry{t_Method}				% function entry
|	nexit{t_Method}				% function exit
|	nblock{t_Statement}			% basic block (BBs only have 1 statement in them)
	% branch (branches on the condition in t_VARIABLE_NAME)
|	nbranch{t_VARIABLE_NAME, TRUE:t_LABEL_NAME, FALSE:t_LABEL_NAME}
.

predicate cfg_edge (N0:t_cfg_node, N1:t_cfg_node) order[N0, N1].

% CFG nodes are inferred from cfg_edges
predicate cfg_node (N:t_cfg_node).
cfg_node (N) :- cfg_edge (N, _).
cfg_node (N) :- cfg_edge (_, N).

% Allow any user to annotation the CFG with strings. cfgdot will pick up on these.
predicate in_annotation (BB:t_cfg_node, ANNOTATION:string).
predicate out_annotation (BB:t_cfg_node, ANNOTATION:string).
