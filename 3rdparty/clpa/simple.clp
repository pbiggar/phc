import "../../src/generated/HIR.clp".

% TODO by declaring the types, we get strong typing
session phc_body (FUNCTION:string).

analyze session_name("phc_body").

?- phc_assignment (A, false, C).
?- phc_php_script (STATEMENTS).
