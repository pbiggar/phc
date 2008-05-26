import "src/generated/MIR.clp".
using dotty.

analyze session_name("mir").

session cfg (METHOD:string).

% To build the CFG, we go through 3 phases. First, we create the linked list
% of nodes, using program points. Secondly, we do a top-down pass through
% this list, leaving the gotos and the branches in the CFG, but adding edges
% to their targets and then following the targets. It is important to stop
% processing if a node is already in the CFG (which may or may not happen
% with back edges). We then have a CFG with basic blocks and edges, but the
% BBs contain gotos and labels, which we dont want. So, phase 3, we go
% through removing them, leaving potentially empty BBs behind. We then merge
% any BBs that need it. This may still leave empty BBs, which is fine.
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
predicate loc (P:pp).
predicate pp_edge (P0:pp, P1:pp).
predicate build_pps (P:pp, STMTS:list[t_Statement], METHOD:t_Method).

% Annotate a script with program points
method (ID, _, yes{STMTs}),
	A = p_entry{ID},
	+loc(A),							% entry point
	+build_pps (A, STMTs, ID).		% connect to statements

% Handle a list of statements - base case
build_pps (PREV, [], METHOD), +loc(p_exit{METHOD}), +pp_edge (PREV, p_exit{METHOD}).

% Handle a list of statements - Recursive case
build_pps (PREV, [H|STMTs], METHOD),
	P = p_s{H},
	+loc(P), +pp_edge (PREV, P),
	+build_pps (P, STMTs, METHOD).

% Build a .dot file to view the PPs
dotty_graph (Name, true, dotgraph{Nodes, Edges}, [], [], []) :-
	Name = "PPs",
	\/(loc (P), N = dg_node{P,[]}):list_all(N, Nodes),
	\/(pp_edge (EN1, EN2), E = dg_edge{EN1,EN2, []}):list_all(E, Edges).



% Phase 2: Build the CFG
type cfg_node ::=
	nentry{t_Method}				% function entry
|	nexit{t_Method}				% function exit
|	n_block{t_Statement}			% basic block (BBs only have 1 statement in them)
|	n_branch{t_VARIABLE_NAME}	% branch (branches on the condition in t_VARIABLE_NAME)
|	n_empty{t_Statement}			% branch target, generally
.

predicate cfg_edge (N0:cfg_node, N1:cfg_node).

% Add a CFG edge between FROM and a cfg_node created from TO (which is in the
% pp_graph).
predicate dfs (FROM:cfg_node, TO:pp).

% Start at the top
pp_edge (p_entry{METHOD}, P), +dfs (nentry{METHOD}, P).

% End condition
dfs (N, p_exit{METHOD}), +cfg_edge (N, nexit{METHOD}).

% Normal statement - add edge and recurse
dfs (N, p_s{S}), 
	S \= statement_Branch{_}, S \= statement_Goto{_},
	(
		S = statement_Label{_}, N1 = n_empty{S}
	; 
		S \= statement_Label{_}, N1 = n_block{S}
	),
	+cfg_edge (N, N1),
	% recurse
		pp_edge (p_s{S}, P1), % get next pp
		+dfs (N1, P1).

% find the PP for a LABEL_NAME
predicate label_name_loc (in LABEL_NAME:string, out PP:pp).

label_name_loc (NAME_VAL, PP) :-
	lABEL_NAME (NAME_ID, NAME_VAL),
	label (LABEL_ID, NAME_ID),
	loc (LOC), LOC = p_s{statement_Label{LABEL_ID}},
	PP = LOC.


% Branch
dfs (N, p_s{S}),
	S = statement_Branch{B},
	branch (B, VAR, TRUE_LABEL, FALSE_LABEL),
	N1 = n_branch {VAR},
	+cfg_edge (N, N1),
	% find targets and recurse
		% find the names of the labels for the branch targets
			lABEL_NAME (TRUE_LABEL, TRUE_LABEL_NAME), 
			lABEL_NAME (FALSE_LABEL, FALSE_LABEL_NAME), 
		% find their PPs
			label_name_loc (TRUE_LABEL_NAME, TRUE_PP),
			label_name_loc (FALSE_LABEL_NAME, FALSE_PP),
		% recurse
			+dfs (N1, TRUE_PP),
			+dfs (N1, FALSE_PP).

% Goto
dfs (N, p_s{S}),
	S = statement_Goto{G},
	goto (G, LABEL),
	N1 = n_block {S},
	+cfg_edge (N, N1),
	% find target and recurse
		% find the names of the labels for the branch targets
			lABEL_NAME (LABEL, LABEL_NAME), 
			label_name_loc (LABEL_NAME, PP),
			+dfs (N1, PP).

% Build a .dot file to view the CFG
dotty_graph (Name, true, dotgraph{[], Edges}, [], [], []) :-
	Name = "CFG",
	\/(cfg_edge (EN1, EN2), E = dg_edge{EN1,EN2, []}):list_all(E, Edges).

% Save the CFGs.
predicate save_cfg (METHOD_NAME:string, N:cfg_node).

cfg_edge (nentry{METHOD}, N),
	% get the name
		method (METHOD, SIG, _), 
		signature (SIG, _, _, NAME_ID, _),
		mETHOD_NAME (NAME_ID, NAME),
	% add it to a session
	+cfg(NAME)->cfg_edge (nentry{METHOD}, N), +save_cfg (NAME, N).

save_cfg (METHOD, N), cfg_edge (N, N1),
	+cfg(METHOD)->cfg_edge (N, N1), +save_cfg (METHOD, N1).
