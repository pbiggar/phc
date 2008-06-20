% Types not supplied by Saturn
type null.
type id = int.

% Forward declarations
type t_Node.
type t_PHP_script.

% Encode attributes
type t_Attr ::=
		attr_str{string}
	|	attr_int{int}
	|	attr_bool{bool}
	|	attr_unavailable.

predicate attr(ID:t_Node, NAME:string, VAL:t_Attr).
predicate source_rep (ID:t_Node, SOURCE:string).

% Generic type
type t_any ::= any{X}.

% Generics
type t_generic ::= gnode{t_Node, TYPE:string, ARGS:list[t_generic]}	
					  | gmarker{NAME:string, bool}
					  | glist{TYPE:string, list[t_generic]}
					  | gmaybe{TYPE:string, maybe[t_generic]}
					  | gstring{string}
					  | gint{int}
					  | gfloat{float}
					  | gbool{bool}
					  | gnull{null}
					  .

% Generic 
predicate to_node (in ANY: t_any, out NODE: t_Node) succeeds [once].
predicate to_generic (in NODE:t_Node, out GENERIC:t_generic) succeeds [once].
predicate list_to_generic_list (in TYPE:string, in IDS:list[A], out GENERICS:t_generic) succeeds [once].

list_to_generic_list (TYPE, [], glist{TYPE, []}) :- .
list_to_generic_list (TYPE, [H|T], glist{TYPE, GEN_LIST}) :- 
	list_to_generic_list (TYPE, T, GEN_T),
	to_node (any{H}, N),
	to_generic (N, GEN_H),
	GEN_T = glist{_, TAIL}, % unwrap, and rewrap in header
	list_append ([GEN_H], TAIL, GEN_LIST).



predicate program (PHP_script:t_PHP_script).
