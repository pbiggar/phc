% Types not supplied by Saturn
type null.
type id = int.

% Generic type
type t_any ::= any{X}.

% Encode attributes
type t_Attr ::=
		attr_str{string}
	|	attr_int{int}
	|	attr_bool{bool}
	|	attr_unavailable.

% Generics
type t_Node.
type t_generic ::= gnode{t_Node, list[t_generic]}	% a predicate ID, and a list of its arguments
					  | gmarker{bool}							% A Marker
					  | glist{list[t_generic]}				% A list of generics
					  | gmaybe{maybe[t_generic]}			% An optional generic
					  | gstring{string}						% values
					  | gint{int}
					  | gfloat{float}
					  | gbool{bool}
					  | gnull{null}
					  .

% Generic lists
predicate list_to_generic_list (in IDS:list[A], out GENERICS:t_generic).
list_to_generic_list ([], glist{[]}) :- .
list_to_generic_list ([H|T], glist{GEN_LIST}) :- 
	list_to_generic_list (T, GEN_T),
	to_node (any{H}, N),
	to_generic (N, GEN_H),
	GEN_T = glist{TAIL}, % unwrap, and rewrap in header
	list_append ([GEN_H], TAIL, GEN_LIST).



% Generics needed for this (to later be added straight from the IR with maketea).
predicate get_type (in NODE:t_Node, out TYPE:string).

% Generics
predicate to_generic (in NODE:t_Node, out GENERIC:t_generic).

% Strickyl a one way process, for any IR type wrapped in a t_any, find a
% canonical node.
predicate to_node (in ANY: t_any, out NODE: t_Node).

predicate attr(ID:t_any, NAME:string, VAL:t_Attr).
predicate source_rep (ID:t_any, SOURCE:string).

% TODO: Make these demand driven, and make their generation automatic,
% preferably using maketea to create a generic solution to automating this,
% and the same for attrs.
source_rep (any{SUBTYPE}, SOURCE), SUBTYPE = global_id {_}, +mir()->source_rep (any{statement_Global{SUBTYPE}}, SOURCE).
source_rep (any{SUBTYPE}, SOURCE), SUBTYPE = return_id {_}, +mir()->source_rep (any{statement_Return{SUBTYPE}}, SOURCE).
source_rep (any{SUBTYPE}, SOURCE), SUBTYPE = assign_var_id {_}, +mir()->source_rep (any{statement_Assign_var{SUBTYPE}}, SOURCE).
source_rep (any{SUBTYPE}, SOURCE), SUBTYPE = assign_array_id {_}, +mir()->source_rep (any{statement_Assign_array{SUBTYPE}}, SOURCE).
source_rep (any{SUBTYPE}, SOURCE), SUBTYPE = eval_expr_id {_}, +mir()->source_rep (any{statement_Eval_expr{SUBTYPE}}, SOURCE).


%?- source_rep (A, B).

% The filename from the file currently being analysed.
predicate filename (FILENAME:string).
