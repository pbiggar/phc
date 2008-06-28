% Types not supplied by Saturn
type null.
type id = int.


% t_Node is the generic node type. It is useful separately from any{} and id
% types, since its type can be matched in a subrule, and it carries its data
% with it. Each type X has a converter, node_X, which wraps an X, turning it
% into a t_Node.
type t_Node.


% A PHP_script is the top-level type.
type t_PHP_script.
predicate program (PHP_script:t_PHP_script).


% Encode attributes
type t_Attr ::=
		attr_str{string}
	|	attr_int{int}
	|	attr_bool{bool}
	|	attr_unavailable.

predicate attr(ID:id, NAME:string, VAL:t_Attr).
predicate source_rep (ID:id, SOURCE:string).


using intops.
% Creating new nodes - we need unused IDs.
predicate next_id (out ID:id) succeeds [once].
% HACK HACK HACK HACK HACK TODO XXX
next_id (RESULT) :- counter (X), RESULT = 1000000 + X.



% Generics

% An any{} constructor can wrap any type, allowing us some degree of generics
% in a predicate. However, if there is no predicate matching any{X}, then the
% predicate relying on it will fail silently.
type t_any ::= any{X}.

% Extract the ID from a Node
predicate get_id (in Node:t_Node, out ID:id) succeeds [once].

% Convert a wrapped Node to a t_Node
predicate to_node (in ANY: t_any, out NODE: t_Node) succeeds [once].

% Encode a tree of each type in generics. This allows us to write very
% succinct visitors, such as the XML_unparser.
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

predicate to_generic (in NODE:t_Node, out GENERIC:t_generic) succeeds [once].
predicate list_to_generic_list (in TYPE:string, in IDS:list[A], out GENERICS:t_generic) succeeds [once].

list_to_generic_list (TYPE, [], glist{TYPE, []}) :- .
list_to_generic_list (TYPE, [H|T], glist{TYPE, GEN_LIST}) :- 
	list_to_generic_list (TYPE, T, GEN_T),
	to_node (any{H}, N),
	to_generic (N, GEN_H),
	GEN_T = glist{_, TAIL}, % unwrap, and rewrap in header
	list_append ([GEN_H], TAIL, GEN_LIST).
