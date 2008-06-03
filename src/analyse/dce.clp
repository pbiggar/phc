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


predicate live_in (BB:t_cfg_node, LIVE_VARIABLES:set[t_VARIABLE_NAME]).
predicate live_out (BB:t_cfg_node, LIVE_VARIABLES:set[t_VARIABLE_NAME]).

% Variables defined in block B
predicate defined (BB:t_cfg_node, VARS:set[t_VARIABLE_NAME]).

% Variables used in block B
predicate used (BB:t_cfg_node, VARS:set[t_VARIABLE_NAME]).


% live_in (Exit) = []
cfg_node (BB), BB = nexit{_}, set_empty(LS_IN), +live_in (BB, LS_IN).

% live_out (B) = U S, for S in Succ (B)
live_out (BB, LS_OUT) :- cfg_node (BB),
	\/(cfg_edge (BB, SUCC), live_in (SUCC, LS_SUCC)):set_union_all(LS_SUCC, LS_OUT).



% live_in (B) = (live_out (B) / defined (B)) U used (B)
live_in (BB, LS_IN) :-
	live_out (BB, LS_OUT), defined (BB, DEF), used (BB, USED),
	set_difference (LS_OUT, DEF, TEMP),
	set_union (TEMP, USED, LS_IN).

% Used
% TODO
cfg_node (BB), BB = nbranch{VAR}, set_singleton (VAR, SET), +used (BB, SET).
cfg_node (BB), BB = nblock{_}, set_empty (SET), +used (BB, SET).

% Defined
% TODO
cfg_node (BB), BB = nbranch{_}, set_empty (SET), +defined (BB, SET).
cfg_node (BB), BB = nblock{_}, set_empty (SET), +defined (BB, SET).

?- live_in (nentry{_}, SET).
?- live_out (BB, SET).
