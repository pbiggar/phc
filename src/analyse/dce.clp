import "cfg.clp".

analyze session_name("cfg").
using set.
using error.

import "cfgdot.clp".

% Dead code elimination.

% Legend:
% U			union
% /			less
% B			Basic block
%
% An assignment to a variable is dead if the variable is no longer live after
% the assignment. Liveness is a backwards analysis, with the following
% transfer functions:
%
% live_in (Exit) = []
%
% live_out (B) = U S, for S in Succ (B)
% live_in (B) = (live_out (B) / defined (B)) U used (B)


predicate live_in (BB:t_cfg_node, VAR_NAME:string).
predicate live_out (BB:t_cfg_node, VAR_NAME:string).

% Variables defined in block B
predicate defined (BB:t_cfg_node, VAR_NAME:string).

% Variables used in block B
predicate used (BB:t_cfg_node, VAR_NAME:string).


% Get that variable name from the vars
predicate defined_var (BB:t_cfg_node, VAR_NAME:t_VARIABLE_NAME).
defined (BB, VAR_NAME) :- 
	defined_var (BB, VAR), mir()->vARIABLE_NAME (VAR, VAR_NAME).

predicate used_var (BB:t_cfg_node, VAR_NAME:t_VARIABLE_NAME).
used (BB, VAR_NAME) :- 
	used_var (BB, VAR), mir()->vARIABLE_NAME (VAR, VAR_NAME).



% Intensional Rules

% live_in (Exit) = []
% Implicit

% live_out (B) = U S, for S in Succ (B)
live_out (BB, OUT) :- cfg_node (BB),
	cfg_edge (BB, SUCC), live_in (SUCC, OUT).

% live_in (B) = (live_out (B) / defined (B)) U used (B)
live_in (BB, VAR) :-
	(live_out (BB, VAR), ~defined (BB, VAR) ; used (BB, VAR)).





% Extensional rules (from the predicates).


% Make sure all rules are handled
predicate handled (BB:t_cfg_node).
predicate error (BB:t_cfg_node).
error (BB) :- cfg_node (BB), ~handled (BB).

print (ERROR) :- error (BB), tostring (BB, BB_STR), str_cat ("Error: ", BB_STR, ERROR).
assert ~error (_).



% Branches - the var is used
cfg_node (BB), BB = nbranch{VAR}, 
	+used_var (BB, VAR), +handled (BB).

% Assign_vars - the LHS is defined. The RHS needs to be checked.
cfg_node (BB), 
	BB = nblock{S},S = statement_Assign_var {ID},
	mir ()->assign_var (ID, no, LHS, false, _),
	+defined_var (BB, LHS).


% Annotate the CFG with liveness info.

in_annotation (BB, STR) :- live_in (BB, STR).
out_annotation (BB, STR) :- live_out (BB, STR).

?- cfg_node (BB).
?- handled (BB).
