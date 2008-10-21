import "optimize.clp".

% Copy-propagation

% Given
%	B = A;
%	C = B;
%
% we can convert this to:
%  B = A;
%  C = A;
%
% which might make B = A dead.
%
% Look at Muchnick, Section 12.5, there are a few differences in our approach. Since all our basic blocks are 1 statement long, we dont need to local phase. We also dont need to keep track of where statements are defined. So its much easier.
%
% copy_in (Entry) = []
% copy_in (BB) = INTERSECT copy_in (P), for all P in Pred (BB)
% copy_out (BB) = (copy_in (BB) / killed (BB)) U copied (BB)
%
% copied (BB) = (A, B), for A := B
% killed (BB) = (A, _), for A in defined (BB)

type copy_info ::= copy_all | copy_var { TARGET:string, SOURCE:string }.

predicate copy_in (BB:t_cfg_node, COPY:copy_info).
predicate copy_out (BB:t_cfg_node, COPY:copy_info).

predicate copied (BB:t_cfg_node, COPY:copy_info).
predicate killed (BB:t_cfg_node, KILL:var_info).

cfg_node (BB), BB = nblock{statement_Assign_var {
	assign_var {_, vARIABLE_NAME{_, LHS}, _, expr_Variable{variable{_, vARIABLE_NAME{_, RHS}}}}}},
	+copied (BB, copy_var {RHS, LHS}).

% Just use the results from liveness
killed (BB, KILL) :-
	defined (BB, KILL).


copy_in (BB, COPY) :-
	cfg_edge (PRED, BB), copy_out (PRED, COPY).


% Intensional Rules

?- copied (BB, C).
?- killed (BB, C).
?- copy_in (BB, C).
?- copy_out (BB, C).

% copy_in (Entry) = []
% implicit.


% copied (BB) = (A, B), for A := B
% killed (BB) = (A, _), for A in defined (BB)
