import "src/generated/MIR.clp".


session cfg (METHOD:string, VERSION:int).


% Phase 2: Build the CFG
type t_cfg_node ::=
  nentry{t_Method}				% function entry
| nexit{t_Method}					% function exit
| nblock{t_Statement}			% basic block (BBs only have 1 statement in
										% them)
| nbranch{	VARIABLE_NAME:t_VARIABLE_NAME,  % branch on VARIABLE_NAME
				TRUE:t_cfg_node, 
				FALSE:t_cfg_node} 
												
| nempty{t_Statement} % We replace labels and gotos with empty blocks
.

predicate cfg_edge (N0:t_cfg_node, N1:t_cfg_node) order[N0, N1].

% CFG nodes are inferred from cfg_edges
predicate cfg_node (N:t_cfg_node).
cfg_node (N) :- cfg_edge (N, _).
cfg_node (N) :- cfg_edge (_, N).

% Allow any user to annotation the CFG with strings. cfgdot, if imported,  will
% pick up on these.
predicate in_annotation (BB:t_cfg_node, ANNOTATION:string).
predicate out_annotation (BB:t_cfg_node, ANNOTATION:string).



% Indicates the CFG has changed this iteration, and another iteration is required.
predicate reiterate ().

% This block, and its incoming and outgoing edges are dead, and will be removed
% in the next version. PRIVATE.
predicate is_dead (BB:t_cfg_node).
is_dead (BB) :- remove_bb (BB).


% Remove a node from the CFG
predicate remove_bb (BB:t_cfg_node).
remove_bb (BB), +replace_bb (BB, []).
replace_bb (BB, _), +is_dead (BB), +reiterate ().

% Replace a CFG node with a list of nodes
predicate replace_bb (BB:t_cfg_node, NEW_BBS:list[t_cfg_node]).
