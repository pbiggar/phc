import "optimize.clp".

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

% Note ommitting deifnitions is safe, as the live-ness for that varaiable
% will continue to propagate, and we cannot kill the definition. Omitting uses
% is not safe, as we may accidentally kill a variable which is later used.

predicate live_in (BB:t_cfg_node, VAR_NAME:string).
predicate live_out (BB:t_cfg_node, VAR_NAME:string).

% Variables defined in block BB
predicate defined (BB:t_cfg_node, VAR_NAME:string).

% Variables used in block BB
predicate used (BB:t_cfg_node, VAR_NAME:string).


% Get that variable name from the vars
predicate defined_var (BB:t_cfg_node, VAR_NAME:t_VARIABLE_NAME).
predicate used_var (BB:t_cfg_node, VAR_NAME:t_VARIABLE_NAME).

defined (BB, NAME) :- defined_var (BB, vARIABLE_NAME{_, NAME}).
used (BB, NAME) :- used_var (BB, vARIABLE_NAME{_, NAME}).


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

% Entry and exit - nothing to do here
handled (BB) :- cfg_node (BB), (BB = nentry{_} ; BB = nexit{_}).

% Branches - the var is used
cfg_node (BB), BB = nbranch{VAR, _, _}, 
	+used_var (BB, VAR), +handled (BB).

% Assign_vars - the LHS is defined. The RHS needs to be checked. IS_REF
% doesnt matter: if it is true, then we conservatively miss some definitions,
% which is OK.
cfg_node (BB), BB = nblock{statement_Assign_var {
	assign_var {_, no, LHS, _, EXPR}}},
	+defined_var (BB, LHS), +use_expr (BB, EXPR).

% Assign array - $x[$y] = $z. All of x, y and z are used (even though $x has
% the potential to be defined).
cfg_node (BB), BB = nblock{statement_Assign_array {
	assign_array {_, no, LHS, INDEX, _, RHS}}},
	+used_var (BB, LHS), +used_var (BB, INDEX), +used_var (BB, RHS),
	+handled (BB).

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
	+defined_var (BB, VAR), +handled (BB).

% globals with reflection - they may-define every variable, which means we
% cannot say any variable is defined. So nothing happens.

cfg_node (BB), BB = nblock{statement_Global {
	global {_, variable_name_Reflection {_}}}},
	+handled (BB).

% Pre_op - the variable is both used and defined
cfg_node (BB), BB = nblock{statement_Pre_op {
	pre_op {_, _, VAR}}},
	% TODO If VAR is simple, it may be defined here, in which case we can
	% remove the definition if VAR is not live on exit, which is not reflected
	% here. Add +defined (VAR).
	+use_variable (BB, VAR), +handled (BB).




% Generic expression handling
predicate use_expr (BB:t_cfg_node, EXPR:t_Expr).

% Literals
use_expr (BB, expr_INT{_}), +handled (BB).
use_expr (BB, expr_STRING{_}), +handled (BB).
use_expr (BB, expr_BOOL{_}), +handled (BB).
use_expr (BB, expr_REAL{_}), +handled (BB).

% Variables
predicate use_variable (BB:t_cfg_node, Variable:t_Variable).
use_expr (BB, expr_Variable{ID}), +use_variable (BB, ID).
use_variable (BB, 
	variable {_, no, variable_name_VARIABLE_NAME{VAR_NAME}, ARRAY_INDICES}),
	+used_var (BB, VAR_NAME),
	+use_variable_names (BB, ARRAY_INDICES),
	+handled (BB).
	
% Cast_op
use_expr (BB, expr_Cast {cast {_, _, VAR}}),
	+used_var (BB, VAR),
	+handled (BB).

% Unary_op
use_expr (BB, expr_Unary_op {unary_op {_, _, VAR}}),
	+used_var (BB, VAR), 
	+handled (BB).

% Bin_op
use_expr (BB, expr_Bin_op {bin_op {_, LEFT, _, RIGHT}}),
	+used_var (BB, LEFT), 
	+used_var (BB, RIGHT), 
	+handled (BB).

% Constant
use_expr (BB, expr_Constant {_}), % no used vars
	+handled (BB).

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
	+handled (BB).

% VARIABLE_NAMEs
predicate use_variable_names (BB:t_cfg_node, list[t_VARIABLE_NAME]).
use_variable_names (BB, [VAR_NAME|TAIL]),
	+used_var (BB, VAR_NAME),
	+use_variable_names (BB, TAIL).
% No need to handle empty list




% Annotate the CFG with liveness info.

in_annotation (BB, STR) :- live_in (BB, STR).
out_annotation (BB, STR) :- live_out (BB, STR).



% Make sure all rules are handled
predicate handled (BB:t_cfg_node).
predicate error (BB:t_cfg_node).
error (BB) :- 
	cfg_node (BB),
	~handled (BB),
	tostring (BB, BB_STR),
	((BB = nblock {B}, to_node (any{B}, NODE), mir()->source_rep (get_id (NODE), SOURCE))
	;
	(BB \= nblock{_}, SOURCE = "SOURCE NOT AVAILABLE")),
	str_cat_list (["Error, not handled: ", BB_STR, " - ", SOURCE], ERROR),
	+print (ERROR).

assert ~error (_).
