type id = int.

% Conjunctive types
type php_Variable	   ::= phc_Variable_id {id}.
type php_Assignment	   ::= phc_Assignment_id {id}.
type php_Eval_expr	   ::= phc_Eval_expr_id {id}.
type php_Actual_parameter  ::= phc_Actual_parameter_id {id}.
type php_Method_invocation ::= phc_Method_invocation_id {id}.
type php_PHP_script	   ::= phc_PHP_script_id {id}.

% Token types
type php_VARIABLE_NAME	::= phc_VARIABLE_NAME_id {id}.
type php_INT		::= phc_INT_id {id}.
type php_METHOD_NAME	::= phc_METHOD_NAME_id {id}.


% Disjunctive types
type php_Literal	::=	phc_Literal_INT_id		{php_INT}.
type php_Expr		::=	phc_Expr_Literal_id		{php_Literal} 
			|	phc_Expr_Variable_id		{php_Variable} 
			|	phc_Expr_Method_invocation_id	{php_Method_invocation} 
			|	phc_Expr_Assignment_id		{php_Assignment}.
type php_Statement	::=	phc_Statement_Eval_expr_id	{php_Eval_expr}.


% Conjunctive Predicates
predicate ast_Variable (ID:php_Variable, VARIABLE_NAME:php_VARIABLE_NAME).
predicate ast_Assignment (ID:php_Assignment, VARIABLE:php_Variable, Expr:php_Expr).
predicate ast_Eval_expr (ID:php_Eval_expr, EXPR:php_Expr).
predicate ast_Actual_parameter (ID:php_Actual_parameter, IS_REF:bool, EXPR:php_Expr).
predicate ast_Method_invocation (ID:php_Method_invocation, METHOD_NAME:php_METHOD_NAME, ACTUAL_PARAMETERS:list[php_Actual_parameter]).
predicate ast_PHP_script (ID:php_PHP_script, STATEMENTS:list[php_Statement]).

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
+ast_Assignment (phc_Assignment_id{2}, phc_Variable_id{3}, phc_Expr_Literal_id{phc_Literal_INT_id{phc_INT_id{102}}}).
+ast_INT (phc_INT_id{102}, 5).
+ast_Eval_expr (phc_Eval_expr_id{1}, phc_Expr_Assignment_id{phc_Assignment_id{9}}).
+ast_Actual_parameter (phc_Actual_parameter_id{12}, false, phc_Expr_Variable_id{phc_Variable_id{20}}).
+ast_Method_invocation (phc_Method_invocation_id{10}, phc_METHOD_NAME_id{11}, [phc_Actual_parameter_id{12}]).
+ast_Assignment (phc_Assignment_id{7}, phc_Variable_id{10}, phc_Expr_Method_invocation_id{phc_Method_invocation_id{10}}).
+ast_Eval_expr (phc_Eval_expr_id{6}, phc_Expr_Assignment_id{phc_Assignment_id{7}}).
+ast_PHP_script (phc_PHP_script_id{0}, [phc_Statement_Eval_expr_id{phc_Eval_expr_id{1}}, phc_Statement_Eval_expr_id{phc_Eval_expr_id{6}}]).

?- ast_Eval_expr(Y, X).
