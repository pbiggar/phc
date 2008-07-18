import "optimize.clp".

% Liveness analysis (for Dead-code elimination).

% Legend:
% U			union
% /			less
% BB			Basic block
%
% An assignment to a variable is dead if the variable is no longer live after
% the assignment. Liveness is a backwards analysis, with the following
% transfer functions:
%
% live_in (Exit) = []
%
% live_out (BB) = U live_in (S), for all S in Succ (BB)
% live_in (BB) = (live_out (BB) / defined (BB)) U used (BB)

% Note omitting definitions is safe, as the live-ness for that variaable
% will continue to propagate, and we cannot kill the definition. Omitting uses
% is not safe, as we may accidentally kill a variable which is later used.


predicate live_in (BB:t_cfg_node, LIVE_INFO:var_info).
predicate live_out (BB:t_cfg_node, LIVE_INFO:var_info).

% Variables defined in block BB
predicate defined (BB:t_cfg_node, LIVE_INFO:var_info).

% Variables used in block BB
predicate used (BB:t_cfg_node, LIVE_INFO:var_info).


% Get that variable name from the vars
predicate defined_var (BB:t_cfg_node, VAR_NAME:t_VARIABLE_NAME).
predicate used_var (BB:t_cfg_node, VAR_NAME:t_VARIABLE_NAME).

defined (BB, var_name{NAME}) :- defined_var (BB, vARIABLE_NAME{_, NAME}).
used (BB, var_name{NAME}) :- used_var (BB, vARIABLE_NAME{_, NAME}).

predicate is_live (in BB:t_cfg_node, in VAR_NAME:string) succeeds [zero,once].
is_live (BB, VAR_NAME) :-
	live_out (BB, var_name{VAR_NAME})
	; live_out (BB, var_bottom).



% Intensional Rules

% live_in (Exit) = []
% Implicit

% live_out (BB) = U live_in (S), for all S in Succ (BB)
live_out (BB, OUT) :- cfg_node (BB),
	cfg_edge (BB, SUCC), live_in (SUCC, OUT).

% live_in (BB) = (live_out (BB) / defined (BB)) U used (BB)
live_in (BB, VAR) :-
	(live_out (BB, VAR), ~defined (BB, VAR) ; used (BB, VAR)).





% Extensional rules (from the predicates).

% Entry and exit - nothing to do here
live_handled (BB) :- cfg_node (BB), (BB = nentry{_} ; BB = nexit{_} ; BB = nempty{_}).

% Branches - the var is used
cfg_node (BB), BB = nbranch{VAR, _, _}, 
	+used_var (BB, VAR), +live_handled (BB).

% Assign_vars - the LHS is defined. The RHS needs to be checked. IS_REF
% doesnt matter: if it is true, then we conservatively miss some definitions,
% which is OK.
cfg_node (BB), BB = nblock{statement_Assign_var {
	assign_var {_, LHS, _, EXPR}}},
	+defined_var (BB, LHS),
	+use_expr (BB, EXPR).

% Assign array - $x[$y] = $z. All of x, y and z are used (even though $x has
% the potential to be defined).
cfg_node (BB), BB = nblock{statement_Assign_array {
	assign_array {_, LHS, INDEX, _, RHS}}},
	+used_var (BB, LHS), +used_var (BB, INDEX), +used_var (BB, RHS),
	+live_handled (BB).

cfg_node (BB), BB = nblock{statement_Push_array {
	push_array {_, ARRAY, _, RHS}}},
	+used_var (BB, ARRAY),
	+used_var (BB, RHS),
	+live_handled (BB).

% Eval_expr - Rewrap it, and treat like a normal expr
cfg_node (BB), BB = nblock{statement_Eval_expr{
	eval_expr{_, EXPR}}},
	+use_expr (BB, EXPR).

% Return - expr is used.
cfg_node (BB), BB = nblock{statement_Return{
	return {_, EXPR}}}, 
	+use_expr (BB, EXPR).

% Globals - the overwrite the variables, so consider it a define
cfg_node (BB), BB = nblock{statement_Global {
	global {_, variable_name_VARIABLE_NAME{VAR}}}},
	+defined_var (BB, VAR), +live_handled (BB).

% globals with reflection - they may-define every variable, which means we
% cannot say any variable is defined. So nothing happens.

cfg_node (BB), BB = nblock{statement_Global {
	global {_, variable_name_Reflection {_}}}},
	+live_handled (BB).

% Pre_op - the variable is both used and defined
cfg_node (BB), BB = nblock{statement_Pre_op {
	pre_op {_, _, VAR}}},
	% TODO If VAR is simple, it may be defined here, in which case we can
	% remove the definition if VAR is not live on exit, which is not reflected
	% here. Add +defined (VAR).
	+used_var (BB, VAR), +live_handled (BB).

% Foreach statements
cfg_node (BB), BB = nblock {statement_Foreach_reset{foreach_reset{_, VAR_NAME, _}}},
	+used_var (BB, VAR_NAME),
	+live_handled (BB).

cfg_node (BB), BB = nblock {statement_Foreach_end{foreach_end{_, VAR_NAME, _}}},
	+used_var (BB, VAR_NAME),
	+live_handled (BB).

cfg_node (BB), BB = nblock {statement_Foreach_next{foreach_next{_, VAR_NAME, _}}},
	+used_var (BB, VAR_NAME),
	+live_handled (BB).






% Expression handling
predicate use_expr (BB:t_cfg_node, EXPR:t_Expr).

% Literals
use_expr (BB, expr_INT{_}), +live_handled (BB).
use_expr (BB, expr_STRING{_}), +live_handled (BB).
use_expr (BB, expr_BOOL{_}), +live_handled (BB).
use_expr (BB, expr_REAL{_}), +live_handled (BB).
use_expr (BB, expr_NIL{_}), +live_handled (BB).

% Variables
use_expr (BB, expr_Variable{variable{_, VAR_NAME}}),
	+used_var (BB, VAR_NAME),
	+live_handled (BB).

use_expr (BB, expr_Index_array {index_array{_, ARRAY_NAME, INDEX_NAME}}),
	+used_var (BB, INDEX_NAME),
	+used_var (BB, ARRAY_NAME),
	+live_handled (BB).

use_expr (BB, expr_Variable_variable {variable_variable{_, _}}),
	+used (BB, var_bottom),
	+live_handled (BB).

% Target_expr
use_expr (BB, expr_Target_expr {target_expr{_, TARGET, VARIABLE_NAME}}),
	% Target
	(( TARGET = target_CLASS_NAME {_})
	;
	(
		TARGET = target_VARIABLE_NAME{T_VAR_NAME}, 
		+used_var (BB, T_VAR_NAME)
	)),

	% Variable_name
	(( 
		VARIABLE_NAME = variable_name_Reflection {_},
		+used (BB, var_bottom)
	)
	;
	(
		VARIABLE_NAME = variable_name_VARIABLE_NAME {VAR_NAME}, 
		+used_var (BB, VAR_NAME)
	)),
	+live_handled (BB).


% Cast_op
use_expr (BB, expr_Cast {cast {_, _, VAR}}),
	+used_var (BB, VAR),
	+live_handled (BB).

% Unary_op
use_expr (BB, expr_Unary_op {unary_op {_, _, VAR}}),
	+used_var (BB, VAR), 
	+live_handled (BB).

% Bin_op
use_expr (BB, expr_Bin_op {bin_op {_, LEFT, _, RIGHT}}),
	+used_var (BB, LEFT), 
	+used_var (BB, RIGHT), 
	+live_handled (BB).

% Constant
use_expr (BB, expr_Constant {_}), % no used vars
	+live_handled (BB).

% Foreach
use_expr (BB, expr_Foreach_has_key{foreach_has_key{_, ARRAY, _}}),
	+used_var (BB, ARRAY), +live_handled (BB).

use_expr (BB, expr_Foreach_get_key{foreach_get_key{_, ARRAY, _}}),
	+used_var (BB, ARRAY), +live_handled (BB).

% Ignore key.
use_expr (BB, expr_Foreach_get_val{foreach_get_val{_, ARRAY, _, _}}),
	+used_var (BB, ARRAY), +live_handled (BB).


% Method invocation
use_expr (BB, expr_Method_invocation {method_invocation {_, no, _, PARAMS}}),
	+use_actual_params (BB, PARAMS). 

% Actual parameters (part of Method_invocation)
% TODO reflection - means all variables are potentially used
predicate use_actual_params (BB:t_cfg_node, list[t_Actual_parameter]).
use_actual_params (BB, [PARAM|TAIL]),
	PARAM = actual_parameter {_, _, no, variable_name_VARIABLE_NAME{VAR}, ARRAY_INDICES},
	+used_var (BB, VAR),
	+use_variable_names (BB, ARRAY_INDICES),
	+use_actual_params (BB, TAIL).

% TODO unsafe, this will succeed if one parameter succeeds, whereas it should fail if any of them fail.
use_actual_params (BB, []),
	+live_handled (BB).

% VARIABLE_NAMEs
predicate use_variable_names (BB:t_cfg_node, list[t_VARIABLE_NAME]).
use_variable_names (BB, [VAR_NAME|TAIL]),
	+used_var (BB, VAR_NAME),
	+use_variable_names (BB, TAIL).
% No need to handle empty list




% Annotate the CFG with liveness info.

in_annotation (BB, STR) :- live_in (BB, var_name{STR}).
out_annotation (BB, STR) :- live_out (BB, var_name{STR}).
in_annotation (BB, "BOTTOM") :- live_in (BB, var_bottom).
out_annotation (BB, "BOTTOM") :- live_out (BB, var_bottom).



% Error checking
predicate live_handled (BB:t_cfg_node).

