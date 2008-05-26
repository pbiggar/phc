% Types not supplied by Saturn
type null.
type id = int.

% Encode attributes
type t_Attr ::=
		attr_str{string}
	|	attr_int{int}
	|	attr_bool{bool}
	|	attr_unavailable.

predicate attr(ID:id, NAME:string, VAL:t_Attr).


% The filename from the file currently being analysed.
predicate filename (FILENAME:string).
