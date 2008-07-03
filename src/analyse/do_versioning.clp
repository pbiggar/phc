% Handle versioning. We can't iterate within Calypso, so if there are any
% dead CFG nodes, we write a new version of the CFG to the DB. It picks up
% the results, and automatically runs optimizations on it. If there is
% nothing marked dead, we turn it into an mir(), which is unparsed into XML
% later (see linearize_cfg.clp).

% Replacing an edge with its new counterpart. get_*_replacement handles cases
% where the BB is dead or not.
reiterate (),
	cfg_edge (BB1, BB2),
	cfg (METHOD, VERSION),
	NEW_BB1 = get_first_replacement (BB1),
	NEW_BB2 = get_last_replacement (BB2),
	+cfg (METHOD, VERSION+1)->cfg_edge (NEW_BB1, NEW_BB2).

predicate get_first_replacement (in IN:t_cfg_node, out OUT:t_cfg_node) succeeds [once].
predicate get_last_replacement (in IN:t_cfg_node, out OUT:t_cfg_node) succeeds [once].
get_first_replacement (BB, BB) :- ~replace_bb (BB, _).
get_first_replacement (BB, H) :- replace_bb (BB, [H|_]).
get_last_replacement (BB, BB) :- ~replace_bb (BB, _).
get_last_replacement (BB, H) :- replace_bb (BB, LIST), [H|_] = list_reverse (LIST).

% If there is more than one node, add it
replace_bb (_, LIST), int_gt (list_length (LIST), 2),
	+add_bbs (LIST).

predicate add_bbs (BBS:list[t_cfg_node]).
add_bbs ([H1,H2|T]),
	cfg (METHOD, VERSION),
	+cfg (METHOD, VERSION+1)->cfg_edge (H1, H2),
	+add_bbs ([H2|T]).

predicate add_list_of_bbs (LIST:list[t_cfg_node]).
% Single element lists means we've done it

add_list_of_bbs ([H1,H2|T]),
	cfg (METHOD, VERSION),
	+cfg (METHOD, VERSION+1)->cfg_edge (H1, H2),
	+add_list_of_bbs ([H2|T]). % recurse


replace_bb (_, _), +reiterate ().
remove_bb (BB), BB = nblock{S},
	+replace_bb (BB, [nempty{S}]).

% Only allow removing blocks
remove_bb (BB), BB \= nblock{_}, +error_in (BB, "Can only handle nblocks").

