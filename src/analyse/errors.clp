% Support code for checking our analyses have no errors.

% Error handling

predicate error_in (BB:t_cfg_node, NAME:string).
error_in (BB, NAME) :- 
	cfg_node (BB),
	(
	  ~live_handled (BB), NAME = "LIVE"
	; ~alias_handled (BB), NAME = "ALIAS"
	).

% This is done in separate predicates so that the error will print before the
% assertion executes.
predicate error (BB:t_cfg_node).
error (BB) :- 
	error_in (BB, NAME),
	tostring (BB, BB_STR),
	((BB = nblock {B}, to_node (any{B}, NODE), mir()->source_rep (get_id (NODE), SOURCE))
	;
	(BB \= nblock{_}, SOURCE = "SOURCE NOT AVAILABLE")),
	str_cat_list (["Error, not handled (", NAME, "): ", BB_STR, " - ", SOURCE], ERROR),
	+print (ERROR).

assert ~error (_).
