% cfg.clp defines the predicates for the CFG. This actually creates the CFG sessions from the MIR. It is intended that do_cft.clp is run, which will create the cfg databases, but cfg.clp will need to be imported by client analyses.

import "src/generated/MIR.clp".
import "src/analyse/cfg.clp".
import "3rdparty/clpa/analysis/base/utility.clp".
import "util.clp".
using dotty.

analyze session_name("mir").

% To build the CFG, we go through 3 phases. First, we create the linked list
% of nodes, using program points. Secondly, we do a top-down pass through
% this list, adding CFG edges between statements. Branches add two edges, one
% to each target. Gotos and labels are passed through, adding edges between
% their predecessors and their successors.  It is important to stop processing
% if a node is already in the CFG (which may or may not happen with back
% edges). After the edges and nodes are added to the current session, we add
% them to the cfg() DB. We do this in two passes so that we can fix the branch
% statements.
%
% Note that the second phase removes any unreachable code.



% Phase 1 - annotate the program with program points.
%
% Its a little tricky to create the CFG from lists of statements, since when
% we find a label, we dont have a way of getting the next item in the list.
% We create a straight linked list of program points for this purpose.

% Program point in a function
type pp ::=
    p_s{t_Statement}			% point of the of statement
  | p_entry{t_Method}		% entry point of function/script
  | p_exit{t_Method}			% exit point of function/script
  . 

% The first step is to add program points. Each point is a statement, but
% this joins them to make it easier to associate each one with the next one
% in the list (for labels and gotos/branches)
predicate pp_node (P:pp).
predicate pp_edge (P0:pp, P1:pp).
predicate build_pps (P:pp, STMTS:list[t_Statement], METHOD:t_Method).
predicate build_pps_from_method_list (STMTS:list[t_Statement]).

% Annotate a script with program points
program (pHP_script{_, METHOD_LIST}),
	+build_pps_from_method_list (METHOD_LIST).

build_pps_from_method_list ([]) :- .
build_pps_from_method_list ([statement_Method{METHOD}|T]),
	+build_pps_from_method_list (T), % recurse
	METHOD = method{_, _, yes{STATEMENTS}},
	PP = p_entry{METHOD},
	+pp_node(PP),							% entry point
	+build_pps (PP, STATEMENTS, METHOD).		% connect to statements

% Handle a list of statements - base case
build_pps (PREV, [], METHOD),
	+pp_node (p_exit{METHOD}),
	+pp_edge (PREV, p_exit{METHOD}).

% Handle a list of statements - Recursive case
build_pps (PREV, [H|STMTs], METHOD),
	P = p_s{H},
	+pp_node(P), +pp_edge (PREV, P),
	+build_pps (P, STMTs, METHOD).

% Build a .dot file to view the PPs
dotty_graph (Name, true, dotgraph{Nodes, Edges}, [], [], []) :-
	create_dot_graphs (),
	Name = "PPs",
	\/(pp_node (P), N = dg_node{P,[]}):list_all(N, Nodes),
	\/(pp_edge (EN1, EN2), E = dg_edge{EN1,EN2, []}):list_all(E, Edges).



% Phase 2: Build the CFG

% Add a CFG edge between FROM and a cfg_node created from TO (which is in the
% pp_graph).
predicate dfs (FROM:t_cfg_node, TO:pp, IS_TARGET:maybe[bool], METHOD:string).

% like cfg_edge, but also encodes the method_name.
predicate method_edge (N1:t_cfg_node, N2:t_cfg_node, IS_TARGET:maybe[bool], METHOD_NAME:string).

% Start at the top
dfs (nentry{METHOD}, P, no, METHOD_NAME) :-
	pp_edge (p_entry{METHOD}, P), 
	% get the name
	METHOD_NAME = get_method_name (METHOD).

% End condition
dfs (N, p_exit{METHOD}, IS_TARGET, METHOD_NAME),
	+method_edge (N, nexit{METHOD}, IS_TARGET, METHOD_NAME),
	+fix_up_branch(METHOD_NAME).

% Normal statement - add edge and recurse
dfs (N, p_s{S}, IS_TARGET, METHOD_NAME), 
	S \= statement_Branch{_}, S \= statement_Goto{_}, S \= statement_Label{_},
	N1 = nblock{S},
	+method_edge (N, N1, IS_TARGET, METHOD_NAME),
	% recurse
		pp_edge (p_s{S}, P1), % get next pp
		+dfs (N1, P1, no, METHOD_NAME).

% Label - create an empty statement and follow the path
dfs (N, p_s{S}, IS_TARGET, METHOD_NAME), 
	S = statement_Label{_},
	N1 = nempty{S},
	+method_edge (N, N1, IS_TARGET, METHOD_NAME),
	% recurse
		pp_edge (p_s{S}, P1), % get next pp
		+dfs (N1, P1, IS_TARGET, METHOD_NAME).

% Goto - create and empty statement and follow the path
dfs (N, p_s{S}, IS_TARGET, METHOD_NAME),
	S = statement_Goto {goto {_, lABEL_NAME{_, LABEL_NAME}}},
	N1 = nempty{S},
	+method_edge (N, N1, IS_TARGET, METHOD_NAME),
	% find target and recurse
		% find the names of the labels for the branch targets
			find_target (LABEL_NAME, PP),
			+dfs (N1, PP, IS_TARGET, METHOD_NAME).


% Branch - create a fake node, which will be fixed up later, and follow both
% paths
dfs (N, p_s{S}, IS_TARGET, METHOD_NAME),
	S = statement_Branch{branch{_, VAR, TRUE_LABEL, FALSE_LABEL}},
	N1 = nbranch {VAR, N, N},
	+method_edge (N, N1, IS_TARGET, METHOD_NAME),
	% find targets and recurse
		% find the names of the labels for the branch targets
			TRUE_LABEL = lABEL_NAME {_, TRUE_LABEL_NAME},
			FALSE_LABEL = lABEL_NAME {_, FALSE_LABEL_NAME},
		% find their PPs
			find_target (TRUE_LABEL_NAME, TRUE_PP),
			find_target (FALSE_LABEL_NAME, FALSE_PP),
		% recurse
			+dfs (N1, TRUE_PP, yes{true}, METHOD_NAME),
			+dfs (N1, FALSE_PP, yes{false}, METHOD_NAME).

% find the PP for a LABEL_NAME.
predicate find_target (in LABEL_NAME:string, out PP:pp).
find_target (LABEL_NAME, PP) :-
	pp_node (LOC), 
	LOC = p_s{statement_Label{label{_, lABEL_NAME{_, LABEL_NAME}}}},
	PP = LOC.




% Phase 3: Fix up and add to the cfg() session.


% After all edges are added, store them in the DB, fixing up the branches as
% we go.
predicate fix_up_branch(METHOD_NAME:string).

% No branches - just add it
fix_up_branch (METHOD_NAME),
	method_edge (N1, N2, _, METHOD_NAME), N1 \= nbranch{_, _, _}, N2 \= nbranch{_, _, _},
	+cfg(METHOD_NAME, 0)->cfg_edge (N1, N2).

% Source is a branch
fix_up_branch (METHOD_NAME),
	method_edge (N1, N2, _, METHOD_NAME), N1 = nbranch{_, _, _}, N2 \= nbranch{_, _, _},
	+cfg(METHOD_NAME, 0)->cfg_edge (get_new_branch (METHOD_NAME, N1), N2).

% Target is a branch
fix_up_branch (METHOD_NAME),
	method_edge (N1, N2, _, METHOD_NAME), N1 \= nbranch{_, _, _}, N2 = nbranch{_, _, _},
	+cfg(METHOD_NAME, 0)->cfg_edge (N1, get_new_branch (METHOD_NAME, N2)).

% Cant have two branches
assert ~(method_edge(nbranch{_, _, _}, nbranch{_, _, _}, _, _)).

predicate get_new_branch (in METHOD_NAME:string, in IN:t_cfg_node, out OUT:t_cfg_node) succeeds [once].
get_new_branch (METHOD_NAME, IN, nbranch{VAR, NT, NF}) :-
	method_edge (IN, NT, yes{true}, METHOD_NAME),
	method_edge (IN, NF, yes{false}, METHOD_NAME),
	IN = nbranch{VAR, _, _}.
