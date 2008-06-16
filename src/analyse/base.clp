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
type t_generic ::= gnode{t_Node, NAME:string, ARGS:list[t_generic]}	
					  | gmarker{NAME:string, bool}
					  | glist{list[t_generic]}
					  | gmaybe{NAME:string, maybe[t_generic]}
					  | gstring{string}
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


% Generics
predicate to_generic (in NODE:t_Node, out GENERIC:t_generic).

% Strictly a one way process, for any IR type wrapped in a t_any, find a
% canonical node.
predicate to_node (in ANY: t_any, out NODE: t_Node).

predicate attr(ID:t_Node, NAME:string, VAL:t_Attr).
predicate source_rep (ID:t_Node, SOURCE:string).

% The filename from the file currently being analysed.
predicate filename (FILENAME:string).
