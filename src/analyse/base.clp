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

% TODO: Make these demand driven, and make their generation automatic, preferably using maketea to crate a generic solution to automating this, and the same for attrs.
source_rep (any{SUBTYPE}, SOURCE), SUBTYPE = global_id {_}, +mir()->source_rep (any{statement_Global{SUBTYPE}}, SOURCE).
source_rep (any{SUBTYPE}, SOURCE), SUBTYPE = return_id {_}, +mir()->source_rep (any{statement_Return{SUBTYPE}}, SOURCE).
source_rep (any{SUBTYPE}, SOURCE), SUBTYPE = assign_var_id {_}, +mir()->source_rep (any{statement_Assign_var{SUBTYPE}}, SOURCE).


%?- source_rep (A, B).

% The filename from the file currently being analysed.
predicate filename (FILENAME:string).
