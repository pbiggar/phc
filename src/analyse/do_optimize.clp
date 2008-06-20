import "optimize.clp".
import "dce.clp".

analyze session_name("cfg").


% Turn the CFG back into mir().

% So we have a CFG for a method, so we need to reconstruct the method
cfg_node (nentry{METHOD}),
	METHOD = method{ID, SIGNATURE, _},
	METHOD_NAME = get_method_name (METHOD),
	build_statement_list (nentry{METHOD}, STATEMENT_LIST),
	NEW_METHOD = method{ID, SIGNATURE, yes{STATEMENT_LIST}},
	+optimized()->method_out (METHOD_NAME, NEW_METHOD).

predicate build_statement_list (in BB:t_cfg_node, out STATEMENTS:list[t_Statement]).

build_statement_list (nentry{METHOD}, STATEMENTS) :- 
	cfg_edge (nentry{METHOD}, E), build_statement_list (E, STATEMENTS).


build_statement_list (nblock{S}, OUT_LIST) :-
	cfg_edge (nblock{S}, E), build_statement_list (E, IN_LIST),
	list_append ([S], IN_LIST, OUT_LIST).


build_statement_list (nexit{_}, []) :- .
