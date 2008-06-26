import "optimize.clp".
import "dce.clp".
import "cfgdot.clp".

analyze session_name("cfg").


% Turn the CFG back into mir().

% So we have a CFG for a method, so we need to reconstruct the method
cfg_node (ENTRY),
	ENTRY = nentry{METHOD},
	METHOD = method{ID, SIGNATURE, _},
	METHOD_NAME = get_method_name (METHOD),

	% Get all the basic blocks and merge them
	\/(linear_statements (_, STATEMENT_LIST)):set_all(STATEMENT_LIST, STATEMENT_LIST_SET),
	set_to_sorted_list (STATEMENT_LIST_SET, STATEMENT_LISTS),
	flatten (STATEMENT_LISTS, STATEMENTS),

	% Add entry goto and exit label seperately, so we can control the ordering.
	cfg_edge (ENTRY, FIRST_TARGET), FIRST_GOTO = bb_goto(FIRST_TARGET),
	LAST_TARGET = bb_label (nexit{METHOD}),
	ALL_STATEMENTS = list_append ([FIRST_GOTO|STATEMENTS], [LAST_TARGET]),
	clean_up_gotos (ALL_STATEMENTS, CLEAN_STATEMENTS),

	% Add it to the optimized DB
	NEW_METHOD = method{ID, SIGNATURE, yes{CLEAN_STATEMENTS}},
	+optimized()->method_out (METHOD_NAME, NEW_METHOD).



% Build a list of statement for a BB
predicate linear_statements (BB:t_cfg_node, out STATEMENTS:list[t_Statement]).

% TODO: When removing statements, dont forget to special-case branches.
cfg_node (BB),
	BB = nbranch{VAR, TRUE, FALSE},
	BRANCH = branch{-1, VAR, bb_label_name (TRUE), bb_label_name (FALSE)},
	STATEMENTS = [bb_label (BB), statement_Branch{BRANCH}],
	+linear_statements (BB, STATEMENTS).

cfg_node (BB),
	BB = nblock{S},
	cfg_edge (BB, E),
	STATEMENTS = [bb_label (BB), S, bb_goto (E)],
	+linear_statements (nblock{S}, STATEMENTS).



% Get labels and gotos for a block
predicate bb_goto (in S:t_cfg_node, out LABEL:t_Statement) succeeds [once].
predicate bb_label (in S:t_cfg_node, out LABEL:t_Statement) succeeds [once].

bb_label (S, statement_Label{label{-1, bb_label_name (S)}}) :- .
bb_goto (S, statement_Goto{goto{-1, bb_label_name (S)}}) :- .

% Get an ID for the label
predicate bb_label_name (in S:t_cfg_node, out LABEL:t_LABEL_NAME) succeeds [once].
bb_label_name (S, lABEL_NAME {-1, LABEL_NAME}) :- counter (LABEL_NUM), LABEL_NAME = to_label_name (LABEL_NUM).

predicate to_label_name (in NUM:int, out NAME:string) succeeds [once].
to_label_name (NUM, NAME) :- % add 6 zeros so they can be sorted numerically
	NUM_STR = tostring (NUM),
	LENGTH = str_len (NUM_STR),
	str_cat_list (["CL", str_times (6 - LENGTH, "0"), NUM_STR], NAME).



% Remove gotos for straight-line code, and remove unused labels
predicate clean_up_gotos (in list[t_Statement], out list[t_Statement]) succeeds [once].
clean_up_gotos ([], []) :- .
clean_up_gotos ([H], [H]) :- .
clean_up_gotos ([H1,H2|T], OUT) :-
	( can_remove_goto (H1, H2), OUT = clean_up_gotos ([H2|T]) )
	;
	( ~can_remove_goto (H1, H2), OUT = [H1|clean_up_gotos ([H2|T])] ).

predicate can_remove_goto (in GOTO:t_Statement, in LABEL:t_Statement).
can_remove_goto (GOTO, LABEL) :-
	GOTO = statement_Goto{goto{-1, LABEL_NAME}},
	LABEL = statement_Label{label{-1, LABEL_NAME}}.
