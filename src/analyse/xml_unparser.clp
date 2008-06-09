import "cfgdot.clp".


% Initially, just dump the CFG in any order. After that, we can work on
% putting the CFG back into a list of statements with labels and gotos. Then,
% we merge all functions, and re-read it with --read-xml=clar.


analyze session_name ("cfg").

% Generics needed for this (to later be added straight from the IR with maketea).
predicate get_type (in NODE:t_any, out TYPE:string).
predicate unwrap (in WRAPPED:t_any, out UNWRAPPED:t_any).
predicate sub_nodes (in NODE:t_any, out SUB_NODES:list[t_any]).

% Generics for unwrap
unwrap (any{statement_Global{N}}, any{N}) :- N = global_id{_}.
unwrap (any{statement_Eval_expr{N}}, any{N}) :- N = eval_expr_id {_}.
unwrap (any{statement_Assign_var{N}}, any{N}) :- N = assign_var_id {_}.
unwrap (any{variable_name_VARIABLE_NAME{N}}, any{N}) :- N = vARIABLE_NAME_id{_}.
unwrap (any{expr_Method_invocation{N}}, any{N}) :- N = method_invocation_id{_}.
unwrap (any{expr_INT{N}}, any{N}) :- N = iNT_id {_}.
unwrap (any{method_name_METHOD_NAME{N}}, any{N}) :- N = mETHOD_NAME_id{_}.

% Generics for get_type
mir()->global (ID, _), +get_type (any{ID}, "Global").
mir()->eval_expr (ID, _), +get_type (any{ID}, "Eval_expr").
mir()->assign_var(ID, _, _, _, _), +get_type (any{ID}, "Assign_var").
mir()->vARIABLE_NAME(ID, _), +get_type (any{ID}, "VARIABLE_NAME").
mir()->method_invocation (ID, _, _, _), +get_type (any{ID}, "Method_invocation").
mir()->iNT (ID, _), +get_type (any{ID}, "INT").
mir()->mETHOD_NAME (ID, _), +get_type (any{ID}, "METHOD_NAME").
mir()->actual_parameter (ID, _, _, _, _), +get_type (any{ID}, "actual_parameter").

% Generics for sub_nodes
mir()->global (ID, VARIABLE_NAME),
	+sub_nodes (any{ID}, [any{VARIABLE_NAME}]).

mir()->eval_expr (ID, EXPR),
	+sub_nodes (any{ID}, [any{EXPR}]).

mir()->assign_var (ID, _, VARIABLE_NAME, false, EXPR), 
	+sub_nodes (any{ID}, [any{VARIABLE_NAME}, any{EXPR}]).

mir()->vARIABLE_NAME (ID, _),
	+sub_nodes (any{ID}, []).

mir()->method_invocation (ID, no, METHOD_NAME, [PARAM]),
	+sub_nodes (any{ID}, [any{METHOD_NAME}, any{PARAM}]).

mir()->iNT (ID, _),
	+sub_nodes (any{ID}, []).
	
mir()->mETHOD_NAME (ID, _),
	+sub_nodes (any{ID}, []).

mir()->actual_parameter (ID, _, _, VARIABLE_NAME, []),
	+sub_nodes (any{ID}, [any{VARIABLE_NAME}]).


sub_nodes (WRAPPED, SUB_NODES) :-
	unwrap (WRAPPED, UNWRAPPED),
	sub_nodes (UNWRAPPED, SUB_NODES).



% Convert to XML

% If there is a node any{N}, its XML rep is STR.
predicate unparse (N:t_cfg_node, STR:string).


% Start off by unparsing the parent into a string
cfg_node (N), N = nentry{_}, cfg_edge (N, E2), to_xml_string (any{N}, STR),
	+unparse(E2, STR).

% Take the unparsed predecessor, and concatenate it with this unparsed node
unparse (E1, PRED_STR), cfg_edge (E1, N),
	to_xml_string (any{N}, UNPARSED),
	str_cat_list ([PRED_STR, "\n", UNPARSED], OUT),
	+unparse (N, OUT).

% Finish when we hit the exit block
print (UNPARSED) :- unparse (nexit{_}, UNPARSED).
print (UNPARSED) :- unparse (nblock{_}, UNPARSED).
print (UNPARSED) :- unparse (nentry{_}, UNPARSED).


predicate to_xml_string (in NODE:t_any, out XML:string).
to_xml_string (any{nentry{_}}, "") :- .
to_xml_string (any{nexit{_}}, "") :- .
to_xml_string (any{nblock{X}}, XML) :- to_xml_string (any{X}, XML).
to_xml_string (any{nbranch{_}}, "branch") :- .

predicate to_xml_string_list (in NODE:list[t_any], out XML:string).
to_xml_string_list ([], "") :- .
to_xml_string_list ([H|T], XML) :- 
	to_xml_string (H, STR),
	to_xml_string_list (T, STRS),
	str_cat (STR, STRS, XML).

to_xml_string (any{S}, XML) :- 
	(unwrap (any{S}, any{ID}) ; S = ID),
	get_type (any{ID}, TYPE),
	sub_nodes (any{ID}, LIST),
	to_xml_string_list (LIST, LIST_STR),
	str_cat_list (["<MIR:", TYPE, ">\n", LIST_STR, "\n</MIR:", TYPE, ">"], XML).

% debugging


assert cfg_node (BB), to_xml_string (any{BB}, _).
%?- unwrap (B, C).
%?- get_type (B, C).
%?- unparse (B, C).
%?- to_xml_string (B, C).
%?- to_xml_string_list (B, C).
%?- sub_nodes (B, C).
