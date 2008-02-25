type php_variable = string.
type php_expr = string.
type php_assigment ::= php_assignment {php_variable, bool, php_expr}.

session phc_body (FUNCTION:string).


	

predicate phc_assignment (ID:STRING, V:php_variable, IS_REF:bool, EXPR:php_expr).

analyze session_name("phc_body").

?- phc_assignment (ID, A, false, C).
