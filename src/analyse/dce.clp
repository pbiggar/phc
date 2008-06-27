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
	S = assign_var{_, no, vARIABLE_NAME{_, VAR_NAME}, false, expr_INT{_}},
	~live_out (BB, VAR_NAME),
	+mark_dead (BB).

cfg_node (BB),
	BB = nblock{statement_Assign_var{S}},
	S = assign_var{_, no, vARIABLE_NAME{_, VAR_NAME}, false, expr_Variable{_}},
	~live_out (BB, VAR_NAME),
	+mark_dead (BB).

