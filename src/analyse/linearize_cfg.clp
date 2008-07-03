% Turn the CFG back into mir().


% So we have a CFG for a method, so we need to reconstruct the method
~reiterate (),
	cfg_node (ENTRY),
	ENTRY = nentry{METHOD},
	METHOD = method{ID, SIGNATURE, _},
	METHOD_NAME = get_method_name (METHOD),

	% Get all the basic blocks and merge them
	+order_nodes ([], [], [ENTRY]), % kick off ordering
	ordered_statements (STATEMENTS),

	CLEAN_STATEMENTS = clean_up_labels (clean_up_gotos (STATEMENTS)),

	% Add it to the optimized DB
	NEW_METHOD = method{ID, SIGNATURE, yes{CLEAN_STATEMENTS}},
	+optimized()->method_out (METHOD_NAME, NEW_METHOD).




% Starting at the first CFG node, find the next nodes, checking if they are in
% the current list. If not, add them (and their associated statements), and
% continue through the list. When there are no more items in the list, finish.
predicate order_nodes (PREV:list[t_cfg_node], STATEMENTS:list[t_Statement], NEXT:list[t_cfg_node]).

% When finished, this holds the completed list.
predicate ordered_statements (STATEMENTS:list[t_Statement]).


% No more statements to analyse
order_nodes (_, STATEMENTS, []),
	% Add the final label for the exit node
	cfg_node (BB), BB = nexit{_},
	list_append (STATEMENTS, [bb_label(BB)], ALL_STATEMENTS),
	+ordered_statements (ALL_STATEMENTS).

% Seen this statement before
order_nodes (PREV, STATEMENTS, [BB|TAIL]),
	list_mem (PREV, BB), 
	+order_nodes (PREV, STATEMENTS, TAIL).

% Havent seen this before
order_nodes (PREV, STATEMENTS, [BB|TAIL]),
	~list_mem (PREV, BB), 
    NPREV = list_append (PREV, [BB]),
	 linear_statements (BB, BB_STATEMENTS),
    NSTATEMENTS = list_append (STATEMENTS, BB_STATEMENTS),
    \/cfg_edge (BB, NEXT):list_all (NEXT, NEXTS), % A bit arbitrary. We could choose directions with a branch.
    NSUCCS = list_append(NEXTS, TAIL),  % order here determines DFS vs BFS
    +order_nodes (NPREV, NSTATEMENTS, NSUCCS).


% Build a list of statement for a BB
predicate linear_statements (BB:t_cfg_node, out STATEMENTS:list[t_Statement]).

cfg_node (BB),
	BB = nbranch{VAR, TRUE, FALSE},
	BRANCH = branch{-1, VAR, bb_label_name (TRUE), bb_label_name (FALSE)},
	STATEMENTS = [bb_label (BB), statement_Branch{BRANCH}],
	+linear_statements (BB, STATEMENTS).

cfg_node (BB),
	BB = nblock{S}, cfg_edge (BB, NEXT),
	+linear_statements (BB, [bb_label (BB), S, bb_goto (NEXT)]).

cfg_node (BB),
	BB = nentry{_}, cfg_edge (BB, NEXT),
	+linear_statements (BB, [bb_goto (NEXT)]).

% This must be the last statement, but with DFS, it might not be. Add it later.
cfg_node (BB),
	BB = nexit{_},
	+linear_statements (BB, []).

cfg_node (BB),
	BB = nempty{_}, cfg_edge (BB, NEXT),
	+linear_statements (BB, [bb_label (BB), bb_goto (NEXT)]).




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

% Remove gotos for straight-line code
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


% Remove unused labels
predicate clean_up_labels (in IN:list[t_Statement], out OUT:list[t_Statement]) succeeds [once].

% Not a label
clean_up_labels (IN, OUT) :-
	USED_LABELS = get_used_labels (IN),
	OUT = remove_unused_labels (IN, USED_LABELS).

using set.

predicate remove_unused_labels (in IN:list[t_Statement], in USED_LABELS:set[string], out OUT:list[t_Statement]) succeeds [once].

remove_unused_labels ([], _, []) :- .
remove_unused_labels ([H|T], USED_LABELS, OUT) :-
	H \= statement_Label{_},
	OUT = [H| remove_unused_labels (T, USED_LABELS)].

remove_unused_labels ([H|T], USED_LABELS, OUT) :- 
	H = statement_Label{label{_, lABEL_NAME{_, NAME}}},
	(
		(~set_member (USED_LABELS, NAME), OUT = remove_unused_labels (T, USED_LABELS))
		;
		(set_member (USED_LABELS, NAME), OUT = [H|remove_unused_labels (T, USED_LABELS)])
	).


predicate get_used_labels (in STATEMENTS:list[t_Statement], out USED_LABELS:set[string]) succeeds [once].

get_used_labels ([], set_empty()) :- .
get_used_labels ([H|T], OUT) :-
	SET = get_used_labels (T),
	(
		(H = statement_Branch {branch {_, _, lABEL_NAME{_, TRUE}, lABEL_NAME{_, FALSE}}},
		OUT1 = set_insert (TRUE, SET),
		OUT = set_insert (FALSE, OUT1)
		);
		(H = statement_Goto {goto {_, lABEL_NAME{_, NAME}}},
		OUT = set_insert (NAME, SET)
		);
		(H \= statement_Branch{_}, H \= statement_Goto{_}, OUT = SET)
	).
