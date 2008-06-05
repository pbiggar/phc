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
% the assignment. Liveness is a backwards analysis, with the following transfer
% functions:
%
% live_in (Exit) = []
%
% live_out (B) = U S, for S in Succ (B)
% live_in (B) = (live_out (B) / defined (B)) U used (B)


predicate live_in (BB:t_cfg_node, LIVE_VARIABLE:t_VARIABLE_NAME).
predicate live_out (BB:t_cfg_node, LIVE_VARIABLE:t_VARIABLE_NAME).

% Variables defined in block B
predicate defined (BB:t_cfg_node, VAR:t_VARIABLE_NAME).

% Variables used in block B
predicate used (BB:t_cfg_node, VARS:t_VARIABLE_NAME).


% live_in (Exit) = []
%cfg_node (BB), BB = nexit{_}, set_empty(LS_IN), +live_in (BB, LS_IN).

% live_out (B) = U S, for S in Succ (B)
live_out (BB, OUT) :- cfg_node (BB),
	cfg_edge (BB, SUCC), live_in (SUCC, OUT).



% live_in (B) = (live_out (B) / defined (B)) U used (B)
live_in (BB, VAR) :-
	live_out (BB, VAR), (~defined (BB, VAR) ;  used (BB, VAR)).

% Used
% TODO
cfg_node (BB), BB = nbranch{VAR}, +used (BB, VAR).

% function call
cfg_node (BB), 
	BB = nblock{S},S = statement_Assign_var {ID},
	mir ()->assign_var (ID, no, LHS, false, _),
	+defined (BB, LHS).




?- live_in (nentry{_}, SET).
?- live_out (BB, SET).
