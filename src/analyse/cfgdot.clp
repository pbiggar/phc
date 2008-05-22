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
	Name = "Test",
	\/(loc (P), N = dg_node{P,[]}):list_all(N, Nodes),
	\/(pp_edge (EN1, EN2), E = dg_edge{EN1,EN2, []}):list_all(E, Edges).



% Phase 2: Build the CFG
type cfg_node ::=
	nentry					% function entry
|	nexit						% function exit
|	n_block{t_Statement}	% basic block (BBs only have 1 statement in them)
|	n_branch{t_VARIABLE_NAME}	% branch (branches on the condition in t_VARIABLE_NAME)
.

predicate cfg_edge (N0:cfg_node, N1:cfg_node).

% Do a depth-first search of the pp graph, starting at P, returning N for the
% node repesenting P, and adding edges as you go.
predicate dfs (P:pp, N:cfg_node).

% Start at the top
pp_edge (p_entry, P), dfs (P, N), +cfg_edge (nentry, N).

% Normal statement - add edge and recurse
dfs (p_s{S}, N), S \= statement_Branch{_}, S = statement_Goto{_},
	N = n_block{S}, % bind N for returning the node
	% recurse
	pp_edge (p_s{S}, P1), dfs (P1, N1),
	+cfg_edge (N, N1).

dfs (p_exit, N), N = nexit, +cfg_edge (N, N).





% Create CFG edges the a branch
%loc(p_s{statement_Branch{B}}),
%	 % find the labels for the branch
%	branch (B, VAR, lABEL_NAME_ID{IFT}, lABEL_NAME_ID{IFF}),
%	% the target of the label will have the same VALUE, not the same ID
%	label (IFT, LABEL_VALUE_TRUE),
%	label (IFF, LABEL_VALUE_FALSE),
%	% TODO we have to extract the value from a LABEL_NAME token here, do it in
%	% a minute. I need to change this structure, it blows.
%	% Find the program points for these labels
%	
%	
%	+cfg_edge (NB, NT), +cfg_edge (NB, NF),
%
%
%cfg_edge (N0, N1) :- pp_edge (P0, P1), 
%	node_for_pp (N0, P0),
%	node_for_pp (N1, P1).
%
%% Get a node to represent the program point
%predicate node_for_pp (P:pp, n:cfg_node).
%
%node_for_pp (p_exit, n_exit).
%node_for_pp (p_s{statement_Branch{B}, n_branch{B}).
%
%% now turn into CFG
%%predicate ebranch (P:pp, COND:t_VARIABLE_NAME, P0:pp, P1:pp).

% Branches and gotos
%build_cfg (PREV, [statement_Goto{GOTO}|STMTs]),
%	goto (GOTO, L1, L2),
	% we need the statement after a label_name, but that isnt avaialbe.
	% Construct program_points first
%	la
%	+edge (PREV, TARGET)
	

%build_cfg (PREV, [statement_Branch{_}|_]),


%?- loc (P).
?- cfg_edge (P0, P1).

