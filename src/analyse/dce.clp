import "live.clp".

% Statements which can be removed if a variable isnt live
%
% Assign_var (non-reference onla, no targety)
% $x = ...
% where ... is:
%	cast
%	unary_op
%	bin_op
%	constant
%	instance_of
%	variable
%	literal
%	foreach_*


cfg_node (BB),
	BB = nblock{statement_Assign_var{S}},
	S = assign_var{_, vARIABLE_NAME{_, VAR_NAME}, false, EXPR},
	~is_side_effecting (EXPR),
	~is_live (BB, VAR_NAME),
	+remove_bb (BB).

cfg_node (BB),
	BB = nblock{statement_Assign_var{S}},
	S = assign_var{_, vARIABLE_NAME{_, VAR_NAME}, false, EXPR},
	is_side_effecting (EXPR),
	~is_live (BB, VAR_NAME),
	+replace_bb (BB, [nblock{statement_Eval_expr {eval_expr{next_id(), EXPR}}}]).

predicate is_side_effecting (in EXPR:t_Expr) succeeds [zero,once].
is_side_effecting (EXPR) :-
	EXPR = expr_New{_} ; EXPR = expr_Method_invocation {_}.
