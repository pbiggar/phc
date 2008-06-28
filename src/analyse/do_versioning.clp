% Handle versioning. We can't iterate within Calypso, so if there are any
% dead CFG nodes, we write a new version of the CFG to the DB. It picks up
% the results, and automatically runs optimizations on it. If there is
% nothing marked dead, we turn it into an mir(), which is unparsed into XML
% later (see linearize_cfg.clp).

% Replacing a single node with multiple nodes
reiterate(),
	cfg_edge (BB1, BB2),
	~is_dead (BB1),

	% get the new target (it may already be dead)
	get_non_dead_target (BB2, TARGET),

	% Create the list of BBs (may be empty),
	((
		replace_bb (BB2, BB_LIST),
		+print (str_cat ("Adding new statements: ", tostring (BB_LIST))))
	; 
	  (~is_dead (BB2), BB_LIST = [])),
	+add_list_of_bbs (flatten ([[BB1], BB_LIST, [TARGET]])).


predicate get_non_dead_target (in BB:t_cfg_node, out TARGET:t_cfg_node) succeeds [many].
get_non_dead_target (BB, TARGET) :-
	(~is_dead (BB), TARGET = BB)
	;
	(	is_dead (BB),
		cfg_edge (BB, NEXT),
		+print (str_cat ("Removing dead statement: ", tostring (BB))),
		get_non_dead_target (NEXT, TARGET)).


predicate add_list_of_bbs (BBS:list[t_cfg_node]).
% Single element lists means we've done it

add_list_of_bbs ([H1,H2|T]),
	cfg (METHOD, VERSION),
	+cfg (METHOD, VERSION+1)->cfg_edge (H1, H2),
	+add_list_of_bbs ([H2|T]). % recurse

