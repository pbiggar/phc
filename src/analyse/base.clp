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

predicate attr(ID:t_any, NAME:string, VAL:t_Attr).
predicate source_rep (ID:t_any, SOURCE:string).


% The filename from the file currently being analysed.
predicate filename (FILENAME:string).
