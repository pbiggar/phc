import "src/generated/MIR.clp".
using dotty.

analyze session_name("mir").


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
  | p_entry						% entry point of function/script
  | p_exit						% exit point of function/script
  . 

% The first step is to add program points. Each point is a statement, but
% this joins them to make it easier to associate each one with the next one
% in the list (for labels and gotos/branches)
predicate loc (P:pp).
predicate pp_edge (P0:pp, P1:pp).
predicate build_pps (P:pp, STMTS:list[t_Statement]).

% Annotate a script with program points
pHP_script (_, STMTs),
	A = p_entry,
	+loc(A),							% entry point
	+build_pps (A, STMTs).		% connect to statements

% Handle a list of statements - base case
build_pps (PREV, []), +loc(p_exit), +pp_edge (PREV, p_exit).

% Handle a list of statements - Recursive case
build_pps (PREV, [H|STMTs]),
	P = p_s{H},
	+loc(P), +pp_edge (PREV, P),
	+build_pps (P, STMTs).

% Build a .dot file to view the PPs
dotty_graph (Name, true, dotgraph{Nodes, Edges}, [], [], []) :-
	Name = "PPs",
	\/(loc (P), N = dg_node{P,[]}):list_all(N, Nodes),
	\/(pp_edge (EN1, EN2), E = dg_edge{EN1,EN2, []}):list_all(E, Edges).



% Phase 2: Build the CFG
type cfg_node ::=
	nentry					% function entry
|	nexit						% function exit
|	n_block{t_Statement}	% basic block (BBs only have 1 statement in them)
|	n_branch{t_VARIABLE_NAME}	% branch (branches on the condition in t_VARIABLE_NAME)
|	n_label{t_Label}		% branch target
.

predicate cfg_edge (N0:cfg_node, N1:cfg_node).

% Add a CFG edge between FROM and a cfg_node created from TO (which is in the
% pp_graph).
predicate dfs (FROM:cfg_node, TO:pp).

% Start at the top
pp_edge (p_entry, P), +dfs (nentry, P).

% End condition
dfs (N, p_exit), +cfg_edge (N, nexit).

% Normal statement - add edge and recurse
dfs (N, p_s{S}), 
	S \= statement_Branch{_}, S \= statement_Goto{_},
	N1 = n_block{S},
	+cfg_edge (N, N1),
	% recurse
		pp_edge (p_s{S}, P1), % get next pp
		+dfs (N1, P1).

% Branch
dfs (N, p_s{S}),
	S = statement_Branch{B},
	branch (B, VAR, IFT_ID, IFF_ID),
	N1 = n_branch {VAR},
	+cfg_edge (N, N1),
	% find targets and recurse
		% find the names of the labels for the branch targets
			lABEL_NAME (IFT_ID, IFT_NAME), 
			lABEL_NAME (IFF_ID, IFF_NAME),
		% find the pp for the TRUE target
			label (L_IFTRUE, L_IFT_ID), lABEL_NAME (L_IFT_ID, IFT_NAME),
			loc (LOC_TRUE), LOC_TRUE = p_s{statement_Label{L_IFTRUE}},
			+dfs (N1, LOC_TRUE),
		% and the FALSE target
			label (L_IFFALSE, L_IFF_ID), lABEL_NAME (L_IFF_ID, IFF_NAME),
			loc (LOC_FALSE), LOC_FALSE = p_s{statement_Label{L_IFFALSE}},
			+dfs (N1, LOC_FALSE).

% Goto
dfs (N, p_s{S}),
	S = statement_Goto{G},
	goto (G, LABEL_ID),
	N1 = n_block {S},
	+cfg_edge (N, N1),
	% find targets and recurse
		% find the names of the labels for the branch targets
			lABEL_NAME (LABEL_ID, LABEL_NAME), 
		% find the pp for the TRUE target
			label (FOUND_LABEL, FOUND_NAME_ID), lABEL_NAME (FOUND_NAME_ID, LABEL_NAME),
			loc (LOC), LOC = p_s{statement_Label{FOUND_LABEL}},
			+dfs (N1, LOC).


% Build a .dot file to view the CFG
dotty_graph (Name, true, dotgraph{[], Edges}, [], [], []) :-
	Name = "CFG",
	\/(cfg_edge (EN1, EN2), E = dg_edge{EN1,EN2, []}):list_all(E, Edges).



%?- dfs (P, N).
?- cfg_edge (P0, P1).
