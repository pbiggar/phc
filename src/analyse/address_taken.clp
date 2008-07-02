% A very simple address-taken alias-analysis. Any variable which is
% referenced, or may be referenced, is marked as is_alias. There is just one
% alias-set, an they all alias each other. Anything is the alias set is
% ignored for scalar optimizations.


type alias = alias_var {string}
				| alias_bottom.

predicate is_alias (VAR_NAME:string) succeeds [zero,once].
is_alias (_) :- in_alias_set (alias_bottom).
is_alias (VAR_NAME) :- in_alias_set (alias_var{VAR_NAME}).

predicate alias_handled (BB:t_cfg_node).

% No aliases
alias_handled (BB) :- cfg_node (BB), 
	(	  BB = nentry{_} 
		; BB = nexit{_},
		; BB = nbranch{_,_,_}
		; BB = nblock{statement_Assign_var {assign_var {_, _, false, _}}},
		; BB = nblock{statement_Assign_array {assign_array {_, _, _, false, _}}}
		; BB = nblock{statement_Push_array {push_array {_, _, _, false, _}}}
		; BB = nblock{statement_Pre_op {pre_op {_, _, _}}}
		; BB = nblock {statement_Foreach_reset{foreach_reset{_, _, _}}}
		; BB = nblock {statement_Foreach_end{foreach_end{_, _, _}}}
		; BB = nblock {statement_Foreach_next{foreach_next{_, _, _}}}


predicate aliased (t_VARIABLE_NAME).
aliased (vARIABLE_NAME{_, VAR_NAME}), +in_alias_set (alias_var{VAR_NAME}).



% Assign_vars - $x =& $y; $x aliases $y;
cfg_node (BB), BB = nblock{statement_Assign_var {
	assign_var {_, LHS, true, EXPR}}},
	+aliased (LHS),
	+alias_expr (BB, EXPR).

% Assign array - $x[$y] =& $z. $z is aliased. $x is not.
cfg_node (BB), BB = nblock{statement_Assign_array {
	assign_array {_, _, _, true, RHS}}},
	+aliased (RHS), +alias_handled (BB).

% Assign array - $x[] =& $z. $z is aliased. $x is not.
cfg_node (BB), BB = nblock{statement_Push_array {
	push_array {_, _, true, RHS}}},
	+aliased (RHS), +alias_handled (BB).

% Eval_expr - RHS may be aliased
cfg_node (BB), BB = nblock{statement_Eval_expr{
	eval_expr{_, EXPR}}},
	+alias_expr (BB, EXPR).

% Return - Since we don't know if the statement is return by reference, we must assume it references.
cfg_node (BB), BB = nblock{statement_Return{
	return {_, EXPR}}}, 
	+alias_expr (BB, EXPR).

% Globals (VARIABLE_NAME) - Any global must be aliased
cfg_node (BB), BB = nblock{statement_Global {
	global {_, variable_name_VARIABLE_NAME{VAR}}}},
	+alias_expr (BB, VAR), +alias_handled (BB).

% Globals (REFLECTION) - Everything is aliased
% cannot say any variable is defined. So nothing happens.
cfg_node (BB), BB = nblock{statement_Global {
	global {_, variable_name_Reflection {_}}}},
	+aliased (BB, alias_bottom),
	+alias_handled (BB).





% Expression handling
predicate alias_expr (BB:t_cfg_node, EXPR:t_Expr).

% No aliases
alias_handled (BB) :- alias_expr (BB, EXPR),
	% Not allowed in MIR:
	%	literal,
	%	cast,
	%	unary_op,
	%	bin_op,
	%	constants
	% Index_array: $x =& $y[$z] or return $y[$z] - Nothing is aliased here
	EXPR = expr_Index_array {index_array{_, _, _}}),
	EXPR = expr_Foreach_has_key{foreach_has_key{_, ARRAY, _}}
	EXPR = expr_Foreach_get_key{foreach_get_key{_, ARRAY, _}}
	EXPR = expr_Foreach_get_val{foreach_get_val{_, ARRAY, _, _}}
	EXPR = expr_Target_expr {target_expr{_, _, _}}


% Variable:  $x =& $y; $y is aliased.
alias_expr (BB, expr_Variable{variable{_, VAR_NAME}}),
	+aliased (BB, VAR_NAME),
	+alias_handled (BB).

% Variable_variable: $x =& $$y - Everything is aliased.
alias_expr (BB, expr_Variable_variable {variable_variable{_, _}}),
	+alised (BB, alias_bottom),
	+alias_handled (BB).

% Method invocation - all parameters can be aliased
alias_expr (BB, expr_Method_invocation {method_invocation {_, _, _, PARAMS}}),
	+alias_actual_params (BB, PARAMS).

% Actual parameters (part of Method_invocation)
% $t->$x[$i]
% $t->$$r[$i]
% $x is aliased unless $t or $i exists
% $r means everything is aliased unless $t or $i
predicate alias_actual_params (BB:t_cfg_node, list[t_Actual_parameter]).

% No target, empty list, VARIABLE_NAME
alias_actual_params (BB, [PARAM|TAIL]),
	PARAM = actual_parameter {_, no, _, variable_name_VARIABLE_NAME{VAR_NAME}, []},
	+aliased_var (BB, VAR),
	+alias_actual_params (BB, TAIL).

% No target, empty list, Reflection
alias_actual_params (BB, [PARAM|TAIL]),
	PARAM = actual_parameter {_, no, _, variable_name_Reflection {_}, []},
	+aliased (BB, alias_bottom),
	+alias_actual_params (BB, TAIL).

% Everything else - No aliases
alias_actual_params (BB, [PARAM|TAIL]),
	PARAM = actual_parameter {_, _, _, _, _},
	+aliased_var (BB, VAR),
	+alias_actual_params (BB, TAIL).

% All params must be handled to get this far
alias_actual_params (BB, []),
	+alias_handled (BB).




% Make sure all rules are alias_handled
predicate alias_handled (BB:t_cfg_node).
predicate error (BB:t_cfg_node).
error (BB) :- 
	cfg_node (BB),
	~alias_handled (BB),
	tostring (BB, BB_STR),
	((BB = nblock {B}, to_node (any{B}, NODE), mir()->source_rep (get_id (NODE), SOURCE))
	;
	(BB \= nblock{_}, SOURCE = "SOURCE NOT AVAILABLE")),
	str_cat_list (["Error, not alias_handled: ", BB_STR, " - ", SOURCE], ERROR),
	+print (ERROR).

assert ~error (_).
