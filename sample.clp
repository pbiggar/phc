type id = int.

% Conjunctive types
type php_Variable ::= phc_Variable_id {id}.
type php_Assignment ::= phc_Assignment_id {id}.
type php_Eval_expr ::= phc_Eval_expr_id {id}.
type php_Actual_parameter ::= phc_Actual_parameter_id {id}.
type php_Method_invocation ::= phc_Method_invocation_id {id}.
type php_PHP_script ::= phc_PHP_script_id {id}.

% Disjunctive types
type php_Expr ::= phc_Expr_id {id}.
type php_Literal ::= phc_Literal_id {id}.
type php_Statement ::= phc_Statement_id {id}.

% Token types
type php_VARIABLE_NAME ::= phc_VARIABLE_NAME_id {id}.
type php_INT ::= phc_INT_id {id}.
type php_METHOD_NAME ::= phc_METHOD_NAME_id {id}.


% Conjunctive Predicates
predicate ast_Variable (ID:php_Variable, VARIABLE_NAME:php_VARIABLE_NAME).
predicate ast_Assignment (ID:php_Assignment, VARIABLE:php_Variable, Expr:php_Expr).
predicate ast_Eval_expr (ID:php_Eval_expr, EXPR:php_Expr).
predicate ast_Actual_parameter (ID:php_Actual_parameter, IS_REF:bool, EXPR:php_Expr).
predicate ast_Method_invocation (ID:php_Method_invocation, METHOD_NAME:php_METHOD_NAME, ACTUAL_PARAMETERS:list[php_Actual_parameter]).
predicate ast_PHP_script (ID:php_PHP_script, STATEMENTS:list[php_Statement]).

% Disjunctive predicates
predicate ast_Expr_Literal		(ID:php_Expr, LITERAL:php_Literal).
predicate ast_Expr_Assignment (ID:php_Expr, ASSIGNMENT:php_Assignment).
predicate ast_Expr_Variable	(ID:php_Expr, VARIABLE:php_Variable).
predicate ast_Expr_Method_invocation (ID:php_Expr, METHOD_INVOCATION:php_Method_invocation).
predicate ast_Literal_INT		(ID:php_Literal, INT:php_INT).
predicate ast_Statement_Eval_expr (ID:php_Statement, EVAL_EXPR:php_Eval_expr).

% Token predicates
predicate ast_VARIABLE_NAME (ID:php_VARIABLE_NAME, VALUE:string).
predicate ast_METHOD_NAME (ID:php_METHOD_NAME, VALUE:string).
predicate ast_INT (ID:php_INT, VALUE:int).


% Data
+ast_VARIABLE_NAME (phc_VARIABLE_NAME_id{4}, "a").
+ast_VARIABLE_NAME (phc_VARIABLE_NAME_id{9}, "TSe0").
+ast_VARIABLE_NAME (phc_VARIABLE_NAME_id{13}, "a").

+ast_METHOD_NAME (phc_METHOD_NAME_id{11}, "var_dump").

+ast_Variable (phc_Variable_id{3}, phc_VARIABLE_NAME_id{4}).
+ast_Variable (phc_Variable_id{8}, phc_VARIABLE_NAME_id{9}).
+ast_Variable (phc_Variable_id{20}, phc_VARIABLE_NAME_id{13}).

+ast_Assignment (phc_Assignment_id{2}, phc_Variable_id{3}, phc_Expr_id{100}).
+ast_Expr_Literal (phc_Expr_id{100}, phc_Literal_id{101}).
+ast_Literal_INT (phc_Literal_id{101}, phc_INT_id{102}).
+ast_INT (phc_INT_id{102}, 5).

+ast_Eval_expr (phc_Eval_expr_id{1}, phc_Expr_id{200}).
+ast_Expr_Assignment(phc_Expr_id{200}, phc_Assignment_id{9}).


+ast_Actual_parameter (phc_Actual_parameter_id{12}, false, phc_Expr_id{300}).
+ast_Expr_Variable (phc_Expr_id{300}, phc_Variable_id{20}).

+ast_Method_invocation (phc_Method_invocation_id{10}, phc_METHOD_NAME_id{11}, [phc_Actual_parameter_id{12}]).

+ast_Assignment (phc_Assignment_id{7}, phc_Variable_id{10}, phc_Expr_id{400}).
+ast_Expr_Method_invocation (phc_Expr_id{400}, phc_Method_invocation_id{10}).

+ast_Eval_expr (phc_Eval_expr_id{6}, phc_Expr_id{500}), 
+ast_Expr_Assignment (phc_Expr_id{500}, phc_Assignment_id{7}).

+ast_PHP_script (phc_PHP_script_id{0}, [phc_Statement_id{600}, phc_Statement_id{601}]),
+ast_Statement_Eval_expr (phc_Statement_id{600}, phc_Eval_expr_id{1}),
+ast_Statement_Eval_expr (phc_Statement_id{601}, phc_Eval_expr_id{6}).

?- ast_Eval_expr(Y, X).
